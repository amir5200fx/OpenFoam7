#include <variableHeightFlowRateInletVelocityFvPatchVectorField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <volFields.hxx>

#include <Time.hxx> // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::variableHeightFlowRateInletVelocityFvPatchVectorField
::variableHeightFlowRateInletVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchField<vector>(p, iF),
	flowRate_(),
	alphaName_("none")
{}


tnbLib::variableHeightFlowRateInletVelocityFvPatchVectorField
::variableHeightFlowRateInletVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchField<vector>(p, iF, dict),
	flowRate_(Function1<scalar>::New("flowRate", dict)),
	alphaName_(dict.lookup("alpha"))
{}


tnbLib::variableHeightFlowRateInletVelocityFvPatchVectorField
::variableHeightFlowRateInletVelocityFvPatchVectorField
(
	const variableHeightFlowRateInletVelocityFvPatchVectorField& ptf,
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchField<vector>(ptf, p, iF, mapper),
	flowRate_(ptf.flowRate_, false),
	alphaName_(ptf.alphaName_)
{}


tnbLib::variableHeightFlowRateInletVelocityFvPatchVectorField
::variableHeightFlowRateInletVelocityFvPatchVectorField
(
	const variableHeightFlowRateInletVelocityFvPatchVectorField& ptf
)
	:
	fixedValueFvPatchField<vector>(ptf),
	flowRate_(ptf.flowRate_, false),
	alphaName_(ptf.alphaName_)
{}


tnbLib::variableHeightFlowRateInletVelocityFvPatchVectorField
::variableHeightFlowRateInletVelocityFvPatchVectorField
(
	const variableHeightFlowRateInletVelocityFvPatchVectorField& ptf,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchField<vector>(ptf, iF),
	flowRate_(ptf.flowRate_, false),
	alphaName_(ptf.alphaName_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::variableHeightFlowRateInletVelocityFvPatchVectorField
::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	scalarField alphap =
		patch().lookupPatchField<volScalarField, scalar>(alphaName_);

	alphap = max(alphap, scalar(0));
	alphap = min(alphap, scalar(1));

	const scalar t = db().time().timeOutputValue();
	scalar flowRate = flowRate_->value(t);

	// a simpler way of doing this would be nice
	scalar avgU = -flowRate / gSum(patch().magSf()*alphap);

	vectorField n(patch().nf());

	operator==(n*avgU*alphap);

	fixedValueFvPatchField<vector>::updateCoeffs();
}


void tnbLib::variableHeightFlowRateInletVelocityFvPatchVectorField::write
(
	Ostream& os
) const
{
	fvPatchField<vector>::write(os);
	writeEntry(os, flowRate_());
	writeEntry(os, "alpha", alphaName_);
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchVectorField,
		variableHeightFlowRateInletVelocityFvPatchVectorField
	);
}


// ************************************************************************* //