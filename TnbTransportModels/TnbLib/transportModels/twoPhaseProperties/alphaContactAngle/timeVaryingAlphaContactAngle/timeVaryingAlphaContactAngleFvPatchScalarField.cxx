#include <timeVaryingAlphaContactAngleFvPatchScalarField.hxx>

#include <Time.hxx>
#include <volMesh.hxx>
#include <fvPatchFieldMapper.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::timeVaryingAlphaContactAngleFvPatchScalarField::
timeVaryingAlphaContactAngleFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	alphaContactAngleFvPatchScalarField(p, iF),
	t0_(0.0),
	thetaT0_(0.0),
	te_(0.0),
	thetaTe_(0.0)
{}


tnbLib::timeVaryingAlphaContactAngleFvPatchScalarField::
timeVaryingAlphaContactAngleFvPatchScalarField
(
	const timeVaryingAlphaContactAngleFvPatchScalarField& gcpsf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	alphaContactAngleFvPatchScalarField(gcpsf, p, iF, mapper),
	t0_(gcpsf.t0_),
	thetaT0_(gcpsf.thetaT0_),
	te_(gcpsf.te_),
	thetaTe_(gcpsf.te_)
{}


tnbLib::timeVaryingAlphaContactAngleFvPatchScalarField::
timeVaryingAlphaContactAngleFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	alphaContactAngleFvPatchScalarField(p, iF, dict),
	t0_(readScalar(dict.lookup("t0"))),
	thetaT0_(readScalar(dict.lookup("thetaT0"))),
	te_(readScalar(dict.lookup("te"))),
	thetaTe_(readScalar(dict.lookup("thetaTe")))
{
	evaluate();
}


tnbLib::timeVaryingAlphaContactAngleFvPatchScalarField::
timeVaryingAlphaContactAngleFvPatchScalarField
(
	const timeVaryingAlphaContactAngleFvPatchScalarField& gcpsf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	alphaContactAngleFvPatchScalarField(gcpsf, iF),
	t0_(gcpsf.t0_),
	thetaT0_(gcpsf.thetaT0_),
	te_(gcpsf.te_),
	thetaTe_(gcpsf.thetaTe_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::scalarField>
tnbLib::timeVaryingAlphaContactAngleFvPatchScalarField::theta
(
	const fvPatchVectorField&,
	const fvsPatchVectorField&
) const
{
	scalar t = patch().boundaryMesh().mesh().time().value();
	scalar theta0 = thetaT0_;

	if (t < t0_)
	{
		theta0 = thetaT0_;
	}
	else if (t > te_)
	{
		theta0 = thetaTe_;
	}
	else
	{
		theta0 = thetaT0_ + (t - t0_)*(thetaTe_ - thetaT0_) / (te_ - t0_);
	}

	return tmp<scalarField>(new scalarField(size(), theta0));
}


void tnbLib::timeVaryingAlphaContactAngleFvPatchScalarField::write
(
	Ostream& os
) const
{
	alphaContactAngleFvPatchScalarField::write(os);
	writeEntry(os, "t0", t0_);
	writeEntry(os, "thetaT0", thetaT0_);
	writeEntry(os, "te", te_);
	writeEntry(os, "thetaTe", thetaTe_);
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		timeVaryingAlphaContactAngleFvPatchScalarField
	);
}

// ************************************************************************* //