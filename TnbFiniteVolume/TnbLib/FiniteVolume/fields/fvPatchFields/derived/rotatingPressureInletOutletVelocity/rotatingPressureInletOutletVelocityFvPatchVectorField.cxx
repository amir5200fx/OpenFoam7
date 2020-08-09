#include <rotatingPressureInletOutletVelocityFvPatchVectorField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::rotatingPressureInletOutletVelocityFvPatchVectorField::
calcTangentialVelocity()
{
	const scalar t = this->db().time().timeOutputValue();
	vector om = omega_->value(t);

	vector axisHat = om / mag(om);
	const vectorField tangentialVelocity
	(
		(-om) ^ (patch().Cf() - axisHat * (axisHat & patch().Cf()))
	);

	const vectorField n(patch().nf());
	refValue() = tangentialVelocity - n * (n & tangentialVelocity);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::rotatingPressureInletOutletVelocityFvPatchVectorField::
rotatingPressureInletOutletVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF
)
	:
	pressureInletOutletVelocityFvPatchVectorField(p, iF),
	omega_()
{}


tnbLib::rotatingPressureInletOutletVelocityFvPatchVectorField::
rotatingPressureInletOutletVelocityFvPatchVectorField
(
	const rotatingPressureInletOutletVelocityFvPatchVectorField& ptf,
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	pressureInletOutletVelocityFvPatchVectorField(ptf, p, iF, mapper),
	omega_(ptf.omega_, false)
{
	calcTangentialVelocity();
}


tnbLib::rotatingPressureInletOutletVelocityFvPatchVectorField::
rotatingPressureInletOutletVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const dictionary& dict
)
	:
	pressureInletOutletVelocityFvPatchVectorField(p, iF, dict),
	omega_(Function1<vector>::New("omega", dict))
{
	calcTangentialVelocity();
}


tnbLib::rotatingPressureInletOutletVelocityFvPatchVectorField::
rotatingPressureInletOutletVelocityFvPatchVectorField
(
	const rotatingPressureInletOutletVelocityFvPatchVectorField& rppvf
)
	:
	pressureInletOutletVelocityFvPatchVectorField(rppvf),
	omega_(rppvf.omega_, false)
{
	calcTangentialVelocity();
}


tnbLib::rotatingPressureInletOutletVelocityFvPatchVectorField::
rotatingPressureInletOutletVelocityFvPatchVectorField
(
	const rotatingPressureInletOutletVelocityFvPatchVectorField& rppvf,
	const DimensionedField<vector, volMesh>& iF
)
	:
	pressureInletOutletVelocityFvPatchVectorField(rppvf, iF),
	omega_(rppvf.omega_, false)
{
	calcTangentialVelocity();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::rotatingPressureInletOutletVelocityFvPatchVectorField::write
(
	Ostream& os
) const
{
	fvPatchVectorField::write(os);
	writeEntry(os, "phi", phiName());
	writeEntry(os, omega_());
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchVectorField,
		rotatingPressureInletOutletVelocityFvPatchVectorField
	);
}

// ************************************************************************* //