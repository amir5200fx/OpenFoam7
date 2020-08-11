#include <SIBS.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

void tnbLib::SIBS::polyExtrapolate
(
	const label iest,
	const scalar xest,
	const scalarField& yest,
	scalarField& yz,
	scalarField& dy,
	scalarField& x,
	scalarRectangularMatrix& d
) const
{
	label n = yz.size();

	x[iest] = xest;

	for (label j = 0; j < n; j++)
	{
		dy[j] = yz[j] = yest[j];
	}

	if (iest == 0)
	{
		for (label j = 0; j < n; j++)
		{
			d(j, 0) = yest[j];
		}
	}
	else
	{
		scalarField c(yest);

		for (label k1 = 0; k1 < iest; k1++)
		{
			scalar delta = 1.0 / (x[iest - k1 - 1] - xest);
			scalar f1 = xest * delta;
			scalar f2 = x[iest - k1 - 1] * delta;

			for (label j = 0; j < n; j++)
			{
				scalar q = d[j][k1];
				d[j][k1] = dy[j];
				delta = c[j] - q;
				dy[j] = f1 * delta;
				c[j] = f2 * delta;
				yz[j] += dy[j];
			}
		}

		for (label j = 0; j < n; j++)
		{
			d[j][iest] = dy[j];
		}
	}
}


// ************************************************************************* //