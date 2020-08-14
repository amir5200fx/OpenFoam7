#pragma once
#include <thermodynamicConstants.hxx>  // added by amir
// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Specie>
inline tnbLib::perfectFluid<Specie>::perfectFluid
(
	const Specie& sp,
	const scalar R,
	const scalar rho0
)
	:
	Specie(sp),
	R_(R),
	rho0_(rho0)
{}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Specie>
inline tnbLib::perfectFluid<Specie>::perfectFluid
(
	const word& name,
	const perfectFluid<Specie>& pf
)
	:
	Specie(name, pf),
	R_(pf.R_),
	rho0_(pf.rho0_)
{}


template<class Specie>
inline tnbLib::autoPtr<tnbLib::perfectFluid<Specie>>
tnbLib::perfectFluid<Specie>::clone() const
{
	return autoPtr<perfectFluid<Specie>>(new perfectFluid<Specie>(*this));
}


template<class Specie>
inline tnbLib::autoPtr<tnbLib::perfectFluid<Specie>>
tnbLib::perfectFluid<Specie>::New
(
	const dictionary& dict
)
{
	return autoPtr<perfectFluid<Specie>>(new perfectFluid<Specie>(dict));
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Specie>
inline tnbLib::scalar tnbLib::perfectFluid<Specie>::R() const
{
	return R_;
}


template<class Specie>
inline tnbLib::scalar tnbLib::perfectFluid<Specie>::rho(scalar p, scalar T) const
{
	return rho0_ + p / (this->R()*T);
}


template<class Specie>
inline tnbLib::scalar tnbLib::perfectFluid<Specie>::H(scalar p, scalar T) const
{
	return p / rho(p, T) - constant::thermodynamic::Pstd / rho(constant::thermodynamic::Pstd, T);
}


template<class Specie>
inline tnbLib::scalar tnbLib::perfectFluid<Specie>::Cp(scalar p, scalar T) const
{
	return
		sqr(p / (rho(p, T)*T)) / this->R()
		- sqr(constant::thermodynamic::Pstd / (rho(constant::thermodynamic::Pstd, T)*T)) / this->R();
}


template<class Specie>
inline tnbLib::scalar tnbLib::perfectFluid<Specie>::E(scalar p, scalar T) const
{
	return 0;
}


template<class Specie>
inline tnbLib::scalar tnbLib::perfectFluid<Specie>::Cv(scalar p, scalar T) const
{
	return 0;
}


template<class Specie>
inline tnbLib::scalar tnbLib::perfectFluid<Specie>::S(scalar p, scalar T) const
{
	return -this->R()*log(p / constant::thermodynamic::Pstd);
}


template<class Specie>
inline tnbLib::scalar tnbLib::perfectFluid<Specie>::psi(scalar p, scalar T) const
{
	return 1.0 / (this->R()*T);
}


template<class Specie>
inline tnbLib::scalar tnbLib::perfectFluid<Specie>::Z(scalar p, scalar T) const
{
	return 1;
}


template<class Specie>
inline tnbLib::scalar tnbLib::perfectFluid<Specie>::CpMCv(scalar p, scalar T) const
{
	const scalar R = this->R();
	const scalar rho = this->rho(p, T);

	return R * sqr(p / (rho*R*T));
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Specie>
inline void tnbLib::perfectFluid<Specie>::operator+=
(
	const perfectFluid<Specie>& pf
	)
{
	scalar Y1 = this->Y();
	Specie::operator+=(pf);

	if (mag(this->Y()) > small)
	{
		Y1 /= this->Y();
		const scalar Y2 = pf.Y() / this->Y();

		R_ = 1.0 / (Y1 / R_ + Y2 / pf.R_);
		rho0_ = Y1 * rho0_ + Y2 * pf.rho0_;
	}
}


template<class Specie>
inline void tnbLib::perfectFluid<Specie>::operator*=(const scalar s)
{
	Specie::operator*=(s);
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

template<class Specie>
inline tnbLib::perfectFluid<Specie> tnbLib::operator+
(
	const perfectFluid<Specie>& pf1,
	const perfectFluid<Specie>& pf2
	)
{
	Specie sp
	(
		static_cast<const Specie&>(pf1)
		+ static_cast<const Specie&>(pf2)
	);

	if (mag(sp.Y()) < small)
	{
		return perfectFluid<Specie>
			(
				sp,
				pf1.R_,
				pf1.rho0_
				);
	}
	else
	{
		const scalar Y1 = pf1.Y() / sp.Y();
		const scalar Y2 = pf2.Y() / sp.Y();

		return perfectFluid<Specie>
			(
				sp,
				1.0 / (Y1 / pf1.R_ + Y2 / pf2.R_),
				Y1*pf1.rho0_ + Y2 * pf2.rho0_
				);
	}
}


template<class Specie>
inline tnbLib::perfectFluid<Specie> tnbLib::operator*
(
	const scalar s,
	const perfectFluid<Specie>& pf
	)
{
	return perfectFluid<Specie>
		(
			s*static_cast<const Specie&>(pf),
			pf.R_,
			pf.rho0_
			);
}


template<class Specie>
inline tnbLib::perfectFluid<Specie> tnbLib::operator==
(
	const perfectFluid<Specie>& pf1,
	const perfectFluid<Specie>& pf2
	)
{
	Specie sp
	(
		static_cast<const Specie&>(pf1)
		== static_cast<const Specie&>(pf2)
	);

	if (mag(sp.Y()) < small)
	{
		return perfectFluid<Specie>
			(
				sp,
				pf1.R_,
				pf1.rho0_
				);
	}
	else
	{
		const scalar Y1 = pf1.Y() / sp.Y();
		const scalar Y2 = pf2.Y() / sp.Y();
		const scalar oneByR = Y2 / pf2.R_ - Y1 / pf1.R_;

		return perfectFluid<Specie>
			(
				sp,
				mag(oneByR) < small ? great : 1 / oneByR,
				Y2*pf2.rho0_ - Y1 * pf1.rho0_
				);
	}
}


// ************************************************************************* //