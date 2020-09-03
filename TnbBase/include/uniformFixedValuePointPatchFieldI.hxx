#pragma once
// * * * * * * * * * * * * * * * * Constructors * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::uniformFixedValuePointPatchField<Type>::
uniformFixedValuePointPatchField
(
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF
)
	:
	fixedValuePointPatchField<Type>(p, iF),
	uniformValue_()
{}


template<class Type>
tnbLib::uniformFixedValuePointPatchField<Type>::
uniformFixedValuePointPatchField
(
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF,
	const dictionary& dict
)
	:
	fixedValuePointPatchField<Type>(p, iF, dict, false),
	uniformValue_(Function1<Type>::New("uniformValue", dict))
{
	if (dict.found("value"))
	{
		fixedValuePointPatchField<Type>::operator==
			(
				Field<Type>("value", dict, p.size())
				);
	}
	else
	{
		const scalar t = this->db().time().timeOutputValue();
		fixedValuePointPatchField<Type>::operator=(uniformValue_->value(t));
	}
}


template<class Type>
tnbLib::uniformFixedValuePointPatchField<Type>::
uniformFixedValuePointPatchField
(
	const uniformFixedValuePointPatchField<Type>& ptf,
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF,
	const pointPatchFieldMapper& mapper
)
	:
	fixedValuePointPatchField<Type>(ptf, p, iF, mapper),
	uniformValue_(ptf.uniformValue_, false)
{
	// For safety re-evaluate
	const scalar t = this->db().time().timeOutputValue();
	fixedValuePointPatchField<Type>::operator=(uniformValue_->value(t));
}


template<class Type>
tnbLib::uniformFixedValuePointPatchField<Type>::
uniformFixedValuePointPatchField
(
	const uniformFixedValuePointPatchField<Type>& ptf
)
	:
	fixedValuePointPatchField<Type>(ptf),
	uniformValue_(ptf.uniformValue_, false)
{}


template<class Type>
tnbLib::uniformFixedValuePointPatchField<Type>::
uniformFixedValuePointPatchField
(
	const uniformFixedValuePointPatchField<Type>& ptf,
	const DimensionedField<Type, pointMesh>& iF
)
	:
	fixedValuePointPatchField<Type>(ptf, iF),
	uniformValue_(ptf.uniformValue_, false)
{
	// For safety re-evaluate
	const scalar t = this->db().time().timeOutputValue();
	fixedValuePointPatchField<Type>::operator==(uniformValue_->value(t));
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::uniformFixedValuePointPatchField<Type>::updateCoeffs()
{
	if (this->updated())
	{
		return;
	}

	const scalar t = this->db().time().timeOutputValue();
	fixedValuePointPatchField<Type>::operator==(uniformValue_->value(t));

	fixedValuePointPatchField<Type>::updateCoeffs();
}


template<class Type>
void tnbLib::uniformFixedValuePointPatchField<Type>::
write(Ostream& os) const
{
	// Note: write value
	fixedValuePointPatchField<Type>::write(os);
	writeEntry(os, uniformValue_());
}


// ************************************************************************* //