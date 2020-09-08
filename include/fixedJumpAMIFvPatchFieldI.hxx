#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::fixedJumpAMIFvPatchField<Type>::fixedJumpAMIFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	jumpCyclicAMIFvPatchField<Type>(p, iF),
	jump_(this->size(), Zero)
{}


template<class Type>
tnbLib::fixedJumpAMIFvPatchField<Type>::fixedJumpAMIFvPatchField
(
	const fixedJumpAMIFvPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	jumpCyclicAMIFvPatchField<Type>(ptf, p, iF, mapper),
	jump_(mapper(ptf.jump_))
{}


template<class Type>
tnbLib::fixedJumpAMIFvPatchField<Type>::fixedJumpAMIFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict
)
	:
	jumpCyclicAMIFvPatchField<Type>(p, iF),
	jump_(p.size(), Zero)
{
	if (this->cyclicAMIPatch().owner())
	{
		jump_ = Field<Type>("jump", dict, p.size());
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
tnbLib::fixedJumpAMIFvPatchField<Type>::fixedJumpAMIFvPatchField
(
	const fixedJumpAMIFvPatchField<Type>& ptf
)
	:
	jumpCyclicAMIFvPatchField<Type>(ptf),
	jump_(ptf.jump_)
{}


template<class Type>
tnbLib::fixedJumpAMIFvPatchField<Type>::fixedJumpAMIFvPatchField
(
	const fixedJumpAMIFvPatchField<Type>& ptf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	jumpCyclicAMIFvPatchField<Type>(ptf, iF),
	jump_(ptf.jump_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::Field<Type>> tnbLib::fixedJumpAMIFvPatchField<Type>::jump() const
{
	if (this->cyclicAMIPatch().owner())
	{
		return jump_;
	}
	else
	{
		const fixedJumpAMIFvPatchField& nbrPatch =
			refCast<const fixedJumpAMIFvPatchField<Type>>
			(
				this->neighbourPatchField()
				);

		if (this->cyclicAMIPatch().applyLowWeightCorrection())
		{
			return this->cyclicAMIPatch().interpolate
			(
				nbrPatch.jump(),
				Field<Type>(this->size(), Zero)
			);
		}
		else
		{
			return this->cyclicAMIPatch().interpolate(nbrPatch.jump());
		}
	}
}


template<class Type>
void tnbLib::fixedJumpAMIFvPatchField<Type>::autoMap
(
	const fvPatchFieldMapper& m
)
{
	jumpCyclicAMIFvPatchField<Type>::autoMap(m);
	m(jump_, jump_);
}


template<class Type>
void tnbLib::fixedJumpAMIFvPatchField<Type>::rmap
(
	const fvPatchField<Type>& ptf,
	const labelList& addr
)
{
	jumpCyclicAMIFvPatchField<Type>::rmap(ptf, addr);

	const fixedJumpAMIFvPatchField<Type>& tiptf =
		refCast<const fixedJumpAMIFvPatchField<Type>>(ptf);
	jump_.rmap(tiptf.jump_, addr);
}


template<class Type>
void tnbLib::fixedJumpAMIFvPatchField<Type>::write(Ostream& os) const
{
	fvPatchField<Type>::write(os);
	writeEntry(os, "patchType", this->interfaceFieldType());

	if (this->cyclicAMIPatch().owner())
	{
		writeEntry(os, "jump", jump_);
	}

	writeEntry(os, "value", *this);
}


// ************************************************************************* //