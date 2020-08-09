#include <mixedEnergyFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <basicThermo.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::mixedEnergyFvPatchScalarField::
mixedEnergyFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	mixedFvPatchScalarField(p, iF)
{
	valueFraction() = 0.0;
	refValue() = 0.0;
	refGrad() = 0.0;
}


tnbLib::mixedEnergyFvPatchScalarField::
mixedEnergyFvPatchScalarField
(
	const mixedEnergyFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	mixedFvPatchScalarField(ptf, p, iF, mapper)
{}


tnbLib::mixedEnergyFvPatchScalarField::
mixedEnergyFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	mixedFvPatchScalarField(p, iF, dict)
{}


tnbLib::mixedEnergyFvPatchScalarField::
mixedEnergyFvPatchScalarField
(
	const mixedEnergyFvPatchScalarField& tppsf
)
	:
	mixedFvPatchScalarField(tppsf)
{}


tnbLib::mixedEnergyFvPatchScalarField::
mixedEnergyFvPatchScalarField
(
	const mixedEnergyFvPatchScalarField& tppsf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	mixedFvPatchScalarField(tppsf, iF)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::mixedEnergyFvPatchScalarField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	const basicThermo& thermo = basicThermo::lookupThermo(*this);
	const label patchi = patch().index();

	const scalarField& pw = thermo.p().boundaryField()[patchi];
	mixedFvPatchScalarField& Tw = refCast<mixedFvPatchScalarField>
		(
			const_cast<fvPatchScalarField&>(thermo.T().boundaryField()[patchi])
			);

	Tw.evaluate();

	valueFraction() = Tw.valueFraction();
	refValue() = thermo.he(pw, Tw.refValue(), patchi);
	refGrad() =
		thermo.Cpv(pw, Tw, patchi)*Tw.refGrad()
		+ patch().deltaCoeffs()*
		(
			thermo.he(pw, Tw, patchi)
			- thermo.he(pw, Tw, patch().faceCells())
			);

	mixedFvPatchScalarField::updateCoeffs();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		mixedEnergyFvPatchScalarField
	);
}

// ************************************************************************* //