#include <cylindricalInletVelocityFvPatchVectorField.hxx>

#include <volFields.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <surfaceFields.hxx>
#include <mathematicalConstants.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::cylindricalInletVelocityFvPatchVectorField::
cylindricalInletVelocityFvPatchVectorField
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
	rpm_()
{}


tnbLib::cylindricalInletVelocityFvPatchVectorField::
cylindricalInletVelocityFvPatchVectorField
(
	const cylindricalInletVelocityFvPatchVectorField& ptf,
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
	rpm_(ptf.rpm_, false)
{}


tnbLib::cylindricalInletVelocityFvPatchVectorField::
cylindricalInletVelocityFvPatchVectorField
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
	rpm_(Function1<scalar>::New("rpm", dict))
{}


tnbLib::cylindricalInletVelocityFvPatchVectorField::
cylindricalInletVelocityFvPatchVectorField
(
	const cylindricalInletVelocityFvPatchVectorField& ptf
)
	:
	fixedValueFvPatchField<vector>(ptf),
	origin_(ptf.origin_),
	axis_(ptf.axis_),
	axialVelocity_(ptf.axialVelocity_, false),
	radialVelocity_(ptf.radialVelocity_, false),
	rpm_(ptf.rpm_, false)
{}


tnbLib::cylindricalInletVelocityFvPatchVectorField::
cylindricalInletVelocityFvPatchVectorField
(
	const cylindricalInletVelocityFvPatchVectorField& ptf,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchField<vector>(ptf, iF),
	origin_(ptf.origin_),
	axis_(ptf.axis_),
	axialVelocity_(ptf.axialVelocity_, false),
	radialVelocity_(ptf.radialVelocity_, false),
	rpm_(ptf.rpm_, false)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::cylindricalInletVelocityFvPatchVectorField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	const scalar t = this->db().time().timeOutputValue();
	const scalar axialVelocity = axialVelocity_->value(t);
	const scalar radialVelocity = radialVelocity_->value(t);
	const scalar rpm = rpm_->value(t);

	const vector axisHat = axis_ / mag(axis_);

	const vectorField r(patch().Cf() - origin_);
	const vectorField d(r - (axisHat & r)*axisHat);

	tmp<vectorField> tangVel
	(
		(rpm*constant::mathematical::pi / 30.0)*(axisHat) ^ d
	);

	operator==(tangVel + axisHat * axialVelocity + radialVelocity * d / mag(d));

	fixedValueFvPatchField<vector>::updateCoeffs();
}


void tnbLib::cylindricalInletVelocityFvPatchVectorField::write(Ostream& os) const
{
	fvPatchField<vector>::write(os);
	writeEntry(os, "origin", origin_);
	writeEntry(os, "axis", axis_);
	writeEntry(os, axialVelocity_());
	writeEntry(os, radialVelocity_());
	writeEntry(os, rpm_());
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchVectorField,
		cylindricalInletVelocityFvPatchVectorField
	);
}


// ************************************************************************* //