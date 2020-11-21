#define FoamNamedEnum_EXPORT_DEFINE

#include <sampledTriSurfaceMesh.hxx>

#include <meshSearch.hxx>
#include <treeDataCell.hxx>
#include <treeDataFace.hxx>
#include <meshTools.hxx>
#include <addToRunTimeSelectionTable.hxx>

#include <OFstream.hxx>  // added by amir
#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace sampledSurfaces
	{
		defineTypeNameAndDebug(triSurfaceMesh, 0);
		addToRunTimeSelectionTable(sampledSurface, triSurfaceMesh, word);

		//- Private class for finding nearest
		//  Comprising:
		//  - global index
		//  - sqr(distance)
		typedef Tuple2<scalar, label> nearInfo;

		class nearestEqOp
		{

		public:

			void operator()(nearInfo& x, const nearInfo& y) const
			{
				if (y.first() < x.first())
				{
					x = y;
				}
			}
		};
	}
}

template<>
const char* tnbLib::NamedEnum
<
	tnbLib::sampledSurfaces::triSurfaceMesh::samplingSource,
	3
>::names[] =
{
	"cells",
	"insideCells",
	"boundaryFaces"
};

const tnbLib::NamedEnum
<
	tnbLib::sampledSurfaces::triSurfaceMesh::samplingSource,
	3
> tnbLib::sampledSurfaces::triSurfaceMesh::samplingSourceNames_;


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

const tnbLib::indexedOctree<tnbLib::treeDataFace>&
tnbLib::sampledSurfaces::triSurfaceMesh::nonCoupledboundaryTree() const
{
	// Variant of meshSearch::boundaryTree() that only does non-coupled
	// boundary faces.

	if (!boundaryTreePtr_.valid())
	{
		// all non-coupled boundary faces (not just walls)
		const polyBoundaryMesh& patches = mesh().boundaryMesh();

		labelList bndFaces(mesh().nFaces() - mesh().nInternalFaces());
		label bndI = 0;
		forAll(patches, patchi)
		{
			const polyPatch& pp = patches[patchi];
			if (!pp.coupled())
			{
				forAll(pp, i)
				{
					bndFaces[bndI++] = pp.start() + i;
				}
			}
		}
		bndFaces.setSize(bndI);


		treeBoundBox overallBb(mesh().points());
		overallBb = overallBb.extend(1e-4);

		boundaryTreePtr_.reset
		(
			new indexedOctree<treeDataFace>
			(
				treeDataFace    // all information needed to search faces
				(
					false,                      // do not cache bb
					mesh(),
					bndFaces                    // boundary faces only
				),
				overallBb,                      // overall search domain
				8,                              // maxLevel
				10,                             // leafsize
				3.0                             // duplicity
				)
		);
	}

	return boundaryTreePtr_();
}


bool tnbLib::sampledSurfaces::triSurfaceMesh::update
(
	const meshSearch& meshSearcher
)
{
	// Find the cells the triangles of the surface are in.
	// Does approximation by looking at the face centres only
	const pointField& fc = surface_.faceCentres();

	List<nearInfo> nearest(fc.size());

	// Global numbering for cells/faces - only used to uniquely identify local
	// elements
	globalIndex globalCells
	(
		(sampleSource_ == cells || sampleSource_ == insideCells)
		? mesh().nCells()
		: mesh().nFaces()
	);

	forAll(nearest, i)
	{
		nearest[i].first() = great;
		nearest[i].second() = labelMax;
	}

	if (sampleSource_ == cells)
	{
		// Search for nearest cell

		const indexedOctree<treeDataCell>& cellTree = meshSearcher.cellTree();

		forAll(fc, triI)
		{
			pointIndexHit nearInfo = cellTree.findNearest
			(
				fc[triI],
				sqr(great)
			);
			if (nearInfo.hit())
			{
				nearest[triI].first() = magSqr(nearInfo.hitPoint() - fc[triI]);
				nearest[triI].second() = globalCells.toGlobal(nearInfo.index());
			}
		}
	}
	else if (sampleSource_ == insideCells)
	{
		// Search for cell containing point

		const indexedOctree<treeDataCell>& cellTree = meshSearcher.cellTree();

		forAll(fc, triI)
		{
			if (cellTree.bb().contains(fc[triI]))
			{
				label index = cellTree.findInside(fc[triI]);
				if (index != -1)
				{
					nearest[triI].first() = 0.0;
					nearest[triI].second() = globalCells.toGlobal(index);
				}
			}
		}
	}
	else
	{
		// Search on all non-coupled boundary faces

		const indexedOctree<treeDataFace>& bTree = nonCoupledboundaryTree();

		forAll(fc, triI)
		{
			pointIndexHit nearInfo = bTree.findNearest
			(
				fc[triI],
				sqr(great)
			);
			if (nearInfo.hit())
			{
				nearest[triI].first() = magSqr(nearInfo.hitPoint() - fc[triI]);
				nearest[triI].second() = globalCells.toGlobal
				(
					bTree.shapes().faceLabels()[nearInfo.index()]
				);
			}
		}
	}


	// See which processor has the nearest. Mark and subset
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	Pstream::listCombineGather(nearest, nearestEqOp());
	Pstream::listCombineScatter(nearest);

	labelList cellOrFaceLabels(fc.size(), -1);

	label nFound = 0;
	forAll(nearest, triI)
	{
		if (nearest[triI].second() == labelMax)
		{
			// Not found on any processor. How to map?
		}
		else if (globalCells.isLocal(nearest[triI].second()))
		{
			cellOrFaceLabels[triI] = globalCells.toLocal
			(
				nearest[triI].second()
			);
			nFound++;
		}
	}


	if (debug)
	{
		Pout << "Local out of faces:" << cellOrFaceLabels.size()
			<< " keeping:" << nFound << endl;
	}

	// Now subset the surface. Do not use triSurface::subsetMesh since requires
	// original surface to be in compact numbering.

	const triSurface& s = surface_;

	// Compact to original triangle
	labelList faceMap(s.size());
	// Compact to original points
	labelList pointMap(s.points().size());
	// From original point to compact points
	labelList reversePointMap(s.points().size(), -1);

	{
		label newPointi = 0;
		label newFacei = 0;

		forAll(s, facei)
		{
			if (cellOrFaceLabels[facei] != -1)
			{
				faceMap[newFacei++] = facei;

				const triSurface::FaceType& f = s[facei];
				forAll(f, fp)
				{
					if (reversePointMap[f[fp]] == -1)
					{
						pointMap[newPointi] = f[fp];
						reversePointMap[f[fp]] = newPointi++;
					}
				}
			}
		}
		faceMap.setSize(newFacei);
		pointMap.setSize(newPointi);
	}


	// Subset cellOrFaceLabels
	cellOrFaceLabels = UIndirectList<label>(cellOrFaceLabels, faceMap)();

	// Store any face per point (without using pointFaces())
	labelList pointToFace(pointMap.size());

	// Create faces and points for subsetted surface
	faceList& faces = this->storedFaces();
	faces.setSize(faceMap.size());
	forAll(faceMap, i)
	{
		const triFace& f = s[faceMap[i]];
		triFace newF
		(
			reversePointMap[f[0]],
			reversePointMap[f[1]],
			reversePointMap[f[2]]
		);
		faces[i] = newF.triFaceFace();

		forAll(newF, fp)
		{
			pointToFace[newF[fp]] = i;
		}
	}

	this->storedPoints() = pointField(s.points(), pointMap);

	if (debug)
	{
		print(Pout);
		Pout << endl;
	}



	// Collect the samplePoints and sampleElements
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (sampledSurface::interpolate())
	{
		samplePoints_.setSize(pointMap.size());
		sampleElements_.setSize(pointMap.size(), -1);

		if (sampleSource_ == cells)
		{
			// samplePoints_   : per surface point a location inside the cell
			// sampleElements_ : per surface point the cell

			forAll(points(), pointi)
			{
				const point& pt = points()[pointi];
				label celli = cellOrFaceLabels[pointToFace[pointi]];
				sampleElements_[pointi] = celli;

				// Check if point inside cell
				if
					(
						mesh().pointInCell
						(
							pt,
							sampleElements_[pointi],
							meshSearcher.decompMode()
						)
						)
				{
					samplePoints_[pointi] = pt;
				}
				else
				{
					// Find nearest point on faces of cell
					const cell& cFaces = mesh().cells()[celli];

					scalar minDistSqr = vGreat;

					forAll(cFaces, i)
					{
						const face& f = mesh().faces()[cFaces[i]];
						pointHit info = f.nearestPoint(pt, mesh().points());
						if (info.distance() < minDistSqr)
						{
							minDistSqr = info.distance();
							samplePoints_[pointi] = info.rawPoint();
						}
					}
				}
			}
		}
		else if (sampleSource_ == insideCells)
		{
			// samplePoints_   : per surface point a location inside the cell
			// sampleElements_ : per surface point the cell

			forAll(points(), pointi)
			{
				const point& pt = points()[pointi];
				label celli = cellOrFaceLabels[pointToFace[pointi]];
				sampleElements_[pointi] = celli;
				samplePoints_[pointi] = pt;
			}
		}
		else
		{
			// samplePoints_   : per surface point a location on the boundary
			// sampleElements_ : per surface point the boundary face containing
			//                   the location

			forAll(points(), pointi)
			{
				const point& pt = points()[pointi];
				label facei = cellOrFaceLabels[pointToFace[pointi]];
				sampleElements_[pointi] = facei;
				samplePoints_[pointi] = mesh().faces()[facei].nearestPoint
				(
					pt,
					mesh().points()
				).rawPoint();
			}
		}
	}
	else
	{
		// if sampleSource_ == cells:
		//      samplePoints_   : n/a
		//      sampleElements_ : per surface triangle the cell
		// if sampleSource_ == insideCells:
		//      samplePoints_   : n/a
		//      sampleElements_ : -1 or per surface triangle the cell
		// else:
		//      samplePoints_   : n/a
		//      sampleElements_ : per surface triangle the boundary face
		samplePoints_.clear();
		sampleElements_.transfer(cellOrFaceLabels);
	}


	if (debug)
	{
		this->clearOut();
		OFstream str(mesh().time().path() / "surfaceToMesh.obj");
		Info << "Dumping correspondence from local surface (points or faces)"
			<< " to mesh (cells or faces) to " << str.name() << endl;
		label vertI = 0;

		if (sampledSurface::interpolate())
		{
			if (sampleSource_ == cells || sampleSource_ == insideCells)
			{
				forAll(samplePoints_, pointi)
				{
					meshTools::writeOBJ(str, points()[pointi]);
					vertI++;

					meshTools::writeOBJ(str, samplePoints_[pointi]);
					vertI++;

					label celli = sampleElements_[pointi];
					meshTools::writeOBJ(str, mesh().cellCentres()[celli]);
					vertI++;
					str << "l " << vertI - 2 << ' ' << vertI - 1 << ' ' << vertI
						<< nl;
				}
			}
			else
			{
				forAll(samplePoints_, pointi)
				{
					meshTools::writeOBJ(str, points()[pointi]);
					vertI++;

					meshTools::writeOBJ(str, samplePoints_[pointi]);
					vertI++;

					label facei = sampleElements_[pointi];
					meshTools::writeOBJ(str, mesh().faceCentres()[facei]);
					vertI++;
					str << "l " << vertI - 2 << ' ' << vertI - 1 << ' ' << vertI
						<< nl;
				}
			}
		}
		else
		{
			if (sampleSource_ == cells || sampleSource_ == insideCells)
			{
				forAll(sampleElements_, triI)
				{
					meshTools::writeOBJ(str, faceCentres()[triI]);
					vertI++;

					label celli = sampleElements_[triI];
					meshTools::writeOBJ(str, mesh().cellCentres()[celli]);
					vertI++;
					str << "l " << vertI - 1 << ' ' << vertI << nl;
				}
			}
			else
			{
				forAll(sampleElements_, triI)
				{
					meshTools::writeOBJ(str, faceCentres()[triI]);
					vertI++;

					label facei = sampleElements_[triI];
					meshTools::writeOBJ(str, mesh().faceCentres()[facei]);
					vertI++;
					str << "l " << vertI - 1 << ' ' << vertI << nl;
				}
			}
		}
	}


	needsUpdate_ = false;
	return true;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::sampledSurfaces::triSurfaceMesh::triSurfaceMesh
(
	const word& name,
	const polyMesh& mesh,
	const word& surfaceName,
	const samplingSource sampleSource
)
	:
	sampledSurface(name, mesh),
	surface_
	(
		IOobject
		(
			surfaceName,
			mesh.time().constant(), // instance
			"triSurface",           // local
			mesh,                   // registry
			IOobject::MUST_READ,
			IOobject::NO_WRITE,
			false
		)
	),
	sampleSource_(sampleSource),
	needsUpdate_(true),
	sampleElements_(0),
	samplePoints_(0)
{}


tnbLib::sampledSurfaces::triSurfaceMesh::triSurfaceMesh
(
	const word& name,
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	sampledSurface(name, mesh, dict),
	surface_
	(
		IOobject
		(
			dict.lookup("surface"),
			mesh.time().constant(), // instance
			"triSurface",           // local
			mesh,                   // registry
			IOobject::MUST_READ,
			IOobject::NO_WRITE,
			false
		)
	),
	sampleSource_(samplingSourceNames_[dict.lookup("source")]),
	needsUpdate_(true),
	sampleElements_(0),
	samplePoints_(0)
{}


tnbLib::sampledSurfaces::triSurfaceMesh::triSurfaceMesh
(
	const word& name,
	const polyMesh& mesh,
	const triSurface& surface,
	const word& sampleSourceName
)
	:
	sampledSurface(name, mesh),
	surface_
	(
		IOobject
		(
			name,
			mesh.time().constant(), // instance
			"triSurface",           // local
			mesh,                  // registry
			IOobject::NO_READ,
			IOobject::NO_WRITE,
			false
		),
		surface
	),
	sampleSource_(samplingSourceNames_[sampleSourceName]),
	needsUpdate_(true),
	sampleElements_(0),
	samplePoints_(0)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::sampledSurfaces::triSurfaceMesh::~triSurfaceMesh()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::sampledSurfaces::triSurfaceMesh::needsUpdate() const
{
	return needsUpdate_;
}


bool tnbLib::sampledSurfaces::triSurfaceMesh::expire()
{
	// already marked as expired
	if (needsUpdate_)
	{
		return false;
	}

	sampledSurface::clearGeom();
	MeshStorage::clear();

	boundaryTreePtr_.clear();
	sampleElements_.clear();
	samplePoints_.clear();

	needsUpdate_ = true;
	return true;
}


bool tnbLib::sampledSurfaces::triSurfaceMesh::update()
{
	if (!needsUpdate_)
	{
		return false;
	}

	// Mesh search engine, no triangulation of faces.
	meshSearch meshSearcher(mesh(), polyMesh::FACE_PLANES);

	return update(meshSearcher);
}


bool tnbLib::sampledSurfaces::triSurfaceMesh::update(const treeBoundBox& bb)
{
	if (!needsUpdate_)
	{
		return false;
	}

	// Mesh search engine on subset, no triangulation of faces.
	meshSearch meshSearcher(mesh(), bb, polyMesh::FACE_PLANES);

	return update(meshSearcher);
}


tnbLib::tmp<tnbLib::scalarField>
tnbLib::sampledSurfaces::triSurfaceMesh::sample
(
	const volScalarField& vField
) const
{
	return sampleField(vField);
}


tnbLib::tmp<tnbLib::vectorField>
tnbLib::sampledSurfaces::triSurfaceMesh::sample
(
	const volVectorField& vField
) const
{
	return sampleField(vField);
}

tnbLib::tmp<tnbLib::sphericalTensorField>
tnbLib::sampledSurfaces::triSurfaceMesh::sample
(
	const volSphericalTensorField& vField
) const
{
	return sampleField(vField);
}


tnbLib::tmp<tnbLib::symmTensorField>
tnbLib::sampledSurfaces::triSurfaceMesh::sample
(
	const volSymmTensorField& vField
) const
{
	return sampleField(vField);
}


tnbLib::tmp<tnbLib::tensorField>
tnbLib::sampledSurfaces::triSurfaceMesh::sample
(
	const volTensorField& vField
) const
{
	return sampleField(vField);
}


tnbLib::tmp<tnbLib::scalarField>
tnbLib::sampledSurfaces::triSurfaceMesh::interpolate
(
	const interpolation<scalar>& interpolator
) const
{
	return interpolateField(interpolator);
}


tnbLib::tmp<tnbLib::vectorField>
tnbLib::sampledSurfaces::triSurfaceMesh::interpolate
(
	const interpolation<vector>& interpolator
) const
{
	return interpolateField(interpolator);
}

tnbLib::tmp<tnbLib::sphericalTensorField>
tnbLib::sampledSurfaces::triSurfaceMesh::interpolate
(
	const interpolation<sphericalTensor>& interpolator
) const
{
	return interpolateField(interpolator);
}


tnbLib::tmp<tnbLib::symmTensorField>
tnbLib::sampledSurfaces::triSurfaceMesh::interpolate
(
	const interpolation<symmTensor>& interpolator
) const
{
	return interpolateField(interpolator);
}


tnbLib::tmp<tnbLib::tensorField>
tnbLib::sampledSurfaces::triSurfaceMesh::interpolate
(
	const interpolation<tensor>& interpolator
) const
{
	return interpolateField(interpolator);
}


void tnbLib::sampledSurfaces::triSurfaceMesh::print(Ostream& os) const
{
	os << "triSurfaceMesh: " << name() << " :"
		<< "  surface:" << surface_.objectRegistry::name()
		<< "  faces:" << faces().size()
		<< "  points:" << points().size();
}


// ************************************************************************* //