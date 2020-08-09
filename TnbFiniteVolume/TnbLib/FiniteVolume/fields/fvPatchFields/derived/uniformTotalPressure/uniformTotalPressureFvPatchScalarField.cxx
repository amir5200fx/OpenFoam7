#include <uniformTotalPressureFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::uniformTotalPressureFvPatchScalarField::
uniformTotalPressureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedValueFvPatchScalarField(p, iF),
	UName_("U"),
	phiName_("phi"),
	rhoName_("rho"),
	psiName_("none"),
	gamma_(0.0),
	p0_()
{}


tnbLib::uniformTotalPressureFvPatchScalarField::
uniformTotalPressureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchScalarField(p, iF, dict, false),
	UName_(dict.lookupOrDefault<word>("U", "U")),
	phiName_(dict.lookupOrDefault<word>("phi", "phi")),
	rhoName_(dict.lookupOrDefault<word>("rho", "rho")),
	psiName_(dict.lookupOrDefault<word>("psi", "none")),
	gamma_(psiName_ != "none" ? readScalar(dict.lookup("gamma")) : 1),
	p0_(Function1<scalar>::New("p0", dict))
{
	if (dict.found("value"))
	{
		fvPatchField<scalar>::operator=
			(
				scalarField("value", dict, p.size())
				);
	}
	else
	{
		const scalar t = this->db().time().timeOutputValue();
		fvPatchScalarField::operator==(p0_->value(t));
	}
}


tnbLib::uniformTotalPressureFvPatchScalarField::
uniformTotalPressureFvPatchScalarField
(
	const uniformTotalPressureFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchScalarField(ptf, p, iF, mapper, false), // Don't map
	UName_(ptf.UName_),
	phiName_(ptf.phiName_),
	rhoName_(ptf.rhoName_),
	psiName_(ptf.psiName_),
	gamma_(ptf.gamma_),
	p0_(ptf.p0_, false)
{
	patchType() = ptf.patchType();

	// Set the patch pressure to the current total pressure
	// This is not ideal but avoids problems with the creation of patch faces
	const scalar t = this->db().time().timeOutputValue();
	fvPatchScalarField::operator==(p0_->value(t));
}


tnbLib::uniformTotalPressureFvPatchScalarField::
uniformTotalPressureFvPatchScalarField
(
	const uniformTotalPressureFvPatchScalarField& ptf
)
	:
	fixedValueFvPatchScalarField(ptf),
	UName_(ptf.UName_),
	phiName_(ptf.phiName_),
	rhoName_(ptf.rhoName_),
	psiName_(ptf.psiName_),
	gamma_(ptf.gamma_),
	p0_(ptf.p0_, false)
{}


tnbLib::uniformTotalPressureFvPatchScalarField::
uniformTotalPressureFvPatchScalarField
(
	const uniformTotalPressureFvPatchScalarField& ptf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedValueFvPatchScalarField(ptf, iF),
	UName_(ptf.UName_),
	phiName_(ptf.phiName_),
	rhoName_(ptf.rhoName_),
	psiName_(ptf.psiName_),
	gamma_(ptf.gamma_),
	p0_(ptf.p0_, false)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::uniformTotalPressureFvPatchScalarField::updateCoeffs
(
	const vectorField& Up
)
{
	if (updated())
	{
		return;
	}

	scalar p0 = p0_->value(this->db().time().timeOutputValue());

	const fvsPatchField<scalar>& phip =
		patch().lookupPatchField<surfaceScalarField, scalar>(phiName_);

	if (internalField().dimensions() == dimPressure)
	{
		if (psiName_ == "none")
		{
			// Variable density and low-speed compressible flow

			const fvPatchField<scalar>& rho =
				patch().lookupPatchField<volScalarField, scalar>(rhoName_);

			operator==(p0 - 0.5*rho*(1.0 - pos0(phip))*magSqr(Up));
		}
		else
		{
			// High-speed compressible flow

			const fvPatchField<scalar>& psip =
				patch().lookupPatchField<volScalarField, scalar>(psiName_);

			if (gamma_ > 1)
			{
				scalar gM1ByG = (gamma_ - 1) / gamma_;

				operator==
					(
						p0
						/ pow
						(
						(1.0 + 0.5*psip*gM1ByG*(1.0 - pos0(phip))*magSqr(Up)),
							1.0 / gM1ByG
						)
						);
			}
			else
			{
				operator==(p0 / (1.0 + 0.5*psip*(1.0 - pos0(phip))*magSqr(Up)));
			}
		}

	}
	else if (internalField().dimensions() == dimPressure / dimDensity)
	{
		// Incompressible flow
		operator==(p0 - 0.5*(1.0 - pos0(phip))*magSqr(Up));
	}
	else
	{
		FatalErrorInFunction
			<< " Incorrect pressure dimensions " << internalField().dimensions()
			<< nl
			<< "    Should be " << dimPressure
			<< " for compressible/variable density flow" << nl
			<< "    or " << dimPressure / dimDensity
			<< " for incompressible flow," << nl
			<< "    on patch " << this->patch().name()
			<< " of field " << this->internalField().name()
			<< " in file " << this->internalField().objectPath()
			<< exit(FatalError);
	}

	fixedValueFvPatchScalarField::updateCoeffs();
}


void tnbLib::uniformTotalPressureFvPatchScalarField::updateCoeffs()
{
	updateCoeffs(patch().lookupPatchField<volVectorField, vector>(UName_));
}


void tnbLib::uniformTotalPressureFvPatchScalarField::write(Ostream& os) const
{
	fvPatchScalarField::write(os);
	writeEntryIfDifferent<word>(os, "U", "U", UName_);
	writeEntryIfDifferent<word>(os, "phi", "phi", phiName_);
	writeEntry(os, "rho", rhoName_);
	writeEntry(os, "psi", psiName_);
	writeEntry(os, "gamma", gamma_);
	writeEntry(os, p0_());
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		uniformTotalPressureFvPatchScalarField
	);
}

// ************************************************************************* //