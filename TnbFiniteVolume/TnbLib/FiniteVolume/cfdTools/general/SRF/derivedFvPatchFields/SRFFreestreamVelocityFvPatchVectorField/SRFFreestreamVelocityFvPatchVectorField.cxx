#include <SRFFreestreamVelocityFvPatchVectorField.hxx>

#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <SRFModel.hxx>
#include <steadyStateDdtScheme.hxx>
#include <addToRunTimeSelectionTable.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::SRFFreestreamVelocityFvPatchVectorField::
SRFFreestreamVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF
)
	:
	inletOutletFvPatchVectorField(p, iF),
	relative_(false),
	UInf_(Zero)
{}


tnbLib::SRFFreestreamVelocityFvPatchVectorField::
SRFFreestreamVelocityFvPatchVectorField
(
	const SRFFreestreamVelocityFvPatchVectorField& ptf,
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	inletOutletFvPatchVectorField(ptf, p, iF, mapper),
	relative_(ptf.relative_),
	UInf_(ptf.UInf_)
{}


tnbLib::SRFFreestreamVelocityFvPatchVectorField::
SRFFreestreamVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const dictionary& dict
)
	:
	inletOutletFvPatchVectorField(p, iF),
	relative_(dict.lookupOrDefault("relative", false)),
	UInf_(dict.lookup("UInf"))
{
	this->phiName_ = dict.lookupOrDefault<word>("phi", "phi");

	fvPatchVectorField::operator=(vectorField("value", dict, p.size()));
}


tnbLib::SRFFreestreamVelocityFvPatchVectorField::
SRFFreestreamVelocityFvPatchVectorField
(
	const SRFFreestreamVelocityFvPatchVectorField& srfvpvf
)
	:
	inletOutletFvPatchVectorField(srfvpvf),
	relative_(srfvpvf.relative_),
	UInf_(srfvpvf.UInf_)
{}


tnbLib::SRFFreestreamVelocityFvPatchVectorField::
SRFFreestreamVelocityFvPatchVectorField
(
	const SRFFreestreamVelocityFvPatchVectorField& srfvpvf,
	const DimensionedField<vector, volMesh>& iF
)
	:
	inletOutletFvPatchVectorField(srfvpvf, iF),
	relative_(srfvpvf.relative_),
	UInf_(srfvpvf.UInf_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::SRFFreestreamVelocityFvPatchVectorField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	// Get reference to the SRF model
	const SRF::SRFModel& srf =
		db().lookupObject<SRF::SRFModel>("SRFProperties");


	word ddtScheme
	(
		this->internalField().mesh()
		.ddtScheme(this->internalField().name())
	);

	if (ddtScheme == fv::steadyStateDdtScheme<scalar>::typeName)
	{
		// If not relative to the SRF include the effect of the SRF
		if (!relative_)
		{
			refValue() = UInf_ - srf.velocity(patch().Cf());
		}
		// If already relative to the SRF simply supply the inlet value
		// as a fixed value
		else
		{
			refValue() = UInf_;
		}
	}
	else
	{
		scalar time = this->db().time().value();
		scalar theta = time * mag(srf.omega().value());

		refValue() =
			cos(theta)*UInf_ + sin(theta)*(srf.axis() ^ UInf_)
			- srf.velocity(patch().Cf());
	}

	// Set the inlet-outlet choice based on the direction of the freestream
	valueFraction() = 1.0 - pos0(refValue() & patch().Sf());

	mixedFvPatchField<vector>::updateCoeffs();
}


void tnbLib::SRFFreestreamVelocityFvPatchVectorField::write(Ostream& os) const
{
	fvPatchVectorField::write(os);
	writeEntry(os, "relative", relative_);
	writeEntry(os, "UInf", UInf_);
	writeEntry(os, "phi", this->phiName_);
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchVectorField,
		SRFFreestreamVelocityFvPatchVectorField
	);
}


// ************************************************************************* //