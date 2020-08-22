#include <uniformDiffusivity.hxx>

#include <surfaceFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(uniformDiffusivity, 0);

	addToRunTimeSelectionTable
	(
		motionDiffusivity,
		uniformDiffusivity,
		Istream
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::uniformDiffusivity::uniformDiffusivity
(
	const fvMesh& mesh,
	Istream&
)
	:
	motionDiffusivity(mesh)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::uniformDiffusivity::~uniformDiffusivity()
{}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::surfaceScalarField>
tnbLib::uniformDiffusivity::operator()() const
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


// ************************************************************************* //