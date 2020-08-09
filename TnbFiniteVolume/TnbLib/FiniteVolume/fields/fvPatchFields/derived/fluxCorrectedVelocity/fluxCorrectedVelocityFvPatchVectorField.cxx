#include <fluxCorrectedVelocityFvPatchVectorField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fluxCorrectedVelocityFvPatchVectorField::
fluxCorrectedVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF
)
	:
	zeroGradientFvPatchVectorField(p, iF),
	phiName_("phi"),
	rhoName_("rho")
{}


tnbLib::fluxCorrectedVelocityFvPatchVectorField::
fluxCorrectedVelocityFvPatchVectorField
(
	const fluxCorrectedVelocityFvPatchVectorField& ptf,
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	zeroGradientFvPatchVectorField(ptf, p, iF, mapper),
	phiName_(ptf.phiName_),
	rhoName_(ptf.rhoName_)
{}


tnbLib::fluxCorrectedVelocityFvPatchVectorField::
fluxCorrectedVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const dictionary& dict
)
	:
	zeroGradientFvPatchVectorField(p, iF),
	phiName_(dict.lookupOrDefault<word>("phi", "phi")),
	rhoName_(dict.lookupOrDefault<word>("rho", "rho"))
{
	fvPatchVectorField::operator=(patchInternalField());
}


tnbLib::fluxCorrectedVelocityFvPatchVectorField::
fluxCorrectedVelocityFvPatchVectorField
(
	const fluxCorrectedVelocityFvPatchVectorField& fcvpvf,
	const DimensionedField<vector, volMesh>& iF
)
	:
	zeroGradientFvPatchVectorField(fcvpvf, iF),
	phiName_(fcvpvf.phiName_),
	rhoName_(fcvpvf.rhoName_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::fluxCorrectedVelocityFvPatchVectorField::evaluate
(
	const Pstream::commsTypes
)
{
	if (!updated())
	{
		updateCoeffs();
	}

	zeroGradientFvPatchVectorField::evaluate();

	const surfaceScalarField& phi =
		db().lookupObject<surfaceScalarField>(phiName_);

	const fvsPatchField<scalar>& phip =
		patch().patchField<surfaceScalarField, scalar>(phi);

	const vectorField n(patch().nf());
	const Field<scalar>& magS = patch().magSf();

	if (phi.dimensions() == dimVelocity * dimArea)
	{
		operator==(*this - n * (n & *this) + n * phip / magS);
	}
	else if (phi.dimensions() == dimDensity * dimVelocity*dimArea)
	{
		const fvPatchField<scalar>& rhop =
			patch().lookupPatchField<volScalarField, scalar>(rhoName_);

		operator==(*this - n * (n & *this) + n * phip / (rhop*magS));
	}
	else
	{
		FatalErrorInFunction
			<< "dimensions of phi are incorrect\n"
			<< "    on patch " << this->patch().name()
			<< " of field " << this->internalField().name()
			<< " in file " << this->internalField().objectPath()
			<< exit(FatalError);
	}
}


void tnbLib::fluxCorrectedVelocityFvPatchVectorField::write(Ostream& os) const
{
	fvPatchVectorField::write(os);
	writeEntryIfDifferent<word>(os, "phi", "phi", phiName_);
	writeEntryIfDifferent<word>(os, "rho", "rho", rhoName_);
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchVectorField,
		fluxCorrectedVelocityFvPatchVectorField
	);
}

// ************************************************************************* //