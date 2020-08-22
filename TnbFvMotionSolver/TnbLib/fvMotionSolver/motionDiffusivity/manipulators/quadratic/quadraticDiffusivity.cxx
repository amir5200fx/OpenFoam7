#include <quadraticDiffusivity.hxx>

#include <surfaceFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(quadraticDiffusivity, 0);

	addToRunTimeSelectionTable
	(
		motionDiffusivity,
		quadraticDiffusivity,
		Istream
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::quadraticDiffusivity::quadraticDiffusivity
(
	const fvMesh& mesh,
	Istream& mdData
)
	:
	motionDiffusivity(mesh),
	basicDiffusivityPtr_(motionDiffusivity::New(mesh, mdData))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::quadraticDiffusivity::~quadraticDiffusivity()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::surfaceScalarField>
tnbLib::quadraticDiffusivity::operator()() const
{
	return sqr(basicDiffusivityPtr_->operator()());
}


void tnbLib::quadraticDiffusivity::correct()
{
	basicDiffusivityPtr_->correct();
}


// ************************************************************************* //