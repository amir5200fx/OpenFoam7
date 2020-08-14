#pragma once
// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Specie>
inline tnbLib::rhoConst<Specie>::rhoConst
(
	const Specie& sp,
	const scalar rho
)
	:
	Specie(sp),
	rho_(rho)
{}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Specie>
inline tnbLib::rhoConst<Specie>::rhoConst
(
	const word& name,
	const rhoConst<Specie>& ico
)
	:
	Specie(name, ico),
	rho_(ico.rho_)
{}


template<class Specie>
inline tnbLib::autoPtr<tnbLib::rhoConst<Specie>>
tnbLib::rhoConst<Specie>::clone() const
{
	return autoPtr<rhoConst<Specie>>(new rhoConst<Specie>(*this));
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Specie>
inline tnbLib::scalar tnbLib::rhoConst<Specie>::rho(scalar p, scalar T) const
{
	return rho_;
}


template<class Specie>
inline tnbLib::scalar tnbLib::rhoConst<Specie>::H(scalar p, scalar T) const
{
	return p / rho_;
}


template<class Specie>
inline tnbLib::scalar tnbLib::rhoConst<Specie>::Cp(scalar p, scalar T) const
{
	return 0;
}


template<class Specie>
inline tnbLib::scalar tnbLib::rhoConst<Specie>::E(scalar p, scalar T) const
{
	return 0;
}


template<class Specie>
inline tnbLib::scalar tnbLib::rhoConst<Specie>::Cv(scalar p, scalar T) const
{
	return 0;
}


template<class Specie>
inline tnbLib::scalar tnbLib::rhoConst<Specie>::S(scalar p, scalar T) const
{
	return 0;
}


template<class Specie>
inline tnbLib::scalar tnbLib::rhoConst<Specie>::psi(scalar p, scalar T) const
{
	return 0;
}


template<class Specie>
inline tnbLib::scalar tnbLib::rhoConst<Specie>::Z(scalar p, scalar T) const
{
	return 0;
}


template<class Specie>
inline tnbLib::scalar tnbLib::rhoConst<Specie>::CpMCv(scalar p, scalar T) const
{
	return 0;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Specie>
inline void tnbLib::rhoConst<Specie>::operator+=(const rhoConst<Specie>& ico)
{
	scalar Y1 = this->Y();
	Specie::operator+=(ico);

	if (mag(this->Y()) > small)
	{
		Y1 /= this->Y();
		const scalar Y2 = ico.Y() / this->Y();

		rho_ = Y1 * rho_ + Y2 * ico.rho_;
	}
}


template<class Specie>
inline void tnbLib::rhoConst<Specie>::operator*=(const scalar s)
{
	Specie::operator*=(s);
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

template<class Specie>
inline tnbLib::rhoConst<Specie> tnbLib::operator+
(
	const rhoConst<Specie>& ico1,
	const rhoConst<Specie>& ico2
	)
{
	Specie sp
	(
		static_cast<const Specie&>(ico1)
		+ static_cast<const Specie&>(ico2)
	);

	if (mag(sp.Y()) < small)
	{
		return rhoConst<Specie>
			(
				sp,
				ico1.rho_
				);
	}
	else
	{
		const scalar Y1 = ico1.Y() / sp.Y();
		const scalar Y2 = ico2.Y() / sp.Y();

		return rhoConst<Specie>
			(
				sp,
				Y1*ico1.rho_ + Y2 * ico2.rho_
				);
	}
}


template<class Specie>
inline tnbLib::rhoConst<Specie> tnbLib::operator*
(
	const scalar s,
	const rhoConst<Specie>& ico
	)
{
	return rhoConst<Specie>(s*static_cast<const Specie&>(ico), ico.rho_);
}


template<class Specie>
inline tnbLib::rhoConst<Specie> tnbLib::operator==
(
	const rhoConst<Specie>& ico1,
	const rhoConst<Specie>& ico2
	)
{
	Specie sp
	(
		static_cast<const Specie&>(ico1)
		== static_cast<const Specie&>(ico2)
	);

	const scalar Y1 = ico1.Y() / sp.Y();
	const scalar Y2 = ico2.Y() / sp.Y();

	return rhoConst<Specie>
		(
			sp,
			Y2*ico2.rho_ - Y1 * ico1.rho_
			);
}


// ************************************************************************* //