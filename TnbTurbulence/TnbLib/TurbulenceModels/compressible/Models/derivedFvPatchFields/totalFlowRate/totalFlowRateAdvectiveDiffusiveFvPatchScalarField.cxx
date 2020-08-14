#include <totalFlowRateAdvectiveDiffusiveFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <IOobjectList.hxx>
#include <turbulentFluidThermoModel.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::totalFlowRateAdvectiveDiffusiveFvPatchScalarField::
totalFlowRateAdvectiveDiffusiveFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	mixedFvPatchField<scalar>(p, iF),
	phiName_("phi"),
	rhoName_("none"),
	massFluxFraction_(1.0)
{
	refValue() = 0.0;
	refGrad() = 0.0;
	valueFraction() = 0.0;
}


tnbLib::totalFlowRateAdvectiveDiffusiveFvPatchScalarField::
totalFlowRateAdvectiveDiffusiveFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	mixedFvPatchField<scalar>(p, iF),
	phiName_(dict.lookupOrDefault<word>("phi", "phi")),
	rhoName_(dict.lookupOrDefault<word>("rho", "none")),
	massFluxFraction_(dict.lookupOrDefault<scalar>("massFluxFraction", 1.0))
{

	refValue() = 1.0;
	refGrad() = 0.0;
	valueFraction() = 0.0;

	if (dict.found("value"))
	{
		fvPatchField<scalar>::operator=
			(
				Field<scalar>("value", dict, p.size())
				);
	}
	else
	{
		fvPatchField<scalar>::operator=(refValue());
	}
}

tnbLib::totalFlowRateAdvectiveDiffusiveFvPatchScalarField::
totalFlowRateAdvectiveDiffusiveFvPatchScalarField
(
	const totalFlowRateAdvectiveDiffusiveFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	mixedFvPatchField<scalar>(ptf, p, iF, mapper),
	phiName_(ptf.phiName_),
	rhoName_(ptf.rhoName_),
	massFluxFraction_(ptf.massFluxFraction_)
{}


tnbLib::totalFlowRateAdvectiveDiffusiveFvPatchScalarField::
totalFlowRateAdvectiveDiffusiveFvPatchScalarField
(
	const totalFlowRateAdvectiveDiffusiveFvPatchScalarField& tppsf
)
	:
	mixedFvPatchField<scalar>(tppsf),
	phiName_(tppsf.phiName_),
	rhoName_(tppsf.rhoName_),
	massFluxFraction_(tppsf.massFluxFraction_)
{}

tnbLib::totalFlowRateAdvectiveDiffusiveFvPatchScalarField::
totalFlowRateAdvectiveDiffusiveFvPatchScalarField
(
	const totalFlowRateAdvectiveDiffusiveFvPatchScalarField& tppsf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	mixedFvPatchField<scalar>(tppsf, iF),
	phiName_(tppsf.phiName_),
	rhoName_(tppsf.rhoName_),
	massFluxFraction_(tppsf.massFluxFraction_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::totalFlowRateAdvectiveDiffusiveFvPatchScalarField::autoMap
(
	const fvPatchFieldMapper& m
)
{
	m(*this, *this);
}


void tnbLib::totalFlowRateAdvectiveDiffusiveFvPatchScalarField::rmap
(
	const fvPatchScalarField& ptf,
	const labelList& addr
)
{
	mixedFvPatchField<scalar>::rmap(ptf, addr);
}


void tnbLib::totalFlowRateAdvectiveDiffusiveFvPatchScalarField::updateCoeffs()
{
	if (this->updated())
	{
		return;
	}

	const label patchi = patch().index();

	const compressible::turbulenceModel& turbModel =
		db().lookupObject<compressible::turbulenceModel>
		(
			IOobject::groupName
			(
				turbulenceModel::propertiesName,
				internalField().group()
			)
			);

	const fvsPatchField<scalar>& phip =
		patch().lookupPatchField<surfaceScalarField, scalar>(phiName_);

	const scalarField alphap(turbModel.alphaEff(patchi));

	refValue() = massFluxFraction_;
	refGrad() = 0.0;

	valueFraction() =
		1.0
		/
		(
			1.0 +
			alphap * patch().deltaCoeffs()*patch().magSf() / max(mag(phip), small)
			);

	mixedFvPatchField<scalar>::updateCoeffs();

	if (debug)
	{
		scalar phi = gSum(-phip * (*this));

		Info << patch().boundaryMesh().mesh().name() << ':'
			<< patch().name() << ':'
			<< this->internalField().name() << " :"
			<< " mass flux[Kg/s]:" << phi
			<< endl;
	}
}


void tnbLib::totalFlowRateAdvectiveDiffusiveFvPatchScalarField::
write(Ostream& os) const
{
	fvPatchField<scalar>::write(os);
	writeEntry(os, "phi", phiName_);
	writeEntry(os, "rho", rhoName_);
	writeEntry(os, "massFluxFraction", massFluxFraction_);
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		totalFlowRateAdvectiveDiffusiveFvPatchScalarField
	);

}

// ************************************************************************* //