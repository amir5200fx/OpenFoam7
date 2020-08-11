#include <EulerSI.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(EulerSI, 0);
	addToRunTimeSelectionTable(ODESolver, EulerSI, dictionary);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::EulerSI::EulerSI(const ODESystem& ode, const dictionary& dict)
	:
	ODESolver(ode, dict),
	adaptiveSolver(ode, dict),
	err_(n_),
	dydx_(n_),
	dfdx_(n_),
	dfdy_(n_, n_),
	a_(n_, n_),
	pivotIndices_(n_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::EulerSI::resize()
{
	if (ODESolver::resize())
	{
		adaptiveSolver::resize(n_);

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


tnbLib::scalar tnbLib::EulerSI::solve
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

		a_(i, i) += 1.0 / dx;
	}

	LUDecompose(a_, pivotIndices_);

	// Calculate error estimate from the change in state:
	forAll(err_, i)
	{
		err_[i] = dydx0[i] + dx * dfdx_[i];
	}

	LUBacksubstitute(a_, pivotIndices_, err_);

	forAll(y, i)
	{
		y[i] = y0[i] + err_[i];
	}

	return normalizeError(y0, y, err_);
}


void tnbLib::EulerSI::solve
(
	scalar& x,
	scalarField& y,
	scalar& dxTry
) const
{
	adaptiveSolver::solve(odes_, x, y, dxTry);
}


// ************************************************************************* //