#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::fixedValueFvsPatchField<Type>::fixedValueFvsPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, surfaceMesh>& iF
)
	:
	fvsPatchField<Type>(p, iF)
{}


template<class Type>
tnbLib::fixedValueFvsPatchField<Type>::fixedValueFvsPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, surfaceMesh>& iF,
	const dictionary& dict
)
	:
	fvsPatchField<Type>(p, iF, Field<Type>("value", dict, p.size()))
{}


template<class Type>
tnbLib::fixedValueFvsPatchField<Type>::fixedValueFvsPatchField
(
	const fixedValueFvsPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, surfaceMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fvsPatchField<Type>(ptf, p, iF, mapper)
{}


template<class Type>
tnbLib::fixedValueFvsPatchField<Type>::fixedValueFvsPatchField
(
	const fixedValueFvsPatchField<Type>& ptf
)
	:
	fvsPatchField<Type>(ptf)
{}


template<class Type>
tnbLib::fixedValueFvsPatchField<Type>::fixedValueFvsPatchField
(
	const fixedValueFvsPatchField<Type>& ptf,
	const DimensionedField<Type, surfaceMesh>& iF
)
	:
	fvsPatchField<Type>(ptf, iF)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::fixedValueFvsPatchField<Type>::valueInternalCoeffs
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
tnbLib::fixedValueFvsPatchField<Type>::valueBoundaryCoeffs
(
	const tmp<scalarField>&
) const
{
	return *this;
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::fixedValueFvsPatchField<Type>::gradientInternalCoeffs() const
{
	return -pTraits<Type>::one*this->patch().deltaCoeffs();
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::fixedValueFvsPatchField<Type>::gradientBoundaryCoeffs() const
{
	return this->patch().deltaCoeffs()*(*this);
}


// ************************************************************************* //