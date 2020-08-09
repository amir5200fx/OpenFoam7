#include <fixedEnergyFvPatchScalarField.hxx>

#include <volFields.hxx>
#include <basicThermo.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fixedEnergyFvPatchScalarField::
fixedEnergyFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedValueFvPatchScalarField(p, iF)
{}


tnbLib::fixedEnergyFvPatchScalarField::
fixedEnergyFvPatchScalarField
(
	const fixedEnergyFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchScalarField(ptf, p, iF, mapper)
{}


tnbLib::fixedEnergyFvPatchScalarField::
fixedEnergyFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchScalarField(p, iF, dict)
{}


tnbLib::fixedEnergyFvPatchScalarField::
fixedEnergyFvPatchScalarField
(
	const fixedEnergyFvPatchScalarField& tppsf
)
	:
	fixedValueFvPatchScalarField(tppsf)
{}


tnbLib::fixedEnergyFvPatchScalarField::
fixedEnergyFvPatchScalarField
(
	const fixedEnergyFvPatchScalarField& tppsf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedValueFvPatchScalarField(tppsf, iF)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::fixedEnergyFvPatchScalarField::updateCoeffs()
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
	operator==(thermo.he(pw, Tw, patchi));

	fixedValueFvPatchScalarField::updateCoeffs();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		fixedEnergyFvPatchScalarField
	);
}

// ************************************************************************* //