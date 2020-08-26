#include <pimpleControl.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(pimpleControl, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::pimpleControl::pimpleControl(fvMesh& mesh, const word& algorithmName)
	:
	pimpleNoLoopControl(mesh, algorithmName, *this),
	pimpleLoop(static_cast<solutionControl&>(*this))
{
	read();

	printResidualControls();

	if (nCorrPimple_ > 1)
	{
		printCorrResidualControls(nCorrPimple_);
	}

	Info << nl << algorithmName << ": Operating solver in "
		<< (mesh.steady() ? "steady-state" : mesh.transient() ? "transient" :
			"mixed steady-state/transient") << " mode with " << nCorrPimple_
		<< " outer corrector" << (nCorrPimple_ == 1 ? "" : "s") << nl;

	if (nCorrPimple_ == 1)
	{
		Info << algorithmName << ": Operating solver in "
			<< (mesh.steady() ? "SIMPLE" : "PISO") << " mode" << nl;
	}

	Info << nl << endl;
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::pimpleControl::~pimpleControl()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool tnbLib::pimpleControl::read()
{
	if (!pimpleNoLoopControl::read() || !pimpleLoop::read())
	{
		return false;
	}

	nCorrPimple_ = dict().lookupOrDefault<label>("nOuterCorrectors", 1);

	return true;
}


bool tnbLib::pimpleControl::loop()
{
	read();

	if (!pimpleLoop::loop(*this))
	{
		updateFinal();

		return false;
	}

	storePrevIterFields();

	updateFinal();

	return true;
}


bool tnbLib::pimpleControl::run(Time& time)
{
	read();

	if (!endIfConverged(time))
	{
		storePrevIterFields();
	}

	return time.run();
}


bool tnbLib::pimpleControl::loop(Time& time)
{
	read();

	if (!endIfConverged(time))
	{
		storePrevIterFields();
	}

	return time.loop();
}


// ************************************************************************* //
