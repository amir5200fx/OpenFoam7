#include <fixedShearStressFvPatchVectorField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <turbulenceModel.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fixedShearStressFvPatchVectorField::fixedShearStressFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchVectorField(p, iF),
	tau0_(Zero)
{}


tnbLib::fixedShearStressFvPatchVectorField::fixedShearStressFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchVectorField(p, iF, dict, false),
	tau0_(dict.lookupOrDefault<vector>("tau", Zero))
{
	fvPatchField<vector>::operator=(patchInternalField());
}


tnbLib::fixedShearStressFvPatchVectorField::fixedShearStressFvPatchVectorField
(
	const fixedShearStressFvPatchVectorField& ptf,
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchVectorField(ptf, p, iF, mapper),
	tau0_(ptf.tau0_)
{}


tnbLib::fixedShearStressFvPatchVectorField::fixedShearStressFvPatchVectorField
(
	const fixedShearStressFvPatchVectorField& ptf
)
	:
	fixedValueFvPatchVectorField(ptf),
	tau0_(ptf.tau0_)
{}


tnbLib::fixedShearStressFvPatchVectorField::fixedShearStressFvPatchVectorField
(
	const fixedShearStressFvPatchVectorField& ptf,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchVectorField(ptf, iF),
	tau0_(ptf.tau0_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::fixedShearStressFvPatchVectorField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	const turbulenceModel& turbModel = db().lookupObject<turbulenceModel>
		(
			IOobject::groupName
			(
				turbulenceModel::propertiesName,
				internalField().group()
			)
			);

	scalarField nuEff(turbModel.nuEff(patch().index()));

	const vectorField Uc(patchInternalField());

	vector tauHat = tau0_ / (mag(tau0_) + rootVSmall);

	const scalarField& ry = patch().deltaCoeffs();

	operator==(tauHat*(tauHat & (tau0_*(1.0 / (ry*nuEff)) + Uc)));

	fixedValueFvPatchVectorField::updateCoeffs();
}


void tnbLib::fixedShearStressFvPatchVectorField::write(Ostream& os) const
{
	fvPatchVectorField::write(os);
	writeEntry(os, "tau", tau0_);
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchVectorField,
		fixedShearStressFvPatchVectorField
	);
}

// ************************************************************************* //