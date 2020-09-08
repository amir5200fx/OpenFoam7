#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::uniformJumpFvPatchField<Type>::uniformJumpFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	fixedJumpFvPatchField<Type>(p, iF),
	jumpTable_()
{}


template<class Type>
tnbLib::uniformJumpFvPatchField<Type>::uniformJumpFvPatchField
(
	const uniformJumpFvPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedJumpFvPatchField<Type>(ptf, p, iF, mapper),
	jumpTable_(ptf.jumpTable_, false)
{}


template<class Type>
tnbLib::uniformJumpFvPatchField<Type>::uniformJumpFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedJumpFvPatchField<Type>(p, iF),
	jumpTable_()
{
	if (this->cyclicPatch().owner())
	{
		jumpTable_ = Function1<Type>::New("jumpTable", dict);
	}

	if (dict.found("value"))
	{
		fvPatchField<Type>::operator=
			(
				Field<Type>("value", dict, p.size())
				);
	}
	else
	{
		this->evaluate(Pstream::commsTypes::blocking);
	}
}


template<class Type>
tnbLib::uniformJumpFvPatchField<Type>::uniformJumpFvPatchField
(
	const uniformJumpFvPatchField<Type>& ptf
)
	:
	fixedJumpFvPatchField<Type>(ptf),
	jumpTable_(ptf.jumpTable_, false)
{}


template<class Type>
tnbLib::uniformJumpFvPatchField<Type>::uniformJumpFvPatchField
(
	const uniformJumpFvPatchField<Type>& ptf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	fixedJumpFvPatchField<Type>(ptf, iF),
	jumpTable_(ptf.jumpTable_, false)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::uniformJumpFvPatchField<Type>::updateCoeffs()
{
	if (this->updated())
	{
		return;
	}

	if (this->cyclicPatch().owner())
	{
		this->jump_ = jumpTable_->value(this->db().time().value());
	}

	fixedJumpFvPatchField<Type>::updateCoeffs();
}


template<class Type>
void tnbLib::uniformJumpFvPatchField<Type>::write(Ostream& os) const
{
	fixedJumpFvPatchField<Type>::write(os);
	if (this->cyclicPatch().owner())
	{
		writeEntry(os, jumpTable_());
	}
}


// ************************************************************************* //