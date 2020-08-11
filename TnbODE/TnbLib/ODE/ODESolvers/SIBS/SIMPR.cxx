#include <SIBS.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

void tnbLib::SIBS::SIMPR
(
	const scalar xStart,
	const scalarField& y,
	const scalarField& dydx,
	const scalarField& dfdx,
	const scalarSquareMatrix& dfdy,
	const scalar deltaX,
	const label nSteps,
	scalarField& yEnd
) const
{
	scalar h = deltaX / nSteps;

	scalarSquareMatrix a(n_);
	for (label i = 0; i < n_; i++)
	{
		for (label j = 0; j < n_; j++)
		{
			a(i, j) = -h * dfdy(i, j);
		}
		++a(i, i);
	}

	labelList pivotIndices(n_);
	LUDecompose(a, pivotIndices);

	for (label i = 0; i < n_; i++)
	{
		yEnd[i] = h * (dydx[i] + h * dfdx[i]);
	}

	LUBacksubstitute(a, pivotIndices, yEnd);

	scalarField del(yEnd);
	scalarField ytemp(n_);

	for (label i = 0; i < n_; i++)
	{
		ytemp[i] = y[i] + del[i];
	}

	scalar x = xStart + h;

	odes_.derivatives(x, ytemp, yEnd);

	for (label nn = 2; nn <= nSteps; nn++)
	{
		for (label i = 0; i < n_; i++)
		{
			yEnd[i] = h * yEnd[i] - del[i];
		}

		LUBacksubstitute(a, pivotIndices, yEnd);

		for (label i = 0; i < n_; i++)
		{
			ytemp[i] += (del[i] += 2.0*yEnd[i]);
		}

		x += h;

		odes_.derivatives(x, ytemp, yEnd);
	}
	for (label i = 0; i < n_; i++)
	{
		yEnd[i] = h * yEnd[i] - del[i];
	}

	LUBacksubstitute(a, pivotIndices, yEnd);

	for (label i = 0; i < n_; i++)
	{
		yEnd[i] += ytemp[i];
	}
}


// ************************************************************************* //