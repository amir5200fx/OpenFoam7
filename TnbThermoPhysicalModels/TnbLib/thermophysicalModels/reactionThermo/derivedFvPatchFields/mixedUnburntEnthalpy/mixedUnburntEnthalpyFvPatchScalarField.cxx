#include <mixedUnburntEnthalpyFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <psiuReactionThermo.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::mixedUnburntEnthalpyFvPatchScalarField::
mixedUnburntEnthalpyFvPatchScalarField
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


tnbLib::mixedUnburntEnthalpyFvPatchScalarField::
mixedUnburntEnthalpyFvPatchScalarField
(
	const mixedUnburntEnthalpyFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	mixedFvPatchScalarField(ptf, p, iF, mapper)
{}


tnbLib::mixedUnburntEnthalpyFvPatchScalarField::
mixedUnburntEnthalpyFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	mixedFvPatchScalarField(p, iF, dict)
{}


tnbLib::mixedUnburntEnthalpyFvPatchScalarField::
mixedUnburntEnthalpyFvPatchScalarField
(
	const mixedUnburntEnthalpyFvPatchScalarField& tppsf
)
	:
	mixedFvPatchScalarField(tppsf)
{}


tnbLib::mixedUnburntEnthalpyFvPatchScalarField::
mixedUnburntEnthalpyFvPatchScalarField
(
	const mixedUnburntEnthalpyFvPatchScalarField& tppsf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	mixedFvPatchScalarField(tppsf, iF)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::mixedUnburntEnthalpyFvPatchScalarField::updateCoeffs()
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
	mixedFvPatchScalarField& Tw = refCast<mixedFvPatchScalarField>
		(
			const_cast<fvPatchScalarField&>(thermo.Tu().boundaryField()[patchi])
			);

	Tw.evaluate();

	valueFraction() = Tw.valueFraction();
	refValue() = thermo.heu(pw, Tw.refValue(), patchi);
	refGrad() = thermo.Cp(pw, Tw, patchi)*Tw.refGrad()
		+ patch().deltaCoeffs()*
		(
			thermo.heu(pw, Tw, patchi)
			- thermo.heu(pw, Tw, patch().faceCells())
			);

	mixedFvPatchScalarField::updateCoeffs();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		mixedUnburntEnthalpyFvPatchScalarField
	);
}

// ************************************************************************* //