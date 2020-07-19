#include <cyclicSlipFvsPatchField.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::cyclicSlipFvsPatchField<Type>::cyclicSlipFvsPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, surfaceMesh>& iF
)
	:
	cyclicFvsPatchField<Type>(p, iF)
{}


template<class Type>
tnbLib::cyclicSlipFvsPatchField<Type>::cyclicSlipFvsPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, surfaceMesh>& iF,
	const dictionary& dict
)
	:
	cyclicFvsPatchField<Type>(p, iF, dict)
{}


template<class Type>
tnbLib::cyclicSlipFvsPatchField<Type>::cyclicSlipFvsPatchField
(
	const cyclicSlipFvsPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, surfaceMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	cyclicFvsPatchField<Type>(ptf, p, iF, mapper)
{}


template<class Type>
tnbLib::cyclicSlipFvsPatchField<Type>::cyclicSlipFvsPatchField
(
	const cyclicSlipFvsPatchField<Type>& ptf
)
	:
	cyclicFvsPatchField<Type>(ptf)
{}


template<class Type>
tnbLib::cyclicSlipFvsPatchField<Type>::cyclicSlipFvsPatchField
(
	const cyclicSlipFvsPatchField<Type>& ptf,
	const DimensionedField<Type, surfaceMesh>& iF
)
	:
	cyclicFvsPatchField<Type>(ptf, iF)
{}


// ************************************************************************* //