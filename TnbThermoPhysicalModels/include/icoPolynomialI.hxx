#pragma once
// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Specie, int PolySize>
inline tnbLib::icoPolynomial<Specie, PolySize>::icoPolynomial
(
	const Specie& sp,
	const Polynomial<PolySize>& rhoCoeffs
)
	:
	Specie(sp),
	rhoCoeffs_(rhoCoeffs)
{}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Specie, int PolySize>
inline tnbLib::icoPolynomial<Specie, PolySize>::icoPolynomial
(
	const word& name,
	const icoPolynomial<Specie, PolySize>& ip
)
	:
	Specie(name, ip),
	rhoCoeffs_(ip.rhoCoeffs_)
{}


template<class Specie, int PolySize>
inline tnbLib::autoPtr<tnbLib::icoPolynomial<Specie, PolySize>>
tnbLib::icoPolynomial<Specie, PolySize>::clone() const
{
	return autoPtr<icoPolynomial<Specie, PolySize>>
		(
			new icoPolynomial<Specie, PolySize>(*this)
			);
}


template<class Specie, int PolySize>
inline tnbLib::autoPtr<tnbLib::icoPolynomial<Specie, PolySize>>
tnbLib::icoPolynomial<Specie, PolySize>::New(const dictionary& dict)
{
	return autoPtr<icoPolynomial<Specie, PolySize>>
		(
			new icoPolynomial<Specie, PolySize>(dict)
			);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Specie, int PolySize>
inline tnbLib::scalar tnbLib::icoPolynomial<Specie, PolySize>::rho
(
	scalar p,
	scalar T
) const
{
	return rhoCoeffs_.value(T);
}


template<class Specie, int PolySize>
inline tnbLib::scalar tnbLib::icoPolynomial<Specie, PolySize>::H
(
	scalar p,
	scalar T
) const
{
	return p / this->rho(p, T);
}


template<class Specie, int PolySize>
inline tnbLib::scalar tnbLib::icoPolynomial<Specie, PolySize>::Cp
(
	scalar p,
	scalar T
) const
{
	return 0;
}


template<class Specie, int PolySize>
inline tnbLib::scalar tnbLib::icoPolynomial<Specie, PolySize>::E
(
	scalar p,
	scalar T
) const
{
	return 0;
}


template<class Specie, int PolySize>
inline tnbLib::scalar tnbLib::icoPolynomial<Specie, PolySize>::Cv
(
	scalar p,
	scalar T
) const
{
	return 0;
}


template<class Specie, int PolySize>
inline tnbLib::scalar tnbLib::icoPolynomial<Specie, PolySize>::S
(
	scalar p,
	scalar T
) const
{
	return 0;
}


template<class Specie, int PolySize>
inline tnbLib::scalar tnbLib::icoPolynomial<Specie, PolySize>::psi
(
	scalar p,
	scalar T
) const
{
	return 0;
}


template<class Specie, int PolySize>
inline tnbLib::scalar tnbLib::icoPolynomial<Specie, PolySize>::Z
(
	scalar p,
	scalar T
) const
{
	return 0;
}


template<class Specie, int PolySize>
inline tnbLib::scalar tnbLib::icoPolynomial<Specie, PolySize>::CpMCv
(
	scalar p,
	scalar T
) const
{
	return 0;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Specie, int PolySize>
inline void tnbLib::icoPolynomial<Specie, PolySize>::operator+=
(
	const icoPolynomial<Specie, PolySize>& ip
	)
{
	scalar Y1 = this->Y();
	Specie::operator+=(ip);

	if (mag(this->Y()) > small)
	{
		Y1 /= this->Y();
		const scalar Y2 = ip.Y() / this->Y();

		rhoCoeffs_ = Y1 * rhoCoeffs_ + Y2 * ip.rhoCoeffs_;
	}
}


template<class Specie, int PolySize>
inline void tnbLib::icoPolynomial<Specie, PolySize>::operator*=(const scalar s)
{
	Specie::operator*=(s);
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

template<class Specie, int PolySize>
tnbLib::icoPolynomial<Specie, PolySize> tnbLib::operator+
(
	const icoPolynomial<Specie, PolySize>& ip1,
	const icoPolynomial<Specie, PolySize>& ip2
	)
{
	Specie sp
	(
		static_cast<const Specie&>(ip1)
		+ static_cast<const Specie&>(ip2)
	);

	if (mag(sp.Y()) < small)
	{
		return icoPolynomial<Specie, PolySize>
			(
				sp,
				ip1.rhoCoeffs_
				);
	}
	else
	{
		const scalar Y1 = ip1.Y() / sp.Y();
		const scalar Y2 = ip2.Y() / sp.Y();

		return icoPolynomial<Specie, PolySize>
			(
				sp,
				Y1*ip1.rhoCoeffs_ + Y2 * ip2.rhoCoeffs_
				);
	}
}


template<class Specie, int PolySize>
tnbLib::icoPolynomial<Specie, PolySize> tnbLib::operator*
(
	const scalar s,
	const icoPolynomial<Specie, PolySize>& ip
	)
{
	return icoPolynomial<Specie, PolySize>
		(
			s*static_cast<const Specie&>(ip),
			ip.rhoCoeffs_
			);
}


template<class Specie, int PolySize>
tnbLib::icoPolynomial<Specie, PolySize> tnbLib::operator==
(
	const icoPolynomial<Specie, PolySize>& ip1,
	const icoPolynomial<Specie, PolySize>& ip2
	)
{
	Specie sp
	(
		static_cast<const Specie&>(ip1)
		== static_cast<const Specie&>(ip2)
	);

	const scalar Y1 = ip1.Y() / sp.Y();
	const scalar Y2 = ip2.Y() / sp.Y();

	return icoPolynomial<Specie, PolySize>
		(
			sp,
			Y2*ip2.rhoCoeffs_ - Y1 * ip1.rhoCoeffs_
			);
}


// ************************************************************************* //