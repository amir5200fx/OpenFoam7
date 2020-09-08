#include <fixedJumpFvPatchField.hxx>

#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::fixedJumpFvPatchField<Type>::fixedJumpFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	jumpCyclicFvPatchField<Type>(p, iF),
	jump_(this->size(), Zero)
{}


template<class Type>
tnbLib::fixedJumpFvPatchField<Type>::fixedJumpFvPatchField
(
	const fixedJumpFvPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	jumpCyclicFvPatchField<Type>(ptf, p, iF, mapper),
	jump_(mapper(ptf.jump_))
{}


template<class Type>
tnbLib::fixedJumpFvPatchField<Type>::fixedJumpFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict
)
	:
	jumpCyclicFvPatchField<Type>(p, iF),
	jump_(p.size(), Zero)
{
	if (this->cyclicPatch().owner())
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
tnbLib::fixedJumpFvPatchField<Type>::fixedJumpFvPatchField
(
	const fixedJumpFvPatchField<Type>& ptf
)
	:
	jumpCyclicFvPatchField<Type>(ptf),
	jump_(ptf.jump_)
{}


template<class Type>
tnbLib::fixedJumpFvPatchField<Type>::fixedJumpFvPatchField
(
	const fixedJumpFvPatchField<Type>& ptf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	jumpCyclicFvPatchField<Type>(ptf, iF),
	jump_(ptf.jump_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::Field<Type>> tnbLib::fixedJumpFvPatchField<Type>::jump() const
{
	if (this->cyclicPatch().owner())
	{
		return jump_;
	}
	else
	{
		return refCast<const fixedJumpFvPatchField<Type>>
			(
				this->neighbourPatchField()
				).jump();
	}
}


template<class Type>
void tnbLib::fixedJumpFvPatchField<Type>::autoMap
(
	const fvPatchFieldMapper& m
)
{
	jumpCyclicFvPatchField<Type>::autoMap(m);
	m(jump_, jump_);
}


template<class Type>
void tnbLib::fixedJumpFvPatchField<Type>::rmap
(
	const fvPatchField<Type>& ptf,
	const labelList& addr
)
{
	jumpCyclicFvPatchField<Type>::rmap(ptf, addr);

	const fixedJumpFvPatchField<Type>& tiptf =
		refCast<const fixedJumpFvPatchField<Type>>(ptf);
	jump_.rmap(tiptf.jump_, addr);
}


template<class Type>
void tnbLib::fixedJumpFvPatchField<Type>::write(Ostream& os) const
{
	fvPatchField<Type>::write(os);
	writeEntry(os, "patchType", this->interfaceFieldType());

	if (this->cyclicPatch().owner())
	{
		writeEntry(os, "jump", jump_);
	}

	writeEntry(os, "value", *this);
}


// ************************************************************************* //