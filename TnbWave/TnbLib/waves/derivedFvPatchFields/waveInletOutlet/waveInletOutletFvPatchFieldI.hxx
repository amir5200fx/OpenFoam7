#pragma once
#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <levelSet.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <waveSuperposition.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::waveInletOutletFvPatchField<Type>::waveInletOutletFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	mixedFvPatchField<Type>(p, iF),
	inletValueAbove_(),
	inletValueBelow_(),
	phiName_("phi")
{}


template<class Type>
tnbLib::waveInletOutletFvPatchField<Type>::waveInletOutletFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict
)
	:
	mixedFvPatchField<Type>(p, iF),
	inletValueAbove_(Function1<Type>::New("inletValueAbove", dict)),
	inletValueBelow_(Function1<Type>::New("inletValueBelow", dict)),
	phiName_(dict.lookupOrDefault<word>("phi", "phi"))
{
	if (dict.found("value"))
	{
		fvPatchField<Type>::operator=(Field<Type>("value", dict, p.size()));
	}
	else
	{
		fvPatchField<Type>::operator=(this->patchInternalField());
	}

	this->refValue() = Zero;
	this->refGrad() = Zero;
	this->valueFraction() = Zero;
}


template<class Type>
tnbLib::waveInletOutletFvPatchField<Type>::waveInletOutletFvPatchField
(
	const waveInletOutletFvPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	mixedFvPatchField<Type>(ptf, p, iF, mapper),
	inletValueAbove_(ptf.inletValueAbove_, false),
	inletValueBelow_(ptf.inletValueBelow_, false),
	phiName_(ptf.phiName_)
{}


template<class Type>
tnbLib::waveInletOutletFvPatchField<Type>::waveInletOutletFvPatchField
(
	const waveInletOutletFvPatchField<Type>& ptf
)
	:
	mixedFvPatchField<Type>(ptf),
	inletValueAbove_(ptf.inletValueAbove_, false),
	inletValueBelow_(ptf.inletValueBelow_, false),
	phiName_(ptf.phiName_)
{}


template<class Type>
tnbLib::waveInletOutletFvPatchField<Type>::waveInletOutletFvPatchField
(
	const waveInletOutletFvPatchField<Type>& ptf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	mixedFvPatchField<Type>(ptf, iF),
	inletValueAbove_(ptf.inletValueAbove_, false),
	inletValueBelow_(ptf.inletValueBelow_, false),
	phiName_(ptf.phiName_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::waveInletOutletFvPatchField<Type>::updateCoeffs()
{
	if (this->updated())
	{
		return;
	}

	const Field<scalar>& phip =
		this->patch().template lookupPatchField<surfaceScalarField, scalar>
		(
			phiName_
			);

	const scalar t = this->db().time().timeOutputValue();
	const waveSuperposition& waves = waveSuperposition::New(this->db());

	const pointField& localPoints = this->patch().patch().localPoints();

	this->refValue() =
		levelSetAverage
		(
			this->patch(),
			waves.height(t, this->patch().Cf()),
			waves.height(t, localPoints),
			Field<Type>(this->size(), inletValueAbove_->value(t)),
			Field<Type>(localPoints.size(), inletValueAbove_->value(t)),
			Field<Type>(this->size(), inletValueBelow_->value(t)),
			Field<Type>(localPoints.size(), inletValueBelow_->value(t))
		);

	this->valueFraction() = 1 - pos0(phip);

	mixedFvPatchField<Type>::updateCoeffs();
}


template<class Type>
void tnbLib::waveInletOutletFvPatchField<Type>::write(Ostream& os) const
{
	fvPatchField<Type>::write(os);
	writeEntry(os, inletValueAbove_());
	writeEntry(os, inletValueBelow_());
	writeEntryIfDifferent<word>(os, "phi", "phi", phiName_);
}


// ************************************************************************* //