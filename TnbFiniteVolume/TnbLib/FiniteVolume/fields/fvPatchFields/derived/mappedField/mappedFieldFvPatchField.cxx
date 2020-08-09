#include <mappedFieldFvPatchField.hxx>

#include <volFields.hxx>
#include <interpolationCell.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::mappedFieldFvPatchField<Type>::mappedFieldFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	fixedValueFvPatchField<Type>(p, iF),
	mappedPatchBase(p.patch()),
	mappedPatchFieldBase<Type>(*this, *this)
{}


template<class Type>
tnbLib::mappedFieldFvPatchField<Type>::mappedFieldFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchField<Type>(p, iF, dict),
	mappedPatchBase(p.patch(), dict),
	mappedPatchFieldBase<Type>(*this, *this, dict)
{}


template<class Type>
tnbLib::mappedFieldFvPatchField<Type>::mappedFieldFvPatchField
(
	const mappedFieldFvPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchField<Type>(ptf, p, iF, mapper),
	mappedPatchBase(p.patch(), ptf),
	mappedPatchFieldBase<Type>(*this, *this, ptf)
{}


template<class Type>
tnbLib::mappedFieldFvPatchField<Type>::mappedFieldFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,

	// mappedPatchBase
	const word& sampleRegion,
	const sampleMode sampleMode,
	const word& samplePatch,
	const scalar distance,

	// My settings
	const word& fieldName,
	const bool setAverage,
	const Type average,
	const word& interpolationScheme
)
	:
	fixedValueFvPatchField<Type>(p, iF),
	mappedPatchBase
	(
		p.patch(),
		sampleRegion,
		sampleMode,
		samplePatch,
		distance
	),
	mappedPatchFieldBase<Type>
	(
		*this,
		*this,
		fieldName,
		setAverage,
		average,
		interpolationScheme
		)
{}


template<class Type>
tnbLib::mappedFieldFvPatchField<Type>::mappedFieldFvPatchField
(
	const mappedFieldFvPatchField<Type>& ptf
)
	:
	fixedValueFvPatchField<Type>(ptf),
	mappedPatchBase(ptf.patch().patch(), ptf),
	mappedPatchFieldBase<Type>(ptf)
{}


template<class Type>
tnbLib::mappedFieldFvPatchField<Type>::mappedFieldFvPatchField
(
	const mappedFieldFvPatchField<Type>& ptf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	fixedValueFvPatchField<Type>(ptf, iF),
	mappedPatchBase(ptf.patch().patch(), ptf),
	mappedPatchFieldBase<Type>(*this, *this, ptf)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::mappedFieldFvPatchField<Type>::autoMap
(
	const fvPatchFieldMapper& m
)
{
	fixedValueFvPatchField<Type>::autoMap(m);
	mappedPatchBase::clearOut();
}


template<class Type>
void tnbLib::mappedFieldFvPatchField<Type>::rmap
(
	const fvPatchField<Type>& ptf,
	const labelList& addr
)
{
	fixedValueFvPatchField<Type>::rmap(ptf, addr);
	mappedPatchBase::clearOut();
}


template<class Type>
void tnbLib::mappedFieldFvPatchField<Type>::updateCoeffs()
{
	if (this->updated())
	{
		return;
	}

	this->operator==(this->mappedField());

	if (debug)
	{
		Info << "operating on field:" << this->internalField().name()
			<< " patch:" << this->patch().name()
			<< "  avg:" << gAverage(*this)
			<< "  min:" << gMin(*this)
			<< "  max:" << gMax(*this)
			<< endl;
	}

	fixedValueFvPatchField<Type>::updateCoeffs();
}


template<class Type>
void tnbLib::mappedFieldFvPatchField<Type>::write(Ostream& os) const
{
	fvPatchField<Type>::write(os);
	mappedPatchBase::write(os);
	mappedPatchFieldBase<Type>::write(os);
	writeEntry(os, "value", *this);
}


// ************************************************************************* //