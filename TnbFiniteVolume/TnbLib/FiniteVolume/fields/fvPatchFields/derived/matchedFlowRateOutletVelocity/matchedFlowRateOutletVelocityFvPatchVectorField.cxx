#include <matchedFlowRateOutletVelocityFvPatchVectorField.hxx>

#include <volFields.hxx>
#include <one.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::matchedFlowRateOutletVelocityFvPatchVectorField::
matchedFlowRateOutletVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchField<vector>(p, iF),
	inletPatchName_(),
	volumetric_(false),
	rhoName_("rho")
{}


tnbLib::matchedFlowRateOutletVelocityFvPatchVectorField::
matchedFlowRateOutletVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchField<vector>(p, iF, dict, false),
	inletPatchName_(dict.lookup("inletPatch")),
	volumetric_(dict.lookupOrDefault("volumetric", true))
{
	if (volumetric_)
	{
		rhoName_ = "none";
	}
	else
	{
		rhoName_ = word(dict.lookupOrDefault<word>("rho", "rho"));
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


tnbLib::matchedFlowRateOutletVelocityFvPatchVectorField::
matchedFlowRateOutletVelocityFvPatchVectorField
(
	const matchedFlowRateOutletVelocityFvPatchVectorField& ptf,
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchField<vector>(ptf, p, iF, mapper),
	inletPatchName_(ptf.inletPatchName_),
	volumetric_(ptf.volumetric_),
	rhoName_(ptf.rhoName_)
{}


tnbLib::matchedFlowRateOutletVelocityFvPatchVectorField::
matchedFlowRateOutletVelocityFvPatchVectorField
(
	const matchedFlowRateOutletVelocityFvPatchVectorField& ptf
)
	:
	fixedValueFvPatchField<vector>(ptf),
	inletPatchName_(ptf.inletPatchName_),
	volumetric_(ptf.volumetric_),
	rhoName_(ptf.rhoName_)
{}


tnbLib::matchedFlowRateOutletVelocityFvPatchVectorField::
matchedFlowRateOutletVelocityFvPatchVectorField
(
	const matchedFlowRateOutletVelocityFvPatchVectorField& ptf,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchField<vector>(ptf, iF),
	inletPatchName_(ptf.inletPatchName_),
	volumetric_(ptf.volumetric_),
	rhoName_(ptf.rhoName_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class RhoType>
void tnbLib::matchedFlowRateOutletVelocityFvPatchVectorField::updateValues
(
	const label inletPatchID,
	const RhoType& rhoOutlet,
	const RhoType& rhoInlet
)
{
	const fvPatch& p = patch();
	const fvPatch& inletPatch = p.boundaryMesh()[inletPatchID];

	const vectorField n(p.nf());

	// Extrapolate patch velocity
	vectorField Up(patchInternalField());

	// Patch normal extrapolated velocity
	scalarField nUp(n & Up);

	// Remove the normal component of the extrapolate patch velocity
	Up -= nUp * n;

	// Remove any reverse flow
	nUp = max(nUp, scalar(0));

	// Lookup non-const access to velocity field
	volVectorField& U
	(
		const_cast<volVectorField&>
		(
			dynamic_cast<const volVectorField&>(internalField())
			)
	);

	// Get the corresponding inlet velocity patch field
	fvPatchVectorField& inletPatchU = U.boundaryFieldRef()[inletPatchID];

	// Ensure that the corresponding inlet velocity patch field is up-to-date
	inletPatchU.updateCoeffs();

	// Calculate the inlet patch flow rate
	const scalar flowRate = -gSum(rhoInlet*(inletPatch.Sf() & inletPatchU));

	// Calculate the extrapolated outlet patch flow rate
	const scalar estimatedFlowRate = gSum(rhoOutlet*(patch().magSf()*nUp));

	if (estimatedFlowRate / flowRate > 0.5)
	{
		nUp *= (mag(flowRate) / mag(estimatedFlowRate));
	}
	else
	{
		nUp += ((flowRate - estimatedFlowRate) / gSum(rhoOutlet*patch().magSf()));
	}

	// Add the corrected normal component of velocity to the patch velocity
	Up += nUp * n;

	// Correct the patch velocity
	operator==(Up);
}


void tnbLib::matchedFlowRateOutletVelocityFvPatchVectorField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	// Find corresponding inlet patch
	const label inletPatchID =
		patch().patch().boundaryMesh().findPatchID(inletPatchName_);

	if (inletPatchID < 0)
	{
		FatalErrorInFunction
			<< "Unable to find inlet patch " << inletPatchName_
			<< exit(FatalError);
	}

	if (volumetric_)
	{
		updateValues(inletPatchID, one(), one());
	}
	else
	{
		// Mass flow-rate
		if (db().foundObject<volScalarField>(rhoName_))
		{
			const volScalarField& rho = db().lookupObject<volScalarField>
				(
					rhoName_
					);

			updateValues
			(
				inletPatchID,
				rho.boundaryField()[patch().index()],
				rho.boundaryField()[inletPatchID]
			);
		}
		else
		{
			FatalErrorInFunction
				<< "Cannot find density field " << rhoName_ << exit(FatalError);
		}
	}

	fixedValueFvPatchVectorField::updateCoeffs();
}


void tnbLib::matchedFlowRateOutletVelocityFvPatchVectorField::write
(
	Ostream& os
) const
{
	fvPatchField<vector>::write(os);
	writeEntry(os, "inletPatch", inletPatchName_);
	if (!volumetric_)
	{
		writeEntry(os, "volumetric", volumetric_);
		writeEntryIfDifferent<word>(os, "rho", "rho", rhoName_);
	}
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchVectorField,
		matchedFlowRateOutletVelocityFvPatchVectorField
	);
}


// ************************************************************************* //