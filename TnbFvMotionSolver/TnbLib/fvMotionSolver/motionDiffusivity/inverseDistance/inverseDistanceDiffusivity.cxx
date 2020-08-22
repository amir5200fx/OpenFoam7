#include <inverseDistanceDiffusivity.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <patchWave.hxx>
#include <HashSet.hxx>
#include <surfaceInterpolate.hxx>
#include <zeroGradientFvPatchFields.hxx>

#include <Time.hxx>  // added by amir
#include <volMesh.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(inverseDistanceDiffusivity, 0);

	addToRunTimeSelectionTable
	(
		motionDiffusivity,
		inverseDistanceDiffusivity,
		Istream
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::inverseDistanceDiffusivity::inverseDistanceDiffusivity
(
	const fvMesh& mesh,
	Istream& mdData
)
	:
	motionDiffusivity(mesh),
	patchNames_(mdData)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::inverseDistanceDiffusivity::~inverseDistanceDiffusivity()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::scalarField> tnbLib::inverseDistanceDiffusivity::y() const
{
	const labelHashSet patchSet(mesh().boundaryMesh().patchSet(patchNames_));

	if (patchSet.size())
	{
		return tmp<scalarField>
			(
				new scalarField(patchWave(mesh(), patchSet, false).distance())
				);
	}
	else
	{
		return tmp<scalarField>(new scalarField(mesh().nCells(), 1.0));
	}
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::surfaceScalarField>
tnbLib::inverseDistanceDiffusivity::operator()() const
{
	volScalarField y_
	(
		IOobject
		(
			"y",
			mesh().time().timeName(),
			mesh()
		),
		mesh(),
		dimless,
		zeroGradientFvPatchScalarField::typeName
	);
	y_.primitiveFieldRef() = y();
	y_.correctBoundaryConditions();

	return surfaceScalarField::New
	(
		"faceDiffusivity",
		1.0 / fvc::interpolate(y_)
	);
}


// ************************************************************************* //