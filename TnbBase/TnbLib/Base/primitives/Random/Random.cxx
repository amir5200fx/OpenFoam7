#include <Random.hxx>

#include <PstreamReduceOps.hxx>

// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::scalar tnbLib::Random::scalarNormal()
{
	// Proper inversion of the distribution. Slow. Exactly maintains
	// the random behaviour of the generator.

	/*
	using namespace constant::mathematical;

	static const scalar sqrtTwo = sqrt(scalar(2));
	static const scalar sqrtPiByTwo = sqrt(pi)/2;
	static const scalar a = 8*(pi - 3)/(3*pi*(4 - pi));

	const scalar x = 2*scalar01() - 1;
	const scalar xPos = mag(x);

	// Initial approximation
	const scalar l = log(1 - sqr(xPos));
	const scalar ll = 2/(pi*a) + l/2;
	scalar y = sqrt(sqrt(sqr(ll) - l/a) - ll);

	// Newton improvement
	label n = 0;
	while (n < 2)
	{
		const scalar dt = (erf(y) - xPos)/exp(- y*y)*sqrtPiByTwo;
		y -= dt;
		n += mag(dt) < rootSmall;
	}

	return sign(x)*sqrtTwo*y;
	*/

	// Box-Muller transform. Fast. Uses rejection and caching so the
	// random sequence is not guaranteed.

	if (scalarNormalStored_)
	{
		scalarNormalStored_ = false;

		return scalarNormalValue_;
	}
	else
	{
		scalar x1, x2, rr;

		do
		{
			x1 = 2 * scalar01() - 1;
			x2 = 2 * scalar01() - 1;
			rr = sqr(x1) + sqr(x2);
		} while (rr >= 1 || rr == 0);

		const scalar f = sqrt(-2 * log(rr) / rr);

		scalarNormalValue_ = x1 * f;
		scalarNormalStored_ = true;

		return x2 * f;
	}
}


tnbLib::scalar tnbLib::Random::globalScalar01()
{
	scalar value = -vGreat;

	if (Pstream::master())
	{
		value = scalar01();
	}

	Pstream::scatter(value);

	return value;
}


// ************************************************************************* //