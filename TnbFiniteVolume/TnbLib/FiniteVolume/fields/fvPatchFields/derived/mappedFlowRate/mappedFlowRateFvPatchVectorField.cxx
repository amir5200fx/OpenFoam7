#include <mappedFlowRateFvPatchVectorField.hxx>

#include <volFields.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <mappedPatchBase.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::mappedFlowRateFvPatchVectorField::mappedFlowRateFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchField<vector>(p, iF),
	nbrPhiName_("none"),
	phiName_("phi"),
	rhoName_("rho")
{}


tnbLib::mappedFlowRateFvPatchVectorField::mappedFlowRateFvPatchVectorField
(
	const mappedFlowRateFvPatchVectorField& ptf,
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchField<vector>(ptf, p, iF, mapper),
	nbrPhiName_(ptf.nbrPhiName_),
	phiName_(ptf.phiName_),
	rhoName_(ptf.rhoName_)
{}


tnbLib::mappedFlowRateFvPatchVectorField::mappedFlowRateFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchField<vector>(p, iF, dict),
	nbrPhiName_(dict.lookupOrDefault<word>("nbrPhi", "phi")),
	phiName_(dict.lookupOrDefault<word>("phi", "phi")),
	rhoName_(dict.lookupOrDefault<word>("rho", "rho"))
{}


tnbLib::mappedFlowRateFvPatchVectorField::mappedFlowRateFvPatchVectorField
(
	const mappedFlowRateFvPatchVectorField& ptf
)
	:
	fixedValueFvPatchField<vector>(ptf),
	nbrPhiName_(ptf.nbrPhiName_),
	phiName_(ptf.phiName_),
	rhoName_(ptf.rhoName_)
{}


tnbLib::mappedFlowRateFvPatchVectorField::mappedFlowRateFvPatchVectorField
(
	const mappedFlowRateFvPatchVectorField& ptf,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchField<vector>(ptf, iF),
	nbrPhiName_(ptf.nbrPhiName_),
	phiName_(ptf.phiName_),
	rhoName_(ptf.rhoName_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::mappedFlowRateFvPatchVectorField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	// Since we're inside initEvaluate/evaluate there might be processor
	// comms underway. Change the tag we use.
	int oldTag = UPstream::msgType();
	UPstream::msgType() = oldTag + 1;

	// Get the coupling information from the mappedPatchBase
	const mappedPatchBase& mpp = refCast<const mappedPatchBase>
		(
			patch().patch()
			);
	const polyMesh& nbrMesh = mpp.sampleMesh();
	const fvPatch& nbrPatch = refCast<const fvMesh>
		(
			nbrMesh
			).boundary()[mpp.samplePolyPatch().index()];

	scalarList phi =
		nbrPatch.lookupPatchField<surfaceScalarField, scalar>(nbrPhiName_);

	mpp.distribute(phi);


	const surfaceScalarField& phiName =
		db().lookupObject<surfaceScalarField>(phiName_);

	scalarField U(-phi / patch().magSf());

	vectorField n(patch().nf());

	if (phiName.dimensions() == dimVelocity * dimArea)
	{
		// volumetric flow-rate
		operator==(n*U);
	}
	else if (phiName.dimensions() == dimDensity * dimVelocity*dimArea)
	{
		const fvPatchField<scalar>& rhop =
			patch().lookupPatchField<volScalarField, scalar>(rhoName_);

		// mass flow-rate
		operator==(n*U / rhop);

		if (debug)
		{
			scalar phi = gSum(rhop*(*this) & patch().Sf());
			Info << patch().boundaryMesh().mesh().name() << ':'
				<< patch().name() << ':'
				<< this->internalField().name() << " <- "
				<< nbrMesh.name() << ':'
				<< nbrPatch.name() << ':'
				<< this->internalField().name() << " :"
				<< " mass flux[Kg/s]:" << -phi
				<< endl;
		}
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

	// Restore tag
	UPstream::msgType() = oldTag;

	fixedValueFvPatchField<vector>::updateCoeffs();
}


void tnbLib::mappedFlowRateFvPatchVectorField::write
(
	Ostream& os
) const
{
	fvPatchField<vector>::write(os);
	writeEntryIfDifferent<word>(os, "phi", "phi", phiName_);
	writeEntryIfDifferent<word>(os, "rho", "rho", rhoName_);
	writeEntry(os, "nbrPhi", nbrPhiName_);
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchVectorField,
		mappedFlowRateFvPatchVectorField
	);
}


// ************************************************************************* //