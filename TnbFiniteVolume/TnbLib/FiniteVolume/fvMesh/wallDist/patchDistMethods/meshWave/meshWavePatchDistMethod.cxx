#include <meshWavePatchDistMethod.hxx>

#include <fvMesh.hxx>
#include <volFields.hxx>
#include <patchWave.hxx>
#include <patchDataWave.hxx>
#include <wallPointData.hxx>
#include <emptyFvPatchFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

#include <Switch.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace patchDistMethods
	{
		defineTypeNameAndDebug(meshWave, 0);
		addToRunTimeSelectionTable(patchDistMethod, meshWave, dictionary);
	}
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::patchDistMethods::meshWave::meshWave
(
	const dictionary& dict,
	const fvMesh& mesh,
	const labelHashSet& patchIDs
)
	:
	patchDistMethod(mesh, patchIDs),
	correctWalls_(dict.lookupOrDefault<Switch>("correctWalls", true)),
	nUnset_(0)
{}


tnbLib::patchDistMethods::meshWave::meshWave
(
	const fvMesh& mesh,
	const labelHashSet& patchIDs,
	const bool correctWalls
)
	:
	patchDistMethod(mesh, patchIDs),
	correctWalls_(correctWalls),
	nUnset_(0)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::patchDistMethods::meshWave::correct(volScalarField& y)
{
	y = dimensionedScalar(dimLength, great);

	// Calculate distance starting from patch faces
	patchWave wave(mesh_, patchIDs_, correctWalls_);

	// Transfer cell values from wave into y
	y.transfer(wave.distance());

	// Transfer values on patches into boundaryField of y
	volScalarField::Boundary& ybf = y.boundaryFieldRef();

	forAll(ybf, patchi)
	{
		if (!isA<emptyFvPatchScalarField>(ybf[patchi]))
		{
			scalarField& waveFld = wave.patchDistance()[patchi];

			ybf[patchi].transfer(waveFld);
		}
	}

	// Transfer number of unset values
	nUnset_ = wave.nUnset();

	return nUnset_ > 0;
}


bool tnbLib::patchDistMethods::meshWave::correct
(
	volScalarField& y,
	volVectorField& n
)
{
	y = dimensionedScalar(dimLength, great);

	// Collect pointers to data on patches
	UPtrList<vectorField> patchData(mesh_.boundaryMesh().size());

	volVectorField::Boundary& nbf = n.boundaryFieldRef();

	forAll(nbf, patchi)
	{
		patchData.set(patchi, &nbf[patchi]);
	}

	// Do mesh wave
	patchDataWave<wallPointData<vector>> wave
	(
		mesh_,
		patchIDs_,
		patchData,
		correctWalls_
	);

	// Transfer cell values from wave into y and n
	y.transfer(wave.distance());

	n.transfer(wave.cellData());

	// Transfer values on patches into boundaryField of y and n
	volScalarField::Boundary& ybf = y.boundaryFieldRef();

	forAll(ybf, patchi)
	{
		scalarField& waveFld = wave.patchDistance()[patchi];

		if (!isA<emptyFvPatchScalarField>(ybf[patchi]))
		{
			ybf[patchi].transfer(waveFld);

			vectorField& wavePatchData = wave.patchData()[patchi];

			nbf[patchi].transfer(wavePatchData);
		}
	}

	// Transfer number of unset values
	nUnset_ = wave.nUnset();

	return nUnset_ > 0;
}


// ************************************************************************* //