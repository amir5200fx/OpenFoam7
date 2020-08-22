#include <exponentialDiffusivity.hxx>

#include <surfaceFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(exponentialDiffusivity, 0);

	addToRunTimeSelectionTable
	(
		motionDiffusivity,
		exponentialDiffusivity,
		Istream
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::exponentialDiffusivity::exponentialDiffusivity
(
	const fvMesh& mesh,
	Istream& mdData
)
	:
	motionDiffusivity(mesh),
	alpha_(readScalar(mdData)),
	basicDiffusivityPtr_(motionDiffusivity::New(mesh, mdData))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::exponentialDiffusivity::~exponentialDiffusivity()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::surfaceScalarField>
tnbLib::exponentialDiffusivity::operator()() const
{
	return exp(-alpha_ / basicDiffusivityPtr_->operator()());
}


void tnbLib::exponentialDiffusivity::correct()
{
	basicDiffusivityPtr_->correct();
}


// ************************************************************************* //