#include <turbulentIntensityKineticEnergyInletFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <surfaceFields.hxx>
#include <volFields.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::turbulentIntensityKineticEnergyInletFvPatchScalarField::
turbulentIntensityKineticEnergyInletFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	inletOutletFvPatchScalarField(p, iF),
	intensity_(0.0),
	UName_("U")
{
	this->refValue() = 0.0;
	this->refGrad() = 0.0;
	this->valueFraction() = 0.0;
}

tnbLib::turbulentIntensityKineticEnergyInletFvPatchScalarField::
turbulentIntensityKineticEnergyInletFvPatchScalarField
(
	const turbulentIntensityKineticEnergyInletFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	inletOutletFvPatchScalarField(ptf, p, iF, mapper),
	intensity_(ptf.intensity_),
	UName_(ptf.UName_)
{}

tnbLib::turbulentIntensityKineticEnergyInletFvPatchScalarField::
turbulentIntensityKineticEnergyInletFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	inletOutletFvPatchScalarField(p, iF),
	intensity_(readScalar(dict.lookup("intensity"))),
	UName_(dict.lookupOrDefault<word>("U", "U"))
{
	this->phiName_ = dict.lookupOrDefault<word>("phi", "phi");

	if (intensity_ < 0 || intensity_ > 1)
	{
		FatalErrorInFunction
			<< "Turbulence intensity should be specified as a fraction 0-1 "
			"of the mean velocity\n"
			"    value given is " << intensity_ << nl
			<< "    on patch " << this->patch().name()
			<< " of field " << this->internalField().name()
			<< " in file " << this->internalField().objectPath()
			<< exit(FatalError);
	}

	fvPatchScalarField::operator=(scalarField("value", dict, p.size()));

	this->refValue() = 0.0;
	this->refGrad() = 0.0;
	this->valueFraction() = 0.0;
}

tnbLib::turbulentIntensityKineticEnergyInletFvPatchScalarField::
turbulentIntensityKineticEnergyInletFvPatchScalarField
(
	const turbulentIntensityKineticEnergyInletFvPatchScalarField& ptf
)
	:
	inletOutletFvPatchScalarField(ptf),
	intensity_(ptf.intensity_),
	UName_(ptf.UName_)
{}


tnbLib::turbulentIntensityKineticEnergyInletFvPatchScalarField::
turbulentIntensityKineticEnergyInletFvPatchScalarField
(
	const turbulentIntensityKineticEnergyInletFvPatchScalarField& ptf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	inletOutletFvPatchScalarField(ptf, iF),
	intensity_(ptf.intensity_),
	UName_(ptf.UName_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::turbulentIntensityKineticEnergyInletFvPatchScalarField::
updateCoeffs()
{
	if (updated())
	{
		return;
	}

	const fvPatchVectorField& Up =
		patch().lookupPatchField<volVectorField, vector>(UName_);

	const fvsPatchScalarField& phip =
		patch().lookupPatchField<surfaceScalarField, scalar>(this->phiName_);

	this->refValue() = 1.5*sqr(intensity_)*magSqr(Up);
	this->valueFraction() = 1.0 - pos0(phip);

	inletOutletFvPatchScalarField::updateCoeffs();
}


void tnbLib::turbulentIntensityKineticEnergyInletFvPatchScalarField::write
(
	Ostream& os
) const
{
	fvPatchScalarField::write(os);
	writeEntry(os, "intensity", intensity_);
	writeEntryIfDifferent<word>(os, "U", "U", UName_);
	writeEntryIfDifferent<word>(os, "phi", "phi", this->phiName_);
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		turbulentIntensityKineticEnergyInletFvPatchScalarField
	);
}

// ************************************************************************* //