#include <gradientUnburntEnthalpyFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <psiuReactionThermo.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::gradientUnburntEnthalpyFvPatchScalarField::
gradientUnburntEnthalpyFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedGradientFvPatchScalarField(p, iF)
{}


tnbLib::gradientUnburntEnthalpyFvPatchScalarField::
gradientUnburntEnthalpyFvPatchScalarField
(
	const gradientUnburntEnthalpyFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedGradientFvPatchScalarField(ptf, p, iF, mapper)
{}


tnbLib::gradientUnburntEnthalpyFvPatchScalarField::
gradientUnburntEnthalpyFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedGradientFvPatchScalarField(p, iF, dict)
{}


tnbLib::gradientUnburntEnthalpyFvPatchScalarField::
gradientUnburntEnthalpyFvPatchScalarField
(
	const gradientUnburntEnthalpyFvPatchScalarField& tppsf
)
	:
	fixedGradientFvPatchScalarField(tppsf)
{}


tnbLib::gradientUnburntEnthalpyFvPatchScalarField::
gradientUnburntEnthalpyFvPatchScalarField
(
	const gradientUnburntEnthalpyFvPatchScalarField& tppsf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedGradientFvPatchScalarField(tppsf, iF)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::gradientUnburntEnthalpyFvPatchScalarField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	const psiuReactionThermo& thermo = db().lookupObject<psiuReactionThermo>
		(
			basicThermo::dictName
			);

	const label patchi = patch().index();

	const scalarField& pw = thermo.p().boundaryField()[patchi];
	fvPatchScalarField& Tw =
		const_cast<fvPatchScalarField&>(thermo.Tu().boundaryField()[patchi]);

	Tw.evaluate();

	gradient() = thermo.Cp(pw, Tw, patchi)*Tw.snGrad()
		+ patch().deltaCoeffs()*
		(
			thermo.heu(pw, Tw, patchi)
			- thermo.heu(pw, Tw, patch().faceCells())
			);

	fixedGradientFvPatchScalarField::updateCoeffs();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		gradientUnburntEnthalpyFvPatchScalarField
	);
}

// ************************************************************************* //