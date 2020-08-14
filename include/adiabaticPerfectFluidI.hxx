#pragma once
#include <thermodynamicConstants.hxx>  // added by amir
// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Specie>
inline tnbLib::adiabaticPerfectFluid<Specie>::adiabaticPerfectFluid
(
	const Specie& sp,
	const scalar p0,
	const scalar rho0,
	const scalar gamma,
	const scalar B
)
	:
	Specie(sp),
	p0_(p0),
	rho0_(rho0),
	gamma_(gamma),
	B_(B)
{}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Specie>
inline tnbLib::adiabaticPerfectFluid<Specie>::adiabaticPerfectFluid
(
	const word& name,
	const adiabaticPerfectFluid<Specie>& pf
)
	:
	Specie(name, pf),
	p0_(pf.p0_),
	rho0_(pf.rho0_),
	gamma_(pf.gamma_),
	B_(pf.B_)
{}


template<class Specie>
inline tnbLib::autoPtr<tnbLib::adiabaticPerfectFluid<Specie>>
tnbLib::adiabaticPerfectFluid<Specie>::clone() const
{
	return autoPtr<adiabaticPerfectFluid<Specie>>
		(
			new adiabaticPerfectFluid<Specie>(*this)
			);
}


template<class Specie>
inline tnbLib::autoPtr<tnbLib::adiabaticPerfectFluid<Specie>>
tnbLib::adiabaticPerfectFluid<Specie>::New
(
	const dictionary& dict
)
{
	return autoPtr<adiabaticPerfectFluid<Specie>>
		(
			new adiabaticPerfectFluid<Specie>(dict)
			);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Specie>
inline tnbLib::scalar tnbLib::adiabaticPerfectFluid<Specie>::rho
(
	scalar p,
	scalar T
) const
{
	return rho0_ * pow((p + B_) / (p0_ + B_), 1.0 / gamma_);
}


template<class Specie>
inline tnbLib::scalar tnbLib::adiabaticPerfectFluid<Specie>::H
(
	scalar p,
	scalar T
) const
{
	// ***HGW This needs to be added, it is not 0
	return 0;
}


template<class Specie>
inline tnbLib::scalar tnbLib::adiabaticPerfectFluid<Specie>::Cp
(
	scalar p,
	scalar T
) const
{
	return 0;
}


template<class Specie>
inline tnbLib::scalar tnbLib::adiabaticPerfectFluid<Specie>::E
(
	scalar p,
	scalar T
) const
{
	// ***HGW This needs to be added, it is H - p/rho
	return 0;
}


template<class Specie>
inline tnbLib::scalar tnbLib::adiabaticPerfectFluid<Specie>::Cv
(
	scalar p,
	scalar T
) const
{
	return 0;
}


template<class Specie>
inline tnbLib::scalar tnbLib::adiabaticPerfectFluid<Specie>::S
(
	scalar p,
	scalar T
) const
{
	scalar n = 1 - 1.0 / gamma_;
	return
		-pow(p0_ + B_, 1.0 / gamma_)*(pow((p + B_), n) - pow((constant::thermodynamic::Pstd + B_), n))
		/ (rho0_*T*n);
}


template<class Specie>
inline tnbLib::scalar tnbLib::adiabaticPerfectFluid<Specie>::psi
(
	scalar p,
	scalar T
) const
{
	return
		(rho0_ / (gamma_*(p0_ + B_)))
		*pow((p + B_) / (p0_ + B_), 1.0 / gamma_ - 1.0);
}


template<class Specie>
inline tnbLib::scalar tnbLib::adiabaticPerfectFluid<Specie>::Z(scalar, scalar) const
{
	return 1;
}


template<class Specie>
inline tnbLib::scalar tnbLib::adiabaticPerfectFluid<Specie>::CpMCv
(
	scalar p,
	scalar T
) const
{
	return 0;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Specie>
inline void tnbLib::adiabaticPerfectFluid<Specie>::operator+=
(
	const adiabaticPerfectFluid<Specie>& pf
	)
{
	scalar Y1 = this->Y();
	Specie::operator+=(pf);

	if (mag(this->Y()) > small)
	{
		Y1 /= this->Y();
		const scalar Y2 = pf.Y() / this->Y();

		p0_ = Y1 * p0_ + Y2 * pf.p0_;
		rho0_ = Y1 * rho0_ + Y2 * pf.rho0_;
		gamma_ = Y1 * gamma_ + Y2 * pf.gamma_;
		B_ = Y1 * B_ + Y2 * pf.B_;
	}
}


template<class Specie>
inline void tnbLib::adiabaticPerfectFluid<Specie>::operator*=(const scalar s)
{
	Specie::operator*=(s);
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

template<class Specie>
inline tnbLib::adiabaticPerfectFluid<Specie> tnbLib::operator+
(
	const adiabaticPerfectFluid<Specie>& pf1,
	const adiabaticPerfectFluid<Specie>& pf2
	)
{
	Specie sp
	(
		static_cast<const Specie&>(pf1)
		+ static_cast<const Specie&>(pf2)
	);

	if (mag(sp.Y()) < small)
	{
		return adiabaticPerfectFluid<Specie>
			(
				sp,
				pf1.p0_,
				pf1.rho0_,
				pf1.gamma_,
				pf1.B_
				);
	}
	else
	{
		const scalar Y1 = pf1.Y() / sp.Y();
		const scalar Y2 = pf2.Y() / sp.Y();

		return adiabaticPerfectFluid<Specie>
			(
				sp,
				Y1*pf1.p0_ + Y2 * pf2.p0_,
				Y1*pf1.rho0_ + Y2 * pf2.rho0_,
				Y1*pf1.gamma_ + Y2 * pf2.gamma_,
				Y1*pf1.B_ + Y2 * pf2.B_
				);
	}
}


template<class Specie>
inline tnbLib::adiabaticPerfectFluid<Specie> tnbLib::operator*
(
	const scalar s,
	const adiabaticPerfectFluid<Specie>& pf
	)
{
	return adiabaticPerfectFluid<Specie>
		(
			s*static_cast<const Specie&>(pf),
			pf.p0_,
			pf.rho0_,
			pf.gamma_,
			pf.B_
			);
}


template<class Specie>
inline tnbLib::adiabaticPerfectFluid<Specie> tnbLib::operator==
(
	const adiabaticPerfectFluid<Specie>& pf1,
	const adiabaticPerfectFluid<Specie>& pf2
	)
{
	Specie sp
	(
		static_cast<const Specie&>(pf1)
		== static_cast<const Specie&>(pf2)
	);

	const scalar Y1 = pf1.Y() / sp.Y();
	const scalar Y2 = pf2.Y() / sp.Y();

	return adiabaticPerfectFluid<Specie>
		(
			sp,
			Y2*pf2.p0_ - Y1 * pf1.p0_,
			Y2*pf2.rho0_ - Y1 * pf1.rho0_,
			Y2*pf2.gamma_ - Y1 * pf1.gamma_,
			Y2*pf2.B_ - Y1 * pf1.B_
			);
}


// ************************************************************************* //