#pragma once
#include <specie.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Thermo, int PolySize>
inline tnbLib::polynomialSolidTransport<Thermo, PolySize>::
polynomialSolidTransport
(
	const Thermo& t,
	const Polynomial<PolySize>& kappaCoeffs
)
	:
	Thermo(t),
	kappaCoeffs_(kappaCoeffs)
{}


template<class Thermo, int PolySize>
inline tnbLib::polynomialSolidTransport<Thermo, PolySize>::
polynomialSolidTransport
(
	const word& name,
	const polynomialSolidTransport& pt
)
	:
	Thermo(name, pt),
	kappaCoeffs_(pt.kappaCoeffs_)
{}


template<class Thermo, int PolySize>
inline tnbLib::autoPtr<tnbLib::polynomialSolidTransport<Thermo, PolySize>>
tnbLib::polynomialSolidTransport<Thermo, PolySize>::clone() const
{
	return autoPtr<polynomialSolidTransport<Thermo, PolySize>>
		(
			new polynomialSolidTransport<Thermo, PolySize>(*this)
			);
}


template<class Thermo, int PolySize>
inline tnbLib::autoPtr<tnbLib::polynomialSolidTransport<Thermo, PolySize>>
tnbLib::polynomialSolidTransport<Thermo, PolySize>::New(const dictionary& dict)
{
	return autoPtr<polynomialSolidTransport<Thermo, PolySize>>
		(
			new polynomialSolidTransport<Thermo, PolySize>(dict)
			);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Thermo, int PolySize>
inline tnbLib::scalar tnbLib::polynomialSolidTransport<Thermo, PolySize>::mu
(
	const scalar p,
	const scalar T
) const
{
	NotImplemented;
	return scalar(0);
}


template<class Thermo, int PolySize>
inline tnbLib::scalar tnbLib::polynomialSolidTransport<Thermo, PolySize>::kappa
(
	const scalar p,
	const scalar T
) const
{
	return kappaCoeffs_.value(T);
}


template<class Thermo, int PolySize>
inline tnbLib::vector tnbLib::polynomialSolidTransport<Thermo, PolySize>::Kappa
(
	const scalar p,
	const scalar T
) const
{
	const scalar kappa(kappaCoeffs_.value(T));
	return vector(kappa, kappa, kappa);
}


template<class Thermo, int PolySize>
inline tnbLib::scalar tnbLib::polynomialSolidTransport<Thermo, PolySize>::alphah
(
	const scalar p, const scalar T
) const
{
	return kappa(p, T) / this->Cp(p, T);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Thermo, int PolySize>
inline void tnbLib::polynomialSolidTransport<Thermo, PolySize>::operator+=
(
	const polynomialSolidTransport<Thermo, PolySize>& pt
	)
{
	scalar Y1 = this->Y();

	Thermo::operator+=(pt);

	Y1 /= this->Y();
	scalar Y2 = pt.Y() / this->Y();

	kappaCoeffs_ = Y1 * kappaCoeffs_ + Y2 * pt.kappaCoeffs_;
}


template<class Thermo, int PolySize>
inline void tnbLib::polynomialSolidTransport<Thermo, PolySize>::operator*=
(
	const scalar s
	)
{
	Thermo::operator*=(s);
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

template<class Thermo, int PolySize>
inline tnbLib::polynomialSolidTransport<Thermo, PolySize> tnbLib::operator+
(
	const polynomialSolidTransport<Thermo, PolySize>& pt1,
	const polynomialSolidTransport<Thermo, PolySize>& pt2
	)
{
	Thermo t
	(
		static_cast<const Thermo&>(pt1) + static_cast<const Thermo&>(pt2)
	);

	scalar Y1 = pt1.Y() / t.Y();
	scalar Y2 = pt2.Y() / t.Y();

	return polynomialSolidTransport<Thermo, PolySize>
		(
			t,
			Y1*pt1.kappaCoeffs_ + Y2 * pt2.kappaCoeffs_
			);
}


template<class Thermo, int PolySize>
inline tnbLib::polynomialSolidTransport<Thermo, PolySize> tnbLib::operator*
(
	const scalar s,
	const polynomialSolidTransport<Thermo, PolySize>& pt
	)
{
	return polynomialSolidTransport<Thermo, PolySize>
		(
			s*static_cast<const Thermo&>(pt),
			pt.kappaCoeffs_
			);
}


// ************************************************************************* //