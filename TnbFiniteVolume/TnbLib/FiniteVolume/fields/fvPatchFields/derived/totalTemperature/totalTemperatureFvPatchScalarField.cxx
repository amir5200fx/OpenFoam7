#include <totalTemperatureFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::totalTemperatureFvPatchScalarField::totalTemperatureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedValueFvPatchScalarField(p, iF),
	UName_("U"),
	phiName_("phi"),
	psiName_("thermo:psi"),
	gamma_(0.0),
	T0_(p.size(), 0.0)
{}


tnbLib::totalTemperatureFvPatchScalarField::totalTemperatureFvPatchScalarField
(
	const totalTemperatureFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchScalarField(ptf, p, iF, mapper),
	UName_(ptf.UName_),
	phiName_(ptf.phiName_),
	psiName_(ptf.psiName_),
	gamma_(ptf.gamma_),
	T0_(mapper(ptf.T0_))
{}


tnbLib::totalTemperatureFvPatchScalarField::totalTemperatureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchScalarField(p, iF, dict, false),
	UName_(dict.lookupOrDefault<word>("U", "U")),
	phiName_(dict.lookupOrDefault<word>("phi", "phi")),
	psiName_(dict.lookupOrDefault<word>("psi", "thermo:psi")),
	gamma_(readScalar(dict.lookup("gamma"))),
	T0_("T0", dict, p.size())
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
		fvPatchField<scalar>::operator=(T0_);
	}
}


tnbLib::totalTemperatureFvPatchScalarField::totalTemperatureFvPatchScalarField
(
	const totalTemperatureFvPatchScalarField& tppsf
)
	:
	fixedValueFvPatchScalarField(tppsf),
	UName_(tppsf.UName_),
	phiName_(tppsf.phiName_),
	psiName_(tppsf.psiName_),
	gamma_(tppsf.gamma_),
	T0_(tppsf.T0_)
{}


tnbLib::totalTemperatureFvPatchScalarField::totalTemperatureFvPatchScalarField
(
	const totalTemperatureFvPatchScalarField& tppsf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedValueFvPatchScalarField(tppsf, iF),
	UName_(tppsf.UName_),
	phiName_(tppsf.phiName_),
	psiName_(tppsf.psiName_),
	gamma_(tppsf.gamma_),
	T0_(tppsf.T0_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::totalTemperatureFvPatchScalarField::autoMap
(
	const fvPatchFieldMapper& m
)
{
	fixedValueFvPatchScalarField::autoMap(m);
	m(T0_, T0_);
}


void tnbLib::totalTemperatureFvPatchScalarField::rmap
(
	const fvPatchScalarField& ptf,
	const labelList& addr
)
{
	fixedValueFvPatchScalarField::rmap(ptf, addr);

	const totalTemperatureFvPatchScalarField& tiptf =
		refCast<const totalTemperatureFvPatchScalarField>(ptf);

	T0_.rmap(tiptf.T0_, addr);
}


void tnbLib::totalTemperatureFvPatchScalarField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	const fvPatchVectorField& Up =
		patch().lookupPatchField<volVectorField, vector>(UName_);

	const fvsPatchField<scalar>& phip =
		patch().lookupPatchField<surfaceScalarField, scalar>(phiName_);

	const fvPatchField<scalar>& psip =
		patch().lookupPatchField<volScalarField, scalar>(psiName_);

	scalar gM1ByG = (gamma_ - 1.0) / gamma_;

	operator==
		(
			T0_ / (1.0 + 0.5*psip*gM1ByG*(1.0 - pos0(phip))*magSqr(Up))
			);

	fixedValueFvPatchScalarField::updateCoeffs();
}


void tnbLib::totalTemperatureFvPatchScalarField::write(Ostream& os) const
{
	fvPatchScalarField::write(os);
	writeEntryIfDifferent<word>(os, "U", "U", UName_);
	writeEntryIfDifferent<word>(os, "phi", "phi", phiName_);
	writeEntryIfDifferent<word>(os, "psi", "thermo:psi", psiName_);
	writeEntry(os, "gamma", gamma_);
	writeEntry(os, "T0", T0_);
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		totalTemperatureFvPatchScalarField
	);
}

// ************************************************************************* //