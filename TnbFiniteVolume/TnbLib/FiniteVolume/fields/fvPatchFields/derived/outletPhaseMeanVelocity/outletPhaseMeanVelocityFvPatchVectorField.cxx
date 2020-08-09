#include <outletPhaseMeanVelocityFvPatchVectorField.hxx>

#include <volFields.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <surfaceFields.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::outletPhaseMeanVelocityFvPatchVectorField
::outletPhaseMeanVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF
)
	:
	mixedFvPatchField<vector>(p, iF),
	UnMean_(nullptr),
	alphaName_("none")
{
	refValue() = Zero;
	refGrad() = Zero;
	valueFraction() = 0.0;
}


tnbLib::outletPhaseMeanVelocityFvPatchVectorField
::outletPhaseMeanVelocityFvPatchVectorField
(
	const outletPhaseMeanVelocityFvPatchVectorField& ptf,
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	mixedFvPatchField<vector>(ptf, p, iF, mapper),
	UnMean_(ptf.UnMean_, false),
	alphaName_(ptf.alphaName_)
{}


tnbLib::outletPhaseMeanVelocityFvPatchVectorField
::outletPhaseMeanVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const dictionary& dict
)
	:
	mixedFvPatchField<vector>(p, iF),
	UnMean_(Function1<scalar>::New("UnMean", dict)),
	alphaName_(dict.lookup("alpha"))
{
	refValue() = Zero;
	refGrad() = Zero;
	valueFraction() = 0.0;

	if (dict.found("value"))
	{
		fvPatchVectorField::operator=
			(
				vectorField("value", dict, p.size())
				);
	}
	else
	{
		fvPatchVectorField::operator=(patchInternalField());
	}
}


tnbLib::outletPhaseMeanVelocityFvPatchVectorField
::outletPhaseMeanVelocityFvPatchVectorField
(
	const outletPhaseMeanVelocityFvPatchVectorField& ptf
)
	:
	mixedFvPatchField<vector>(ptf),
	UnMean_(ptf.UnMean_, false),
	alphaName_(ptf.alphaName_)
{}


tnbLib::outletPhaseMeanVelocityFvPatchVectorField
::outletPhaseMeanVelocityFvPatchVectorField
(
	const outletPhaseMeanVelocityFvPatchVectorField& ptf,
	const DimensionedField<vector, volMesh>& iF
)
	:
	mixedFvPatchField<vector>(ptf, iF),
	UnMean_(ptf.UnMean_, false),
	alphaName_(ptf.alphaName_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::outletPhaseMeanVelocityFvPatchVectorField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	const scalar t = this->db().time().timeOutputValue();

	scalarField alphap =
		patch().lookupPatchField<volScalarField, scalar>(alphaName_);

	alphap = max(alphap, scalar(0));
	alphap = min(alphap, scalar(1));

	// Get the patchInternalField (zero-gradient field)
	vectorField Uzg(patchInternalField());

	// Calculate the phase mean zero-gradient normal velocity
	const scalar UnzgMean =
		gSum(alphap*(patch().Sf() & Uzg))
		/ gSum(alphap*patch().magSf());

	// Set the refValue and valueFraction to adjust the boundary field
	// such that the phase mean is UnMean_
	const scalar UnMean = UnMean_->value(t);
	if (UnzgMean >= UnMean)
	{
		refValue() = Zero;
		valueFraction() = 1.0 - UnMean / UnzgMean;
	}
	else
	{
		refValue() = (UnMean + UnzgMean)*patch().nf();
		valueFraction() = 1.0 - UnzgMean / UnMean;
	}

	mixedFvPatchField<vector>::updateCoeffs();
}


void tnbLib::outletPhaseMeanVelocityFvPatchVectorField::write
(
	Ostream& os
) const
{
	fvPatchField<vector>::write(os);

	writeEntry(os, UnMean_());
	writeEntry(os, "alpha", alphaName_);
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchVectorField,
		outletPhaseMeanVelocityFvPatchVectorField
	);
}


// ************************************************************************* //