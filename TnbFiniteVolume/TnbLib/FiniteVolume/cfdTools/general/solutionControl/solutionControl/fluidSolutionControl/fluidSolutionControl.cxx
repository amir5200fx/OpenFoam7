#include <fluidSolutionControl.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(fluidSolutionControl, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fluidSolutionControl::fluidSolutionControl
(
	fvMesh& mesh,
	const word& algorithmName
)
	:
	nonOrthogonalSolutionControl(mesh, algorithmName),
	frozenFlow_(false),
	momentumPredictor_(true),
	transonic_(false),
	consistent_(false)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::fluidSolutionControl::~fluidSolutionControl()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool tnbLib::fluidSolutionControl::read()
{
	if (!nonOrthogonalSolutionControl::read())
	{
		return false;
	}

	const dictionary& solutionDict = dict();

	// The solveFluid keyword is maintained here for backwards compatibility
	frozenFlow_ = !solutionDict.lookupOrDefault<bool>("solveFluid", true);
	frozenFlow_ = solutionDict.lookupOrDefault<bool>("frozenFlow", frozenFlow_);

	momentumPredictor_ =
		solutionDict.lookupOrDefault<bool>("momentumPredictor", true);
	transonic_ = solutionDict.lookupOrDefault<bool>("transonic", false);
	consistent_ = solutionDict.lookupOrDefault<bool>("consistent", false);

	return true;
}


// ************************************************************************* //