#include <swirlFlowRateInletVelocityFvPatchVectorField.hxx>

#include <volFields.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <surfaceFields.hxx>
#include <mathematicalConstants.hxx>

#include <Time.hxx> // added by amir
#include <PstreamReduceOps.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::swirlFlowRateInletVelocityFvPatchVectorField::
swirlFlowRateInletVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchField<vector>(p, iF),
	phiName_("phi"),
	rhoName_("rho"),
	origin_(),
	axis_(Zero),
	flowRate_(),
	rpm_()
{}


tnbLib::swirlFlowRateInletVelocityFvPatchVectorField::
swirlFlowRateInletVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchField<vector>(p, iF, dict),
	phiName_(dict.lookupOrDefault<word>("phi", "phi")),
	rhoName_(dict.lookupOrDefault<word>("rho", "rho")),
	origin_
	(
		dict.lookupOrDefault
		(
			"origin",
			returnReduce(patch().size(), sumOp<label>())
			? gSum(patch().Cf()*patch().magSf()) / gSum(patch().magSf())
			: Zero
		)
	),
	axis_
	(
		dict.lookupOrDefault
		(
			"axis",
			returnReduce(patch().size(), sumOp<label>())
			? -gSum(patch().Sf()) / gSum(patch().magSf())
			: Zero
		)
	),
	flowRate_(Function1<scalar>::New("flowRate", dict)),
	rpm_(Function1<scalar>::New("rpm", dict))
{}


tnbLib::swirlFlowRateInletVelocityFvPatchVectorField::
swirlFlowRateInletVelocityFvPatchVectorField
(
	const swirlFlowRateInletVelocityFvPatchVectorField& ptf,
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchField<vector>(ptf, p, iF, mapper),
	phiName_(ptf.phiName_),
	rhoName_(ptf.rhoName_),
	origin_(ptf.origin_),
	axis_(ptf.axis_),
	flowRate_(ptf.flowRate_, false),
	rpm_(ptf.rpm_, false)
{}


tnbLib::swirlFlowRateInletVelocityFvPatchVectorField::
swirlFlowRateInletVelocityFvPatchVectorField
(
	const swirlFlowRateInletVelocityFvPatchVectorField& ptf
)
	:
	fixedValueFvPatchField<vector>(ptf),
	phiName_(ptf.phiName_),
	rhoName_(ptf.rhoName_),
	origin_(ptf.origin_),
	axis_(ptf.axis_),
	flowRate_(ptf.flowRate_, false),
	rpm_(ptf.rpm_, false)
{}


tnbLib::swirlFlowRateInletVelocityFvPatchVectorField::
swirlFlowRateInletVelocityFvPatchVectorField
(
	const swirlFlowRateInletVelocityFvPatchVectorField& ptf,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchField<vector>(ptf, iF),
	phiName_(ptf.phiName_),
	rhoName_(ptf.rhoName_),
	origin_(ptf.origin_),
	axis_(ptf.axis_),
	flowRate_(ptf.flowRate_, false),
	rpm_(ptf.rpm_, false)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::swirlFlowRateInletVelocityFvPatchVectorField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	const scalar t = this->db().time().timeOutputValue();
	const scalar flowRate = flowRate_->value(t);
	const scalar rpm = rpm_->value(t);

	const scalar totArea = gSum(patch().magSf());
	const scalar avgU = -flowRate / totArea;

	const vector axisHat = axis_ / mag(axis_);

	// Update angular velocity - convert [rpm] to [rad/s]
	tmp<vectorField> tangentialVelocity
	(
		axisHat ^ (rpm*constant::mathematical::pi / 30.0)*(patch().Cf() - origin_)
	);

	tmp<vectorField> n = patch().nf();

	const surfaceScalarField& phi =
		db().lookupObject<surfaceScalarField>(phiName_);

	if (phi.dimensions() == dimVelocity * dimArea)
	{
		// volumetric flow-rate
		operator==(tangentialVelocity + n * avgU);
	}
	else if (phi.dimensions() == dimDensity * dimVelocity*dimArea)
	{
		const fvPatchField<scalar>& rhop =
			patch().lookupPatchField<volScalarField, scalar>(rhoName_);

		// mass flow-rate
		operator==(tangentialVelocity + n * avgU / rhop);
	}
	else
	{
		FatalErrorInFunction
			<< "dimensions of " << phiName_ << " are incorrect" << nl
			<< "    on patch " << this->patch().name()
			<< " of field " << this->internalField().name()
			<< " in file " << this->internalField().objectPath()
			<< nl << exit(FatalError);
	}

	fixedValueFvPatchField<vector>::updateCoeffs();
}


void tnbLib::swirlFlowRateInletVelocityFvPatchVectorField::write
(
	Ostream& os
) const
{
	fvPatchField<vector>::write(os);
	writeEntryIfDifferent<word>(os, "phi", "phi", phiName_);
	writeEntryIfDifferent<word>(os, "rho", "rho", rhoName_);
	writeEntry(os, "origin", origin_);
	writeEntry(os, "axis", axis_);
	writeEntry(os, flowRate_());
	writeEntry(os, rpm_());
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchVectorField,
		swirlFlowRateInletVelocityFvPatchVectorField
	);
}


// ************************************************************************* //