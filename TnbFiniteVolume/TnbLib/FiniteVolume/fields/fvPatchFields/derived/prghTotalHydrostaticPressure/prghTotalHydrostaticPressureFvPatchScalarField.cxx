#include <prghTotalHydrostaticPressureFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <uniformDimensionedFields.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::prghTotalHydrostaticPressureFvPatchScalarField::
prghTotalHydrostaticPressureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedValueFvPatchScalarField(p, iF),
	UName_("U"),
	phiName_("phi"),
	rhoName_("rho"),
	ph_rghName_("ph_rgh")
{}


tnbLib::prghTotalHydrostaticPressureFvPatchScalarField::
prghTotalHydrostaticPressureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchScalarField(p, iF, dict),
	UName_(dict.lookupOrDefault<word>("U", "U")),
	phiName_(dict.lookupOrDefault<word>("phi", "phi")),
	rhoName_(dict.lookupOrDefault<word>("rho", "rho")),
	ph_rghName_(dict.lookupOrDefault<word>("ph_rgh", "ph_rgh"))
{}


tnbLib::prghTotalHydrostaticPressureFvPatchScalarField::
prghTotalHydrostaticPressureFvPatchScalarField
(
	const prghTotalHydrostaticPressureFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchScalarField(ptf, p, iF, mapper),
	UName_(ptf.UName_),
	phiName_(ptf.phiName_),
	rhoName_(ptf.rhoName_),
	ph_rghName_(ptf.ph_rghName_)
{}


tnbLib::prghTotalHydrostaticPressureFvPatchScalarField::
prghTotalHydrostaticPressureFvPatchScalarField
(
	const prghTotalHydrostaticPressureFvPatchScalarField& ptf
)
	:
	fixedValueFvPatchScalarField(ptf),
	UName_(ptf.UName_),
	phiName_(ptf.phiName_),
	rhoName_(ptf.rhoName_),
	ph_rghName_(ptf.ph_rghName_)
{}


tnbLib::prghTotalHydrostaticPressureFvPatchScalarField::
prghTotalHydrostaticPressureFvPatchScalarField
(
	const prghTotalHydrostaticPressureFvPatchScalarField& ptf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedValueFvPatchScalarField(ptf, iF),
	UName_(ptf.UName_),
	phiName_(ptf.phiName_),
	rhoName_(ptf.rhoName_),
	ph_rghName_(ptf.ph_rghName_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::prghTotalHydrostaticPressureFvPatchScalarField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	const scalarField& rhop =
		patch().lookupPatchField<volScalarField, scalar>(rhoName_);

	const scalarField& ph_rghp =
		patch().lookupPatchField<volScalarField, scalar>(ph_rghName_);

	const scalarField& phip =
		patch().lookupPatchField<surfaceScalarField, scalar>(phiName_);

	const vectorField& Up =
		patch().lookupPatchField<volVectorField, vector>(UName_);

	operator==
		(
			ph_rghp
			- 0.5*rhop*(1.0 - pos0(phip))*magSqr(Up)
			);

	fixedValueFvPatchScalarField::updateCoeffs();
}


void tnbLib::prghTotalHydrostaticPressureFvPatchScalarField::write
(
	Ostream& os
) const
{
	fvPatchScalarField::write(os);
	writeEntryIfDifferent<word>(os, "U", "U", UName_);
	writeEntryIfDifferent<word>(os, "phi", "phi", phiName_);
	writeEntryIfDifferent<word>(os, "rho", "rho", rhoName_);
	writeEntryIfDifferent<word>(os, "ph_rgh", "ph_rgh", ph_rghName_);
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		prghTotalHydrostaticPressureFvPatchScalarField
	);
}

// ************************************************************************* //