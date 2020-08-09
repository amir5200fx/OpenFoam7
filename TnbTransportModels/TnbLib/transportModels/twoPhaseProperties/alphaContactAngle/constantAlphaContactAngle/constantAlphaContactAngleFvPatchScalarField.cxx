#include <constantAlphaContactAngleFvPatchScalarField.hxx>

#include <volMesh.hxx>
#include <fvPatchFieldMapper.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::constantAlphaContactAngleFvPatchScalarField::
constantAlphaContactAngleFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	alphaContactAngleFvPatchScalarField(p, iF),
	theta0_(0.0)
{}


tnbLib::constantAlphaContactAngleFvPatchScalarField::
constantAlphaContactAngleFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	alphaContactAngleFvPatchScalarField(p, iF, dict),
	theta0_(readScalar(dict.lookup("theta0")))
{
	evaluate();
}


tnbLib::constantAlphaContactAngleFvPatchScalarField::
constantAlphaContactAngleFvPatchScalarField
(
	const constantAlphaContactAngleFvPatchScalarField& gcpsf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	alphaContactAngleFvPatchScalarField(gcpsf, p, iF, mapper),
	theta0_(gcpsf.theta0_)
{}


tnbLib::constantAlphaContactAngleFvPatchScalarField::
constantAlphaContactAngleFvPatchScalarField
(
	const constantAlphaContactAngleFvPatchScalarField& gcpsf
)
	:
	alphaContactAngleFvPatchScalarField(gcpsf),
	theta0_(gcpsf.theta0_)
{}


tnbLib::constantAlphaContactAngleFvPatchScalarField::
constantAlphaContactAngleFvPatchScalarField
(
	const constantAlphaContactAngleFvPatchScalarField& gcpsf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	alphaContactAngleFvPatchScalarField(gcpsf, iF),
	theta0_(gcpsf.theta0_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::scalarField>
tnbLib::constantAlphaContactAngleFvPatchScalarField::theta
(
	const fvPatchVectorField&,
	const fvsPatchVectorField&
) const
{
	return tmp<scalarField>(new scalarField(size(), theta0_));
}


void tnbLib::constantAlphaContactAngleFvPatchScalarField::write
(
	Ostream& os
) const
{
	alphaContactAngleFvPatchScalarField::write(os);
	writeEntry(os, "theta0", theta0_);
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		constantAlphaContactAngleFvPatchScalarField
	);
}

// ************************************************************************* //