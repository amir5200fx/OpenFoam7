#include <variableHeightFlowRateFvPatchField.hxx>

#include <fvPatchFieldMapper.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::variableHeightFlowRateFvPatchScalarField
::variableHeightFlowRateFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	mixedFvPatchField<scalar>(p, iF),
	phiName_("phi"),
	lowerBound_(0.0),
	upperBound_(1.0)
{
	this->refValue() = 0.0;
	this->refGrad() = 0.0;
	this->valueFraction() = 0.0;
}


tnbLib::variableHeightFlowRateFvPatchScalarField
::variableHeightFlowRateFvPatchScalarField
(
	const variableHeightFlowRateFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	mixedFvPatchScalarField(ptf, p, iF, mapper),
	phiName_(ptf.phiName_),
	lowerBound_(ptf.lowerBound_),
	upperBound_(ptf.upperBound_)
{}


tnbLib::variableHeightFlowRateFvPatchScalarField
::variableHeightFlowRateFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	mixedFvPatchScalarField(p, iF),
	phiName_(dict.lookupOrDefault<word>("phi", "phi")),
	lowerBound_(readScalar(dict.lookup("lowerBound"))),
	upperBound_(readScalar(dict.lookup("upperBound")))
{
	this->refValue() = 0.0;

	if (dict.found("value"))
	{
		fvPatchScalarField::operator=
			(
				scalarField("value", dict, p.size())
				);
	}
	else
	{
		fvPatchScalarField::operator=(this->patchInternalField());
	}

	this->refGrad() = 0.0;
	this->valueFraction() = 0.0;
}


tnbLib::variableHeightFlowRateFvPatchScalarField
::variableHeightFlowRateFvPatchScalarField
(
	const variableHeightFlowRateFvPatchScalarField& ptf
)
	:
	mixedFvPatchScalarField(ptf),
	phiName_(ptf.phiName_),
	lowerBound_(ptf.lowerBound_),
	upperBound_(ptf.upperBound_)
{}


tnbLib::variableHeightFlowRateFvPatchScalarField
::variableHeightFlowRateFvPatchScalarField
(
	const variableHeightFlowRateFvPatchScalarField& ptf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	mixedFvPatchScalarField(ptf, iF),
	phiName_(ptf.phiName_),
	lowerBound_(ptf.lowerBound_),
	upperBound_(ptf.upperBound_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::variableHeightFlowRateFvPatchScalarField::updateCoeffs()
{
	if (this->updated())
	{
		return;
	}

	const fvsPatchField<scalar>& phip =
		patch().lookupPatchField<surfaceScalarField, scalar>(phiName_);

	scalarField alphap(this->patchInternalField());


	forAll(phip, i)
	{
		if (phip[i] < -small)
		{
			if (alphap[i] < lowerBound_)
			{
				this->refValue()[i] = 0.0;
			}
			else if (alphap[i] > upperBound_)
			{
				this->refValue()[i] = 1.0;
			}
			else
			{
				this->refValue()[i] = alphap[i];
			}

			this->valueFraction()[i] = 1.0;
		}
		else
		{
			this->refValue()[i] = 0.0;
			this->valueFraction()[i] = 0.0;
		}
	}

	mixedFvPatchScalarField::updateCoeffs();
}


void tnbLib::variableHeightFlowRateFvPatchScalarField::write(Ostream& os) const
{
	fvPatchScalarField::write(os);
	if (phiName_ != "phi")
	{
		writeEntry(os, "phi", phiName_);
	}
	writeEntry(os, "lowerBound", lowerBound_);
	writeEntry(os, "upperBound", upperBound_);
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		variableHeightFlowRateFvPatchScalarField
	);
}

// ************************************************************************* //