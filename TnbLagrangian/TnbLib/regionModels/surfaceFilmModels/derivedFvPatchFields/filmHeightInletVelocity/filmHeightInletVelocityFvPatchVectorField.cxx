#include <filmHeightInletVelocityFvPatchVectorField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::filmHeightInletVelocityFvPatchVectorField::
filmHeightInletVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchVectorField(p, iF),
	phiName_("phi"),
	rhoName_("rho"),
	deltafName_("deltaf")
{}


tnbLib::filmHeightInletVelocityFvPatchVectorField::
filmHeightInletVelocityFvPatchVectorField
(
	const filmHeightInletVelocityFvPatchVectorField& ptf,
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchVectorField(ptf, p, iF, mapper),
	phiName_(ptf.phiName_),
	rhoName_(ptf.rhoName_),
	deltafName_(ptf.deltafName_)
{}


tnbLib::filmHeightInletVelocityFvPatchVectorField::
filmHeightInletVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchVectorField(p, iF, dict),
	phiName_(dict.lookupOrDefault<word>("phi", "phi")),
	rhoName_(dict.lookupOrDefault<word>("rho", "rho")),
	deltafName_(dict.lookupOrDefault<word>("deltaf", "deltaf"))
{}


tnbLib::filmHeightInletVelocityFvPatchVectorField::
filmHeightInletVelocityFvPatchVectorField
(
	const filmHeightInletVelocityFvPatchVectorField& fhivpvf
)
	:
	fixedValueFvPatchVectorField(fhivpvf),
	phiName_(fhivpvf.phiName_),
	rhoName_(fhivpvf.rhoName_),
	deltafName_(fhivpvf.deltafName_)
{}


tnbLib::filmHeightInletVelocityFvPatchVectorField::
filmHeightInletVelocityFvPatchVectorField
(
	const filmHeightInletVelocityFvPatchVectorField& fhivpvf,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchVectorField(fhivpvf, iF),
	phiName_(fhivpvf.phiName_),
	rhoName_(fhivpvf.rhoName_),
	deltafName_(fhivpvf.deltafName_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::filmHeightInletVelocityFvPatchVectorField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	const fvsPatchField<scalar>& phip =
		patch().lookupPatchField<surfaceScalarField, scalar>(phiName_);

	const fvPatchField<scalar>& rhop =
		patch().lookupPatchField<volScalarField, scalar>(rhoName_);

	const fvPatchField<scalar>& deltafp =
		patch().lookupPatchField<volScalarField, scalar>(deltafName_);

	vectorField n(patch().nf());
	const scalarField& magSf = patch().magSf();

	operator==(n*phip / (rhop*magSf*deltafp + rootVSmall));

	fixedValueFvPatchVectorField::updateCoeffs();
}


void tnbLib::filmHeightInletVelocityFvPatchVectorField::write(Ostream& os) const
{
	fvPatchVectorField::write(os);
	writeEntryIfDifferent<word>(os, "phi", "phi", phiName_);
	writeEntryIfDifferent<word>(os, "rho", "rho", rhoName_);
	writeEntryIfDifferent<word>(os, "deltaf", "deltaf", deltafName_);
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void tnbLib::filmHeightInletVelocityFvPatchVectorField::operator=
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
		filmHeightInletVelocityFvPatchVectorField
	);
}


// ************************************************************************* //