#pragma once
#include <volFields.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::fixedMeanFvPatchField<Type>::fixedMeanFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	fixedValueFvPatchField<Type>(p, iF),
	meanValue_()
{}


template<class Type>
tnbLib::fixedMeanFvPatchField<Type>::fixedMeanFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchField<Type>(p, iF, dict),
	meanValue_(Function1<Type>::New("meanValue", dict))
{}


template<class Type>
tnbLib::fixedMeanFvPatchField<Type>::fixedMeanFvPatchField
(
	const fixedMeanFvPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchField<Type>(ptf, p, iF, mapper),
	meanValue_(ptf.meanValue_, false)
{}


template<class Type>
tnbLib::fixedMeanFvPatchField<Type>::fixedMeanFvPatchField
(
	const fixedMeanFvPatchField<Type>& ptf
)
	:
	fixedValueFvPatchField<Type>(ptf),
	meanValue_(ptf.meanValue_, false)
{}


template<class Type>
tnbLib::fixedMeanFvPatchField<Type>::fixedMeanFvPatchField
(
	const fixedMeanFvPatchField<Type>& ptf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	fixedValueFvPatchField<Type>(ptf, iF),
	meanValue_(ptf.meanValue_, false)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::fixedMeanFvPatchField<Type>::updateCoeffs()
{
	if (this->updated())
	{
		return;
	}

	const scalar t = this->db().time().timeOutputValue();
	Type meanValue = meanValue_->value(t);

	Field<Type> newValues(this->patchInternalField());

	Type meanValuePsi =
		gSum(this->patch().magSf()*newValues)
		/ gSum(this->patch().magSf());

	if (mag(meanValue) > small && mag(meanValuePsi) / mag(meanValue) > 0.5)
	{
		newValues *= mag(meanValue) / mag(meanValuePsi);
	}
	else
	{
		newValues += (meanValue - meanValuePsi);
	}

	this->operator==(newValues);

	fixedValueFvPatchField<Type>::updateCoeffs();
}


template<class Type>
void tnbLib::fixedMeanFvPatchField<Type>::write(Ostream& os) const
{
	fvPatchField<Type>::write(os);
	writeEntry(os, meanValue_());
	writeEntry(os, "value", *this);
}


// ************************************************************************* //