#include <fanPressureJumpFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::fanPressureJumpFvPatchScalarField::calcFanJump()
{
	const fvsPatchField<scalar>& phip =
		patch().lookupPatchField<surfaceScalarField, scalar>(phiName_);

	const bool massBasedFlux =
		phip.internalField().dimensions() == dimDensity * dimVelocity*dimArea;

	const scalar dir = reverse_ ? -1 : 1;

	//- Jump table is defined in backward compatibility mode
	if (jumpTable_.valid())
	{
		//- Patch normal velocity field
		scalarField Un(max(dir*phip / patch().magSf(), scalar(0)));

		if (massBasedFlux)
		{
			const fvPatchField<scalar>& rhop =
				patch().lookupPatchField<volScalarField, scalar>(rhoName_);

			Un /= rhop;
		}

		jump_ = dir * max(jumpTable_->value(Un), scalar(0));
	}
	else
	{
		scalar volFlowRate = 0;

		if (massBasedFlux)
		{
			const scalarField& rhop =
				patch().lookupPatchField<volScalarField, scalar>(rhoName_);

			volFlowRate = gSum(phip / rhop);
		}
		else
		{
			volFlowRate = gSum(phip);
		}


		jump_ = dir * max(fanCurve_->value(max(dir*volFlowRate, 0)), 0);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fanPressureJumpFvPatchScalarField::fanPressureJumpFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedJumpFvPatchScalarField(p, iF),
	fanCurve_(),
	jumpTable_(),
	reverse_(false),
	phiName_("phi"),
	rhoName_("rho")
{}


tnbLib::fanPressureJumpFvPatchScalarField::fanPressureJumpFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedJumpFvPatchScalarField(p, iF),
	fanCurve_(),
	jumpTable_(),
	reverse_(dict.lookupOrDefault<Switch>("reverse", false)),
	phiName_(dict.lookupOrDefault<word>("phi", "phi")),
	rhoName_(dict.lookupOrDefault<word>("rho", "rho"))
{
	if (cyclicPatch().owner())
	{
		if (dict.found("jumpTable"))
		{
			//- backward compatibility model
			jumpTable_ = Function1<scalar>::New("jumpTable", dict);
		}
		else
		{
			fanCurve_ = Function1<scalar>::New("fanCurve", dict);
		}
	}

	if (dict.found("value"))
	{
		fvPatchScalarField::operator=
			(
				scalarField("value", dict, p.size())
				);
	}
	else
	{
		evaluate(Pstream::commsTypes::blocking);
	}
}


tnbLib::fanPressureJumpFvPatchScalarField::fanPressureJumpFvPatchScalarField
(
	const fanPressureJumpFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedJumpFvPatchScalarField(ptf, p, iF, mapper),
	fanCurve_(ptf.fanCurve_, false),
	jumpTable_(ptf.jumpTable_, false),
	reverse_(ptf.reverse_),
	phiName_(ptf.phiName_),
	rhoName_(ptf.rhoName_)
{}


tnbLib::fanPressureJumpFvPatchScalarField::fanPressureJumpFvPatchScalarField
(
	const fanPressureJumpFvPatchScalarField& ptf
)
	:
	fixedJumpFvPatchScalarField(ptf),
	fanCurve_(ptf.fanCurve_, false),
	jumpTable_(ptf.jumpTable_, false),
	reverse_(ptf.reverse_),
	phiName_(ptf.phiName_),
	rhoName_(ptf.rhoName_)
{}


tnbLib::fanPressureJumpFvPatchScalarField::fanPressureJumpFvPatchScalarField
(
	const fanPressureJumpFvPatchScalarField& ptf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedJumpFvPatchScalarField(ptf, iF),
	fanCurve_(ptf.fanCurve_, false),
	jumpTable_(ptf.jumpTable_, false),
	reverse_(ptf.reverse_),
	phiName_(ptf.phiName_),
	rhoName_(ptf.rhoName_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::fanPressureJumpFvPatchScalarField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	if (cyclicPatch().owner())
	{
		calcFanJump();
	}

	fixedJumpFvPatchScalarField::updateCoeffs();
}


void tnbLib::fanPressureJumpFvPatchScalarField::write(Ostream& os) const
{
	fixedJumpFvPatchScalarField::write(os);

	if (jumpTable_.valid()) writeEntry(os, jumpTable_());
	if (fanCurve_.valid()) writeEntry(os, fanCurve_());

	writeEntryIfDifferent<Switch>(os, "reverse", false, reverse_);
	writeEntryIfDifferent<word>(os, "phi", "phi", phiName_);
	writeEntryIfDifferent<word>(os, "rho", "rho", rhoName_);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		fanPressureJumpFvPatchScalarField
	);
};


// ************************************************************************* //