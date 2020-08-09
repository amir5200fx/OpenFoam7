#include <gradientEnergyFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <basicThermo.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::gradientEnergyFvPatchScalarField::
gradientEnergyFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedGradientFvPatchScalarField(p, iF)
{}


tnbLib::gradientEnergyFvPatchScalarField::
gradientEnergyFvPatchScalarField
(
	const gradientEnergyFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedGradientFvPatchScalarField(ptf, p, iF, mapper)
{}


tnbLib::gradientEnergyFvPatchScalarField::
gradientEnergyFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedGradientFvPatchScalarField(p, iF, dict)
{}


tnbLib::gradientEnergyFvPatchScalarField::
gradientEnergyFvPatchScalarField
(
	const gradientEnergyFvPatchScalarField& tppsf
)
	:
	fixedGradientFvPatchScalarField(tppsf)
{}


tnbLib::gradientEnergyFvPatchScalarField::
gradientEnergyFvPatchScalarField
(
	const gradientEnergyFvPatchScalarField& tppsf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedGradientFvPatchScalarField(tppsf, iF)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::gradientEnergyFvPatchScalarField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	const basicThermo& thermo = basicThermo::lookupThermo(*this);
	const label patchi = patch().index();

	const scalarField& pw = thermo.p().boundaryField()[patchi];
	fvPatchScalarField& Tw =
		const_cast<fvPatchScalarField&>(thermo.T().boundaryField()[patchi]);

	Tw.evaluate();

	gradient() = thermo.Cpv(pw, Tw, patchi)*Tw.snGrad()
		+ patch().deltaCoeffs()*
		(
			thermo.he(pw, Tw, patchi)
			- thermo.he(pw, Tw, patch().faceCells())
			);

	fixedGradientFvPatchScalarField::updateCoeffs();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		gradientEnergyFvPatchScalarField
	);
}

// ************************************************************************* //