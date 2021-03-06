#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::uniformFixedValueFvPatchField<Type>::uniformFixedValueFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	fixedValueFvPatchField<Type>(p, iF),
	uniformValue_()
{}


template<class Type>
tnbLib::uniformFixedValueFvPatchField<Type>::uniformFixedValueFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const Field<Type>& fld
)
	:
	fixedValueFvPatchField<Type>(p, iF, fld),
	uniformValue_()
{}


template<class Type>
tnbLib::uniformFixedValueFvPatchField<Type>::uniformFixedValueFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchField<Type>(p, iF, dict, false),
	uniformValue_(Function1<Type>::New("uniformValue", dict))
{
	this->evaluate();
}


template<class Type>
tnbLib::uniformFixedValueFvPatchField<Type>::uniformFixedValueFvPatchField
(
	const uniformFixedValueFvPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchField<Type>(ptf, p, iF, mapper, false), // Don't map
	uniformValue_(ptf.uniformValue_, false)
{
	// Evaluate since value not mapped
	this->evaluate();
}


template<class Type>
tnbLib::uniformFixedValueFvPatchField<Type>::uniformFixedValueFvPatchField
(
	const uniformFixedValueFvPatchField<Type>& ptf
)
	:
	fixedValueFvPatchField<Type>(ptf),
	uniformValue_(ptf.uniformValue_, false)
{}


template<class Type>
tnbLib::uniformFixedValueFvPatchField<Type>::uniformFixedValueFvPatchField
(
	const uniformFixedValueFvPatchField<Type>& ptf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	fixedValueFvPatchField<Type>(ptf, iF),
	uniformValue_(ptf.uniformValue_, false)
{
	// Evaluate the profile if defined
	if (ptf.uniformValue_.valid())
	{
		this->evaluate();
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::uniformFixedValueFvPatchField<Type>::updateCoeffs()
{
	if (this->updated())
	{
		return;
	}

	const scalar t = this->db().time().timeOutputValue();
	fvPatchField<Type>::operator==(uniformValue_->value(t));

	fixedValueFvPatchField<Type>::updateCoeffs();
}


template<class Type>
void tnbLib::uniformFixedValueFvPatchField<Type>::write(Ostream& os) const
{
	fvPatchField<Type>::write(os);
	writeEntry(os, uniformValue_());
	writeEntry(os, "value", *this);
}


// ************************************************************************* //