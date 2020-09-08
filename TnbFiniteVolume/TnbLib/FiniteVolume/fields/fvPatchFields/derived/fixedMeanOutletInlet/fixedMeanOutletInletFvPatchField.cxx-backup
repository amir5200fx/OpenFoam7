#include <fixedMeanOutletInletFvPatchField.hxx>

#include <volFields.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::fixedMeanOutletInletFvPatchField<Type>::fixedMeanOutletInletFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	outletInletFvPatchField<Type>(p, iF),
	meanValue_()
{}


template<class Type>
tnbLib::fixedMeanOutletInletFvPatchField<Type>::fixedMeanOutletInletFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict
)
	:
	outletInletFvPatchField<Type>(p, iF),
	meanValue_(Function1<Type>::New("meanValue", dict))
{
	this->phiName_ = dict.lookupOrDefault<word>("phi", "phi");

	fvPatchField<Type>::operator=
		(
			Field<Type>("value", dict, p.size())
			);

	this->refValue() = *this;
	this->refGrad() = Zero;
	this->valueFraction() = 0.0;
}


template<class Type>
tnbLib::fixedMeanOutletInletFvPatchField<Type>::fixedMeanOutletInletFvPatchField
(
	const fixedMeanOutletInletFvPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	outletInletFvPatchField<Type>(ptf, p, iF, mapper),
	meanValue_(ptf.meanValue_, false)
{}


template<class Type>
tnbLib::fixedMeanOutletInletFvPatchField<Type>::fixedMeanOutletInletFvPatchField
(
	const fixedMeanOutletInletFvPatchField<Type>& ptf
)
	:
	outletInletFvPatchField<Type>(ptf),
	meanValue_(ptf.meanValue_, false)
{}


template<class Type>
tnbLib::fixedMeanOutletInletFvPatchField<Type>::fixedMeanOutletInletFvPatchField
(
	const fixedMeanOutletInletFvPatchField<Type>& ptf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	outletInletFvPatchField<Type>(ptf, iF),
	meanValue_(ptf.meanValue_, false)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::fixedMeanOutletInletFvPatchField<Type>::updateCoeffs()
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

	this->refValue() = newValues;

	outletInletFvPatchField<Type>::updateCoeffs();
}


template<class Type>
void tnbLib::fixedMeanOutletInletFvPatchField<Type>::write(Ostream& os) const
{
	fvPatchField<Type>::write(os);
	writeEntry(os, meanValue_());
	writeEntry(os, "value", *this);
}


// ************************************************************************* //