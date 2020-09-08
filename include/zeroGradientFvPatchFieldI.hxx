#pragma once
#include <fvPatchFieldMapper.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::zeroGradientFvPatchField<Type>::zeroGradientFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	fvPatchField<Type>(p, iF)
{}


template<class Type>
tnbLib::zeroGradientFvPatchField<Type>::zeroGradientFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict
)
	:
	fvPatchField<Type>(p, iF, dict, false)
{
	fvPatchField<Type>::operator=(this->patchInternalField());
}


template<class Type>
tnbLib::zeroGradientFvPatchField<Type>::zeroGradientFvPatchField
(
	const zeroGradientFvPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fvPatchField<Type>(ptf, p, iF, mapper)
{}


template<class Type>
tnbLib::zeroGradientFvPatchField<Type>::zeroGradientFvPatchField
(
	const zeroGradientFvPatchField& zgpf
)
	:
	fvPatchField<Type>(zgpf)
{}


template<class Type>
tnbLib::zeroGradientFvPatchField<Type>::zeroGradientFvPatchField
(
	const zeroGradientFvPatchField& zgpf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	fvPatchField<Type>(zgpf, iF)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::zeroGradientFvPatchField<Type>::evaluate(const Pstream::commsTypes)
{
	if (!this->updated())
	{
		this->updateCoeffs();
	}

	fvPatchField<Type>::operator==(this->patchInternalField());
	fvPatchField<Type>::evaluate();
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::zeroGradientFvPatchField<Type>::valueInternalCoeffs
(
	const tmp<scalarField>&
) const
{
	return tmp<Field<Type>>
		(
			new Field<Type>(this->size(), pTraits<Type>::one)
			);
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::zeroGradientFvPatchField<Type>::valueBoundaryCoeffs
(
	const tmp<scalarField>&
) const
{
	return tmp<Field<Type>>
		(
			new Field<Type>(this->size(), Zero)
			);
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::zeroGradientFvPatchField<Type>::gradientInternalCoeffs() const
{
	return tmp<Field<Type>>
		(
			new Field<Type>(this->size(), Zero)
			);
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::zeroGradientFvPatchField<Type>::gradientBoundaryCoeffs() const
{
	return tmp<Field<Type>>
		(
			new Field<Type>(this->size(), Zero)
			);
}


// ************************************************************************* //