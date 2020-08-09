#include <movingWallVelocityFvPatchVectorField.hxx>

#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <fvcMeshPhi.hxx>
#include <addToRunTimeSelectionTable.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::movingWallVelocityFvPatchVectorField::
movingWallVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchVectorField(p, iF)
{}


tnbLib::movingWallVelocityFvPatchVectorField::
movingWallVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchVectorField(p, iF, dict)
{}


tnbLib::movingWallVelocityFvPatchVectorField::
movingWallVelocityFvPatchVectorField
(
	const movingWallVelocityFvPatchVectorField& ptf,
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchVectorField(ptf, p, iF, mapper)
{}


tnbLib::movingWallVelocityFvPatchVectorField::
movingWallVelocityFvPatchVectorField
(
	const movingWallVelocityFvPatchVectorField& mwvpvf
)
	:
	fixedValueFvPatchVectorField(mwvpvf)
{}


tnbLib::movingWallVelocityFvPatchVectorField::
movingWallVelocityFvPatchVectorField
(
	const movingWallVelocityFvPatchVectorField& mwvpvf,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchVectorField(mwvpvf, iF)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::movingWallVelocityFvPatchVectorField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	const fvMesh& mesh = internalField().mesh();

	if (mesh.moving())
	{
		const fvPatch& p = patch();
		const polyPatch& pp = p.patch();
		const pointField& oldPoints = mesh.oldPoints();

		vectorField oldFc(pp.size());

		forAll(oldFc, i)
		{
			oldFc[i] = pp[i].centre(oldPoints);
		}

		const scalar deltaT = mesh.time().deltaTValue();

		const vectorField Up((pp.faceCentres() - oldFc) / deltaT);

		const volVectorField& U =
			static_cast<const volVectorField&>(internalField());

		scalarField phip
		(
			p.patchField<surfaceScalarField, scalar>(fvc::meshPhi(U))
		);

		const vectorField n(p.nf());
		const scalarField& magSf = p.magSf();
		tmp<scalarField> Un = phip / (magSf + vSmall);


		vectorField::operator=(Up + n * (Un - (n & Up)));
	}

	fixedValueFvPatchVectorField::updateCoeffs();
}


void tnbLib::movingWallVelocityFvPatchVectorField::write(Ostream& os) const
{
	fvPatchVectorField::write(os);
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchVectorField,
		movingWallVelocityFvPatchVectorField
	);
}

// ************************************************************************* //