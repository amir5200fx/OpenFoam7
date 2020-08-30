#include <sampledCuttingPlane.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <emptyFvPatchFields.hxx>  // added by amir
#include <calculatedFvPatchFields.hxx>  // added by amir
#include <Time.hxx>  // added by amir
#include <volMesh.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace sampledSurfaces
	{
		defineTypeNameAndDebug(cuttingPlane, 0);
		addToRunTimeSelectionTable(sampledSurface, cuttingPlane, word);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::sampledSurfaces::cuttingPlane::createGeometry()
{
	if (debug)
	{
		Pout << "cuttingPlane::createGeometry :updating geometry."
			<< endl;
	}

	// Clear any stored topologies
	facesPtr_.clear();
	isoSurfPtr_.ptr();
	pointDistance_.clear();
	cellDistancePtr_.clear();

	// Clear derived data
	clearGeom();

	// Get any subMesh
	if (zoneID_.index() != -1 && !subMeshPtr_.valid())
	{
		const polyBoundaryMesh& patches = mesh().boundaryMesh();

		// Patch to put exposed internal faces into
		const label exposedPatchi = patches.findPatchID(exposedPatchName_);

		DebugInfo
			<< "Allocating subset of size "
			<< mesh().cellZones()[zoneID_.index()].size()
			<< " with exposed faces into patch "
			<< patches[exposedPatchi].name() << endl;

		subMeshPtr_.reset
		(
			new fvMeshSubset(static_cast<const fvMesh&>(mesh()))
		);
		subMeshPtr_().setLargeCellSubset
		(
			labelHashSet(mesh().cellZones()[zoneID_.index()]),
			exposedPatchi
		);
	}


	// Select either the submesh or the underlying mesh
	const fvMesh& mesh =
		(
			subMeshPtr_.valid()
			? subMeshPtr_().subMesh()
			: static_cast<const fvMesh&>(this->mesh())
			);


	// Distance to cell centres
	// ~~~~~~~~~~~~~~~~~~~~~~~~

	cellDistancePtr_.reset
	(
		new volScalarField
		(
			IOobject
			(
				"cellDistance",
				mesh.time().timeName(),
				mesh.time(),
				IOobject::NO_READ,
				IOobject::NO_WRITE,
				false
			),
			mesh,
			dimensionedScalar(dimLength, 0)
		)
	);
	volScalarField& cellDistance = cellDistancePtr_();

	// Internal field
	{
		const pointField& cc = mesh.cellCentres();
		scalarField& fld = cellDistance.primitiveFieldRef();

		forAll(cc, i)
		{
			// Signed distance
			fld[i] = (cc[i] - plane_.refPoint()) & plane_.normal();
		}
	}

	volScalarField::Boundary& cellDistanceBf =
		cellDistance.boundaryFieldRef();

	// Patch fields
	{
		forAll(cellDistanceBf, patchi)
		{
			if
				(
					isA<emptyFvPatchScalarField>
					(
						cellDistanceBf[patchi]
						)
					)
			{
				cellDistanceBf.set
				(
					patchi,
					new calculatedFvPatchScalarField
					(
						mesh.boundary()[patchi],
						cellDistance
					)
				);

				const polyPatch& pp = mesh.boundary()[patchi].patch();
				pointField::subField cc = pp.patchSlice(mesh.faceCentres());

				fvPatchScalarField& fld = cellDistanceBf[patchi];
				fld.setSize(pp.size());
				forAll(fld, i)
				{
					fld[i] = (cc[i] - plane_.refPoint()) & plane_.normal();
				}
			}
			else
			{
				const pointField& cc = mesh.C().boundaryField()[patchi];
				fvPatchScalarField& fld = cellDistanceBf[patchi];

				forAll(fld, i)
				{
					fld[i] = (cc[i] - plane_.refPoint()) & plane_.normal();
				}
			}
		}
	}


	// On processor patches the mesh.C() will already be the cell centre
	// on the opposite side so no need to swap cellDistance.


	// Distance to points
	pointDistance_.setSize(mesh.nPoints());
	{
		const pointField& pts = mesh.points();

		forAll(pointDistance_, i)
		{
			pointDistance_[i] = (pts[i] - plane_.refPoint()) & plane_.normal();
		}
	}


	if (debug)
	{
		Pout << "Writing cell distance:" << cellDistance.objectPath() << endl;
		cellDistance.write();
		pointScalarField pDist
		(
			IOobject
			(
				"pointDistance",
				mesh.time().timeName(),
				mesh.time(),
				IOobject::NO_READ,
				IOobject::NO_WRITE,
				false
			),
			pointMesh::New(mesh),
			dimensionedScalar(dimLength, 0)
		);
		pDist.primitiveFieldRef() = pointDistance_;

		Pout << "Writing point distance:" << pDist.objectPath() << endl;
		pDist.write();
	}


	//- Direct from cell field and point field.
	isoSurfPtr_.reset
	(
		new isoSurface
		(
			mesh,
			cellDistance,
			pointDistance_,
			0,
			regularise_ ? isoSurface::DIAGCELL : isoSurface::NONE
		)
	);

	if (debug)
	{
		print(Pout);
		Pout << endl;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::sampledSurfaces::cuttingPlane::cuttingPlane
(
	const word& name,
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	sampledSurface(name, mesh, dict),
	plane_(dict),
	regularise_(dict.lookupOrDefault("regularise", true)),
	average_(dict.lookupOrDefault("average", false)),
	zoneID_(dict.lookupOrDefault("zone", word::null), mesh.cellZones()),
	exposedPatchName_(word::null),
	needsUpdate_(true),
	subMeshPtr_(nullptr),
	cellDistancePtr_(nullptr),
	isoSurfPtr_(nullptr)
{
	if (zoneID_.index() != -1)
	{
		dict.lookup("exposedPatchName") >> exposedPatchName_;

		if (mesh.boundaryMesh().findPatchID(exposedPatchName_) == -1)
		{
			FatalErrorInFunction
				<< "Cannot find patch " << exposedPatchName_
				<< " in which to put exposed faces." << endl
				<< "Valid patches are " << mesh.boundaryMesh().names()
				<< exit(FatalError);
		}

		if (debug && zoneID_.index() != -1)
		{
			Info << "Restricting to cellZone " << zoneID_.name()
				<< " with exposed internal faces into patch "
				<< exposedPatchName_ << endl;
		}
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::sampledSurfaces::cuttingPlane::~cuttingPlane()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::sampledSurfaces::cuttingPlane::needsUpdate() const
{
	return needsUpdate_;
}


bool tnbLib::sampledSurfaces::cuttingPlane::expire()
{
	if (debug)
	{
		Pout << "cuttingPlane::expire :"
			<< " needsUpdate_:" << needsUpdate_ << endl;
	}

	// Clear derived data
	clearGeom();

	// Already marked as expired
	if (needsUpdate_)
	{
		return false;
	}

	needsUpdate_ = true;
	return true;
}


bool tnbLib::sampledSurfaces::cuttingPlane::update()
{
	if (debug)
	{
		Pout << "cuttingPlane::update :"
			<< " needsUpdate_:" << needsUpdate_ << endl;
	}

	if (!needsUpdate_)
	{
		return false;
	}

	createGeometry();

	needsUpdate_ = false;
	return true;
}


tnbLib::tmp<tnbLib::scalarField>
tnbLib::sampledSurfaces::cuttingPlane::sample
(
	const volScalarField& vField
) const
{
	return sampleField(vField);
}


tnbLib::tmp<tnbLib::vectorField>
tnbLib::sampledSurfaces::cuttingPlane::sample
(
	const volVectorField& vField
) const
{
	return sampleField(vField);
}


tnbLib::tmp<tnbLib::sphericalTensorField>
tnbLib::sampledSurfaces::cuttingPlane::sample
(
	const volSphericalTensorField& vField
) const
{
	return sampleField(vField);
}


tnbLib::tmp<tnbLib::symmTensorField>
tnbLib::sampledSurfaces::cuttingPlane::sample
(
	const volSymmTensorField& vField
) const
{
	return sampleField(vField);
}


tnbLib::tmp<tnbLib::tensorField>
tnbLib::sampledSurfaces::cuttingPlane::sample
(
	const volTensorField& vField
) const
{
	return sampleField(vField);
}


tnbLib::tmp<tnbLib::scalarField>
tnbLib::sampledSurfaces::cuttingPlane::interpolate
(
	const interpolation<scalar>& interpolator
) const
{
	return interpolateField(interpolator);
}


tnbLib::tmp<tnbLib::vectorField>
tnbLib::sampledSurfaces::cuttingPlane::interpolate
(
	const interpolation<vector>& interpolator
) const
{
	return interpolateField(interpolator);
}

tnbLib::tmp<tnbLib::sphericalTensorField>
tnbLib::sampledSurfaces::cuttingPlane::interpolate
(
	const interpolation<sphericalTensor>& interpolator
) const
{
	return interpolateField(interpolator);
}


tnbLib::tmp<tnbLib::symmTensorField>
tnbLib::sampledSurfaces::cuttingPlane::interpolate
(
	const interpolation<symmTensor>& interpolator
) const
{
	return interpolateField(interpolator);
}


tnbLib::tmp<tnbLib::tensorField>
tnbLib::sampledSurfaces::cuttingPlane::interpolate
(
	const interpolation<tensor>& interpolator
) const
{
	return interpolateField(interpolator);
}


void tnbLib::sampledSurfaces::cuttingPlane::print(Ostream& os) const
{
	os << "cuttingPlane: " << name() << " :"
		<< "  plane:" << plane_
		<< "  faces:" << faces().size()
		<< "  points:" << points().size();
}


// ************************************************************************* //