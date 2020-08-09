#include <freestreamPressureFvPatchScalarField.hxx>

#include <volFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::freestreamPressureFvPatchScalarField::
freestreamPressureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	mixedFvPatchScalarField(p, iF),
	UName_("U"),
	supersonic_(false)
{}


tnbLib::freestreamPressureFvPatchScalarField::
freestreamPressureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	mixedFvPatchScalarField(p, iF),
	UName_(dict.lookupOrDefault<word>("U", "U")),
	supersonic_
	(
		dict.lookupOrDefault<Switch>("supersonic", false)
	)
{
	freestreamValue() = scalarField("freestreamValue", dict, p.size());

	if (dict.found("value"))
	{
		fvPatchScalarField::operator=
			(
				scalarField("value", dict, p.size())
				);
	}
	else
	{
		fvPatchScalarField::operator=(freestreamValue());
	}

	refGrad() = Zero;
	valueFraction() = 0;
}


tnbLib::freestreamPressureFvPatchScalarField::
freestreamPressureFvPatchScalarField
(
	const freestreamPressureFvPatchScalarField& psf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	mixedFvPatchScalarField(psf, p, iF, mapper),
	UName_(psf.UName_),
	supersonic_(psf.supersonic_)
{}


tnbLib::freestreamPressureFvPatchScalarField::
freestreamPressureFvPatchScalarField
(
	const freestreamPressureFvPatchScalarField& psf
)
	:
	mixedFvPatchScalarField(psf),
	UName_(psf.UName_),
	supersonic_(psf.supersonic_)
{}


tnbLib::freestreamPressureFvPatchScalarField::
freestreamPressureFvPatchScalarField
(
	const freestreamPressureFvPatchScalarField& psf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	mixedFvPatchScalarField(psf, iF),
	UName_(psf.UName_),
	supersonic_(psf.supersonic_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::freestreamPressureFvPatchScalarField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	const Field<vector>& Up =
		patch().template lookupPatchField<volVectorField, vector>
		(
			UName_
			);

	const Field<scalar> magUp(mag(Up));

	const Field<vector> nf(patch().nf());

	Field<scalar>& vf = valueFraction();

	if (supersonic_)
	{
		forAll(vf, i)
		{
			if (magUp[i] > vSmall)
			{
				vf[i] = 0.5 - 0.5*(Up[i] & nf[i]) / magUp[i];
			}
			else
			{
				vf[i] = 0.5;
			}
		}
	}
	else
	{
		forAll(vf, i)
		{
			if (magUp[i] > vSmall)
			{
				vf[i] = 0.5 + 0.5*(Up[i] & nf[i]) / magUp[i];
			}
			else
			{
				vf[i] = 0.5;
			}
		}
	}

	mixedFvPatchField<scalar>::updateCoeffs();
}


void tnbLib::freestreamPressureFvPatchScalarField::write(Ostream& os) const
{
	fvPatchScalarField::write(os);
	writeEntryIfDifferent<word>(os, "U", "U", UName_);
	writeEntry(os, "freestreamValue", freestreamValue());
	writeEntry(os, "supersonic", supersonic_);
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		freestreamPressureFvPatchScalarField
	);
}

// ************************************************************************* //
