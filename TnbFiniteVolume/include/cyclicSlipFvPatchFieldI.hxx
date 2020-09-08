#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::cyclicSlipFvPatchField<Type>::cyclicSlipFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	cyclicFvPatchField<Type>(p, iF)
{}


template<class Type>
tnbLib::cyclicSlipFvPatchField<Type>::cyclicSlipFvPatchField
(
	const cyclicSlipFvPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	cyclicFvPatchField<Type>(ptf, p, iF, mapper)
{}


template<class Type>
tnbLib::cyclicSlipFvPatchField<Type>::cyclicSlipFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict
)
	:
	cyclicFvPatchField<Type>(p, iF, dict)
{}


template<class Type>
tnbLib::cyclicSlipFvPatchField<Type>::cyclicSlipFvPatchField
(
	const cyclicSlipFvPatchField<Type>& ptf
)
	:
	cyclicFvPatchField<Type>(ptf)
{}


template<class Type>
tnbLib::cyclicSlipFvPatchField<Type>::cyclicSlipFvPatchField
(
	const cyclicSlipFvPatchField<Type>& ptf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	cyclicFvPatchField<Type>(ptf, iF)
{}


// ************************************************************************* //