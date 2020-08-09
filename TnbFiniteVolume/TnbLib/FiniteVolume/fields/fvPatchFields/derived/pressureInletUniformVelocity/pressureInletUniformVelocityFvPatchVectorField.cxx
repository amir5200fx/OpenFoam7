#include <pressureInletUniformVelocityFvPatchVectorField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::pressureInletUniformVelocityFvPatchVectorField::
pressureInletUniformVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF
)
	:
	pressureInletVelocityFvPatchVectorField(p, iF)
{}


tnbLib::pressureInletUniformVelocityFvPatchVectorField::
pressureInletUniformVelocityFvPatchVectorField
(
	const pressureInletUniformVelocityFvPatchVectorField& ptf,
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	pressureInletVelocityFvPatchVectorField(ptf, p, iF, mapper)
{}


tnbLib::pressureInletUniformVelocityFvPatchVectorField::
pressureInletUniformVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const dictionary& dict
)
	:
	pressureInletVelocityFvPatchVectorField(p, iF, dict)
{}


tnbLib::pressureInletUniformVelocityFvPatchVectorField::
pressureInletUniformVelocityFvPatchVectorField
(
	const pressureInletUniformVelocityFvPatchVectorField& pivpvf
)
	:
	pressureInletVelocityFvPatchVectorField(pivpvf)
{}


tnbLib::pressureInletUniformVelocityFvPatchVectorField::
pressureInletUniformVelocityFvPatchVectorField
(
	const pressureInletUniformVelocityFvPatchVectorField& pivpvf,
	const DimensionedField<vector, volMesh>& iF
)
	:
	pressureInletVelocityFvPatchVectorField(pivpvf, iF)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::pressureInletUniformVelocityFvPatchVectorField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	pressureInletVelocityFvPatchVectorField::updateCoeffs();

	operator==(patch().nf()*gSum(patch().Sf() & *this) / gSum(patch().magSf()));
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void tnbLib::pressureInletUniformVelocityFvPatchVectorField::operator=
(
	const fvPatchField<vector>& pvf
	)
{
	operator==(patch().nf()*gSum(patch().Sf() & pvf) / gSum(patch().magSf()));
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchVectorField,
		pressureInletUniformVelocityFvPatchVectorField
	);
}

// ************************************************************************* //