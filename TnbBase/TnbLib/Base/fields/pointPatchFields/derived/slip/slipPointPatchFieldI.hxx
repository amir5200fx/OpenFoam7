#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::slipPointPatchField<Type>::slipPointPatchField
(
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF
)
	:
	basicSymmetryPointPatchField<Type>(p, iF)
{}


template<class Type>
tnbLib::slipPointPatchField<Type>::slipPointPatchField
(
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF,
	const dictionary& dict
)
	:
	basicSymmetryPointPatchField<Type>(p, iF, dict)
{}


template<class Type>
tnbLib::slipPointPatchField<Type>::slipPointPatchField
(
	const slipPointPatchField<Type>& ptf,
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF,
	const pointPatchFieldMapper& mapper
)
	:
	basicSymmetryPointPatchField<Type>(ptf, p, iF, mapper)
{}


template<class Type>
tnbLib::slipPointPatchField<Type>::slipPointPatchField
(
	const slipPointPatchField<Type>& ptf,
	const DimensionedField<Type, pointMesh>& iF
)
	:
	basicSymmetryPointPatchField<Type>(ptf, iF)
{}


// ************************************************************************* //