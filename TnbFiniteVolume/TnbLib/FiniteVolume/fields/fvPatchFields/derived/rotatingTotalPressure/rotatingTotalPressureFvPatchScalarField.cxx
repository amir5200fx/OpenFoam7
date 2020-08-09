#include <rotatingTotalPressureFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::rotatingTotalPressureFvPatchScalarField::
rotatingTotalPressureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	totalPressureFvPatchScalarField(p, iF),
	omega_()
{}


tnbLib::rotatingTotalPressureFvPatchScalarField::
rotatingTotalPressureFvPatchScalarField
(
	const rotatingTotalPressureFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	totalPressureFvPatchScalarField(ptf, p, iF, mapper),
	omega_(ptf.omega_, false)
{}


tnbLib::rotatingTotalPressureFvPatchScalarField::
rotatingTotalPressureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	totalPressureFvPatchScalarField(p, iF, dict),
	omega_(Function1<vector>::New("omega", dict))
{}


tnbLib::rotatingTotalPressureFvPatchScalarField::
rotatingTotalPressureFvPatchScalarField
(
	const rotatingTotalPressureFvPatchScalarField& rtppsf
)
	:
	totalPressureFvPatchScalarField(rtppsf),
	omega_(rtppsf.omega_, false)
{}


tnbLib::rotatingTotalPressureFvPatchScalarField::
rotatingTotalPressureFvPatchScalarField
(
	const rotatingTotalPressureFvPatchScalarField& rtppsf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	totalPressureFvPatchScalarField(rtppsf, iF),
	omega_(rtppsf.omega_, false)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::rotatingTotalPressureFvPatchScalarField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	const scalar t = this->db().time().timeOutputValue();
	const vector om = omega_->value(t);

	vector axisHat = om / mag(om);
	tmp<vectorField> rotationVelocity =
		om ^ (patch().Cf() - axisHat * (axisHat & patch().Cf()));

	const vectorField Up
	(
		patch().lookupPatchField<volVectorField, vector>(UName())
		+ rotationVelocity
	);

	totalPressureFvPatchScalarField::updateCoeffs(p0(), Up);
}


void tnbLib::rotatingTotalPressureFvPatchScalarField::write(Ostream& os) const
{
	totalPressureFvPatchScalarField::write(os);
	writeEntry(os, omega_());
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		rotatingTotalPressureFvPatchScalarField
	);
}

// ************************************************************************* //