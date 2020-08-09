#include <noSlipFvPatchVectorField.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::noSlipFvPatchVectorField::noSlipFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchVectorField(p, iF)
{
	operator==(Zero);
}


tnbLib::noSlipFvPatchVectorField::noSlipFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchVectorField(p, iF, dict, false)
{
	operator==(Zero);
}


tnbLib::noSlipFvPatchVectorField::noSlipFvPatchVectorField
(
	const noSlipFvPatchVectorField& ptf,
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchVectorField(ptf, p, iF, mapper, false) // Don't map
{
	operator==(Zero);
}


tnbLib::noSlipFvPatchVectorField::noSlipFvPatchVectorField
(
	const noSlipFvPatchVectorField& mwvpvf
)
	:
	fixedValueFvPatchVectorField(mwvpvf)
{}


tnbLib::noSlipFvPatchVectorField::noSlipFvPatchVectorField
(
	const noSlipFvPatchVectorField& mwvpvf,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchVectorField(mwvpvf, iF)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::noSlipFvPatchVectorField::write(Ostream& os) const
{
	fvPatchVectorField::write(os);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchVectorField,
		noSlipFvPatchVectorField
	);
}

// ************************************************************************* //