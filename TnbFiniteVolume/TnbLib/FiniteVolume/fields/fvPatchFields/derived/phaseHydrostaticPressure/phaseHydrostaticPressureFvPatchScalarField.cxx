#include <phaseHydrostaticPressureFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <uniformDimensionedFields.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::phaseHydrostaticPressureFvPatchScalarField::
phaseHydrostaticPressureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	mixedFvPatchScalarField(p, iF),
	phaseFraction_("alpha"),
	rho_(0.0),
	pRefValue_(0.0),
	pRefPoint_(Zero)
{
	this->refValue() = 0.0;
	this->refGrad() = 0.0;
	this->valueFraction() = 0.0;
}


tnbLib::phaseHydrostaticPressureFvPatchScalarField::
phaseHydrostaticPressureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	mixedFvPatchScalarField(p, iF),
	phaseFraction_(dict.lookupOrDefault<word>("phaseFraction", "alpha")),
	rho_(readScalar(dict.lookup("rho"))),
	pRefValue_(readScalar(dict.lookup("pRefValue"))),
	pRefPoint_(dict.lookup("pRefPoint"))
{
	this->refValue() = pRefValue_;

	if (dict.found("value"))
	{
		fvPatchScalarField::operator=
			(
				scalarField("value", dict, p.size())
				);
	}
	else
	{
		fvPatchScalarField::operator=(this->refValue());
	}

	this->refGrad() = 0.0;
	this->valueFraction() = 0.0;
}


tnbLib::phaseHydrostaticPressureFvPatchScalarField::
phaseHydrostaticPressureFvPatchScalarField
(
	const phaseHydrostaticPressureFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	mixedFvPatchScalarField(ptf, p, iF, mapper),
	phaseFraction_(ptf.phaseFraction_),
	rho_(ptf.rho_),
	pRefValue_(ptf.pRefValue_),
	pRefPoint_(ptf.pRefPoint_)
{}


tnbLib::phaseHydrostaticPressureFvPatchScalarField::
phaseHydrostaticPressureFvPatchScalarField
(
	const phaseHydrostaticPressureFvPatchScalarField& ptf
)
	:
	mixedFvPatchScalarField(ptf),
	phaseFraction_(ptf.phaseFraction_)
{}


tnbLib::phaseHydrostaticPressureFvPatchScalarField::
phaseHydrostaticPressureFvPatchScalarField
(
	const phaseHydrostaticPressureFvPatchScalarField& ptf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	mixedFvPatchScalarField(ptf, iF),
	phaseFraction_(ptf.phaseFraction_),
	rho_(ptf.rho_),
	pRefValue_(ptf.pRefValue_),
	pRefPoint_(ptf.pRefPoint_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::phaseHydrostaticPressureFvPatchScalarField::updateCoeffs()
{
	if (this->updated())
	{
		return;
	}

	const scalarField& alphap =
		patch().lookupPatchField<volScalarField, scalar>
		(
			phaseFraction_
			);

	const uniformDimensionedVectorField& g =
		db().lookupObject<uniformDimensionedVectorField>("g");

	// scalar rhor = 1000;
	// scalarField alphap1 = max(min(alphap, 1.0), 0.0);
	// valueFraction() = alphap1/(alphap1 + rhor*(1.0 - alphap1));
	valueFraction() = max(min(alphap, scalar(1)), scalar(0));

	refValue() =
		pRefValue_
		+ rho_ * ((g.value() & patch().Cf()) - (g.value() & pRefPoint_));

	mixedFvPatchScalarField::updateCoeffs();
}


void tnbLib::phaseHydrostaticPressureFvPatchScalarField::write(Ostream& os) const
{
	fvPatchScalarField::write(os);
	if (phaseFraction_ != "alpha")
	{
		writeEntry(os, "phaseFraction", phaseFraction_);
	}
	writeEntry(os, "rho", rho_);
	writeEntry(os, "pRefValue", pRefValue_);
	writeEntry(os, "pRefPoint", pRefPoint_);
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void tnbLib::phaseHydrostaticPressureFvPatchScalarField::operator=
(
	const fvPatchScalarField& ptf
	)
{
	fvPatchScalarField::operator=
		(
			valueFraction()*refValue() + (1 - valueFraction())*ptf
			);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		phaseHydrostaticPressureFvPatchScalarField
	);
}

// ************************************************************************* //