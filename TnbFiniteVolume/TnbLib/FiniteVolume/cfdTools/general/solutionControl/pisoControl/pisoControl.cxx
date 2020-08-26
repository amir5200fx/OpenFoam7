#include <pisoControl.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(pisoControl, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::pisoControl::pisoControl(fvMesh& mesh, const word& algorithmName)
	:
	fluidSolutionControl(mesh, algorithmName),
	nCorrPiso_(-1),
	corrPiso_(0)
{
	read();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::pisoControl::~pisoControl()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool tnbLib::pisoControl::read()
{
	if (!fluidSolutionControl::read())
	{
		return false;
	}

	const dictionary& solutionDict = dict();

	nCorrPiso_ = solutionDict.lookupOrDefault<label>("nCorrectors", 1);

	return true;
}


bool tnbLib::pisoControl::isFinal() const
{
	return
		(!anyNonOrthogonalIter() && finalPisoIter())
		|| (finalNonOrthogonalIter() && finalPisoIter())
		|| (finalNonOrthogonalIter() && !anyPisoIter());
}


bool tnbLib::pisoControl::correct()
{
	read();

	if (finalPisoIter())
	{
		corrPiso_ = 0;

		updateFinal();

		return false;
	}

	++corrPiso_;

	updateFinal();

	return true;
}


bool tnbLib::pisoControl::run(Time& time)
{
	return time.run();
}


bool tnbLib::pisoControl::loop(Time& time)
{
	return time.loop();
}


// ************************************************************************* //