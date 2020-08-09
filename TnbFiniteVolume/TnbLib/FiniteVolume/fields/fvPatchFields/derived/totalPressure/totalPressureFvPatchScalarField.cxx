#include <totalPressureFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::totalPressureFvPatchScalarField::totalPressureFvPatchScalarField
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
	p0_(p.size(), 0.0)
{}


tnbLib::totalPressureFvPatchScalarField::totalPressureFvPatchScalarField
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
	p0_("p0", dict, p.size())
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
		fvPatchField<scalar>::operator=(p0_);
	}
}


tnbLib::totalPressureFvPatchScalarField::totalPressureFvPatchScalarField
(
	const totalPressureFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchScalarField(ptf, p, iF, mapper),
	UName_(ptf.UName_),
	phiName_(ptf.phiName_),
	rhoName_(ptf.rhoName_),
	psiName_(ptf.psiName_),
	gamma_(ptf.gamma_),
	p0_(mapper(ptf.p0_))
{}


tnbLib::totalPressureFvPatchScalarField::totalPressureFvPatchScalarField
(
	const totalPressureFvPatchScalarField& tppsf
)
	:
	fixedValueFvPatchScalarField(tppsf),
	UName_(tppsf.UName_),
	phiName_(tppsf.phiName_),
	rhoName_(tppsf.rhoName_),
	psiName_(tppsf.psiName_),
	gamma_(tppsf.gamma_),
	p0_(tppsf.p0_)
{}


tnbLib::totalPressureFvPatchScalarField::totalPressureFvPatchScalarField
(
	const totalPressureFvPatchScalarField& tppsf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedValueFvPatchScalarField(tppsf, iF),
	UName_(tppsf.UName_),
	phiName_(tppsf.phiName_),
	rhoName_(tppsf.rhoName_),
	psiName_(tppsf.psiName_),
	gamma_(tppsf.gamma_),
	p0_(tppsf.p0_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::totalPressureFvPatchScalarField::autoMap
(
	const fvPatchFieldMapper& m
)
{
	fixedValueFvPatchScalarField::autoMap(m);
	m(p0_, p0_);
}


void tnbLib::totalPressureFvPatchScalarField::rmap
(
	const fvPatchScalarField& ptf,
	const labelList& addr
)
{
	fixedValueFvPatchScalarField::rmap(ptf, addr);

	const totalPressureFvPatchScalarField& tiptf =
		refCast<const totalPressureFvPatchScalarField>(ptf);

	p0_.rmap(tiptf.p0_, addr);
}


void tnbLib::totalPressureFvPatchScalarField::updateCoeffs
(
	const scalarField& p0p,
	const vectorField& Up
)
{
	if (updated())
	{
		return;
	}

	const fvsPatchField<scalar>& phip =
		patch().lookupPatchField<surfaceScalarField, scalar>(phiName_);

	if (internalField().dimensions() == dimPressure)
	{
		if (psiName_ == "none")
		{
			// Variable density and low-speed compressible flow

			const fvPatchField<scalar>& rho =
				patch().lookupPatchField<volScalarField, scalar>(rhoName_);

			operator==(p0p - 0.5*rho*(1.0 - pos0(phip))*magSqr(Up));
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
						p0p
						/ pow
						(
						(1.0 + 0.5*psip*gM1ByG*(1.0 - pos0(phip))*magSqr(Up)),
							1.0 / gM1ByG
						)
						);
			}
			else
			{
				operator==(p0p / (1.0 + 0.5*psip*(1.0 - pos0(phip))*magSqr(Up)));
			}
		}

	}
	else if (internalField().dimensions() == dimPressure / dimDensity)
	{
		// Incompressible flow
		operator==(p0p - 0.5*(1.0 - pos0(phip))*magSqr(Up));
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


void tnbLib::totalPressureFvPatchScalarField::updateCoeffs()
{
	updateCoeffs
	(
		p0(),
		patch().lookupPatchField<volVectorField, vector>(UName())
	);
}


void tnbLib::totalPressureFvPatchScalarField::write(Ostream& os) const
{
	fvPatchScalarField::write(os);
	writeEntryIfDifferent<word>(os, "U", "U", UName_);
	writeEntryIfDifferent<word>(os, "phi", "phi", phiName_);
	writeEntry(os, "rho", rhoName_);
	writeEntry(os, "psi", psiName_);
	writeEntry(os, "gamma", gamma_);
	writeEntry(os, "p0", p0_);
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		totalPressureFvPatchScalarField
	);
}

// ************************************************************************* //