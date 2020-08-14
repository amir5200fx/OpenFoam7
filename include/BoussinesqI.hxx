#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Specie>
inline tnbLib::Boussinesq<Specie>::Boussinesq
(
	const Specie& sp, const scalar rho0, const scalar T0, const scalar beta
)
	:
	Specie(sp),
	rho0_(rho0),
	T0_(T0),
	beta_(beta)
{}


template<class Specie>
inline tnbLib::Boussinesq<Specie>::Boussinesq
(
	const word& name,
	const Boussinesq<Specie>& b
)
	:
	Specie(name, b),
	rho0_(b.rho0_),
	T0_(b.T0_),
	beta_(b.beta_)
{}


template<class Specie>
inline tnbLib::autoPtr<tnbLib::Boussinesq<Specie>>
tnbLib::Boussinesq<Specie>::clone() const
{
	return autoPtr<Boussinesq<Specie>>
		(
			new Boussinesq<Specie>(*this)
			);
}


template<class Specie>
inline tnbLib::autoPtr<tnbLib::Boussinesq<Specie>>
tnbLib::Boussinesq<Specie>::New
(
	const dictionary& dict
)
{
	return autoPtr<Boussinesq<Specie>>
		(
			new Boussinesq<Specie>(dict)
			);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Specie>
inline tnbLib::scalar tnbLib::Boussinesq<Specie>::rho
(
	scalar p,
	scalar T
) const
{
	return rho0_ * (1.0 - beta_ * (T - T0_));
}


template<class Specie>
inline tnbLib::scalar tnbLib::Boussinesq<Specie>::H(scalar p, scalar T) const
{
	return p / this->rho(p, T);
}


template<class Specie>
inline tnbLib::scalar tnbLib::Boussinesq<Specie>::Cp(scalar p, scalar T) const
{
	return 0;
}


template<class Specie>
inline tnbLib::scalar tnbLib::Boussinesq<Specie>::E(scalar p, scalar T) const
{
	return 0;
}


template<class Specie>
inline tnbLib::scalar tnbLib::Boussinesq<Specie>::Cv(scalar p, scalar T) const
{
	return 0;
}


template<class Specie>
inline tnbLib::scalar tnbLib::Boussinesq<Specie>::S
(
	scalar p,
	scalar T
) const
{
	return 0;
}


template<class Specie>
inline tnbLib::scalar tnbLib::Boussinesq<Specie>::psi
(
	scalar p,
	scalar T
) const
{
	return 0;
}


template<class Specie>
inline tnbLib::scalar tnbLib::Boussinesq<Specie>::Z
(
	scalar p,
	scalar T
) const
{
	return 0;
}


template<class Specie>
inline tnbLib::scalar tnbLib::Boussinesq<Specie>::CpMCv
(
	scalar p,
	scalar T
) const
{
	return 0;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Specie>
inline void tnbLib::Boussinesq<Specie>::operator=
(
	const Boussinesq<Specie>& b
	)
{
	Specie::operator=(b);

	rho0_ = b.rho0_;
	T0_ = b.T0_;
	beta_ = b.beta_;
}


template<class Specie>
inline void tnbLib::Boussinesq<Specie>::operator+=
(
	const Boussinesq<Specie>& b
	)
{
	scalar Y1 = this->Y();
	Specie::operator+=(b);

	if (mag(this->Y()) > small)
	{
		Y1 /= this->Y();
		const scalar Y2 = b.Y() / this->Y();

		rho0_ = Y1 * rho0_ + Y2 * b.rho0_;
		T0_ = Y1 * T0_ + Y2 * b.T0_;
		beta_ = Y1 * beta_ + Y2 * b.beta_;
	}
}


template<class Specie>
inline void tnbLib::Boussinesq<Specie>::operator*=(const scalar s)
{
	Specie::operator*=(s);
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

template<class Specie>
inline tnbLib::Boussinesq<Specie> tnbLib::operator+
(
	const Boussinesq<Specie>& b1,
	const Boussinesq<Specie>& b2
	)
{
	Specie sp(static_cast<const Specie&>(b1) + static_cast<const Specie&>(b2));

	if (mag(sp.Y()) < small)
	{
		return Boussinesq<Specie>
			(
				sp,
				b1.rho0_,
				b1.T0_,
				b1.beta_
				);
	}
	else
	{
		const scalar Y1 = b1.Y() / sp.Y();
		const scalar Y2 = b2.Y() / sp.Y();

		return Boussinesq<Specie>
			(
				sp,
				Y1*b1.rho0_ + Y2 * b2.rho0_,
				Y1*b1.T0_ + Y2 * b2.T0_,
				Y1*b1.beta_ + Y2 * b2.beta_
				);
	}
}


template<class Specie>
inline tnbLib::Boussinesq<Specie> tnbLib::operator*
(
	const scalar s,
	const Boussinesq<Specie>& b
	)
{
	return Boussinesq<Specie>
		(
			s*static_cast<const Specie&>(b),
			b.rho0_,
			b.T0_,
			b.beta_
			);
}


template<class Specie>
inline tnbLib::Boussinesq<Specie> tnbLib::operator==
(
	const Boussinesq<Specie>& b1,
	const Boussinesq<Specie>& b2
	)
{
	Specie sp(static_cast<const Specie&>(b1) == static_cast<const Specie&>(b2));

	const scalar Y1 = b1.Y() / sp.Y();
	const scalar Y2 = b2.Y() / sp.Y();

	return Boussinesq<Specie>
		(
			sp,
			Y2*b2.rho0_ - Y1 * b1.rho0_,
			Y2*b2.T0_ - Y1 * b1.T0_,
			Y2*b2.beta_ - Y1 * b1.beta_
			);
}


// ************************************************************************* //