#include <quadraticEqn.hxx>

#include <linearEqn.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::Roots<2> tnbLib::quadraticEqn::roots() const
{
	/*

	This function solves a quadraticEqn equation of the following form:

		a*x^2 + b*x + c = 0
		  x^2 + B*x + C = 0

	The quadraticEqn formula is as follows:

		x = - B/2 +- sqrt(B*B - 4*C)/2

	If the sqrt generates a complex number, this provides the result. If not
	then the real root with the smallest floating point error is calculated.

		x0 = - B/2 - sign(B)*sqrt(B*B - 4*C)/2

	The other root is the obtained using an identity.

		x1 = C/x0

	*/

	const scalar a = this->a();
	const scalar b = this->b();
	const scalar c = this->c();

	if (a == 0)
	{
		return Roots<2>(linearEqn(b, c).roots(), rootType::nan, 0);
	}

	// This is assumed not to over- or under-flow. If it does, all bets are off.
	const scalar disc = b * b / 4 - a * c;

	// How many roots of what types are available?
	const bool oneReal = disc == 0;
	const bool twoReal = disc > 0;
	// const bool twoComplex = disc < 0;

	if (oneReal)
	{
		const Roots<1> r = linearEqn(a, b / 2).roots();
		return Roots<2>(r, r);
	}
	else if (twoReal)
	{
		const scalar x = -b / 2 - sign(b)*sqrt(disc);
		return Roots<2>(linearEqn(-a, x).roots(), linearEqn(-x, c).roots());
	}
	else // if (twoComplex)
	{
		return Roots<2>(rootType::complex, 0);
	}
}

// ************************************************************************* //