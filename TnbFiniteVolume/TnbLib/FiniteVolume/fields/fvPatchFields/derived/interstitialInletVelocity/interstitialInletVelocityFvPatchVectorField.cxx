#include <interstitialInletVelocityFvPatchVectorField.hxx>

#include <volFields.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::interstitialInletVelocityFvPatchVectorField::
interstitialInletVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchVectorField(p, iF),
	inletVelocity_(p.size(), Zero),
	alphaName_("alpha")
{}


tnbLib::interstitialInletVelocityFvPatchVectorField::
interstitialInletVelocityFvPatchVectorField
(
	const interstitialInletVelocityFvPatchVectorField& ptf,
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchVectorField(ptf, p, iF, mapper),
	inletVelocity_(mapper(ptf.inletVelocity_)),
	alphaName_(ptf.alphaName_)
{}


tnbLib::interstitialInletVelocityFvPatchVectorField::
interstitialInletVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchVectorField(p, iF, dict),
	inletVelocity_("inletVelocity", dict, p.size()),
	alphaName_(dict.lookupOrDefault<word>("alpha", "alpha"))
{}


tnbLib::interstitialInletVelocityFvPatchVectorField::
interstitialInletVelocityFvPatchVectorField
(
	const interstitialInletVelocityFvPatchVectorField& ptf
)
	:
	fixedValueFvPatchVectorField(ptf),
	inletVelocity_(ptf.inletVelocity_),
	alphaName_(ptf.alphaName_)
{}


tnbLib::interstitialInletVelocityFvPatchVectorField::
interstitialInletVelocityFvPatchVectorField
(
	const interstitialInletVelocityFvPatchVectorField& ptf,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchVectorField(ptf, iF),
	inletVelocity_(ptf.inletVelocity_),
	alphaName_(ptf.alphaName_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::interstitialInletVelocityFvPatchVectorField::autoMap
(
	const fvPatchFieldMapper& m
)
{
	fixedValueFvPatchVectorField::autoMap(m);
	m(inletVelocity_, inletVelocity_);
}


void tnbLib::interstitialInletVelocityFvPatchVectorField::rmap
(
	const fvPatchVectorField& ptf,
	const labelList& addr
)
{
	fixedValueFvPatchVectorField::rmap(ptf, addr);

	const interstitialInletVelocityFvPatchVectorField& tiptf =
		refCast<const interstitialInletVelocityFvPatchVectorField>(ptf);

	inletVelocity_.rmap(tiptf.inletVelocity_, addr);
}


void tnbLib::interstitialInletVelocityFvPatchVectorField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	const fvPatchField<scalar>& alphap =
		patch().lookupPatchField<volScalarField, scalar>(alphaName_);

	operator==(inletVelocity_ / alphap);
	fixedValueFvPatchVectorField::updateCoeffs();
}


void tnbLib::interstitialInletVelocityFvPatchVectorField::write(Ostream& os) const
{
	fvPatchField<vector>::write(os);
	writeEntryIfDifferent<word>(os, "alpha", "alpha", alphaName_);
	writeEntry(os, "inletVelocity", inletVelocity_);
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchVectorField,
		interstitialInletVelocityFvPatchVectorField
	);
}


// ************************************************************************* //