#include <smoothDelta.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <FaceCellWave.hxx>

#include <globalMeshData.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace LESModels
	{
		defineTypeNameAndDebug(smoothDelta, 0);
		addToRunTimeSelectionTable(LESdelta, smoothDelta, dictionary);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::LESModels::smoothDelta::setChangedFaces
(
	const polyMesh& mesh,
	const volScalarField& delta,
	DynamicList<label>& changedFaces,
	DynamicList<deltaData>& changedFacesInfo
)
{
	for (label facei = 0; facei < mesh.nInternalFaces(); facei++)
	{
		scalar ownDelta = delta[mesh.faceOwner()[facei]];

		scalar neiDelta = delta[mesh.faceNeighbour()[facei]];

		// Check if owner delta much larger than neighbour delta or vice versa

		if (ownDelta > maxDeltaRatio_ * neiDelta)
		{
			changedFaces.append(facei);
			changedFacesInfo.append(deltaData(ownDelta));
		}
		else if (neiDelta > maxDeltaRatio_ * ownDelta)
		{
			changedFaces.append(facei);
			changedFacesInfo.append(deltaData(neiDelta));
		}
	}

	// Insert all faces of coupled patches no matter what. Let FaceCellWave
	// sort it out.
	forAll(mesh.boundaryMesh(), patchi)
	{
		const polyPatch& patch = mesh.boundaryMesh()[patchi];

		if (patch.coupled())
		{
			forAll(patch, patchFacei)
			{
				label meshFacei = patch.start() + patchFacei;

				scalar ownDelta = delta[mesh.faceOwner()[meshFacei]];

				changedFaces.append(meshFacei);
				changedFacesInfo.append(deltaData(ownDelta));
			}
		}
	}

	changedFaces.shrink();
	changedFacesInfo.shrink();
}


void tnbLib::LESModels::smoothDelta::calcDelta()
{
	const fvMesh& mesh = turbulenceModel_.mesh();

	const volScalarField& geometricDelta = geometricDelta_();

	// Fill changed faces with info
	DynamicList<label> changedFaces(mesh.nFaces() / 100 + 100);
	DynamicList<deltaData> changedFacesInfo(changedFaces.size());

	setChangedFaces(mesh, geometricDelta, changedFaces, changedFacesInfo);

	// Set initial field on cells.
	List<deltaData> cellDeltaData(mesh.nCells());

	forAll(geometricDelta, celli)
	{
		cellDeltaData[celli] = geometricDelta[celli];
	}

	// Set initial field on faces.
	List<deltaData> faceDeltaData(mesh.nFaces());


	// Propagate information over whole domain.
	FaceCellWave<deltaData, scalar> deltaCalc
	(
		mesh,
		changedFaces,
		changedFacesInfo,
		faceDeltaData,
		cellDeltaData,
		mesh.globalData().nTotalCells() + 1,  // max iterations
		maxDeltaRatio_
	);

	forAll(delta_, celli)
	{
		delta_[celli] = cellDeltaData[celli].delta();
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::LESModels::smoothDelta::smoothDelta
(
	const word& name,
	const turbulenceModel& turbulence,
	const dictionary& dict
)
	:
	LESdelta(name, turbulence),
	geometricDelta_
	(
		LESdelta::New
		(
			"geometricDelta",
			turbulence,
			dict.optionalSubDict(type() + "Coeffs")
		)
	),
	maxDeltaRatio_
	(
		readScalar
		(
			dict.optionalSubDict(type() + "Coeffs").lookup("maxDeltaRatio")
		)
	)
{
	calcDelta();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::LESModels::smoothDelta::read(const dictionary& dict)
{
	const dictionary& coeffsDict(dict.optionalSubDict(type() + "Coeffs"));

	geometricDelta_().read(coeffsDict);
	coeffsDict.lookup("maxDeltaRatio") >> maxDeltaRatio_;
	calcDelta();
}


void tnbLib::LESModels::smoothDelta::correct()
{
	geometricDelta_().correct();

	if (turbulenceModel_.mesh().changing())
	{
		calcDelta();
	}
}


// ************************************************************************* //