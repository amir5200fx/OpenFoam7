#include <pressureInletVelocityFvPatchVectorField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::pressureInletVelocityFvPatchVectorField::
pressureInletVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchVectorField(p, iF),
	phiName_("phi"),
	rhoName_("rho")
{}


tnbLib::pressureInletVelocityFvPatchVectorField::
pressureInletVelocityFvPatchVectorField
(
	const pressureInletVelocityFvPatchVectorField& ptf,
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchVectorField(ptf, p, iF, mapper),
	phiName_(ptf.phiName_),
	rhoName_(ptf.rhoName_)
{}


tnbLib::pressureInletVelocityFvPatchVectorField::
pressureInletVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchVectorField(p, iF, dict),
	phiName_(dict.lookupOrDefault<word>("phi", "phi")),
	rhoName_(dict.lookupOrDefault<word>("rho", "rho"))
{}


tnbLib::pressureInletVelocityFvPatchVectorField::
pressureInletVelocityFvPatchVectorField
(
	const pressureInletVelocityFvPatchVectorField& pivpvf
)
	:
	fixedValueFvPatchVectorField(pivpvf),
	phiName_(pivpvf.phiName_),
	rhoName_(pivpvf.rhoName_)
{}


tnbLib::pressureInletVelocityFvPatchVectorField::
pressureInletVelocityFvPatchVectorField
(
	const pressureInletVelocityFvPatchVectorField& pivpvf,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchVectorField(pivpvf, iF),
	phiName_(pivpvf.phiName_),
	rhoName_(pivpvf.rhoName_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::pressureInletVelocityFvPatchVectorField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	const surfaceScalarField& phi =
		db().lookupObject<surfaceScalarField>(phiName_);

	const fvsPatchField<scalar>& phip =
		patch().patchField<surfaceScalarField, scalar>(phi);

	tmp<vectorField> n = patch().nf();
	const Field<scalar>& magS = patch().magSf();

	if (phi.dimensions() == dimVelocity * dimArea)
	{
		operator==(n*phip / magS);
	}
	else if (phi.dimensions() == dimDensity * dimVelocity*dimArea)
	{
		const fvPatchField<scalar>& rhop =
			patch().lookupPatchField<volScalarField, scalar>(rhoName_);

		operator==(n*phip / (rhop*magS));
	}
	else
	{
		FatalErrorInFunction
			<< "dimensions of phi are not correct"
			<< "\n    on patch " << this->patch().name()
			<< " of field " << this->internalField().name()
			<< " in file " << this->internalField().objectPath()
			<< exit(FatalError);
	}

	fixedValueFvPatchVectorField::updateCoeffs();
}


void tnbLib::pressureInletVelocityFvPatchVectorField::write(Ostream& os) const
{
	fvPatchVectorField::write(os);
	writeEntryIfDifferent<word>(os, "phi", "phi", phiName_);
	writeEntryIfDifferent<word>(os, "rho", "rho", rhoName_);
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void tnbLib::pressureInletVelocityFvPatchVectorField::operator=
(
	const fvPatchField<vector>& pvf
	)
{
	fvPatchField<vector>::operator=(patch().nf()*(patch().nf() & pvf));
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchVectorField,
		pressureInletVelocityFvPatchVectorField
	);
}

// ************************************************************************* //