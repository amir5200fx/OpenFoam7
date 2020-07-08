#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::quadraticEqn::quadraticEqn()
{}


inline tnbLib::quadraticEqn::quadraticEqn(const tnbLib::zero)
	:
	VectorSpace<quadraticEqn, scalar, 3>(tnbLib::zero())
{}


inline tnbLib::quadraticEqn::quadraticEqn
(
	const scalar a,
	const scalar b,
	const scalar c
)
{
	this->v_[coefficient::a] = a;
	this->v_[coefficient::b] = b;
	this->v_[coefficient::c] = c;
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::scalar tnbLib::quadraticEqn::a() const
{
	return this->v_[coefficient::a];
}


inline tnbLib::scalar tnbLib::quadraticEqn::b() const
{
	return this->v_[coefficient::b];
}


inline tnbLib::scalar tnbLib::quadraticEqn::c() const
{
	return this->v_[coefficient::c];
}


inline tnbLib::scalar& tnbLib::quadraticEqn::a()
{
	return this->v_[coefficient::a];
}


inline tnbLib::scalar& tnbLib::quadraticEqn::b()
{
	return this->v_[coefficient::b];
}


inline tnbLib::scalar& tnbLib::quadraticEqn::c()
{
	return this->v_[coefficient::c];
}


inline tnbLib::scalar tnbLib::quadraticEqn::value(const scalar x) const
{
	return x * (x*a() + b()) + c();
}


inline tnbLib::scalar tnbLib::quadraticEqn::derivative(const scalar x) const
{
	return x * 2 * a() + b();
}


inline tnbLib::scalar tnbLib::quadraticEqn::error(const scalar x) const
{
	return
		small * mag(x)*(mag(x*a()) + mag(b()))
		+ small * (mag(x*(x*a() + b())) + mag(c()));
}


// ************************************************************************* //