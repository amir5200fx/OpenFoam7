#include <adaptiveSolver.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::adaptiveSolver::adaptiveSolver
(
	const ODESystem& ode,
	const dictionary& dict
)
	:
	safeScale_(dict.lookupOrDefault<scalar>("safeScale", 0.9)),
	alphaInc_(dict.lookupOrDefault<scalar>("alphaIncrease", 0.2)),
	alphaDec_(dict.lookupOrDefault<scalar>("alphaDecrease", 0.25)),
	minScale_(dict.lookupOrDefault<scalar>("minScale", 0.2)),
	maxScale_(dict.lookupOrDefault<scalar>("maxScale", 10)),
	dydx0_(ode.nEqns()),
	yTemp_(ode.nEqns())
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::adaptiveSolver::resize(const label n)
{
	ODESolver::resizeField(dydx0_, n);
	ODESolver::resizeField(yTemp_, n);

	return true;
}


void tnbLib::adaptiveSolver::solve
(
	const ODESystem& odes,
	scalar& x,
	scalarField& y,
	scalar& dxTry
) const
{
	scalar dx = dxTry;
	scalar err = 0.0;

	odes.derivatives(x, y, dydx0_);

	// Loop over solver and adjust step-size as necessary
	// to achieve desired error
	do
	{
		// Solve step and provide error estimate
		err = solve(x, y, dydx0_, dx, yTemp_);

		// If error is large reduce dx
		if (err > 1)
		{
			scalar scale = max(safeScale_*pow(err, -alphaDec_), minScale_);
			dx *= scale;

			if (dx < vSmall)
			{
				FatalErrorInFunction
					<< "stepsize underflow"
					<< exit(FatalError);
			}
		}
	} while (err > 1);

	// Update the state
	x += dx;
	y = yTemp_;

	// If the error is small increase the step-size
	if (err > pow(maxScale_ / safeScale_, -1.0 / alphaInc_))
	{
		dxTry =
			min(max(safeScale_*pow(err, -alphaInc_), minScale_), maxScale_)*dx;
	}
	else
	{
		dxTry = safeScale_ * maxScale_*dx;
	}
}


// ************************************************************************* //