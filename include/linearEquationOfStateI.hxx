#pragma once
#include <thermodynamicConstants.hxx>
// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Specie>
inline tnbLib::linear<Specie>::linear
(
	const Specie& sp,
	const scalar psi,
	const scalar rho0
)
	:
	Specie(sp),
	psi_(psi),
	rho0_(rho0)
{}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Specie>
inline tnbLib::linear<Specie>::linear
(
	const word& name,
	const linear<Specie>& pf
)
	:
	Specie(name, pf),
	psi_(pf.psi_),
	rho0_(pf.rho0_)
{}


template<class Specie>
inline tnbLib::autoPtr<tnbLib::linear<Specie>>
tnbLib::linear<Specie>::clone() const
{
	return autoPtr<linear<Specie>>(new linear<Specie>(*this));
}


template<class Specie>
inline tnbLib::autoPtr<tnbLib::linear<Specie>>
tnbLib::linear<Specie>::New
(
	const dictionary& dict
)
{
	return autoPtr<linear<Specie>>(new linear<Specie>(dict));
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Specie>
inline tnbLib::scalar tnbLib::linear<Specie>::rho(scalar p, scalar T) const
{
	return rho0_ + psi_ * p;
}


template<class Specie>
inline tnbLib::scalar tnbLib::linear<Specie>::H(scalar p, scalar T) const
{
	return log(rho(p, T)) / psi_;
}


template<class Specie>
inline tnbLib::scalar tnbLib::linear<Specie>::Cp(scalar p, scalar T) const
{
	return 0;
}


template<class Specie>
inline tnbLib::scalar tnbLib::linear<Specie>::E(scalar p, scalar T) const
{
	const scalar rho = this->rho(p, T);

	return log(rho) / psi_ - p / rho;
}


template<class Specie>
inline tnbLib::scalar tnbLib::linear<Specie>::Cv(scalar p, scalar T) const
{
	return 0;
}


template<class Specie>
inline tnbLib::scalar tnbLib::linear<Specie>::S(scalar p, scalar T) const
{
	return -log((rho0_ + psi_ * p) / (rho0_ + psi_ * constant::thermodynamic::Pstd)) / (T*psi_);
}


template<class Specie>
inline tnbLib::scalar tnbLib::linear<Specie>::psi(scalar p, scalar T) const
{
	return psi_;
}


template<class Specie>
inline tnbLib::scalar tnbLib::linear<Specie>::Z(scalar p, scalar T) const
{
	return 1;
}


template<class Specie>
inline tnbLib::scalar tnbLib::linear<Specie>::CpMCv(scalar p, scalar T) const
{
	return 0;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Specie>
inline void tnbLib::linear<Specie>::operator+=
(
	const linear<Specie>& pf
	)
{
	scalar Y1 = this->Y();
	Specie::operator+=(pf);

	if (mag(this->Y()) > small)
	{
		Y1 /= this->Y();
		const scalar Y2 = pf.Y() / this->Y();

		psi_ = Y1 * psi_ + Y2 * pf.psi_;
		rho0_ = Y1 * rho0_ + Y2 * pf.rho0_;
	}
}


template<class Specie>
inline void tnbLib::linear<Specie>::operator*=(const scalar s)
{
	Specie::operator*=(s);
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

template<class Specie>
inline tnbLib::linear<Specie> tnbLib::operator+
(
	const linear<Specie>& pf1,
	const linear<Specie>& pf2
	)
{
	Specie sp
	(
		static_cast<const Specie&>(pf1)
		+ static_cast<const Specie&>(pf2)
	);

	if (mag(sp.Y()) < small)
	{
		return linear<Specie>
			(
				sp,
				pf1.psi_,
				pf1.rho0_
				);
	}
	else
	{
		const scalar Y1 = pf1.Y() / sp.Y();
		const scalar Y2 = pf2.Y() / sp.Y();

		return linear<Specie>
			(
				sp,
				Y1*pf1.psi_ + Y2 * pf2.psi_,
				Y1*pf1.rho0_ + Y2 * pf2.rho0_
				);
	}
}


template<class Specie>
inline tnbLib::linear<Specie> tnbLib::operator*
(
	const scalar s,
	const linear<Specie>& pf
	)
{
	return linear<Specie>
		(
			s*static_cast<const Specie&>(pf),
			pf.psi_,
			pf.rho0_
			);
}


template<class Specie>
inline tnbLib::linear<Specie> tnbLib::operator==
(
	const linear<Specie>& pf1,
	const linear<Specie>& pf2
	)
{
	Specie sp
	(
		static_cast<const Specie&>(pf1)
		== static_cast<const Specie&>(pf2)
	);

	const scalar Y1 = pf1.Y() / sp.Y();
	const scalar Y2 = pf2.Y() / sp.Y();

	return linear<Specie>
		(
			sp,
			Y2*pf2.psi_ - Y1 * pf1.psi_,
			Y2*pf2.rho0_ - Y1 * pf1.rho0_
			);
}


// ************************************************************************* //