#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::zeroGradientPointPatchField<Type>::zeroGradientPointPatchField
(
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF
)
	:
	pointPatchField<Type>(p, iF)
{}


template<class Type>
tnbLib::zeroGradientPointPatchField<Type>::zeroGradientPointPatchField
(
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF,
	const dictionary& dict
)
	:
	pointPatchField<Type>(p, iF, dict)
{}


template<class Type>
tnbLib::zeroGradientPointPatchField<Type>::zeroGradientPointPatchField
(
	const zeroGradientPointPatchField<Type>& ptf,
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF,
	const pointPatchFieldMapper& mapper
)
	:
	pointPatchField<Type>(ptf, p, iF, mapper)
{}


template<class Type>
tnbLib::zeroGradientPointPatchField<Type>::zeroGradientPointPatchField
(
	const zeroGradientPointPatchField<Type>& ptf,
	const DimensionedField<Type, pointMesh>& iF
)
	:
	pointPatchField<Type>(ptf, iF)
{}


// ************************************************************************* //