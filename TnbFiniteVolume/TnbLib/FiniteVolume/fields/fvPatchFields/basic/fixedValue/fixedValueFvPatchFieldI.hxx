#pragma once
#include <fvPatchFieldMapper.hxx>  // added by amir

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::fixedValueFvPatchField<Type>::fixedValueFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	fvPatchField<Type>(p, iF)
{}


template<class Type>
tnbLib::fixedValueFvPatchField<Type>::fixedValueFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict,
	const bool valueRequired
)
	:
	fvPatchField<Type>(p, iF, dict, valueRequired)
{}


template<class Type>
tnbLib::fixedValueFvPatchField<Type>::fixedValueFvPatchField
(
	const fixedValueFvPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& mapper,
	const bool mappingRequired
)
	:
	fvPatchField<Type>(ptf, p, iF, mapper, mappingRequired)
{
	if (mappingRequired && notNull(iF) && mapper.hasUnmapped())
	{
		WarningInFunction
			<< "On field " << iF.name() << " patch " << p.name()
			<< " patchField " << this->type()
			<< " : mapper does not map all values." << nl
			<< "    To avoid this warning fully specify the mapping in derived"
			<< " patch fields." << endl;
	}
}


template<class Type>
tnbLib::fixedValueFvPatchField<Type>::fixedValueFvPatchField
(
	const fixedValueFvPatchField<Type>& ptf
)
	:
	fvPatchField<Type>(ptf)
{}


template<class Type>
tnbLib::fixedValueFvPatchField<Type>::fixedValueFvPatchField
(
	const fixedValueFvPatchField<Type>& ptf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	fvPatchField<Type>(ptf, iF)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::fixedValueFvPatchField<Type>::valueInternalCoeffs
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
tnbLib::fixedValueFvPatchField<Type>::valueBoundaryCoeffs
(
	const tmp<scalarField>&
) const
{
	return *this;
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::fixedValueFvPatchField<Type>::gradientInternalCoeffs() const
{
	return -pTraits<Type>::one*this->patch().deltaCoeffs();
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::fixedValueFvPatchField<Type>::gradientBoundaryCoeffs() const
{
	return this->patch().deltaCoeffs()*(*this);
}


template<class Type>
void tnbLib::fixedValueFvPatchField<Type>::write(Ostream& os) const
{
	fvPatchField<Type>::write(os);
	writeEntry(os, "value", *this);
}


// ************************************************************************* //