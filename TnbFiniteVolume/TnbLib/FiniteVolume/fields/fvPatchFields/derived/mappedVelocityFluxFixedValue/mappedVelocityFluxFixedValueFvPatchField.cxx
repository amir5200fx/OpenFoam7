#include <mappedVelocityFluxFixedValueFvPatchField.hxx>

#include <fvPatchFieldMapper.hxx>
#include <mappedPatchBase.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::mappedVelocityFluxFixedValueFvPatchField::
mappedVelocityFluxFixedValueFvPatchField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchVectorField(p, iF),
	phiName_("phi")
{}


tnbLib::mappedVelocityFluxFixedValueFvPatchField::
mappedVelocityFluxFixedValueFvPatchField
(
	const mappedVelocityFluxFixedValueFvPatchField& ptf,
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchVectorField(ptf, p, iF, mapper),
	phiName_(ptf.phiName_)
{
	if (!isA<mappedPatchBase>(this->patch().patch()))
	{
		FatalErrorInFunction
			<< "Patch type '" << p.type()
			<< "' not type '" << mappedPatchBase::typeName << "'"
			<< " for patch " << p.name()
			<< " of field " << internalField().name()
			<< " in file " << internalField().objectPath()
			<< exit(FatalError);
	}
}


tnbLib::mappedVelocityFluxFixedValueFvPatchField::
mappedVelocityFluxFixedValueFvPatchField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchVectorField(p, iF, dict),
	phiName_(dict.lookupOrDefault<word>("phi", "phi"))
{
	if (!isA<mappedPatchBase>(this->patch().patch()))
	{
		FatalErrorInFunction
			<< "Patch type '" << p.type()
			<< "' not type '" << mappedPatchBase::typeName << "'"
			<< " for patch " << p.name()
			<< " of field " << internalField().name()
			<< " in file " << internalField().objectPath()
			<< exit(FatalError);
	}

	const mappedPatchBase& mpp = refCast<const mappedPatchBase>
		(
			this->patch().patch()
			);
	if (mpp.mode() == mappedPolyPatch::NEARESTCELL)
	{
		FatalErrorInFunction
			<< "Patch " << p.name()
			<< " of type '" << p.type()
			<< "' can not be used in 'nearestCell' mode"
			<< " of field " << internalField().name()
			<< " in file " << internalField().objectPath()
			<< exit(FatalError);
	}
}


tnbLib::mappedVelocityFluxFixedValueFvPatchField::
mappedVelocityFluxFixedValueFvPatchField
(
	const mappedVelocityFluxFixedValueFvPatchField& ptf
)
	:
	fixedValueFvPatchVectorField(ptf),
	phiName_(ptf.phiName_)
{}


tnbLib::mappedVelocityFluxFixedValueFvPatchField::
mappedVelocityFluxFixedValueFvPatchField
(
	const mappedVelocityFluxFixedValueFvPatchField& ptf,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchVectorField(ptf, iF),
	phiName_(ptf.phiName_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::mappedVelocityFluxFixedValueFvPatchField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	// Since we're inside initEvaluate/evaluate there might be processor
	// comms underway. Change the tag we use.
	int oldTag = UPstream::msgType();
	UPstream::msgType() = oldTag + 1;

	// Get the mappedPatchBase
	const mappedPatchBase& mpp = refCast<const mappedPatchBase>
		(
			mappedVelocityFluxFixedValueFvPatchField::patch().patch()
			);
	const fvMesh& nbrMesh = refCast<const fvMesh>(mpp.sampleMesh());
	const word& fieldName = internalField().name();
	const volVectorField& UField =
		nbrMesh.lookupObject<volVectorField>(fieldName);

	surfaceScalarField& phiField =
		nbrMesh.lookupObjectRef<surfaceScalarField>(phiName_);

	vectorField newUValues;
	scalarField newPhiValues;

	switch (mpp.mode())
	{
	case mappedPolyPatch::NEARESTFACE:
	{
		vectorField allUValues(nbrMesh.nFaces(), Zero);
		scalarField allPhiValues(nbrMesh.nFaces(), 0.0);

		forAll(UField.boundaryField(), patchi)
		{
			const fvPatchVectorField& Upf = UField.boundaryField()[patchi];
			const scalarField& phipf = phiField.boundaryField()[patchi];

			label faceStart = Upf.patch().start();

			forAll(Upf, facei)
			{
				allUValues[faceStart + facei] = Upf[facei];
				allPhiValues[faceStart + facei] = phipf[facei];
			}
		}

		mpp.distribute(allUValues);
		newUValues.transfer(allUValues);

		mpp.distribute(allPhiValues);
		newPhiValues.transfer(allPhiValues);

		break;
	}
	case mappedPolyPatch::NEARESTPATCHFACE:
	case mappedPolyPatch::NEARESTPATCHFACEAMI:
	{
		const label nbrPatchID =
			nbrMesh.boundaryMesh().findPatchID(mpp.samplePatch());

		newUValues = UField.boundaryField()[nbrPatchID];
		mpp.distribute(newUValues);

		newPhiValues = phiField.boundaryField()[nbrPatchID];
		mpp.distribute(newPhiValues);

		break;
	}
	default:
	{
		FatalErrorInFunction
			<< "patch can only be used in NEARESTPATCHFACE, "
			<< "NEARESTPATCHFACEAMI or NEARESTFACE mode" << nl
			<< abort(FatalError);
	}
	}

	operator==(newUValues);
	phiField.boundaryFieldRef()[patch().index()] == newPhiValues;

	// Restore tag
	UPstream::msgType() = oldTag;

	fixedValueFvPatchVectorField::updateCoeffs();
}


void tnbLib::mappedVelocityFluxFixedValueFvPatchField::write
(
	Ostream& os
) const
{
	fvPatchVectorField::write(os);
	writeEntryIfDifferent<word>(os, "phi", "phi", phiName_);
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchVectorField,
		mappedVelocityFluxFixedValueFvPatchField
	);
}


// ************************************************************************* //