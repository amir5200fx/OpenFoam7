#pragma once
#include <specie.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Thermo, int PolySize>
inline tnbLib::logPolynomialTransport<Thermo, PolySize>::logPolynomialTransport
(
	const Thermo& t,
	const Polynomial<PolySize>& muCoeffs,
	const Polynomial<PolySize>& kappaCoeffs
)
	:
	Thermo(t),
	muCoeffs_(muCoeffs),
	kappaCoeffs_(kappaCoeffs)
{}


template<class Thermo, int PolySize>
inline tnbLib::logPolynomialTransport<Thermo, PolySize>::logPolynomialTransport
(
	const word& name,
	const logPolynomialTransport& pt
)
	:
	Thermo(name, pt),
	muCoeffs_(pt.muCoeffs_),
	kappaCoeffs_(pt.kappaCoeffs_)
{}


template<class Thermo, int PolySize>
inline tnbLib::autoPtr<tnbLib::logPolynomialTransport<Thermo, PolySize>>
tnbLib::logPolynomialTransport<Thermo, PolySize>::clone() const
{
	return autoPtr<logPolynomialTransport<Thermo, PolySize>>
		(
			new logPolynomialTransport<Thermo, PolySize>(*this)
			);
}


template<class Thermo, int PolySize>
inline tnbLib::autoPtr<tnbLib::logPolynomialTransport<Thermo, PolySize>>
tnbLib::logPolynomialTransport<Thermo, PolySize>::New(const dictionary& dict)
{
	return autoPtr<logPolynomialTransport<Thermo, PolySize>>
		(
			new logPolynomialTransport<Thermo, PolySize>(dict)
			);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Thermo, int PolySize>
inline tnbLib::scalar tnbLib::logPolynomialTransport<Thermo, PolySize>::mu
(
	const scalar p,
	const scalar T
) const
{
	return exp(muCoeffs_.value(log(T)));
}


template<class Thermo, int PolySize>
inline tnbLib::scalar tnbLib::logPolynomialTransport<Thermo, PolySize>::kappa
(
	const scalar p,
	const scalar T
) const
{
	return exp(kappaCoeffs_.value(log(T)));
}


template<class Thermo, int PolySize>
inline tnbLib::scalar tnbLib::logPolynomialTransport<Thermo, PolySize>::alphah
(
	const scalar p, const scalar T
) const
{
	return kappa(p, T) / this->Cp(p, T);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Thermo, int PolySize>
inline void tnbLib::logPolynomialTransport<Thermo, PolySize>::operator+=
(
	const logPolynomialTransport<Thermo, PolySize>& pt
	)
{
	scalar Y1 = this->Y();

	Thermo::operator+=(pt);

	if (mag(this->Y()) > small)
	{
		Y1 /= this->Y();
		scalar Y2 = pt.Y() / this->Y();

		muCoeffs_ = Y1 * muCoeffs_ + Y2 * pt.muCoeffs_;
		kappaCoeffs_ = Y1 * kappaCoeffs_ + Y2 * pt.kappaCoeffs_;
	}
}


template<class Thermo, int PolySize>
inline void tnbLib::logPolynomialTransport<Thermo, PolySize>::operator*=
(
	const scalar s
	)
{
	Thermo::operator*=(s);
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

template<class Thermo, int PolySize>
inline tnbLib::logPolynomialTransport<Thermo, PolySize> tnbLib::operator+
(
	const logPolynomialTransport<Thermo, PolySize>& pt1,
	const logPolynomialTransport<Thermo, PolySize>& pt2
	)
{
	Thermo t
	(
		static_cast<const Thermo&>(pt1) + static_cast<const Thermo&>(pt2)
	);

	if (mag(t.Y()) < small)
	{
		return logPolynomialTransport<Thermo>
			(
				t,
				0,
				pt1.muCoeffs_,
				pt1.kappaCoeffs_
				);
	}
	else
	{
		scalar Y1 = pt1.Y() / t.Y();
		scalar Y2 = pt2.Y() / t.Y();

		return logPolynomialTransport<Thermo, PolySize>
			(
				t,
				Y1*pt1.muCoeffs_ + Y2 * pt2.muCoeffs_,
				Y1*pt1.kappaCoeffs_ + Y2 * pt2.kappaCoeffs_
				);
	}
}


template<class Thermo, int PolySize>
inline tnbLib::logPolynomialTransport<Thermo, PolySize> tnbLib::operator*
(
	const scalar s,
	const logPolynomialTransport<Thermo, PolySize>& pt
	)
{
	return logPolynomialTransport<Thermo, PolySize>
		(
			s*static_cast<const Thermo&>(pt),
			pt.muCoeffs_,
			pt.kappaCoeffs_
			);
}


// ************************************************************************* //