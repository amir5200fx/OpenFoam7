#include <pressureNormalInletOutletVelocityFvPatchVectorField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::pressureNormalInletOutletVelocityFvPatchVectorField::
pressureNormalInletOutletVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF
)
	:
	mixedFvPatchVectorField(p, iF),
	phiName_("phi"),
	rhoName_("rho")
{
	refValue() = *this;
	refGrad() = Zero;
	valueFraction() = 0.0;
}


tnbLib::pressureNormalInletOutletVelocityFvPatchVectorField::
pressureNormalInletOutletVelocityFvPatchVectorField
(
	const pressureNormalInletOutletVelocityFvPatchVectorField& ptf,
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	mixedFvPatchVectorField(ptf, p, iF, mapper),
	phiName_(ptf.phiName_),
	rhoName_(ptf.rhoName_)
{}


tnbLib::pressureNormalInletOutletVelocityFvPatchVectorField::
pressureNormalInletOutletVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const dictionary& dict
)
	:
	mixedFvPatchVectorField(p, iF),
	phiName_(dict.lookupOrDefault<word>("phi", "phi")),
	rhoName_(dict.lookupOrDefault<word>("rho", "rho"))
{
	fvPatchVectorField::operator=(vectorField("value", dict, p.size()));
	refValue() = *this;
	refGrad() = Zero;
	valueFraction() = 0.0;
}


tnbLib::pressureNormalInletOutletVelocityFvPatchVectorField::
pressureNormalInletOutletVelocityFvPatchVectorField
(
	const pressureNormalInletOutletVelocityFvPatchVectorField& pivpvf
)
	:
	mixedFvPatchVectorField(pivpvf),
	phiName_(pivpvf.phiName_),
	rhoName_(pivpvf.rhoName_)
{}


tnbLib::pressureNormalInletOutletVelocityFvPatchVectorField::
pressureNormalInletOutletVelocityFvPatchVectorField
(
	const pressureNormalInletOutletVelocityFvPatchVectorField& pivpvf,
	const DimensionedField<vector, volMesh>& iF
)
	:
	mixedFvPatchVectorField(pivpvf, iF),
	phiName_(pivpvf.phiName_),
	rhoName_(pivpvf.rhoName_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::pressureNormalInletOutletVelocityFvPatchVectorField::updateCoeffs()
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
		refValue() = n * phip / magS;
	}
	else if (phi.dimensions() == dimDensity * dimVelocity*dimArea)
	{
		const fvPatchField<scalar>& rhop =
			patch().lookupPatchField<volScalarField, scalar>(rhoName_);

		refValue() = n * phip / (rhop*magS);
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

	valueFraction() = 1.0 - pos0(phip);

	mixedFvPatchVectorField::updateCoeffs();
}


void tnbLib::pressureNormalInletOutletVelocityFvPatchVectorField::write
(
	Ostream& os
) const
{
	fvPatchVectorField::write(os);
	writeEntry(os, "phi", phiName_);
	writeEntry(os, "rho", rhoName_);
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void tnbLib::pressureNormalInletOutletVelocityFvPatchVectorField::operator=
(
	const fvPatchField<vector>& pvf
	)
{
	fvPatchField<vector>::operator=
		(
			valueFraction()*(patch().nf()*(patch().nf() & pvf))
			+ (1 - valueFraction())*pvf
			);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchVectorField,
		pressureNormalInletOutletVelocityFvPatchVectorField
	);
}

// ************************************************************************* //