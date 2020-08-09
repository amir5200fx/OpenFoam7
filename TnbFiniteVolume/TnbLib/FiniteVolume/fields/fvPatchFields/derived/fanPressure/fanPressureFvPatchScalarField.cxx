#include <fanPressureFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	template<>
	const char* NamedEnum
		<
		fanPressureFvPatchScalarField::fanFlowDirection,
		2
		>::names[] =
	{
		"in",
		"out"
	};
}

const tnbLib::NamedEnum
<
	tnbLib::fanPressureFvPatchScalarField::fanFlowDirection,
	2
> tnbLib::fanPressureFvPatchScalarField::fanFlowDirectionNames_;


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fanPressureFvPatchScalarField::fanPressureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	totalPressureFvPatchScalarField(p, iF),
	fanCurve_(),
	direction_(ffdOut)
{}


tnbLib::fanPressureFvPatchScalarField::fanPressureFvPatchScalarField
(
	const fanPressureFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	totalPressureFvPatchScalarField(ptf, p, iF, mapper),
	fanCurve_(ptf.fanCurve_),
	direction_(ptf.direction_)
{}


tnbLib::fanPressureFvPatchScalarField::fanPressureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	totalPressureFvPatchScalarField(p, iF, dict),
	fanCurve_(dict),
	direction_(fanFlowDirectionNames_.read(dict.lookup("direction")))
{}


tnbLib::fanPressureFvPatchScalarField::fanPressureFvPatchScalarField
(
	const fanPressureFvPatchScalarField& pfopsf
)
	:
	totalPressureFvPatchScalarField(pfopsf),
	fanCurve_(pfopsf.fanCurve_),
	direction_(pfopsf.direction_)
{}


tnbLib::fanPressureFvPatchScalarField::fanPressureFvPatchScalarField
(
	const fanPressureFvPatchScalarField& pfopsf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	totalPressureFvPatchScalarField(pfopsf, iF),
	fanCurve_(pfopsf.fanCurve_),
	direction_(pfopsf.direction_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::fanPressureFvPatchScalarField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	// Retrieve flux field
	const surfaceScalarField& phi =
		db().lookupObject<surfaceScalarField>(phiName());

	const fvsPatchField<scalar>& phip =
		patch().patchField<surfaceScalarField, scalar>(phi);

	int dir = 2 * direction_ - 1;

	// Average volumetric flow rate
	scalar volFlowRate = 0;

	if (phi.dimensions() == dimVelocity * dimArea)
	{
		volFlowRate = dir * gSum(phip);
	}
	else if (phi.dimensions() == dimVelocity * dimArea*dimDensity)
	{
		const scalarField& rhop =
			patch().lookupPatchField<volScalarField, scalar>(rhoName());
		volFlowRate = dir * gSum(phip / rhop);
	}
	else
	{
		FatalErrorInFunction
			<< "dimensions of phi are not correct"
			<< "\n    on patch " << patch().name()
			<< " of field " << internalField().name()
			<< " in file " << internalField().objectPath() << nl
			<< exit(FatalError);
	}

	// Pressure drop for this flow rate
	const scalar pdFan = fanCurve_(max(volFlowRate, 0.0));

	totalPressureFvPatchScalarField::updateCoeffs
	(
		p0() - dir * pdFan,
		patch().lookupPatchField<volVectorField, vector>(UName())
	);
}


void tnbLib::fanPressureFvPatchScalarField::write(Ostream& os) const
{
	totalPressureFvPatchScalarField::write(os);
	fanCurve_.write(os);
	writeEntry(os, "direction", fanFlowDirectionNames_[direction_]);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		fanPressureFvPatchScalarField
	);
};


// ************************************************************************* //