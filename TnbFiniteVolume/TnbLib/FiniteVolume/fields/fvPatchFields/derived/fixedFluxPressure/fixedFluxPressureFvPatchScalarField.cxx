#include <fixedFluxPressureFvPatchScalarField.hxx>

#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fixedFluxPressureFvPatchScalarField::fixedFluxPressureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedGradientFvPatchScalarField(p, iF),
	curTimeIndex_(-1)
{}


tnbLib::fixedFluxPressureFvPatchScalarField::fixedFluxPressureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedGradientFvPatchScalarField(p, iF),
	curTimeIndex_(-1)
{
	if (dict.found("value") && dict.found("gradient"))
	{
		fvPatchField<scalar>::operator=
			(
				scalarField("value", dict, p.size())
				);
		gradient() = scalarField("gradient", dict, p.size());
	}
	else
	{
		fvPatchField<scalar>::operator=(patchInternalField());
		gradient() = 0.0;
	}
}


tnbLib::fixedFluxPressureFvPatchScalarField::fixedFluxPressureFvPatchScalarField
(
	const fixedFluxPressureFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedGradientFvPatchScalarField(p, iF),
	curTimeIndex_(-1)
{
	patchType() = ptf.patchType();

	// Map gradient. Set unmapped values and overwrite with mapped ptf
	gradient() = 0.0;
	mapper(gradient(), ptf.gradient());

	// Evaluate the value field from the gradient if the internal field is valid
	if (notNull(iF) && iF.size())
	{
		scalarField::operator=
			(
				// patchInternalField() + gradient()/patch().deltaCoeffs()
				// ***HGW Hack to avoid the construction of mesh.deltaCoeffs
				// which fails for AMI patches for some mapping operations
				patchInternalField() + gradient()*(patch().nf() & patch().delta())
				);
	}
	else
	{
		// Enforce mapping of values so we have a valid starting value. This
		// constructor is used when reconstructing fields
		mapper(*this, ptf);
	}
}


tnbLib::fixedFluxPressureFvPatchScalarField::fixedFluxPressureFvPatchScalarField
(
	const fixedFluxPressureFvPatchScalarField& wbppsf
)
	:
	fixedGradientFvPatchScalarField(wbppsf),
	curTimeIndex_(-1)
{}


tnbLib::fixedFluxPressureFvPatchScalarField::fixedFluxPressureFvPatchScalarField
(
	const fixedFluxPressureFvPatchScalarField& wbppsf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedGradientFvPatchScalarField(wbppsf, iF),
	curTimeIndex_(-1)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::fixedFluxPressureFvPatchScalarField::updateCoeffs
(
	const scalarField& snGradp
)
{
	if (updated())
	{
		return;
	}

	curTimeIndex_ = this->db().time().timeIndex();

	gradient() = snGradp;
	fixedGradientFvPatchScalarField::updateCoeffs();
}


void tnbLib::fixedFluxPressureFvPatchScalarField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	if (curTimeIndex_ != this->db().time().timeIndex())
	{
		FatalErrorInFunction
			<< "updateCoeffs(const scalarField& snGradp) MUST be called before"
			" updateCoeffs() or evaluate() to set the boundary gradient."
			<< exit(FatalError);
	}
}


void tnbLib::fixedFluxPressureFvPatchScalarField::write(Ostream& os) const
{
	fixedGradientFvPatchScalarField::write(os);
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		fixedFluxPressureFvPatchScalarField
	);
}


// ************************************************************************* //