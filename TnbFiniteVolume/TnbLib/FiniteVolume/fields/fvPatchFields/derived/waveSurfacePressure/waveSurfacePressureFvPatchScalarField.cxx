#define FoamNamedEnum_EXPORT_DEFINE
#include <waveSurfacePressureFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <uniformDimensionedFields.hxx>
#include <EulerDdtScheme.hxx>
#include <CrankNicolsonDdtScheme.hxx>
#include <backwardDdtScheme.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	template<>
	const char* NamedEnum
		<
		waveSurfacePressureFvPatchScalarField::ddtSchemeType,
		3
		>::names[] =
	{
		fv::EulerDdtScheme<scalar>::typeName_(),
		fv::CrankNicolsonDdtScheme<scalar>::typeName_(),
		fv::backwardDdtScheme<scalar>::typeName_()
	};
}


const tnbLib::NamedEnum
<
	tnbLib::waveSurfacePressureFvPatchScalarField::ddtSchemeType,
	3
>   tnbLib::waveSurfacePressureFvPatchScalarField::ddtSchemeTypeNames_;


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::waveSurfacePressureFvPatchScalarField::
waveSurfacePressureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedValueFvPatchScalarField(p, iF),
	phiName_("phi"),
	zetaName_("zeta"),
	rhoName_("rho")
{}


tnbLib::waveSurfacePressureFvPatchScalarField::
waveSurfacePressureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchScalarField(p, iF, dict),
	phiName_(dict.lookupOrDefault<word>("phi", "phi")),
	zetaName_(dict.lookupOrDefault<word>("zeta", "zeta")),
	rhoName_(dict.lookupOrDefault<word>("rho", "rho"))
{}


tnbLib::waveSurfacePressureFvPatchScalarField::
waveSurfacePressureFvPatchScalarField
(
	const waveSurfacePressureFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchScalarField(ptf, p, iF, mapper),
	phiName_(ptf.phiName_),
	zetaName_(ptf.zetaName_),
	rhoName_(ptf.rhoName_)
{}


tnbLib::waveSurfacePressureFvPatchScalarField::
waveSurfacePressureFvPatchScalarField
(
	const waveSurfacePressureFvPatchScalarField& wspsf
)
	:
	fixedValueFvPatchScalarField(wspsf),
	phiName_(wspsf.phiName_),
	zetaName_(wspsf.zetaName_),
	rhoName_(wspsf.rhoName_)
{}


tnbLib::waveSurfacePressureFvPatchScalarField::
waveSurfacePressureFvPatchScalarField
(
	const waveSurfacePressureFvPatchScalarField& wspsf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedValueFvPatchScalarField(wspsf, iF),
	phiName_(wspsf.phiName_),
	zetaName_(wspsf.zetaName_),
	rhoName_(wspsf.rhoName_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::waveSurfacePressureFvPatchScalarField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	const label patchi = patch().index();

	const scalar dt = db().time().deltaTValue();

	// Retrieve non-const access to zeta field from the database
	volVectorField& zeta = db().lookupObjectRef<volVectorField>(zetaName_);
	vectorField& zetap = zeta.boundaryFieldRef()[patchi];

	// Lookup d/dt scheme from database for zeta
	const word ddtSchemeName(zeta.mesh().ddtScheme(zeta.name()));
	ddtSchemeType ddtScheme(ddtSchemeTypeNames_[ddtSchemeName]);

	// Retrieve the flux field from the database
	const surfaceScalarField& phi =
		db().lookupObject<surfaceScalarField>(phiName_);

	// Cache the patch face-normal vectors
	tmp<vectorField> nf(patch().nf());

	// Change in zeta due to flux
	vectorField dZetap(dt*nf()*phi.boundaryField()[patchi] / patch().magSf());

	if (phi.dimensions() == dimDensity * dimVelocity*dimArea)
	{
		const scalarField& rhop =
			patch().lookupPatchField<volScalarField, scalar>(rhoName_);

		dZetap /= rhop;
	}

	const volVectorField& zeta0 = zeta.oldTime();

	switch (ddtScheme)
	{
	case tsEuler:
	case tsCrankNicolson:
	{
		zetap = zeta0.boundaryField()[patchi] + dZetap;

		break;
	}
	case tsBackward:
	{
		scalar dt0 = db().time().deltaT0Value();

		scalar c = 1.0 + dt / (dt + dt0);
		scalar c00 = dt * dt / (dt0*(dt + dt0));
		scalar c0 = c + c00;

		zetap =
			(
				c0*zeta0.boundaryField()[patchi]
				- c00 * zeta0.oldTime().boundaryField()[patchi]
				+ dZetap
				) / c;

		break;
	}
	default:
	{
		FatalErrorInFunction
			<< ddtSchemeName << nl
			<< "    on patch " << this->patch().name()
			<< " of field " << this->internalField().name()
			<< " in file " << this->internalField().objectPath()
			<< abort(FatalError);
	}
	}


	Info << "min/max zetap = " << gMin(zetap & nf()) << ", "
		<< gMax(zetap & nf()) << endl;

	// Update the surface pressure
	const uniformDimensionedVectorField& g =
		db().lookupObject<uniformDimensionedVectorField>("g");

	operator==(-g.value() & zetap);

	fixedValueFvPatchScalarField::updateCoeffs();
}


void tnbLib::waveSurfacePressureFvPatchScalarField::write(Ostream& os) const
{
	fvPatchScalarField::write(os);
	writeEntryIfDifferent<word>(os, "phi", "phi", phiName_);
	writeEntryIfDifferent<word>(os, "zeta", "zeta", zetaName_);
	writeEntryIfDifferent<word>(os, "rho", "rho", rhoName_);
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		waveSurfacePressureFvPatchScalarField
	);
}

// ************************************************************************* //