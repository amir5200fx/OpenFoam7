#include <fixedFluxExtrapolatedPressureFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fixedFluxExtrapolatedPressureFvPatchScalarField::
fixedFluxExtrapolatedPressureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedFluxPressureFvPatchScalarField(p, iF)
{}


tnbLib::fixedFluxExtrapolatedPressureFvPatchScalarField::
fixedFluxExtrapolatedPressureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedFluxPressureFvPatchScalarField(p, iF, dict)
{}


tnbLib::fixedFluxExtrapolatedPressureFvPatchScalarField::
fixedFluxExtrapolatedPressureFvPatchScalarField
(
	const fixedFluxExtrapolatedPressureFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedFluxPressureFvPatchScalarField(ptf, p, iF, mapper)
{}


tnbLib::fixedFluxExtrapolatedPressureFvPatchScalarField::
fixedFluxExtrapolatedPressureFvPatchScalarField
(
	const fixedFluxExtrapolatedPressureFvPatchScalarField& wbppsf
)
	:
	fixedFluxPressureFvPatchScalarField(wbppsf)
{}


tnbLib::fixedFluxExtrapolatedPressureFvPatchScalarField::
fixedFluxExtrapolatedPressureFvPatchScalarField
(
	const fixedFluxExtrapolatedPressureFvPatchScalarField& wbppsf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedFluxPressureFvPatchScalarField(wbppsf, iF)
{}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		fixedFluxExtrapolatedPressureFvPatchScalarField
	);
}


// ************************************************************************* //