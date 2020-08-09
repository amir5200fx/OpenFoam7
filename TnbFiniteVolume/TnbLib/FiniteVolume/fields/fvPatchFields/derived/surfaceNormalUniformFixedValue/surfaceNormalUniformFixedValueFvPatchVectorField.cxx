#include <surfaceNormalUniformFixedValueFvPatchVectorField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <volFields.hxx>
#include <fvPatchFieldMapper.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::surfaceNormalUniformFixedValueFvPatchVectorField::
surfaceNormalUniformFixedValueFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchVectorField(p, iF),
	uniformValue_()
{}


tnbLib::surfaceNormalUniformFixedValueFvPatchVectorField::
surfaceNormalUniformFixedValueFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchVectorField(p, iF, dict, false),
	uniformValue_(Function1<scalar>::New("uniformValue", dict))
{
	this->evaluate();
}


tnbLib::surfaceNormalUniformFixedValueFvPatchVectorField::
surfaceNormalUniformFixedValueFvPatchVectorField
(
	const surfaceNormalUniformFixedValueFvPatchVectorField& pvf,
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchVectorField(pvf, p, iF, mapper, false), // Don't map
	uniformValue_(pvf.uniformValue_, false)
{
	// Evaluate since value not mapped
	this->evaluate();
}


tnbLib::surfaceNormalUniformFixedValueFvPatchVectorField::
surfaceNormalUniformFixedValueFvPatchVectorField
(
	const surfaceNormalUniformFixedValueFvPatchVectorField& pvf
)
	:
	fixedValueFvPatchVectorField(pvf),
	uniformValue_(pvf.uniformValue_, false)
{}


tnbLib::surfaceNormalUniformFixedValueFvPatchVectorField::
surfaceNormalUniformFixedValueFvPatchVectorField
(
	const surfaceNormalUniformFixedValueFvPatchVectorField& pvf,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchVectorField(pvf, iF),
	uniformValue_(pvf.uniformValue_, false)
{
	// Evaluate the profile if defined
	if (pvf.uniformValue_.valid())
	{
		this->evaluate();
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::surfaceNormalUniformFixedValueFvPatchVectorField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	const scalar t = this->db().time().timeOutputValue();
	fvPatchVectorField::operator=(uniformValue_->value(t)*patch().nf());

	fvPatchVectorField::updateCoeffs();
}


void tnbLib::surfaceNormalUniformFixedValueFvPatchVectorField::write
(
	Ostream& os
) const
{
	fvPatchVectorField::write(os);
	writeEntry(os, uniformValue_());
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchVectorField,
		surfaceNormalUniformFixedValueFvPatchVectorField
	);
}

// ************************************************************************* //