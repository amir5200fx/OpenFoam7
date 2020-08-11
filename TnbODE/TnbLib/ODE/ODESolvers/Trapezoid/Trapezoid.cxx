#include <Trapezoid.hxx>

#include <addToRunTimeSelectionTable.hxx>
// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(Trapezoid, 0);
	addToRunTimeSelectionTable(ODESolver, Trapezoid, dictionary);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::Trapezoid::Trapezoid(const ODESystem& ode, const dictionary& dict)
	:
	ODESolver(ode, dict),
	adaptiveSolver(ode, dict),
	err_(n_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::Trapezoid::resize()
{
	if (ODESolver::resize())
	{
		adaptiveSolver::resize(n_);

		resizeField(err_);

		return true;
	}
	else
	{
		return false;
	}
}


tnbLib::scalar tnbLib::Trapezoid::solve
(
	const scalar x0,
	const scalarField& y0,
	const scalarField& dydx0,
	const scalar dx,
	scalarField& y
) const
{
	// Predict the state using 1st-order Trapezoid method
	forAll(y, i)
	{
		y[i] = y0[i] + dx * dydx0[i];
	}

	// Evaluate the system for the predicted state
	odes_.derivatives(x0 + dx, y, err_);

	// Update the state as the average between the prediction and the correction
	// and estimate the error from the difference
	forAll(y, i)
	{
		y[i] = y0[i] + 0.5*dx*(dydx0[i] + err_[i]);
		err_[i] = 0.5*dx*(err_[i] - dydx0[i]);
	}

	return normalizeError(y0, y, err_);
}


void tnbLib::Trapezoid::solve
(
	scalar& x,
	scalarField& y,
	scalar& dxTry
) const
{
	adaptiveSolver::solve(odes_, x, y, dxTry);
}


// ************************************************************************* //
