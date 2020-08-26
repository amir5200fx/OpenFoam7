#include <MarshakRadiationFixedTemperatureFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <radiationModel.hxx>
#include <physicoChemicalConstants.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::MarshakRadiationFixedTemperatureFvPatchScalarField::
MarshakRadiationFixedTemperatureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	mixedFvPatchScalarField(p, iF),
	radiationCoupledBase(p, "undefined", scalarField::null()),
	Trad_(p.size())
{
	refValue() = 0.0;
	refGrad() = 0.0;
	valueFraction() = 0.0;
}


tnbLib::MarshakRadiationFixedTemperatureFvPatchScalarField::
MarshakRadiationFixedTemperatureFvPatchScalarField
(
	const MarshakRadiationFixedTemperatureFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	mixedFvPatchScalarField(ptf, p, iF, mapper),
	radiationCoupledBase
	(
		p,
		ptf.emissivityMethod(),
		ptf.emissivity_,
		mapper
	),
	Trad_(mapper(ptf.Trad_))
{}


tnbLib::MarshakRadiationFixedTemperatureFvPatchScalarField::
MarshakRadiationFixedTemperatureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	mixedFvPatchScalarField(p, iF),
	radiationCoupledBase(p, dict),
	Trad_("Trad", dict, p.size())
{
	// refValue updated on each call to updateCoeffs()
	refValue() = 4.0*constant::physicoChemical::sigma.value()*pow4(Trad_);

	// zero gradient
	refGrad() = 0.0;

	valueFraction() = 1.0;

	fvPatchScalarField::operator=(refValue());
}


tnbLib::MarshakRadiationFixedTemperatureFvPatchScalarField::
MarshakRadiationFixedTemperatureFvPatchScalarField
(
	const MarshakRadiationFixedTemperatureFvPatchScalarField& ptf
)
	:
	mixedFvPatchScalarField(ptf),
	radiationCoupledBase
	(
		ptf.patch(),
		ptf.emissivityMethod(),
		ptf.emissivity_
	),
	Trad_(ptf.Trad_)
{}


tnbLib::MarshakRadiationFixedTemperatureFvPatchScalarField::
MarshakRadiationFixedTemperatureFvPatchScalarField
(
	const MarshakRadiationFixedTemperatureFvPatchScalarField& ptf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	mixedFvPatchScalarField(ptf, iF),
	radiationCoupledBase
	(
		ptf.patch(),
		ptf.emissivityMethod(),
		ptf.emissivity_
	),
	Trad_(ptf.Trad_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::MarshakRadiationFixedTemperatureFvPatchScalarField::autoMap
(
	const fvPatchFieldMapper& m
)
{
	mixedFvPatchScalarField::autoMap(m);
	radiationCoupledBase::autoMap(m);
	m(Trad_, Trad_);
}


void tnbLib::MarshakRadiationFixedTemperatureFvPatchScalarField::rmap
(
	const fvPatchScalarField& ptf,
	const labelList& addr
)
{
	mixedFvPatchScalarField::rmap(ptf, addr);
	radiationCoupledBase::rmap(ptf, addr);
	const MarshakRadiationFixedTemperatureFvPatchScalarField& mrptf =
		refCast<const MarshakRadiationFixedTemperatureFvPatchScalarField>(ptf);

	Trad_.rmap(mrptf.Trad_, addr);
}


void tnbLib::MarshakRadiationFixedTemperatureFvPatchScalarField::updateCoeffs()
{
	if (this->updated())
	{
		return;
	}

	// Since we're inside initEvaluate/evaluate there might be processor
	// comms underway. Change the tag we use.
	int oldTag = UPstream::msgType();
	UPstream::msgType() = oldTag + 1;

	// Re-calc reference value
	refValue() = 4.0*constant::physicoChemical::sigma.value()*pow4(Trad_);

	// Diffusion coefficient - created by radiation model's ::updateCoeffs()
	const scalarField& gamma =
		patch().lookupPatchField<volScalarField, scalar>("gammaRad");

	const scalarField temissivity = emissivity();

	const scalarField Ep(temissivity / (2 * (2 - temissivity)));

	// Set value fraction
	valueFraction() = 1.0 / (1.0 + gamma * patch().deltaCoeffs() / Ep);

	// Restore tag
	UPstream::msgType() = oldTag;

	mixedFvPatchScalarField::updateCoeffs();
}


void tnbLib::MarshakRadiationFixedTemperatureFvPatchScalarField::write
(
	Ostream& os
) const
{
	mixedFvPatchScalarField::write(os);
	radiationCoupledBase::write(os);
	writeEntry(os, "Trad", Trad_);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		MarshakRadiationFixedTemperatureFvPatchScalarField
	);
}


// ************************************************************************* //