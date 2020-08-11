#include <Euler.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(Euler, 0);
	addToRunTimeSelectionTable(ODESolver, Euler, dictionary);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::Euler::Euler(const ODESystem& ode, const dictionary& dict)
	:
	ODESolver(ode, dict),
	adaptiveSolver(ode, dict),
	err_(n_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::Euler::resize()
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


tnbLib::scalar tnbLib::Euler::solve
(
	const scalar x0,
	const scalarField& y0,
	const scalarField& dydx0,
	const scalar dx,
	scalarField& y
) const
{
	// Calculate error estimate from the change in state:
	forAll(err_, i)
	{
		err_[i] = dx * dydx0[i];
	}

	// Update the state
	forAll(y, i)
	{
		y[i] = y0[i] + err_[i];
	}

	return normalizeError(y0, y, err_);
}


void tnbLib::Euler::solve
(
	scalar& x,
	scalarField& y,
	scalar& dxTry
) const
{
	adaptiveSolver::solve(odes_, x, y, dxTry);
}


// ************************************************************************* //