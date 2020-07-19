#include <coupledFvsPatchField.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::coupledFvsPatchField<Type>::coupledFvsPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, surfaceMesh>& iF
)
	:
	fvsPatchField<Type>(p, iF)
{}


template<class Type>
tnbLib::coupledFvsPatchField<Type>::coupledFvsPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, surfaceMesh>& iF,
	const Field<Type>& f
)
	:
	fvsPatchField<Type>(p, iF, f)
{}


template<class Type>
tnbLib::coupledFvsPatchField<Type>::coupledFvsPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, surfaceMesh>& iF,
	const dictionary& dict
)
	:
	fvsPatchField<Type>(p, iF, dict)
{}


template<class Type>
tnbLib::coupledFvsPatchField<Type>::coupledFvsPatchField
(
	const coupledFvsPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, surfaceMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fvsPatchField<Type>(ptf, p, iF, mapper)
{}


template<class Type>
tnbLib::coupledFvsPatchField<Type>::coupledFvsPatchField
(
	const coupledFvsPatchField<Type>& ptf
)
	:
	fvsPatchField<Type>(ptf)
{}


template<class Type>
tnbLib::coupledFvsPatchField<Type>::coupledFvsPatchField
(
	const coupledFvsPatchField<Type>& ptf,
	const DimensionedField<Type, surfaceMesh>& iF
)
	:
	fvsPatchField<Type>(ptf, iF)
{}


// ************************************************************************* //