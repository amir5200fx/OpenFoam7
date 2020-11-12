#pragma once

// .cxx

// * * * * * * * * * * * * * * * * Constructors * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::zeroFixedValuePointPatchField<Type>::
zeroFixedValuePointPatchField
(
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF
)
	:
	fixedValuePointPatchField<Type>(p, iF)
{}


template<class Type>
tnbLib::zeroFixedValuePointPatchField<Type>::
zeroFixedValuePointPatchField
(
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF,
	const dictionary& dict
)
	:
	fixedValuePointPatchField<Type>(p, iF, dict, false)
{
	fixedValuePointPatchField<Type>::operator=(Zero);
}


template<class Type>
tnbLib::zeroFixedValuePointPatchField<Type>::
zeroFixedValuePointPatchField
(
	const zeroFixedValuePointPatchField<Type>& ptf,
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF,
	const pointPatchFieldMapper& mapper
)
	:
	fixedValuePointPatchField<Type>(ptf, p, iF, mapper)
{
	// For safety re-evaluate
	fixedValuePointPatchField<Type>::operator=(Zero);
}


template<class Type>
tnbLib::zeroFixedValuePointPatchField<Type>::
zeroFixedValuePointPatchField
(
	const zeroFixedValuePointPatchField<Type>& ptf
)
	:
	fixedValuePointPatchField<Type>(ptf)
{}


template<class Type>
tnbLib::zeroFixedValuePointPatchField<Type>::
zeroFixedValuePointPatchField
(
	const zeroFixedValuePointPatchField<Type>& ptf,
	const DimensionedField<Type, pointMesh>& iF
)
	:
	fixedValuePointPatchField<Type>(ptf, iF)
{
	// For safety re-evaluate
	fixedValuePointPatchField<Type>::operator=(Zero);
}


// ************************************************************************* //