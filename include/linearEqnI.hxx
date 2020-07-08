#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::linearEqn::linearEqn()
{}


inline tnbLib::linearEqn::linearEqn(const tnbLib::zero)
	:
	VectorSpace<linearEqn, scalar, 2>(tnbLib::zero())
{}


inline tnbLib::linearEqn::linearEqn(const scalar a, const scalar b)
{
	this->v_[coefficient::a] = a;
	this->v_[coefficient::b] = b;
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::scalar tnbLib::linearEqn::a() const
{
	return this->v_[coefficient::a];
}


inline tnbLib::scalar tnbLib::linearEqn::b() const
{
	return this->v_[coefficient::b];
}


inline tnbLib::scalar& tnbLib::linearEqn::a()
{
	return this->v_[coefficient::a];
}


inline tnbLib::scalar& tnbLib::linearEqn::b()
{
	return this->v_[coefficient::b];
}


inline tnbLib::scalar tnbLib::linearEqn::value(const scalar x) const
{
	return x * a() + b();
}


inline tnbLib::scalar tnbLib::linearEqn::derivative(const scalar x) const
{
	return a();
}


inline tnbLib::scalar tnbLib::linearEqn::error(const scalar x) const
{
	return small * (mag(x*a()) + mag(b()));
}


inline tnbLib::Roots<1> tnbLib::linearEqn::roots() const
{
	/*

	This function solves a linear equation of the following form:

		a*x + b = 0
		  x + b = 0

	*/

	const scalar a = this->a();
	const scalar b = this->b();

	if (a == 0)
	{
		return Roots<1>(rootType::nan, 0);
	}

	if (mag(b / vGreat) >= mag(a))
	{
		return Roots<1>
			(
				sign(a) == sign(b)
				? rootType::negInf
				: rootType::posInf,
				0
				);
	}

	return Roots<1>(rootType::real, -b / a);
}


// ************************************************************************* //