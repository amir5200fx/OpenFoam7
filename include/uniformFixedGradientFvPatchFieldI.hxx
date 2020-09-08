#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::uniformFixedGradientFvPatchField<Type>::uniformFixedGradientFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	fixedGradientFvPatchField<Type>(p, iF),
	uniformGradient_()
{}


template<class Type>
tnbLib::uniformFixedGradientFvPatchField<Type>::uniformFixedGradientFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const Field<Type>& fld
)
	:
	fixedGradientFvPatchField<Type>(p, iF, fld),
	uniformGradient_()
{}


template<class Type>
tnbLib::uniformFixedGradientFvPatchField<Type>::uniformFixedGradientFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedGradientFvPatchField<Type>(p, iF),
	uniformGradient_(Function1<Type>::New("uniformGradient", dict))
{
	this->evaluate();
}


template<class Type>
tnbLib::uniformFixedGradientFvPatchField<Type>::uniformFixedGradientFvPatchField
(
	const uniformFixedGradientFvPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedGradientFvPatchField<Type>(ptf, p, iF, mapper),
	uniformGradient_(ptf.uniformGradient_, false)
{}


template<class Type>
tnbLib::uniformFixedGradientFvPatchField<Type>::uniformFixedGradientFvPatchField
(
	const uniformFixedGradientFvPatchField<Type>& ptf
)
	:
	fixedGradientFvPatchField<Type>(ptf),
	uniformGradient_(ptf.uniformGradient_, false)
{}


template<class Type>
tnbLib::uniformFixedGradientFvPatchField<Type>::uniformFixedGradientFvPatchField
(
	const uniformFixedGradientFvPatchField<Type>& ptf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	fixedGradientFvPatchField<Type>(ptf, iF),
	uniformGradient_(ptf.uniformGradient_, false)
{
	// Evaluate the profile if defined
	if (ptf.uniformGradient_.valid())
	{
		this->evaluate();
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::uniformFixedGradientFvPatchField<Type>::updateCoeffs()
{
	if (this->updated())
	{
		return;
	}

	const scalar t = this->db().time().timeOutputValue();
	this->gradient() = uniformGradient_->value(t);

	fixedGradientFvPatchField<Type>::updateCoeffs();
}


template<class Type>
void tnbLib::uniformFixedGradientFvPatchField<Type>::write(Ostream& os) const
{
	fixedGradientFvPatchField<Type>::write(os);
	writeEntry(os, uniformGradient_());
	writeEntry(os, "value", *this);
}


// ************************************************************************* //