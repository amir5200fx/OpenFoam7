#include <patchWave.hxx>

#include <polyMesh.hxx>
#include <wallPoint.hxx>
#include <globalMeshData.hxx>

#include <SubField.hxx>  // added by amir

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::patchWave::setChangedFaces
(
	const labelHashSet& patchIDs,
	labelList& changedFaces,
	List<wallPoint>& faceDist
) const
{
	const polyMesh& mesh = cellDistFuncs::mesh();

	label nChangedFaces = 0;

	forAll(mesh.boundaryMesh(), patchi)
	{
		if (patchIDs.found(patchi))
		{
			const polyPatch& patch = mesh.boundaryMesh()[patchi];

			forAll(patch.faceCentres(), patchFacei)
			{
				label meshFacei = patch.start() + patchFacei;

				changedFaces[nChangedFaces] = meshFacei;

				faceDist[nChangedFaces] =
					wallPoint
					(
						patch.faceCentres()[patchFacei],
						0.0
					);

				nChangedFaces++;
			}
		}
	}
}


tnbLib::label tnbLib::patchWave::getValues(const MeshWave<wallPoint>& waveInfo)
{
	const List<wallPoint>& cellInfo = waveInfo.allCellInfo();
	const List<wallPoint>& faceInfo = waveInfo.allFaceInfo();

	label nIllegal = 0;

	// Copy cell values
	distance_.setSize(cellInfo.size());

	forAll(cellInfo, celli)
	{
		scalar dist = cellInfo[celli].distSqr();

		if (cellInfo[celli].valid(waveInfo.data()))
		{
			distance_[celli] = tnbLib::sqrt(dist);
		}
		else
		{
			distance_[celli] = dist;

			nIllegal++;
		}
	}

	// Copy boundary values
	forAll(patchDistance_, patchi)
	{
		const polyPatch& patch = mesh().boundaryMesh()[patchi];

		// Allocate storage for patchDistance
		scalarField* patchDistPtr = new scalarField(patch.size());

		patchDistance_.set(patchi, patchDistPtr);

		scalarField& patchField = *patchDistPtr;

		forAll(patchField, patchFacei)
		{
			label meshFacei = patch.start() + patchFacei;

			scalar dist = faceInfo[meshFacei].distSqr();

			if (faceInfo[meshFacei].valid(waveInfo.data()))
			{
				// Adding small to avoid problems with /0 in the turbulence
				// models
				patchField[patchFacei] = tnbLib::sqrt(dist) + small;
			}
			else
			{
				patchField[patchFacei] = dist;

				nIllegal++;
			}
		}
	}
	return nIllegal;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::patchWave::patchWave
(
	const polyMesh& mesh,
	const labelHashSet& patchIDs,
	const bool correctWalls
)
	:
	cellDistFuncs(mesh),
	patchIDs_(patchIDs),
	correctWalls_(correctWalls),
	nUnset_(0),
	distance_(mesh.nCells()),
	patchDistance_(mesh.boundaryMesh().size())
{
	patchWave::correct();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::patchWave::~patchWave()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::patchWave::correct()
{
	// Set initial changed faces: set wallPoint for wall faces to wall centre

	label nPatch = sumPatchSize(patchIDs_);

	List<wallPoint> faceDist(nPatch);
	labelList changedFaces(nPatch);

	// Set to faceDist information to facecentre on walls.
	setChangedFaces(patchIDs_, changedFaces, faceDist);

	// Do calculate wall distance by 'growing' from faces.
	MeshWave<wallPoint> waveInfo
	(
		mesh(),
		changedFaces,
		faceDist,
		mesh().globalData().nTotalCells() + 1 // max iterations
	);

	// Copy distance into return field
	nUnset_ = getValues(waveInfo);

	// Correct wall cells for true distance
	if (correctWalls_)
	{
		Map<label> nearestFace(2 * nPatch);

		correctBoundaryFaceCells
		(
			patchIDs_,
			distance_,
			nearestFace
		);

		correctBoundaryPointCells
		(
			patchIDs_,
			distance_,
			nearestFace
		);
	}
}


// ************************************************************************* //