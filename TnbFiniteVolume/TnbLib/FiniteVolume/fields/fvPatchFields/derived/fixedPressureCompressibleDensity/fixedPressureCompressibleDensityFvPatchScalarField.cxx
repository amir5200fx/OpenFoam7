#include <fixedPressureCompressibleDensityFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <surfaceFields.hxx>
#include <volFields.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fixedPressureCompressibleDensityFvPatchScalarField::
fixedPressureCompressibleDensityFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedValueFvPatchField<scalar>(p, iF),
	pName_("p")
{}


tnbLib::fixedPressureCompressibleDensityFvPatchScalarField::
fixedPressureCompressibleDensityFvPatchScalarField
(
	const fixedPressureCompressibleDensityFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchField<scalar>(ptf, p, iF, mapper),
	pName_(ptf.pName_)
{}


tnbLib::fixedPressureCompressibleDensityFvPatchScalarField::
fixedPressureCompressibleDensityFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchField<scalar>(p, iF, dict),
	pName_(dict.lookupOrDefault<word>("p", "p"))
{}


tnbLib::fixedPressureCompressibleDensityFvPatchScalarField::
fixedPressureCompressibleDensityFvPatchScalarField
(
	const fixedPressureCompressibleDensityFvPatchScalarField& ptf
)
	:
	fixedValueFvPatchField<scalar>(ptf),
	pName_(ptf.pName_)
{}


tnbLib::fixedPressureCompressibleDensityFvPatchScalarField::
fixedPressureCompressibleDensityFvPatchScalarField
(
	const fixedPressureCompressibleDensityFvPatchScalarField& ptf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedValueFvPatchField<scalar>(ptf, iF),
	pName_(ptf.pName_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::fixedPressureCompressibleDensityFvPatchScalarField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	const fvPatchField<scalar>& pp =
		patch().lookupPatchField<volScalarField, scalar>(pName_);

	const dictionary& thermoProps =
		db().lookupObject<IOdictionary>("thermodynamicProperties");

	const scalar rholSat =
		dimensionedScalar(thermoProps.lookup("rholSat")).value();

	const scalar pSat =
		dimensionedScalar(thermoProps.lookup("pSat")).value();

	const scalar psil = dimensionedScalar(thermoProps.lookup("psil")).value();

	operator==(rholSat + psil * (pp - pSat));

	fixedValueFvPatchField<scalar>::updateCoeffs();
}


void tnbLib::fixedPressureCompressibleDensityFvPatchScalarField::write
(
	Ostream& os
) const
{
	fvPatchField<scalar>::write(os);
	writeEntryIfDifferent<word>(os, "p", "p", pName_);
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		fixedPressureCompressibleDensityFvPatchScalarField
	);
}

// ************************************************************************* //