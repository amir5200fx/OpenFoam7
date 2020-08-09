#include <turbulentMixingLengthFrequencyInletFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <surfaceFields.hxx>
#include <volFields.hxx>
#include <turbulenceModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	turbulentMixingLengthFrequencyInletFvPatchScalarField::
		turbulentMixingLengthFrequencyInletFvPatchScalarField
		(
			const fvPatch& p,
			const DimensionedField<scalar, volMesh>& iF
		)
		:
		inletOutletFvPatchScalarField(p, iF),
		mixingLength_(0.0),
		kName_("undefined-k")
	{
		this->refValue() = 0.0;
		this->refGrad() = 0.0;
		this->valueFraction() = 0.0;
	}

	turbulentMixingLengthFrequencyInletFvPatchScalarField::
		turbulentMixingLengthFrequencyInletFvPatchScalarField
		(
			const turbulentMixingLengthFrequencyInletFvPatchScalarField& ptf,
			const fvPatch& p,
			const DimensionedField<scalar, volMesh>& iF,
			const fvPatchFieldMapper& mapper
		)
		:
		inletOutletFvPatchScalarField(ptf, p, iF, mapper),
		mixingLength_(ptf.mixingLength_),
		kName_(ptf.kName_)
	{}

	turbulentMixingLengthFrequencyInletFvPatchScalarField::
		turbulentMixingLengthFrequencyInletFvPatchScalarField
		(
			const fvPatch& p,
			const DimensionedField<scalar, volMesh>& iF,
			const dictionary& dict
		)
		:
		inletOutletFvPatchScalarField(p, iF),
		mixingLength_(readScalar(dict.lookup("mixingLength"))),
		kName_(dict.lookupOrDefault<word>("k", "k"))
	{
		this->phiName_ = dict.lookupOrDefault<word>("phi", "phi");

		fvPatchScalarField::operator=(scalarField("value", dict, p.size()));

		this->refValue() = 0.0;
		this->refGrad() = 0.0;
		this->valueFraction() = 0.0;
	}

	turbulentMixingLengthFrequencyInletFvPatchScalarField::
		turbulentMixingLengthFrequencyInletFvPatchScalarField
		(
			const turbulentMixingLengthFrequencyInletFvPatchScalarField& ptf
		)
		:
		inletOutletFvPatchScalarField(ptf),
		mixingLength_(ptf.mixingLength_),
		kName_(ptf.kName_)
	{}

	turbulentMixingLengthFrequencyInletFvPatchScalarField::
		turbulentMixingLengthFrequencyInletFvPatchScalarField
		(
			const turbulentMixingLengthFrequencyInletFvPatchScalarField& ptf,
			const DimensionedField<scalar, volMesh>& iF
		)
		:
		inletOutletFvPatchScalarField(ptf, iF),
		mixingLength_(ptf.mixingLength_),
		kName_(ptf.kName_)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	void turbulentMixingLengthFrequencyInletFvPatchScalarField::updateCoeffs()
	{
		if (updated())
		{
			return;
		}

		// Lookup Cmu corresponding to the turbulence model selected
		const turbulenceModel& turbModel = db().lookupObject<turbulenceModel>
			(
				IOobject::groupName
				(
					turbulenceModel::propertiesName,
					internalField().group()
				)
				);

		const scalar Cmu =
			turbModel.coeffDict().lookupOrDefault<scalar>("Cmu", 0.09);

		const scalar Cmu25 = pow(Cmu, 0.25);

		const fvPatchScalarField& kp =
			patch().lookupPatchField<volScalarField, scalar>(kName_);

		const fvsPatchScalarField& phip =
			patch().lookupPatchField<surfaceScalarField, scalar>(this->phiName_);

		this->refValue() = sqrt(kp) / (Cmu25*mixingLength_);
		this->valueFraction() = 1.0 - pos0(phip);

		inletOutletFvPatchScalarField::updateCoeffs();
	}


	void turbulentMixingLengthFrequencyInletFvPatchScalarField::write
	(
		Ostream& os
	) const
	{
		fvPatchScalarField::write(os);
		writeEntry(os, "mixingLength", mixingLength_);
		writeEntry(os, "phi", this->phiName_);
		writeEntry(os, "k", kName_);
		writeEntry(os, "value", *this);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	makePatchTypeField
	(
		fvPatchScalarField,
		turbulentMixingLengthFrequencyInletFvPatchScalarField
	);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //