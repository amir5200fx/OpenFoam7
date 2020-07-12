#include <cellDistFuncs.hxx>

#include <polyMesh.hxx>
#include <wallPolyPatch.hxx>
#include <polyBoundaryMesh.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(cellDistFuncs, 0);
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

// Find val in first nElems elements of elems.
tnbLib::label tnbLib::cellDistFuncs::findIndex
(
	const label nElems,
	const labelList& elems,
	const label val
)
{
	for (label i = 0; i < nElems; i++)
	{
		if (elems[i] == val)
		{
			return i;
		}
	}
	return -1;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::cellDistFuncs::cellDistFuncs(const polyMesh& mesh)
	:
	mesh_(mesh)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::labelHashSet tnbLib::cellDistFuncs::getPatchIDs
(
	const wordReList& patchNames
) const
{
	return mesh().boundaryMesh().patchSet(patchNames, false);
}


// Return smallest true distance from p to any of wallFaces.
// Note that even if normal hits face we still check other faces.
// Note that wallFaces is untruncated and we explicitly pass in size.
tnbLib::scalar tnbLib::cellDistFuncs::smallestDist
(
	const point& p,
	const polyPatch& patch,
	const label nWallFaces,
	const labelList& wallFaces,
	label& minFacei
) const
{
	const pointField& points = patch.points();

	scalar minDist = great;
	minFacei = -1;

	for (label wallFacei = 0; wallFacei < nWallFaces; wallFacei++)
	{
		label patchFacei = wallFaces[wallFacei];

		pointHit curHit = patch[patchFacei].nearestPoint(p, points);

		if (curHit.distance() < minDist)
		{
			minDist = curHit.distance();
			minFacei = patch.start() + patchFacei;
		}
	}

	return minDist;
}


// Get point neighbours of facei (including facei). Returns number of faces.
// Note: does not allocate storage but does use linear search to determine
// uniqueness. For polygonal faces this might be quite inefficient.
tnbLib::label tnbLib::cellDistFuncs::getPointNeighbours
(
	const primitivePatch& patch,
	const label patchFacei,
	labelList& neighbours
) const
{
	label nNeighbours = 0;

	// Add myself
	neighbours[nNeighbours++] = patchFacei;

	// Add all face neighbours
	const labelList& faceNeighbours = patch.faceFaces()[patchFacei];

	forAll(faceNeighbours, faceNeighbourI)
	{
		neighbours[nNeighbours++] = faceNeighbours[faceNeighbourI];
	}

	// Remember part of neighbours that contains edge-connected faces.
	label nEdgeNbs = nNeighbours;


	// Add all point-only neighbours by linear searching in edge neighbours.
	// Assumes that point-only neighbours are not using multiple points on
	// face.

	const face& f = patch.localFaces()[patchFacei];

	forAll(f, fp)
	{
		label pointi = f[fp];

		const labelList& pointNbs = patch.pointFaces()[pointi];

		forAll(pointNbs, nbI)
		{
			label facei = pointNbs[nbI];

			// Check for facei in edge-neighbours part of neighbours
			if (findIndex(nEdgeNbs, neighbours, facei) == -1)
			{
				neighbours[nNeighbours++] = facei;
			}
		}
	}


	if (debug)
	{
		// Check for duplicates

		// Use hashSet to determine nbs.
		labelHashSet nbs(4 * f.size());

		forAll(f, fp)
		{
			const labelList& pointNbs = patch.pointFaces()[f[fp]];

			forAll(pointNbs, i)
			{
				nbs.insert(pointNbs[i]);
			}
		}

		// Subtract ours.
		for (label i = 0; i < nNeighbours; i++)
		{
			label nb = neighbours[i];

			if (!nbs.found(nb))
			{
				SeriousErrorInFunction
					<< "getPointNeighbours : patchFacei:" << patchFacei
					<< " verts:" << f << endl;

				forAll(f, fp)
				{
					SeriousErrorInFunction
						<< "point:" << f[fp] << " pointFaces:"
						<< patch.pointFaces()[f[fp]] << endl;
				}

				for (label i = 0; i < nNeighbours; i++)
				{
					SeriousErrorInFunction
						<< "fast nbr:" << neighbours[i]
						<< endl;
				}

				FatalErrorInFunction
					<< "Problem: fast pointNeighbours routine included " << nb
					<< " which is not in proper neighbour list " << nbs.toc()
					<< abort(FatalError);
			}
			nbs.erase(nb);
		}

		if (nbs.size())
		{
			FatalErrorInFunction
				<< "Problem: fast pointNeighbours routine did not find "
				<< nbs.toc() << abort(FatalError);
		}
	}

	return nNeighbours;
}


// size of largest patch (out of supplied subset of patches)
tnbLib::label tnbLib::cellDistFuncs::maxPatchSize
(
	const labelHashSet& patchIDs
) const
{
	label maxSize = 0;

	forAll(mesh().boundaryMesh(), patchi)
	{
		if (patchIDs.found(patchi))
		{
			const polyPatch& patch = mesh().boundaryMesh()[patchi];

			maxSize = tnbLib::max(maxSize, patch.size());
		}
	}
	return maxSize;
}


// sum of patch sizes (out of supplied subset of patches)
tnbLib::label tnbLib::cellDistFuncs::sumPatchSize
(
	const labelHashSet& patchIDs
)
const
{
	label sum = 0;

	forAll(mesh().boundaryMesh(), patchi)
	{
		if (patchIDs.found(patchi))
		{
			const polyPatch& patch = mesh().boundaryMesh()[patchi];

			sum += patch.size();
		}
	}
	return sum;
}


// Gets nearest wall for cells next to wall
void tnbLib::cellDistFuncs::correctBoundaryFaceCells
(
	const labelHashSet& patchIDs,
	scalarField& wallDistCorrected,
	Map<label>& nearestFace
) const
{
	// Size neighbours array for maximum possible (= size of largest patch)
	label maxPointNeighbours = maxPatchSize(patchIDs);

	labelList neighbours(maxPointNeighbours);


	// Correct all cells with face on wall
	const vectorField& cellCentres = mesh().cellCentres();
	const labelList& faceOwner = mesh().faceOwner();

	forAll(mesh().boundaryMesh(), patchi)
	{
		if (patchIDs.found(patchi))
		{
			const polyPatch& patch = mesh().boundaryMesh()[patchi];

			// Check cells with face on wall
			forAll(patch, patchFacei)
			{
				label nNeighbours = getPointNeighbours
				(
					patch,
					patchFacei,
					neighbours
				);

				label celli = faceOwner[patch.start() + patchFacei];

				label minFacei = -1;

				wallDistCorrected[celli] = smallestDist
				(
					cellCentres[celli],
					patch,
					nNeighbours,
					neighbours,
					minFacei
				);

				// Store wallCell and its nearest neighbour
				nearestFace.insert(celli, minFacei);
			}
		}
	}

}


// Correct all cells connected to wall (via point) and not in nearestFace
void tnbLib::cellDistFuncs::correctBoundaryPointCells
(
	const labelHashSet& patchIDs,
	scalarField& wallDistCorrected,
	Map<label>& nearestFace
) const
{
	// Correct all (non-visited) cells with point on wall

	const vectorField& cellCentres = mesh().cellCentres();

	forAll(mesh().boundaryMesh(), patchi)
	{
		if (patchIDs.found(patchi))
		{
			const polyPatch& patch = mesh().boundaryMesh()[patchi];

			const labelList& meshPoints = patch.meshPoints();
			const labelListList& pointFaces = patch.pointFaces();

			forAll(meshPoints, meshPointi)
			{
				label vertI = meshPoints[meshPointi];

				const labelList& neighbours = mesh().pointCells(vertI);

				forAll(neighbours, neighbourI)
				{
					label celli = neighbours[neighbourI];

					if (!nearestFace.found(celli))
					{
						const labelList& wallFaces = pointFaces[meshPointi];

						label minFacei = -1;

						wallDistCorrected[celli] = smallestDist
						(
							cellCentres[celli],
							patch,
							wallFaces.size(),
							wallFaces,
							minFacei
						);

						// Store wallCell and its nearest neighbour
						nearestFace.insert(celli, minFacei);
					}
				}
			}
		}
	}
}


// ************************************************************************* //