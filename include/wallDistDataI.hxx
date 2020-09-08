#pragma once
#include <patchDataWave.hxx>
#include <wallPolyPatch.hxx>
#include <emptyFvPatchFields.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class TransferType>
tnbLib::wallDistData<TransferType>::wallDistData
(
	const tnbLib::fvMesh& mesh,
	GeometricField<Type, fvPatchField, volMesh>& field,
	const bool correctWalls
)
	:
	volScalarField
	(
		IOobject
		(
			"y",
			mesh.time().timeName(),
			mesh
		),
		mesh,
		dimensionedScalar(dimLength, great)
	),
	cellDistFuncs(mesh),
	field_(field),
	correctWalls_(correctWalls),
	nUnset_(0)
{
	correct();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class TransferType>
tnbLib::wallDistData<TransferType>::~wallDistData()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class TransferType>
void tnbLib::wallDistData<TransferType>::correct()
{
	const polyMesh& mesh = cellDistFuncs::mesh();

	//
	// Fill data on wall patches with initial values
	//

	// Get patchids of walls
	labelHashSet wallPatchIDs(getPatchIDs<wallPolyPatch>());

	// Collect pointers to data on patches
	UPtrList<Field<Type>> patchData(mesh.boundaryMesh().size());

	typename GeometricField<Type, fvPatchField, volMesh>::
		Boundary& fieldBf = field_.boundaryFieldRef();

	forAll(fieldBf, patchi)
	{
		patchData.set(patchi, &fieldBf[patchi]);
	}

	// Do mesh wave
	patchDataWave<TransferType> wave
	(
		mesh,
		wallPatchIDs,
		patchData,
		correctWalls_
	);

	// Transfer cell values from wave into *this and field_
	transfer(wave.distance());

	field_.transfer(wave.cellData());

	typename GeometricField<Type, fvPatchField, volMesh>::
		Boundary& bf = boundaryFieldRef();

	// Transfer values on patches into boundaryField of *this and field_
	forAll(bf, patchi)
	{
		scalarField& waveFld = wave.patchDistance()[patchi];

		if (!isA<emptyFvPatchScalarField>(boundaryField()[patchi]))
		{
			bf[patchi].transfer(waveFld);
			Field<Type>& wavePatchData = wave.patchData()[patchi];
			fieldBf[patchi].transfer(wavePatchData);
		}
	}

	// Transfer number of unset values
	nUnset_ = wave.nUnset();
}


// ************************************************************************* //