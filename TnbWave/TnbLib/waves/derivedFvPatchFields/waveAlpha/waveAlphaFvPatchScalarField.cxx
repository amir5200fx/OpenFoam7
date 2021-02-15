#include <waveAlphaFvPatchScalarField.hxx>

#include <waveAlphaFvPatchScalarField.hxx>

#include <wavePressureFvPatchScalarField.hxx>
#include <waveVelocityFvPatchVectorField.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <levelSet.hxx>
#include <surfaceFields.hxx>
#include <volFields.hxx>
#include <fvMeshSubset.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::waveAlphaFvPatchScalarField::waveAlphaFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	mixedFvPatchScalarField(p, iF),
	UName_("U"),
	liquid_(true),
	inletOutlet_(true)
{
	refValue() = Zero;
	refGrad() = Zero;
	valueFraction() = 0;
}


tnbLib::waveAlphaFvPatchScalarField::waveAlphaFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	mixedFvPatchScalarField(p, iF),
	UName_(dict.lookupOrDefault<word>("U", "U")),
	liquid_(dict.lookupOrDefault<Switch>("liquid", true)),
	inletOutlet_(dict.lookupOrDefault<Switch>("inletOutlet", true))
{
	if (dict.found("value"))
	{
		fvPatchScalarField::operator=(scalarField("value", dict, p.size()));
	}
	else
	{
		fvPatchScalarField::operator=(patchInternalField());
	}

	refValue() = *this;
	refGrad() = Zero;
	valueFraction() = 0;
}


tnbLib::waveAlphaFvPatchScalarField::waveAlphaFvPatchScalarField
(
	const waveAlphaFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	mixedFvPatchScalarField(ptf, p, iF, mapper),
	UName_(ptf.UName_),
	liquid_(ptf.liquid_),
	inletOutlet_(ptf.inletOutlet_)
{}


tnbLib::waveAlphaFvPatchScalarField::waveAlphaFvPatchScalarField
(
	const waveAlphaFvPatchScalarField& ptf
)
	:
	mixedFvPatchScalarField(ptf),
	UName_(ptf.UName_),
	liquid_(ptf.liquid_),
	inletOutlet_(ptf.inletOutlet_)
{}

tnbLib::waveAlphaFvPatchScalarField::waveAlphaFvPatchScalarField
(
	const waveAlphaFvPatchScalarField& ptf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	mixedFvPatchScalarField(ptf, iF),
	UName_(ptf.UName_),
	liquid_(ptf.liquid_),
	inletOutlet_(ptf.inletOutlet_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::scalarField> tnbLib::waveAlphaFvPatchScalarField::alpha() const
{
	const scalar t = db().time().timeOutputValue();
	const waveSuperposition& waves = waveSuperposition::New(db());

	return
		levelSetFraction
		(
			patch(),
			waves.height(t, patch().Cf()),
			waves.height(t, patch().patch().localPoints()),
			!liquid_
		);
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::waveAlphaFvPatchScalarField::alphan() const
{
	const scalar t = db().time().timeOutputValue();
	const waveSuperposition& waves = waveSuperposition::New(db());
	const waveVelocityFvPatchVectorField& Up =
		refCast<const waveVelocityFvPatchVectorField>
		(
			patch().lookupPatchField<volVectorField, scalar>(UName_)
			);

	const fvMeshSubset& subset = Up.faceCellSubset();
	const fvMesh& meshs = subset.subMesh();
	const label patchis = findIndex(subset.patchMap(), patch().index());

	const scalarField alphas
	(
		levelSetFraction
		(
			meshs,
			waves.height(t, meshs.cellCentres())(),
			waves.height(t, meshs.points())(),
			!liquid_
		)
	);

	tmp<scalarField> tResult(new scalarField(patch().size()));
	scalarField& result = tResult.ref();

	if (patchis != -1)
	{
		forAll(meshs.boundary()[patchis], is)
		{
			const label fs = is + meshs.boundary()[patchis].patch().start();
			const label cs = meshs.boundary()[patchis].faceCells()[is];
			const label f = subset.faceMap()[fs];
			const label i = patch().patch().whichFace(f);
			result[i] = alphas[cs];
		}
	}

	return tResult;
}


void tnbLib::waveAlphaFvPatchScalarField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	const fvPatchVectorField& Up =
		patch().lookupPatchField<volVectorField, scalar>(UName_);

	if (!isA<waveVelocityFvPatchVectorField>(Up))
	{
		FatalErrorInFunction
			<< "The corresponding condition for the velocity "
			<< "field " << UName_ << " on patch " << patch().name()
			<< " is not of type " << waveVelocityFvPatchVectorField::typeName
			<< exit(FatalError);
	}

	const waveVelocityFvPatchVectorField& Uwp =
		refCast<const waveVelocityFvPatchVectorField>(Up);

	const fvPatchScalarField& pp =
		patch().lookupPatchField<volScalarField, scalar>(Uwp.pName());

	if (isA<wavePressureFvPatchScalarField>(pp))
	{
		const scalarField alpha(this->alpha()), alphan(this->alphan());
		const scalarField out(pos0(Uwp.U() & patch().Sf()));

		valueFraction() = out;
		refValue() = alpha;
		refGrad() = (alpha - alphan)*patch().deltaCoeffs();
	}
	else
	{
		refValue() = alpha();

		if (inletOutlet_)
		{
			const scalarField& phip =
				patch().lookupPatchField<surfaceScalarField, scalar>("phi");
			const scalarField out(pos0(phip));

			valueFraction() = 1 - out;
		}
		else
		{
			valueFraction() = 1;
		}
	}

	mixedFvPatchScalarField::updateCoeffs();
}


void tnbLib::waveAlphaFvPatchScalarField::write
(
	Ostream& os
) const
{
	mixedFvPatchScalarField::write(os);
	writeEntryIfDifferent<word>(os, "U", "U", UName_);
	writeEntryIfDifferent<Switch>(os, "inletOutlet", true, inletOutlet_);
	writeEntryIfDifferent<Switch>(os, "liquid", true, liquid_);
}


// * * * * * * * * * * * * * * Build Macro Function  * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField(fvPatchScalarField, waveAlphaFvPatchScalarField);
}

// ************************************************************************* //