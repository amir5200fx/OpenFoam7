#include <temperatureDependentAlphaContactAngleFvPatchScalarField.hxx>

#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::temperatureDependentAlphaContactAngleFvPatchScalarField::
temperatureDependentAlphaContactAngleFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	alphaContactAngleFvPatchScalarField(p, iF),
	TName_("T"),
	theta0_()
{}


tnbLib::temperatureDependentAlphaContactAngleFvPatchScalarField::
temperatureDependentAlphaContactAngleFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	alphaContactAngleFvPatchScalarField(p, iF, dict),
	TName_(dict.lookupOrDefault<word>("T", "T")),
	theta0_(Function1<scalar>::New("theta0", dict))
{
	evaluate();
}


tnbLib::temperatureDependentAlphaContactAngleFvPatchScalarField::
temperatureDependentAlphaContactAngleFvPatchScalarField
(
	const temperatureDependentAlphaContactAngleFvPatchScalarField& psf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	alphaContactAngleFvPatchScalarField(psf, p, iF, mapper),
	TName_(psf.TName_),
	theta0_(psf.theta0_, false)
{}


tnbLib::temperatureDependentAlphaContactAngleFvPatchScalarField::
temperatureDependentAlphaContactAngleFvPatchScalarField
(
	const temperatureDependentAlphaContactAngleFvPatchScalarField& psf
)
	:
	alphaContactAngleFvPatchScalarField(psf),
	TName_(psf.TName_),
	theta0_(psf.theta0_, false)
{}


tnbLib::temperatureDependentAlphaContactAngleFvPatchScalarField::
temperatureDependentAlphaContactAngleFvPatchScalarField
(
	const temperatureDependentAlphaContactAngleFvPatchScalarField& psf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	alphaContactAngleFvPatchScalarField(psf, iF),
	TName_(psf.TName_),
	theta0_(psf.theta0_, false)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::scalarField>
tnbLib::temperatureDependentAlphaContactAngleFvPatchScalarField::theta
(
	const fvPatchVectorField&,
	const fvsPatchVectorField&
) const
{
	return theta0_->value
	(
		patch().lookupPatchField<volScalarField, scalar>(TName_)
	);
}


void tnbLib::temperatureDependentAlphaContactAngleFvPatchScalarField::write
(
	Ostream& os
) const
{
	alphaContactAngleFvPatchScalarField::write(os);
	writeEntryIfDifferent<word>(os, "T", "T", TName_);
	writeEntry(os, theta0_());
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		temperatureDependentAlphaContactAngleFvPatchScalarField
	);
}

// ************************************************************************* //