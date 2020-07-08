#include <meshTriangulation.hxx>

#include <polyMesh.hxx>
#include <faceTriangulation.hxx>

#include <IndirectList.hxx>  // added by amir

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

bool tnbLib::meshTriangulation::isInternalFace
(
	const primitiveMesh& mesh,
	const boolList& includedCell,
	const label facei
)
{
	if (mesh.isInternalFace(facei))
	{
		label own = mesh.faceOwner()[facei];
		label nei = mesh.faceNeighbour()[facei];

		if (includedCell[own] && includedCell[nei])
		{
			// Neighbouring cell will get included in subset
			// as well so face is internal.
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}


void tnbLib::meshTriangulation::getFaces
(
	const primitiveMesh& mesh,
	const boolList& includedCell,
	boolList& faceIsCut,
	label& nFaces,
	label& nInternalFaces
)
{
	// All faces to be triangulated.
	faceIsCut.setSize(mesh.nFaces());
	faceIsCut = false;

	nFaces = 0;
	nInternalFaces = 0;

	forAll(includedCell, celli)
	{
		// Include faces of cut cells only.
		if (includedCell[celli])
		{
			const labelList& cFaces = mesh.cells()[celli];

			forAll(cFaces, i)
			{
				label facei = cFaces[i];

				if (!faceIsCut[facei])
				{
					// First visit of face.
					nFaces++;
					faceIsCut[facei] = true;

					// See if would become internal or external face
					if (isInternalFace(mesh, includedCell, facei))
					{
						nInternalFaces++;
					}
				}
			}
		}
	}

	Pout << "Subset consists of " << nFaces << " faces out of " << mesh.nFaces()
		<< " of which " << nInternalFaces << " are internal" << endl;
}


void tnbLib::meshTriangulation::insertTriangles
(
	const triFaceList& faceTris,
	const label facei,
	const label regionI,
	const bool reverse,

	List<labelledTri>& triangles,
	label& triI
)
{
	// Copy triangles. Optionally reverse them
	forAll(faceTris, i)
	{
		const triFace& f = faceTris[i];

		labelledTri& tri = triangles[triI];

		if (reverse)
		{
			tri[0] = f[0];
			tri[2] = f[1];
			tri[1] = f[2];
		}
		else
		{
			tri[0] = f[0];
			tri[1] = f[1];
			tri[2] = f[2];
		}

		tri.region() = regionI;

		faceMap_[triI] = facei;

		triI++;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Null constructor
tnbLib::meshTriangulation::meshTriangulation()
	:
	triSurface(),
	nInternalFaces_(0),
	faceMap_()
{}


// Construct from faces of cells
tnbLib::meshTriangulation::meshTriangulation
(
	const polyMesh& mesh,
	const label internalFacesPatch,
	const boolList& includedCell,
	const bool faceCentreDecomposition
)
	:
	triSurface(),
	nInternalFaces_(0),
	faceMap_()
{
	const faceList& faces = mesh.faces();
	const pointField& points = mesh.points();
	const polyBoundaryMesh& patches = mesh.boundaryMesh();

	// All faces to be triangulated.
	boolList faceIsCut;
	label nFaces, nInternalFaces;

	getFaces
	(
		mesh,
		includedCell,
		faceIsCut,
		nFaces,
		nInternalFaces
	);


	// Find upper limit for number of triangles
	// (can be less if triangulation fails)
	label nTotTri = 0;

	if (faceCentreDecomposition)
	{
		forAll(faceIsCut, facei)
		{
			if (faceIsCut[facei])
			{
				nTotTri += faces[facei].size();
			}
		}
	}
	else
	{
		forAll(faceIsCut, facei)
		{
			if (faceIsCut[facei])
			{
				nTotTri += faces[facei].nTriangles(points);
			}
		}
	}
	Pout << "nTotTri : " << nTotTri << endl;


	// Storage for new and old points (only for faceCentre decomposition;
	// for triangulation uses only existing points)
	pointField newPoints;

	if (faceCentreDecomposition)
	{
		newPoints.setSize(mesh.nPoints() + faces.size());
		forAll(mesh.points(), pointi)
		{
			newPoints[pointi] = mesh.points()[pointi];
		}
		// Face centres
		forAll(faces, facei)
		{
			newPoints[mesh.nPoints() + facei] = mesh.faceCentres()[facei];
		}
	}

	// Storage for all triangles
	List<labelledTri> triangles(nTotTri);
	faceMap_.setSize(nTotTri);
	label triI = 0;


	if (faceCentreDecomposition)
	{
		// Decomposition around face centre
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		// Triangulate internal faces
		forAll(faceIsCut, facei)
		{
			if (faceIsCut[facei] && isInternalFace(mesh, includedCell, facei))
			{
				// Face was internal to the mesh and will be 'internal' to
				// the surface.

				// Triangulate face
				const face& f = faces[facei];

				forAll(f, fp)
				{
					faceMap_[triI] = facei;

					triangles[triI++] =
						labelledTri
						(
							f[fp],
							f.nextLabel(fp),
							mesh.nPoints() + facei,     // face centre
							internalFacesPatch
						);
				}
			}
		}
		nInternalFaces_ = triI;


		// Triangulate external faces
		forAll(faceIsCut, facei)
		{
			if (faceIsCut[facei] && !isInternalFace(mesh, includedCell, facei))
			{
				// Face will become outside of the surface.

				label patchi = -1;
				bool reverse = false;

				if (mesh.isInternalFace(facei))
				{
					patchi = internalFacesPatch;

					// Check orientation. Check which side of the face gets
					// included (note: only one side is).
					if (includedCell[mesh.faceOwner()[facei]])
					{
						reverse = false;
					}
					else
					{
						reverse = true;
					}
				}
				else
				{
					// Face was already outside so orientation ok.

					patchi = patches.whichPatch(facei);

					reverse = false;
				}


				// Triangulate face
				const face& f = faces[facei];

				if (reverse)
				{
					forAll(f, fp)
					{
						faceMap_[triI] = facei;

						triangles[triI++] =
							labelledTri
							(
								f.nextLabel(fp),
								f[fp],
								mesh.nPoints() + facei,     // face centre
								patchi
							);
					}
				}
				else
				{
					forAll(f, fp)
					{
						faceMap_[triI] = facei;

						triangles[triI++] =
							labelledTri
							(
								f[fp],
								f.nextLabel(fp),
								mesh.nPoints() + facei,     // face centre
								patchi
							);
					}
				}
			}
		}
	}
	else
	{
		// Triangulation using existing vertices
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		// Triangulate internal faces
		forAll(faceIsCut, facei)
		{
			if (faceIsCut[facei] && isInternalFace(mesh, includedCell, facei))
			{
				// Face was internal to the mesh and will be 'internal' to
				// the surface.

				// Triangulate face. Fall back to naive triangulation if failed.
				faceTriangulation faceTris(points, faces[facei], true);

				if (faceTris.empty())
				{
					WarningInFunction
						<< "Could not find triangulation for face " << facei
						<< " vertices " << faces[facei] << " coords "
						<< IndirectList<point>(points, faces[facei])() << endl;
				}
				else
				{
					// Copy triangles. Make them internalFacesPatch
					insertTriangles
					(
						faceTris,
						facei,
						internalFacesPatch,
						false,                  // no reverse

						triangles,
						triI
					);
				}
			}
		}
		nInternalFaces_ = triI;


		// Triangulate external faces
		forAll(faceIsCut, facei)
		{
			if (faceIsCut[facei] && !isInternalFace(mesh, includedCell, facei))
			{
				// Face will become outside of the surface.

				label patchi = -1;
				bool reverse = false;

				if (mesh.isInternalFace(facei))
				{
					patchi = internalFacesPatch;

					// Check orientation. Check which side of the face gets
					// included (note: only one side is).
					if (includedCell[mesh.faceOwner()[facei]])
					{
						reverse = false;
					}
					else
					{
						reverse = true;
					}
				}
				else
				{
					// Face was already outside so orientation ok.

					patchi = patches.whichPatch(facei);

					reverse = false;
				}

				// Triangulate face
				faceTriangulation faceTris(points, faces[facei], true);

				if (faceTris.empty())
				{
					WarningInFunction
						<< "Could not find triangulation for face " << facei
						<< " vertices " << faces[facei] << " coords "
						<< IndirectList<point>(points, faces[facei])() << endl;
				}
				else
				{
					// Copy triangles. Optionally reverse them
					insertTriangles
					(
						faceTris,
						facei,
						patchi,
						reverse,    // whether to reverse

						triangles,
						triI
					);
				}
			}
		}
	}

	// Shrink if necessary (because of invalid triangulations)
	triangles.setSize(triI);
	faceMap_.setSize(triI);

	Pout << "nInternalFaces_:" << nInternalFaces_ << endl;
	Pout << "triangles:" << triangles.size() << endl;


	geometricSurfacePatchList surfPatches(patches.size());

	forAll(patches, patchi)
	{
		surfPatches[patchi] =
			geometricSurfacePatch
			(
				patches[patchi].physicalType(),
				patches[patchi].name(),
				patchi
			);
	}

	// Create globally numbered tri surface
	if (faceCentreDecomposition)
	{
		// Use newPoints (mesh points + face centres)
		triSurface globalSurf(triangles, surfPatches, newPoints);

		// Create locally numbered tri surface
		triSurface::operator=
			(
				triSurface
				(
					globalSurf.localFaces(),
					surfPatches,
					globalSurf.localPoints()
				)
				);
	}
	else
	{
		// Use mesh points
		triSurface globalSurf(triangles, surfPatches, mesh.points());

		// Create locally numbered tri surface
		triSurface::operator=
			(
				triSurface
				(
					globalSurf.localFaces(),
					surfPatches,
					globalSurf.localPoints()
				)
				);
	}
}


// ************************************************************************* //