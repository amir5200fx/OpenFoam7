#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::cubicEqn::cubicEqn()
{}


inline tnbLib::cubicEqn::cubicEqn(const tnbLib::zero)
	:
	VectorSpace<cubicEqn, scalar, 4>(tnbLib::zero())
{}


inline tnbLib::cubicEqn::cubicEqn
(
	const scalar a,
	const scalar b,
	const scalar c,
	const scalar d
)
{
	this->v_[coefficient::a] = a;
	this->v_[coefficient::b] = b;
	this->v_[coefficient::c] = c;
	this->v_[coefficient::d] = d;
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::scalar tnbLib::cubicEqn::a() const
{
	return this->v_[coefficient::a];
}


inline tnbLib::scalar tnbLib::cubicEqn::b() const
{
	return this->v_[coefficient::b];
}


inline tnbLib::scalar tnbLib::cubicEqn::c() const
{
	return this->v_[coefficient::c];
}


inline tnbLib::scalar tnbLib::cubicEqn::d() const
{
	return this->v_[coefficient::d];
}


inline tnbLib::scalar& tnbLib::cubicEqn::a()
{
	return this->v_[coefficient::a];
}


inline tnbLib::scalar& tnbLib::cubicEqn::b()
{
	return this->v_[coefficient::b];
}


inline tnbLib::scalar& tnbLib::cubicEqn::c()
{
	return this->v_[coefficient::c];
}


inline tnbLib::scalar& tnbLib::cubicEqn::d()
{
	return this->v_[coefficient::d];
}


inline tnbLib::scalar tnbLib::cubicEqn::value(const scalar x) const
{
	return x * (x*(x*a() + b()) + c()) + d();
}


inline tnbLib::scalar tnbLib::cubicEqn::derivative(const scalar x) const
{
	return x * (x * 3 * a() + 2 * b()) + c();
}


inline tnbLib::scalar tnbLib::cubicEqn::error(const scalar x) const
{
	return
		small * magSqr(x)*(mag(x*a()) + mag(b()))
		+ small * mag(x)*(mag(x*(x*a() + b())) + mag(c()))
		+ small * (mag(x*(x*(x*a() + b()) + c())) + mag(d()));
}


// ************************************************************************* //