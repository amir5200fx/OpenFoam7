#pragma once
#include <fvPatchFieldMapper.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::extrapolatedCalculatedFvPatchField<Type>::
extrapolatedCalculatedFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	calculatedFvPatchField<Type>(p, iF)
{}


template<class Type>
tnbLib::extrapolatedCalculatedFvPatchField<Type>::
extrapolatedCalculatedFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict
)
	:
	calculatedFvPatchField<Type>(p, iF, dict, false)
{
	evaluate();
}


template<class Type>
tnbLib::extrapolatedCalculatedFvPatchField<Type>::
extrapolatedCalculatedFvPatchField
(
	const extrapolatedCalculatedFvPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	calculatedFvPatchField<Type>(ptf, p, iF, mapper)
{}


template<class Type>
tnbLib::extrapolatedCalculatedFvPatchField<Type>::
extrapolatedCalculatedFvPatchField
(
	const extrapolatedCalculatedFvPatchField<Type>& ptf
)
	:
	calculatedFvPatchField<Type>(ptf)
{}


template<class Type>
tnbLib::extrapolatedCalculatedFvPatchField<Type>::
extrapolatedCalculatedFvPatchField
(
	const extrapolatedCalculatedFvPatchField<Type>& ptf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	calculatedFvPatchField<Type>(ptf, iF)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::extrapolatedCalculatedFvPatchField<Type>::evaluate
(
	const Pstream::commsTypes
)
{
	if (!this->updated())
	{
		this->updateCoeffs();
	}

	calculatedFvPatchField<Type>::operator==(this->patchInternalField());
	calculatedFvPatchField<Type>::evaluate();
}


// ************************************************************************* //