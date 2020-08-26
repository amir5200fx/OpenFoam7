#include <SRFVelocityFvPatchVectorField.hxx>

#include <volFields.hxx>
#include <SRFModel.hxx>
#include <addToRunTimeSelectionTable.hxx>

#include <fvPatchFieldMapper.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::SRFVelocityFvPatchVectorField::SRFVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchVectorField(p, iF),
	relative_(0),
	inletValue_(p.size(), Zero)
{}


tnbLib::SRFVelocityFvPatchVectorField::SRFVelocityFvPatchVectorField
(
	const SRFVelocityFvPatchVectorField& ptf,
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchVectorField(ptf, p, iF, mapper),
	relative_(ptf.relative_),
	inletValue_(mapper(ptf.inletValue_))
{}


tnbLib::SRFVelocityFvPatchVectorField::SRFVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchVectorField(p, iF, dict),
	relative_(dict.lookup("relative")),
	inletValue_("inletValue", dict, p.size())
{}


tnbLib::SRFVelocityFvPatchVectorField::SRFVelocityFvPatchVectorField
(
	const SRFVelocityFvPatchVectorField& srfvpvf
)
	:
	fixedValueFvPatchVectorField(srfvpvf),
	relative_(srfvpvf.relative_),
	inletValue_(srfvpvf.inletValue_)
{}


tnbLib::SRFVelocityFvPatchVectorField::SRFVelocityFvPatchVectorField
(
	const SRFVelocityFvPatchVectorField& srfvpvf,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchVectorField(srfvpvf, iF),
	relative_(srfvpvf.relative_),
	inletValue_(srfvpvf.inletValue_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::SRFVelocityFvPatchVectorField::autoMap
(
	const fvPatchFieldMapper& m
)
{
	m(*this, *this);
	m(inletValue_, inletValue_);
}


void tnbLib::SRFVelocityFvPatchVectorField::rmap
(
	const fvPatchVectorField& ptf,
	const labelList& addr
)
{
	fixedValueFvPatchVectorField::rmap(ptf, addr);

	const SRFVelocityFvPatchVectorField& tiptf =
		refCast<const SRFVelocityFvPatchVectorField>(ptf);

	inletValue_.rmap(tiptf.inletValue_, addr);
}


void tnbLib::SRFVelocityFvPatchVectorField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	// If not relative to the SRF include the effect of the SRF
	if (!relative_)
	{
		// Get reference to the SRF model
		const SRF::SRFModel& srf =
			db().lookupObject<SRF::SRFModel>("SRFProperties");

		// Determine patch velocity due to SRF
		const vectorField SRFVelocity(srf.velocity(patch().Cf()));

		operator==(-SRFVelocity + inletValue_);
	}
	// If already relative to the SRF simply supply the inlet value as a fixed
	// value
	else
	{
		operator==(inletValue_);
	}

	fixedValueFvPatchVectorField::updateCoeffs();
}


void tnbLib::SRFVelocityFvPatchVectorField::write(Ostream& os) const
{
	fvPatchVectorField::write(os);
	writeEntry(os, "relative", relative_);
	writeEntry(os, "inletValue", inletValue_);
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchVectorField,
		SRFVelocityFvPatchVectorField
	);
}

// ************************************************************************* //