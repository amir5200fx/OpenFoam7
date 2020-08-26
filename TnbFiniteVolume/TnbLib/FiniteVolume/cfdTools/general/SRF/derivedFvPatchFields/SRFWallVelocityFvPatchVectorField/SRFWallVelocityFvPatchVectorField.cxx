#include <SRFWallVelocityFvPatchVectorField.hxx>

#include <volFields.hxx>
#include <SRFModel.hxx>
#include <addToRunTimeSelectionTable.hxx>

#include <fvPatchFieldMapper.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::SRFWallVelocityFvPatchVectorField::SRFWallVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchVectorField(p, iF)
{}


tnbLib::SRFWallVelocityFvPatchVectorField::SRFWallVelocityFvPatchVectorField
(
	const SRFWallVelocityFvPatchVectorField& ptf,
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchVectorField(ptf, p, iF, mapper)
{}


tnbLib::SRFWallVelocityFvPatchVectorField::SRFWallVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchVectorField(p, iF, dict)
{}


tnbLib::SRFWallVelocityFvPatchVectorField::SRFWallVelocityFvPatchVectorField
(
	const SRFWallVelocityFvPatchVectorField& srfvpvf
)
	:
	fixedValueFvPatchVectorField(srfvpvf)
{}


tnbLib::SRFWallVelocityFvPatchVectorField::SRFWallVelocityFvPatchVectorField
(
	const SRFWallVelocityFvPatchVectorField& srfvpvf,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchVectorField(srfvpvf, iF)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::SRFWallVelocityFvPatchVectorField::autoMap
(
	const fvPatchFieldMapper& m
)
{
	m(*this, *this);
}


void tnbLib::SRFWallVelocityFvPatchVectorField::rmap
(
	const fvPatchVectorField& ptf,
	const labelList& addr
)
{
	fixedValueFvPatchVectorField::rmap(ptf, addr);
}


void tnbLib::SRFWallVelocityFvPatchVectorField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	// Get reference to the SRF model
	const SRF::SRFModel& srf =
		db().lookupObject<SRF::SRFModel>("SRFProperties");

	// Determine patch velocity due to SRF
	const vectorField Up(-srf.velocity(patch().Cf()));

	// Remove the component of Up normal to the wall
	// just in case it is not exactly circular
	const vectorField n(patch().nf());
	vectorField::operator=(Up - n * (n & Up));

	fixedValueFvPatchVectorField::updateCoeffs();
}


void tnbLib::SRFWallVelocityFvPatchVectorField::write(Ostream& os) const
{
	fvPatchVectorField::write(os);
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchVectorField,
		SRFWallVelocityFvPatchVectorField
	);
}

// ************************************************************************* //