#include <Rosenbrock12.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(Rosenbrock12, 0);
	addToRunTimeSelectionTable(ODESolver, Rosenbrock12, dictionary);

	const scalar
		Rosenbrock12::gamma = 1 + 1.0 / std::sqrt(2.0),
		Rosenbrock12::a21 = 1.0 / gamma,
		Rosenbrock12::c2 = 1.0,
		Rosenbrock12::c21 = -2.0 / gamma,
		Rosenbrock12::b1 = (3.0 / 2.0) / gamma,
		Rosenbrock12::b2 = (1.0 / 2.0) / gamma,
		Rosenbrock12::e1 = b1 - 1.0 / gamma,
		Rosenbrock12::e2 = b2,
		Rosenbrock12::d1 = gamma,
		Rosenbrock12::d2 = -gamma;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::Rosenbrock12::Rosenbrock12(const ODESystem& ode, const dictionary& dict)
	:
	ODESolver(ode, dict),
	adaptiveSolver(ode, dict),
	k1_(n_),
	k2_(n_),
	err_(n_),
	dydx_(n_),
	dfdx_(n_),
	dfdy_(n_, n_),
	a_(n_, n_),
	pivotIndices_(n_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::Rosenbrock12::resize()
{
	if (ODESolver::resize())
	{
		adaptiveSolver::resize(n_);

		resizeField(k1_);
		resizeField(k2_);
		resizeField(err_);
		resizeField(dydx_);
		resizeField(dfdx_);
		resizeMatrix(dfdy_);
		resizeMatrix(a_);
		resizeField(pivotIndices_);

		return true;
	}
	else
	{
		return false;
	}
}


tnbLib::scalar tnbLib::Rosenbrock12::solve
(
	const scalar x0,
	const scalarField& y0,
	const scalarField& dydx0,
	const scalar dx,
	scalarField& y
) const
{
	odes_.jacobian(x0, y0, dfdx_, dfdy_);

	for (label i = 0; i < n_; i++)
	{
		for (label j = 0; j < n_; j++)
		{
			a_(i, j) = -dfdy_(i, j);
		}

		a_(i, i) += 1.0 / (gamma*dx);
	}

	LUDecompose(a_, pivotIndices_);

	// Calculate k1:
	forAll(k1_, i)
	{
		k1_[i] = dydx0[i] + dx * d1*dfdx_[i];
	}

	LUBacksubstitute(a_, pivotIndices_, k1_);

	// Calculate k2:
	forAll(y, i)
	{
		y[i] = y0[i] + a21 * k1_[i];
	}

	odes_.derivatives(x0 + c2 * dx, y, dydx_);

	forAll(k2_, i)
	{
		k2_[i] = dydx_[i] + dx * d2*dfdx_[i] + c21 * k1_[i] / dx;
	}

	LUBacksubstitute(a_, pivotIndices_, k2_);

	// Calculate error and update state:
	forAll(y, i)
	{
		y[i] = y0[i] + b1 * k1_[i] + b2 * k2_[i];
		err_[i] = e1 * k1_[i] + e2 * k2_[i];
	}

	return normalizeError(y0, y, err_);
}


void tnbLib::Rosenbrock12::solve
(
	scalar& x,
	scalarField& y,
	scalar& dxTry
) const
{
	adaptiveSolver::solve(odes_, x, y, dxTry);
}


// ************************************************************************* //