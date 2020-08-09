#include <inletOutletTotalTemperatureFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::inletOutletTotalTemperatureFvPatchScalarField::
inletOutletTotalTemperatureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	inletOutletFvPatchScalarField(p, iF),
	UName_("U"),
	psiName_("psi"),
	gamma_(0.0),
	T0_(p.size(), 0.0)
{
	this->refValue() = Zero;
	this->refGrad() = Zero;
	this->valueFraction() = 0.0;
}


tnbLib::inletOutletTotalTemperatureFvPatchScalarField::
inletOutletTotalTemperatureFvPatchScalarField
(
	const inletOutletTotalTemperatureFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	inletOutletFvPatchScalarField(ptf, p, iF, mapper),
	UName_(ptf.UName_),
	psiName_(ptf.psiName_),
	gamma_(ptf.gamma_),
	T0_(mapper(ptf.T0_))
{}


tnbLib::inletOutletTotalTemperatureFvPatchScalarField::
inletOutletTotalTemperatureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	inletOutletFvPatchScalarField(p, iF),
	UName_(dict.lookupOrDefault<word>("U", "U")),
	psiName_(dict.lookupOrDefault<word>("psi", "thermo:psi")),
	gamma_(readScalar(dict.lookup("gamma"))),
	T0_("T0", dict, p.size())
{
	this->phiName_ = dict.lookupOrDefault<word>("phi", "phi");

	this->refValue() = Zero;
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

	this->refGrad() = Zero;
	this->valueFraction() = 0.0;
}


tnbLib::inletOutletTotalTemperatureFvPatchScalarField::
inletOutletTotalTemperatureFvPatchScalarField
(
	const inletOutletTotalTemperatureFvPatchScalarField& tppsf
)
	:
	inletOutletFvPatchScalarField(tppsf),
	UName_(tppsf.UName_),
	psiName_(tppsf.psiName_),
	gamma_(tppsf.gamma_),
	T0_(tppsf.T0_)
{}


tnbLib::inletOutletTotalTemperatureFvPatchScalarField::
inletOutletTotalTemperatureFvPatchScalarField
(
	const inletOutletTotalTemperatureFvPatchScalarField& tppsf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	inletOutletFvPatchScalarField(tppsf, iF),
	UName_(tppsf.UName_),
	psiName_(tppsf.psiName_),
	gamma_(tppsf.gamma_),
	T0_(tppsf.T0_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::inletOutletTotalTemperatureFvPatchScalarField::autoMap
(
	const fvPatchFieldMapper& m
)
{
	inletOutletFvPatchScalarField::autoMap(m);
	m(T0_, T0_);
}


void tnbLib::inletOutletTotalTemperatureFvPatchScalarField::rmap
(
	const fvPatchScalarField& ptf,
	const labelList& addr
)
{
	inletOutletFvPatchScalarField::rmap(ptf, addr);

	const inletOutletTotalTemperatureFvPatchScalarField& tiptf =
		refCast<const inletOutletTotalTemperatureFvPatchScalarField>(ptf);

	T0_.rmap(tiptf.T0_, addr);
}


void tnbLib::inletOutletTotalTemperatureFvPatchScalarField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	const fvPatchVectorField& Up =
		patch().lookupPatchField<volVectorField, vector>(UName_);

	const fvsPatchField<scalar>& phip =
		patch().lookupPatchField<surfaceScalarField, scalar>(this->phiName_);

	const fvPatchField<scalar>& psip =
		patch().lookupPatchField<volScalarField, scalar>(psiName_);

	scalar gM1ByG = (gamma_ - 1.0) / gamma_;

	this->refValue() =
		T0_ / (1.0 + 0.5*psip*gM1ByG*(1.0 - pos0(phip))*magSqr(Up));
	this->valueFraction() = 1.0 - pos0(phip);

	inletOutletFvPatchScalarField::updateCoeffs();
}


void tnbLib::inletOutletTotalTemperatureFvPatchScalarField::write(Ostream& os)
const
{
	fvPatchScalarField::write(os);
	writeEntryIfDifferent<word>(os, "U", "U", UName_);
	writeEntryIfDifferent<word>(os, "phi", "phi", this->phiName_);
	writeEntryIfDifferent<word>(os, "psi", "psi", psiName_);
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
		inletOutletTotalTemperatureFvPatchScalarField
	);
}

// ************************************************************************* //