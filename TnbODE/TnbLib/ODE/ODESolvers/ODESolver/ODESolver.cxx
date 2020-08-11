#include <ODESolver.hxx>

#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(ODESolver, 0);
	defineRunTimeSelectionTable(ODESolver, dictionary);
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

tnbLib::scalar tnbLib::ODESolver::normalizeError
(
	const scalarField& y0,
	const scalarField& y,
	const scalarField& err
) const
{
	// Calculate the maximum error
	scalar maxErr = 0.0;
	forAll(err, i)
	{
		scalar tol = absTol_[i] + relTol_[i] * max(mag(y0[i]), mag(y[i]));
		maxErr = max(maxErr, mag(err[i]) / tol);
	}

	return maxErr;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::ODESolver::ODESolver(const ODESystem& ode, const dictionary& dict)
	:
	odes_(ode),
	maxN_(ode.nEqns()),
	n_(ode.nEqns()),
	absTol_(n_, dict.lookupOrDefault<scalar>("absTol", small)),
	relTol_(n_, dict.lookupOrDefault<scalar>("relTol", 1e-4)),
	maxSteps_(dict.lookupOrDefault<scalar>("maxSteps", 10000))
{}


tnbLib::ODESolver::ODESolver
(
	const ODESystem& ode,
	const scalarField& absTol,
	const scalarField& relTol
)
	:
	odes_(ode),
	maxN_(ode.nEqns()),
	n_(ode.nEqns()),
	absTol_(absTol),
	relTol_(relTol),
	maxSteps_(10000)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::ODESolver::resize()
{
	if (odes_.nEqns() != n_)
	{
		if (odes_.nEqns() > maxN_)
		{
			FatalErrorInFunction
				<< "Specified number of equations " << odes_.nEqns()
				<< " greater than maximum " << maxN_
				<< abort(FatalError);
		}

		n_ = odes_.nEqns();

		resizeField(absTol_);
		resizeField(relTol_);

		return true;
	}
	else
	{
		return false;
	}
}


void tnbLib::ODESolver::solve
(
	scalar& x,
	scalarField& y,
	scalar& dxTry
) const
{
	stepState step(dxTry);
	solve(x, y, step);
	dxTry = step.dxTry;
}


void tnbLib::ODESolver::solve
(
	scalar& x,
	scalarField& y,
	stepState& step
) const
{
	scalar x0 = x;
	solve(x, y, step.dxTry);
	step.dxDid = x - x0;
}


void tnbLib::ODESolver::solve
(
	const scalar xStart,
	const scalar xEnd,
	scalarField& y,
	scalar& dxTry
) const
{
	stepState step(dxTry);
	scalar x = xStart;

	for (label nStep = 0; nStep < maxSteps_; nStep++)
	{
		// Store previous iteration dxTry
		scalar dxTry0 = step.dxTry;

		step.reject = false;

		// Check if this is a truncated step and set dxTry to integrate to xEnd
		if ((x + step.dxTry - xEnd)*(x + step.dxTry - xStart) > 0)
		{
			step.last = true;
			step.dxTry = xEnd - x;
		}

		// Integrate as far as possible up to step.dxTry
		solve(x, y, step);

		// Check if reached xEnd
		if ((x - xEnd)*(xEnd - xStart) >= 0)
		{
			if (nStep > 0 && step.last)
			{
				step.dxTry = dxTry0;
			}

			dxTry = step.dxTry;

			return;
		}

		step.first = false;

		// If the step.dxTry was reject set step.prevReject
		if (step.reject)
		{
			step.prevReject = true;
		}
	}

	FatalErrorInFunction
		<< "Integration steps greater than maximum " << maxSteps_ << nl
		<< "    xStart = " << xStart << ", xEnd = " << xEnd
		<< ", x = " << x << ", dxDid = " << step.dxDid << nl
		<< "    y = " << y
		<< exit(FatalError);
}


// ************************************************************************* //