#include <flowRateInletVelocityFvPatchVectorField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <volFields.hxx>
#include <one.hxx>

#include <Time.hxx> // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::flowRateInletVelocityFvPatchVectorField::
flowRateInletVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchField<vector>(p, iF),
	flowRate_(),
	volumetric_(false),
	rhoName_("rho"),
	rhoInlet_(0.0),
	extrapolateProfile_(false)
{}


tnbLib::flowRateInletVelocityFvPatchVectorField::
flowRateInletVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchField<vector>(p, iF, dict, false),
	rhoInlet_(dict.lookupOrDefault<scalar>("rhoInlet", -vGreat)),
	extrapolateProfile_
	(
		dict.lookupOrDefault<Switch>("extrapolateProfile", false)
	)
{
	if (dict.found("volumetricFlowRate"))
	{
		volumetric_ = true;
		flowRate_ = Function1<scalar>::New("volumetricFlowRate", dict);
		rhoName_ = "rho";
	}
	else if (dict.found("massFlowRate"))
	{
		volumetric_ = false;
		flowRate_ = Function1<scalar>::New("massFlowRate", dict);
		rhoName_ = word(dict.lookupOrDefault<word>("rho", "rho"));
	}
	else
	{
		FatalIOErrorInFunction
		(
			dict
		) << "Please supply either 'volumetricFlowRate' or"
			<< " 'massFlowRate' and 'rho'" << exit(FatalIOError);
	}

	// Value field require if mass based
	if (dict.found("value"))
	{
		fvPatchField<vector>::operator=
			(
				vectorField("value", dict, p.size())
				);
	}
	else
	{
		evaluate(Pstream::commsTypes::blocking);
	}
}


tnbLib::flowRateInletVelocityFvPatchVectorField::
flowRateInletVelocityFvPatchVectorField
(
	const flowRateInletVelocityFvPatchVectorField& ptf,
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchField<vector>(ptf, p, iF, mapper),
	flowRate_(ptf.flowRate_, false),
	volumetric_(ptf.volumetric_),
	rhoName_(ptf.rhoName_),
	rhoInlet_(ptf.rhoInlet_),
	extrapolateProfile_(ptf.extrapolateProfile_)
{}


tnbLib::flowRateInletVelocityFvPatchVectorField::
flowRateInletVelocityFvPatchVectorField
(
	const flowRateInletVelocityFvPatchVectorField& ptf
)
	:
	fixedValueFvPatchField<vector>(ptf),
	flowRate_(ptf.flowRate_, false),
	volumetric_(ptf.volumetric_),
	rhoName_(ptf.rhoName_),
	rhoInlet_(ptf.rhoInlet_),
	extrapolateProfile_(ptf.extrapolateProfile_)
{}


tnbLib::flowRateInletVelocityFvPatchVectorField::
flowRateInletVelocityFvPatchVectorField
(
	const flowRateInletVelocityFvPatchVectorField& ptf,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchField<vector>(ptf, iF),
	flowRate_(ptf.flowRate_, false),
	volumetric_(ptf.volumetric_),
	rhoName_(ptf.rhoName_),
	rhoInlet_(ptf.rhoInlet_),
	extrapolateProfile_(ptf.extrapolateProfile_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class RhoType>
void tnbLib::flowRateInletVelocityFvPatchVectorField::updateValues
(
	const RhoType& rho
)
{
	const scalar t = db().time().timeOutputValue();

	const vectorField n(patch().nf());

	if (extrapolateProfile_)
	{
		vectorField Up(this->patchInternalField());

		// Patch normal extrapolated velocity
		scalarField nUp(n & Up);

		// Remove the normal component of the extrapolate patch velocity
		Up -= nUp * n;

		// Remove any reverse flow
		nUp = min(nUp, scalar(0));

		const scalar flowRate = flowRate_->value(t);
		const scalar estimatedFlowRate = -gSum(rho*(this->patch().magSf()*nUp));

		if (estimatedFlowRate / flowRate > 0.5)
		{
			nUp *= (mag(flowRate) / mag(estimatedFlowRate));
		}
		else
		{
			nUp -= ((flowRate - estimatedFlowRate) / gSum(rho*patch().magSf()));
		}

		// Add the corrected normal component of velocity to the patch velocity
		Up += nUp * n;

		// Correct the patch velocity
		this->operator==(Up);
	}
	else
	{
		const scalar avgU = -flowRate_->value(t) / gSum(rho*patch().magSf());
		operator==(avgU*n);
	}
}


void tnbLib::flowRateInletVelocityFvPatchVectorField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	if (volumetric_ || rhoName_ == "none")
	{
		updateValues(one());
	}
	else
	{
		// Mass flow-rate
		if (db().foundObject<volScalarField>(rhoName_))
		{
			const fvPatchField<scalar>& rhop =
				patch().lookupPatchField<volScalarField, scalar>(rhoName_);

			updateValues(rhop);
		}
		else
		{
			// Use constant density
			if (rhoInlet_ < 0)
			{
				FatalErrorInFunction
					<< "Did not find registered density field " << rhoName_
					<< " and no constant density 'rhoInlet' specified"
					<< exit(FatalError);
			}

			updateValues(rhoInlet_);
		}
	}

	fixedValueFvPatchVectorField::updateCoeffs();
}


void tnbLib::flowRateInletVelocityFvPatchVectorField::write(Ostream& os) const
{
	fvPatchField<vector>::write(os);
	writeEntry(os, flowRate_());
	if (!volumetric_)
	{
		writeEntryIfDifferent<word>(os, "rho", "rho", rhoName_);
		writeEntryIfDifferent<scalar>(os, "rhoInlet", -vGreat, rhoInlet_);
	}
	writeEntry(os, "extrapolateProfile", extrapolateProfile_);
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchVectorField,
		flowRateInletVelocityFvPatchVectorField
	);
}


// ************************************************************************* //