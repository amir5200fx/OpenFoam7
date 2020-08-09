#include <freestreamVelocityFvPatchVectorField.hxx>

#include <addToRunTimeSelectionTable.hxx>

#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::freestreamVelocityFvPatchVectorField::freestreamVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF
)
	:
	mixedFvPatchVectorField(p, iF)
{}


tnbLib::freestreamVelocityFvPatchVectorField::freestreamVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const dictionary& dict
)
	:
	mixedFvPatchVectorField(p, iF)
{
	freestreamValue() = vectorField("freestreamValue", dict, p.size());

	if (dict.found("value"))
	{
		fvPatchVectorField::operator=
			(
				vectorField("value", dict, p.size())
				);
	}
	else
	{
		fvPatchVectorField::operator=(freestreamValue());
	}

	refGrad() = Zero;
	valueFraction() = 1;
}


tnbLib::freestreamVelocityFvPatchVectorField::freestreamVelocityFvPatchVectorField
(
	const freestreamVelocityFvPatchVectorField& ptf,
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	mixedFvPatchVectorField(ptf, p, iF, mapper)
{}


tnbLib::freestreamVelocityFvPatchVectorField::freestreamVelocityFvPatchVectorField
(
	const freestreamVelocityFvPatchVectorField& wbppsf
)
	:
	mixedFvPatchVectorField(wbppsf)
{}


tnbLib::freestreamVelocityFvPatchVectorField::freestreamVelocityFvPatchVectorField
(
	const freestreamVelocityFvPatchVectorField& wbppsf,
	const DimensionedField<vector, volMesh>& iF
)
	:
	mixedFvPatchVectorField(wbppsf, iF)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::freestreamVelocityFvPatchVectorField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	const Field<vector>& Up = *this;
	const Field<scalar> magUp(mag(Up));

	const Field<vector> nf(patch().nf());

	Field<scalar>& vf = valueFraction();

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

	mixedFvPatchField<vector>::updateCoeffs();
}


void tnbLib::freestreamVelocityFvPatchVectorField::write(Ostream& os) const
{
	fvPatchVectorField::write(os);
	writeEntry(os, "freestreamValue", freestreamValue());
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchVectorField,
		freestreamVelocityFvPatchVectorField
	);
}

// ************************************************************************* //