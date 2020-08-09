#include <translatingWallVelocityFvPatchVectorField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <volFields.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::translatingWallVelocityFvPatchVectorField::
translatingWallVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchField<vector>(p, iF),
	U_(0)
{}


tnbLib::translatingWallVelocityFvPatchVectorField::
translatingWallVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchField<vector>(p, iF, dict, false),
	U_(Function1<vector>::New("U", dict))
{
	// Evaluate the wall velocity
	updateCoeffs();
}


tnbLib::translatingWallVelocityFvPatchVectorField::
translatingWallVelocityFvPatchVectorField
(
	const translatingWallVelocityFvPatchVectorField& ptf,
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchField<vector>(ptf, p, iF, mapper),
	U_(ptf.U_, false)
{}


tnbLib::translatingWallVelocityFvPatchVectorField::
translatingWallVelocityFvPatchVectorField
(
	const translatingWallVelocityFvPatchVectorField& twvpvf
)
	:
	fixedValueFvPatchField<vector>(twvpvf),
	U_(twvpvf.U_, false)
{}


tnbLib::translatingWallVelocityFvPatchVectorField::
translatingWallVelocityFvPatchVectorField
(
	const translatingWallVelocityFvPatchVectorField& twvpvf,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchField<vector>(twvpvf, iF),
	U_(twvpvf.U_, false)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::translatingWallVelocityFvPatchVectorField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	const scalar t = this->db().time().timeOutputValue();
	const vector U = U_->value(t);

	// Remove the component of U normal to the wall in case the wall is not flat
	const vectorField n(patch().nf());
	vectorField::operator=(U - n * (n & U));

	fixedValueFvPatchVectorField::updateCoeffs();
}


void tnbLib::translatingWallVelocityFvPatchVectorField::write(Ostream& os) const
{
	fvPatchVectorField::write(os);
	writeEntry(os, U_());
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchVectorField,
		translatingWallVelocityFvPatchVectorField
	);
}

// ************************************************************************* //