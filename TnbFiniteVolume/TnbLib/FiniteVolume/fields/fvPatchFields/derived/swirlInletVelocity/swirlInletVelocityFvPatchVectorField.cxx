#include <swirlInletVelocityFvPatchVectorField.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::swirlInletVelocityFvPatchVectorField::
swirlInletVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchField<vector>(p, iF),
	origin_(Zero),
	axis_(Zero),
	axialVelocity_(),
	radialVelocity_(),
	tangentialVelocity_()
{}


tnbLib::swirlInletVelocityFvPatchVectorField::
swirlInletVelocityFvPatchVectorField
(
	const swirlInletVelocityFvPatchVectorField& ptf,
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchField<vector>(ptf, p, iF, mapper),
	origin_(ptf.origin_),
	axis_(ptf.axis_),
	axialVelocity_(ptf.axialVelocity_, false),
	radialVelocity_(ptf.radialVelocity_, false),
	tangentialVelocity_(ptf.tangentialVelocity_, false)
{}


tnbLib::swirlInletVelocityFvPatchVectorField::
swirlInletVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchField<vector>(p, iF, dict),
	origin_(dict.lookup("origin")),
	axis_(dict.lookup("axis")),
	axialVelocity_(Function1<scalar>::New("axialVelocity", dict)),
	radialVelocity_(Function1<scalar>::New("radialVelocity", dict)),
	tangentialVelocity_(Function1<scalar>::New("tangentialVelocity", dict))
{}


tnbLib::swirlInletVelocityFvPatchVectorField::
swirlInletVelocityFvPatchVectorField
(
	const swirlInletVelocityFvPatchVectorField& ptf
)
	:
	fixedValueFvPatchField<vector>(ptf),
	origin_(ptf.origin_),
	axis_(ptf.axis_),
	axialVelocity_(ptf.axialVelocity_, false),
	radialVelocity_(ptf.radialVelocity_, false),
	tangentialVelocity_(ptf.tangentialVelocity_, false)
{}


tnbLib::swirlInletVelocityFvPatchVectorField::
swirlInletVelocityFvPatchVectorField
(
	const swirlInletVelocityFvPatchVectorField& ptf,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchField<vector>(ptf, iF),
	origin_(ptf.origin_),
	axis_(ptf.axis_),
	axialVelocity_(ptf.axialVelocity_, false),
	radialVelocity_(ptf.radialVelocity_, false),
	tangentialVelocity_(ptf.tangentialVelocity_, false)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::swirlInletVelocityFvPatchVectorField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	const vector axisHat = axis_ / mag(axis_);

	// Radius vector in plane of rotation
	vectorField r(patch().Cf() - origin_);
	r -= (axisHat & r)*axisHat;
	const scalarField magr(mag(r));
	const vectorField rHat(r / magr);

	const scalarField axialVelocity(axialVelocity_->value(magr));
	const scalarField radialVelocity(radialVelocity_->value(magr));
	const scalarField tangentialVelocity(tangentialVelocity_->value(magr));

	operator==
		(
			axialVelocity*axisHat
			+ radialVelocity * rHat
			+ tangentialVelocity * (axisHat ^ rHat)
			);

	fixedValueFvPatchField<vector>::updateCoeffs();
}


void tnbLib::swirlInletVelocityFvPatchVectorField::write(Ostream& os) const
{
	fvPatchField<vector>::write(os);
	writeEntry(os, "origin", origin_);
	writeEntry(os, "axis", axis_);
	writeEntry(os, axialVelocity_());
	writeEntry(os, radialVelocity_());
	writeEntry(os, tangentialVelocity_());
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchVectorField,
		swirlInletVelocityFvPatchVectorField
	);
}


// ************************************************************************* //