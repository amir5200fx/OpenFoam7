#include <simpleControl.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(simpleControl, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::simpleControl::simpleControl(fvMesh& mesh, const word& algorithmName)
	:
	fluidSolutionControl(mesh, algorithmName),
	singleRegionConvergenceControl
	(
		static_cast<singleRegionSolutionControl&>(*this)
	)
{
	read();
	printResidualControls();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::simpleControl::~simpleControl()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool tnbLib::simpleControl::read()
{
	return fluidSolutionControl::read() && readResidualControls();
}


bool tnbLib::simpleControl::run(Time& time)
{
	read();

	if (!endIfConverged(time))
	{
		storePrevIterFields();
	}

	return time.run();
}


bool tnbLib::simpleControl::loop(Time& time)
{
	read();

	if (!endIfConverged(time))
	{
		storePrevIterFields();
	}

	return time.loop();
}


// ************************************************************************* //