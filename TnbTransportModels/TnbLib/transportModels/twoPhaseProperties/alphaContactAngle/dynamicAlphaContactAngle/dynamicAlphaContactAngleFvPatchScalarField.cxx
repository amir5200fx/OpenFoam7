#include <dynamicAlphaContactAngleFvPatchScalarField.hxx>

#include <volMesh.hxx>
#include <fvPatchFieldMapper.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::dynamicAlphaContactAngleFvPatchScalarField::
dynamicAlphaContactAngleFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	alphaContactAngleFvPatchScalarField(p, iF),
	theta0_(0.0),
	uTheta_(0.0),
	thetaA_(0.0),
	thetaR_(0.0)
{}


tnbLib::dynamicAlphaContactAngleFvPatchScalarField::
dynamicAlphaContactAngleFvPatchScalarField
(
	const dynamicAlphaContactAngleFvPatchScalarField& gcpsf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	alphaContactAngleFvPatchScalarField(gcpsf, p, iF, mapper),
	theta0_(gcpsf.theta0_),
	uTheta_(gcpsf.uTheta_),
	thetaA_(gcpsf.thetaA_),
	thetaR_(gcpsf.thetaR_)
{}


tnbLib::dynamicAlphaContactAngleFvPatchScalarField::
dynamicAlphaContactAngleFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	alphaContactAngleFvPatchScalarField(p, iF, dict),
	theta0_(readScalar(dict.lookup("theta0"))),
	uTheta_(readScalar(dict.lookup("uTheta"))),
	thetaA_
	(
		dict.found("thetaA")
		? readScalar(dict.lookup("thetaA"))
		: readScalar(dict.lookup("thetaRec"))
	),
	thetaR_
	(
		dict.found("thetaR")
		? readScalar(dict.lookup("thetaR"))
		: readScalar(dict.lookup("thetaAdv"))
	)
{
	evaluate();
}


tnbLib::dynamicAlphaContactAngleFvPatchScalarField::
dynamicAlphaContactAngleFvPatchScalarField
(
	const dynamicAlphaContactAngleFvPatchScalarField& gcpsf
)
	:
	alphaContactAngleFvPatchScalarField(gcpsf),
	theta0_(gcpsf.theta0_),
	uTheta_(gcpsf.uTheta_),
	thetaA_(gcpsf.thetaA_),
	thetaR_(gcpsf.thetaR_)
{}


tnbLib::dynamicAlphaContactAngleFvPatchScalarField::
dynamicAlphaContactAngleFvPatchScalarField
(
	const dynamicAlphaContactAngleFvPatchScalarField& gcpsf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	alphaContactAngleFvPatchScalarField(gcpsf, iF),
	theta0_(gcpsf.theta0_),
	uTheta_(gcpsf.uTheta_),
	thetaA_(gcpsf.thetaA_),
	thetaR_(gcpsf.thetaR_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::scalarField>
tnbLib::dynamicAlphaContactAngleFvPatchScalarField::theta
(
	const fvPatchVectorField& Up,
	const fvsPatchVectorField& nHat
) const
{
	if (uTheta_ < small)
	{
		return tmp<scalarField>(new scalarField(size(), theta0_));
	}

	const vectorField nf(patch().nf());

	// Calculated the component of the velocity parallel to the wall
	vectorField Uwall(Up.patchInternalField() - Up);
	Uwall -= (nf & Uwall)*nf;

	// Find the direction of the interface parallel to the wall
	vectorField nWall(nHat - (nf & nHat)*nf);

	// Normalise nWall
	nWall /= (mag(nWall) + small);

	// Calculate Uwall resolved normal to the interface parallel to
	// the interface
	scalarField uwall(nWall & Uwall);

	return theta0_ + (thetaA_ - thetaR_)*tanh(uwall / uTheta_);
}


void tnbLib::dynamicAlphaContactAngleFvPatchScalarField::write(Ostream& os) const
{
	alphaContactAngleFvPatchScalarField::write(os);
	writeEntry(os, "theta0", theta0_);
	writeEntry(os, "uTheta", uTheta_);
	writeEntry(os, "thetaA", thetaA_);
	writeEntry(os, "thetaR", thetaR_);
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		dynamicAlphaContactAngleFvPatchScalarField
	);
}


// ************************************************************************* //