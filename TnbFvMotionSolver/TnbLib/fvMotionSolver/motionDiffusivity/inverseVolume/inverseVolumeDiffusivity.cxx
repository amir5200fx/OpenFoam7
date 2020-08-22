#include <inverseVolumeDiffusivity.hxx>

#include <patchWave.hxx>
#include <HashSet.hxx>
#include <surfaceInterpolate.hxx>
#include <zeroGradientFvPatchFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

#include <Time.hxx> // added by amir
#include <volMesh.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(inverseVolumeDiffusivity, 0);

	addToRunTimeSelectionTable
	(
		motionDiffusivity,
		inverseVolumeDiffusivity,
		Istream
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::inverseVolumeDiffusivity::inverseVolumeDiffusivity
(
	const fvMesh& mesh,
	Istream& mdData
)
	:
	motionDiffusivity(mesh)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::inverseVolumeDiffusivity::~inverseVolumeDiffusivity()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::surfaceScalarField>
tnbLib::inverseVolumeDiffusivity::operator()() const
{
	volScalarField V
	(
		tnbLib::IOobject
		(
			"V",
			mesh().time().timeName(),
			mesh(),
			tnbLib::IOobject::NO_READ,
			tnbLib::IOobject::NO_WRITE,
			false
		),
		mesh(),
		dimless,
		zeroGradientFvPatchScalarField::typeName
	);

	V.primitiveFieldRef() = mesh().V();
	V.correctBoundaryConditions();

	return surfaceScalarField::New
	(
		"faceDiffusivity",
		1.0 / fvc::interpolate(V)
	);
}


// ************************************************************************* //