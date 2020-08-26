#include <pimpleLoop.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(pimpleLoop, 0);
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

bool tnbLib::pimpleLoop::read()
{
	nCorrPimple_ =
		control_.dict().lookupOrDefault<label>("nOuterCorrectors", 1);

	return true;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::pimpleLoop::pimpleLoop(const solutionControl& control)
	:
	control_(control),
	nCorrPimple_(-1),
	corrPimple_(0),
	converged_(false)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::pimpleLoop::~pimpleLoop()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool tnbLib::pimpleLoop::loop(correctorConvergenceControl& convergence)
{
	read();

	// Handle quit conditions first
	{
		// If converged on the last iteration then end the correction loop
		if (converged_)
		{
			Info << control_.algorithmName() << ": Converged in " << corrPimple_
				<< " iterations" << endl;

			corrPimple_ = 0;
			converged_ = false;

			return false;
		}

		// If all corrections have been completed then end the correction loop
		if (corrPimple_ >= nCorrPimple_)
		{
			if (convergence.hasCorrResidualControls() && nCorrPimple_ > 1)
			{
				Info << control_.algorithmName() << ": Not converged within "
					<< nCorrPimple_ << " iterations" << endl;
			}

			corrPimple_ = 0;
			converged_ = false;

			return false;
		}
	}

	// If we reached here, we are doing another loop
	++corrPimple_;

	// Set up the next loop
	{
		// If convergence has been reached then set the flag so that the loop
		// exits next time around
		if (!firstPimpleIter() && convergence.corrCriteriaSatisfied())
		{
			Info << control_.algorithmName() << ": Converged " << nl
				<< control_.algorithmSpace() << "  Doing final iteration"
				<< endl;
			converged_ = true;
		}

		// Set up the next iteration by storing the index of the solution to
		// check the convergence of
		if (firstPimpleIter())
		{
			convergence.resetCorrSolveIndex();
		}
		else
		{
			convergence.updateCorrSolveIndex();
		}

		// Print the number of the iteration about to take place
		if (nCorrPimple_ > 1)
		{
			Info << control_.algorithmName() << ": Iteration " << corrPimple_
				<< endl;
		}

		return true;
	}
}


// ************************************************************************* //