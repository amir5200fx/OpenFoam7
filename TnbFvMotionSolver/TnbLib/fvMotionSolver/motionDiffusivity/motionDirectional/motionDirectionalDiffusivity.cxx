#include <motionDirectionalDiffusivity.hxx>

#include <surfaceInterpolate.hxx>
#include <zeroGradientFvPatchFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

#include <Time.hxx>  // added by amir
#include <volMesh.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(motionDirectionalDiffusivity, 0);

	addToRunTimeSelectionTable
	(
		motionDiffusivity,
		motionDirectionalDiffusivity,
		Istream
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::motionDirectionalDiffusivity::motionDirectionalDiffusivity
(
	const fvMesh& mesh,
	Istream& mdData
)
	:
	motionDiffusivity(mesh),
	diffusivityVector_(mdData)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::motionDirectionalDiffusivity::~motionDirectionalDiffusivity()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::surfaceScalarField>
tnbLib::motionDirectionalDiffusivity::operator()() const
{
	if (mesh().foundObject<volVectorField>("cellMotionU"))
	{
		const volVectorField& cellMotionU =
			mesh().lookupObject<volVectorField>("cellMotionU");

		volVectorField D
		(
			IOobject
			(
				"D",
				mesh().time().timeName(),
				mesh()
			),
			diffusivityVector_.y()*vector::one
			+ (diffusivityVector_.x() - diffusivityVector_.y())*cellMotionU
			/ (mag(cellMotionU) + dimensionedScalar(dimVelocity, small)),
			zeroGradientFvPatchVectorField::typeName
		);
		D.correctBoundaryConditions();

		const surfaceVectorField n(mesh().Sf() / mesh().magSf());

		return surfaceScalarField::New
		(
			"faceDiffusivity",
			(n & cmptMultiply(fvc::interpolate(D), n))
		);
	}
	else
	{
		return tmp<surfaceScalarField>
			(
				new surfaceScalarField
				(
					IOobject
					(
						"faceDiffusivity",
						mesh().time().timeName(),
						mesh(),
						IOobject::NO_READ,
						IOobject::NO_WRITE
					),
					mesh(),
					dimensionedScalar(dimless, 1.0)
				)
				);
	}
}


// ************************************************************************* //