#include <nonOrthogonalSolutionControl.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(nonOrthogonalSolutionControl, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::nonOrthogonalSolutionControl::nonOrthogonalSolutionControl
(
	fvMesh& mesh,
	const word& algorithmName
)
	:
	singleRegionSolutionControl(mesh, algorithmName),
	nCorrNonOrth_(-1),
	corrNonOrth_(0)
{
	read();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::nonOrthogonalSolutionControl::~nonOrthogonalSolutionControl()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool tnbLib::nonOrthogonalSolutionControl::read()
{
	if (!singleRegionSolutionControl::read())
	{
		return false;
	}

	const dictionary& solutionDict = dict();

	nCorrNonOrth_ =
		solutionDict.lookupOrDefault<label>("nNonOrthogonalCorrectors", 0);

	return true;
}


bool tnbLib::nonOrthogonalSolutionControl::correctNonOrthogonal()
{
	read();

	if (finalNonOrthogonalIter())
	{
		corrNonOrth_ = 0;

		updateFinal();

		return false;
	}

	++corrNonOrth_;

	updateFinal();

	return true;
}


// ************************************************************************* //