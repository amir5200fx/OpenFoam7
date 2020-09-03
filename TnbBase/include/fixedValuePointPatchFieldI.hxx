#pragma once
#include <boolList.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::fixedValuePointPatchField<Type>::fixedValuePointPatchField
(
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF
)
	:
	valuePointPatchField<Type>(p, iF)
{}


template<class Type>
tnbLib::fixedValuePointPatchField<Type>::fixedValuePointPatchField
(
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF,
	const dictionary& dict,
	const bool valueRequired
)
	:
	valuePointPatchField<Type>(p, iF, dict, valueRequired)
{}


template<class Type>
tnbLib::fixedValuePointPatchField<Type>::fixedValuePointPatchField
(
	const fixedValuePointPatchField<Type>& ptf,
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF,
	const pointPatchFieldMapper& mapper
)
	:
	valuePointPatchField<Type>(ptf, p, iF, mapper)
{}


template<class Type>
tnbLib::fixedValuePointPatchField<Type>::fixedValuePointPatchField
(
	const fixedValuePointPatchField<Type>& ptf,
	const DimensionedField<Type, pointMesh>& iF
)
	:
	valuePointPatchField<Type>(ptf, iF)
{}


// ************************************************************************* //