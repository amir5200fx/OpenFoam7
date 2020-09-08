#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::uniformJumpAMIFvPatchField<Type>::uniformJumpAMIFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	fixedJumpAMIFvPatchField<Type>(p, iF),
	jumpTable_()
{}


template<class Type>
tnbLib::uniformJumpAMIFvPatchField<Type>::uniformJumpAMIFvPatchField
(
	const uniformJumpAMIFvPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedJumpAMIFvPatchField<Type>(ptf, p, iF, mapper),
	jumpTable_(ptf.jumpTable_, false)
{}


template<class Type>
tnbLib::uniformJumpAMIFvPatchField<Type>::uniformJumpAMIFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedJumpAMIFvPatchField<Type>(p, iF),
	jumpTable_()
{
	if (this->cyclicAMIPatch().owner())
	{
		jumpTable_ = Function1<Type>::New("jumpTable", dict);
	}

	if (dict.found("value"))
	{
		fvPatchField<Type>::operator=(Field<Type>("value", dict, p.size()));
	}
	else
	{
		this->evaluate(Pstream::commsTypes::blocking);
	}
}


template<class Type>
tnbLib::uniformJumpAMIFvPatchField<Type>::uniformJumpAMIFvPatchField
(
	const uniformJumpAMIFvPatchField<Type>& ptf
)
	:
	fixedJumpAMIFvPatchField<Type>(ptf),
	jumpTable_(ptf.jumpTable_, false)
{}


template<class Type>
tnbLib::uniformJumpAMIFvPatchField<Type>::uniformJumpAMIFvPatchField
(
	const uniformJumpAMIFvPatchField<Type>& ptf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	fixedJumpAMIFvPatchField<Type>(ptf, iF),
	jumpTable_(ptf.jumpTable_, false)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::uniformJumpAMIFvPatchField<Type>::updateCoeffs()
{
	if (this->updated())
	{
		return;
	}

	if (this->cyclicAMIPatch().owner())
	{
		this->jump_ = jumpTable_->value(this->db().time().value());
	}

	fixedJumpAMIFvPatchField<Type>::updateCoeffs();
}


template<class Type>
void tnbLib::uniformJumpAMIFvPatchField<Type>::write(Ostream& os) const
{
	fixedJumpAMIFvPatchField<Type>::write(os);
	if (this->cyclicAMIPatch().owner())
	{
		writeEntry(os, jumpTable_());
	}
}


// ************************************************************************* //