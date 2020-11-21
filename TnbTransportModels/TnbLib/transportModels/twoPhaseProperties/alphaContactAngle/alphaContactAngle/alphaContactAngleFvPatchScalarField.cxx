#define FoamNamedEnum_EXPORT_DEFINE

#include <alphaContactAngleFvPatchScalarField.hxx>

#include <fvPatchFieldMapper.hxx>
#include <volMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(alphaContactAngleFvPatchScalarField, 0);

	template<>
	const char* tnbLib::NamedEnum
		<
		tnbLib::alphaContactAngleFvPatchScalarField::limitControls,
		4
		>::names[] =
	{
		"none",
		"gradient",
		"zeroGradient",
		"alpha"
	};
}


const tnbLib::NamedEnum
<
	tnbLib::alphaContactAngleFvPatchScalarField::limitControls,
	4
> tnbLib::alphaContactAngleFvPatchScalarField::limitControlNames_;


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::alphaContactAngleFvPatchScalarField::alphaContactAngleFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedGradientFvPatchScalarField(p, iF),
	limit_(lcZeroGradient)
{}


tnbLib::alphaContactAngleFvPatchScalarField::alphaContactAngleFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedGradientFvPatchScalarField(p, iF),
	limit_(limitControlNames_.read(dict.lookup("limit")))
{
	if (dict.found("gradient"))
	{
		gradient() = scalarField("gradient", dict, p.size());
		fixedGradientFvPatchScalarField::updateCoeffs();
		fixedGradientFvPatchScalarField::evaluate();
	}
	else
	{
		fvPatchField<scalar>::operator=(patchInternalField());
		gradient() = 0.0;
	}
}


tnbLib::alphaContactAngleFvPatchScalarField::alphaContactAngleFvPatchScalarField
(
	const alphaContactAngleFvPatchScalarField& acpsf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedGradientFvPatchScalarField(acpsf, p, iF, mapper),
	limit_(acpsf.limit_)
{}


tnbLib::alphaContactAngleFvPatchScalarField::alphaContactAngleFvPatchScalarField
(
	const alphaContactAngleFvPatchScalarField& acpsf
)
	:
	fixedGradientFvPatchScalarField(acpsf),
	limit_(acpsf.limit_)
{}


tnbLib::alphaContactAngleFvPatchScalarField::alphaContactAngleFvPatchScalarField
(
	const alphaContactAngleFvPatchScalarField& acpsf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedGradientFvPatchScalarField(acpsf, iF),
	limit_(acpsf.limit_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::alphaContactAngleFvPatchScalarField::evaluate
(
	const Pstream::commsTypes
)
{
	if (limit_ == lcGradient)
	{
		gradient() =
			patch().deltaCoeffs()
			*(
				max(min
				(
					*this + gradient() / patch().deltaCoeffs(),
					scalar(1)), scalar(0)
				) - *this
				);
	}
	else if (limit_ == lcZeroGradient)
	{
		gradient() = 0.0;
	}

	fixedGradientFvPatchScalarField::evaluate();

	if (limit_ == lcAlpha)
	{
		scalarField::operator=(max(min(*this, scalar(1)), scalar(0)));
	}
}


void tnbLib::alphaContactAngleFvPatchScalarField::write
(
	Ostream& os
) const
{
	fixedGradientFvPatchScalarField::write(os);
	writeEntry(os, "limit", limitControlNames_[limit_]);
}


// ************************************************************************* //