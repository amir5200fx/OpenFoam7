#pragma once
#include <volFields.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::mappedFixedValueFvPatchField<Type>::mappedFixedValueFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	fixedValueFvPatchField<Type>(p, iF),
	mappedPatchFieldBase<Type>(this->mapper(p, iF), *this)
{}


template<class Type>
tnbLib::mappedFixedValueFvPatchField<Type>::mappedFixedValueFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchField<Type>(p, iF, dict),
	mappedPatchFieldBase<Type>(this->mapper(p, iF), *this, dict)
{}


template<class Type>
tnbLib::mappedFixedValueFvPatchField<Type>::mappedFixedValueFvPatchField
(
	const mappedFixedValueFvPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchField<Type>(ptf, p, iF, mapper),
	mappedPatchFieldBase<Type>(this->mapper(p, iF), *this, ptf)
{}


template<class Type>
tnbLib::mappedFixedValueFvPatchField<Type>::mappedFixedValueFvPatchField
(
	const mappedFixedValueFvPatchField<Type>& ptf
)
	:
	fixedValueFvPatchField<Type>(ptf),
	mappedPatchFieldBase<Type>(ptf)
{}


template<class Type>
tnbLib::mappedFixedValueFvPatchField<Type>::mappedFixedValueFvPatchField
(
	const mappedFixedValueFvPatchField<Type>& ptf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	fixedValueFvPatchField<Type>(ptf, iF),
	mappedPatchFieldBase<Type>(this->mapper(this->patch(), iF), *this, ptf)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
const tnbLib::mappedPatchBase& tnbLib::mappedFixedValueFvPatchField<Type>::mapper
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
{
	if (!isA<mappedPatchBase>(p.patch()))
	{
		FatalErrorInFunction
			<< "' not type '" << mappedPatchBase::typeName << "'"
			<< "\n    for patch " << p.patch().name()
			<< " of field " << iF.name()
			<< " in file " << iF.objectPath()
			<< exit(FatalError);
	}
	return refCast<const mappedPatchBase>(p.patch());
}


template<class Type>
void tnbLib::mappedFixedValueFvPatchField<Type>::updateCoeffs()
{
	if (this->updated())
	{
		return;
	}

	this->operator==(this->mappedField());

	if (debug)
	{
		Info << "mapped on field:"
			<< this->internalField().name()
			<< " patch:" << this->patch().name()
			<< "  avg:" << gAverage(*this)
			<< "  min:" << gMin(*this)
			<< "  max:" << gMax(*this)
			<< endl;
	}

	fixedValueFvPatchField<Type>::updateCoeffs();
}


template<class Type>
void tnbLib::mappedFixedValueFvPatchField<Type>::write(Ostream& os) const
{
	fvPatchField<Type>::write(os);
	mappedPatchFieldBase<Type>::write(os);
	writeEntry(os, "value", *this);
}


// ************************************************************************* //