#pragma once
#include <specie.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Thermo>
inline tnbLib::WLFTransport<Thermo>::WLFTransport
(
	const word& name,
	const WLFTransport& wlft
)
	:
	Thermo(name, wlft),
	mu0_(wlft.mu0_),
	Tr_(wlft.Tr_),
	C1_(wlft.C1_),
	C2_(wlft.C2_),
	rPr_(wlft.rPr_)
{}


template<class Thermo>
inline tnbLib::autoPtr<tnbLib::WLFTransport<Thermo>>
tnbLib::WLFTransport<Thermo>::clone() const
{
	return autoPtr<WLFTransport<Thermo>>
		(
			new WLFTransport<Thermo>(*this)
			);
}


template<class Thermo>
inline tnbLib::autoPtr<tnbLib::WLFTransport<Thermo>>
tnbLib::WLFTransport<Thermo>::New
(
	const dictionary& dict
)
{
	return autoPtr<WLFTransport<Thermo>>
		(
			new WLFTransport<Thermo>(dict)
			);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Thermo>
inline tnbLib::scalar tnbLib::WLFTransport<Thermo>::mu
(
	const scalar p,
	const scalar T
) const
{
	return mu0_ * exp(-C1_ * (T - Tr_) / (C2_ + T - Tr_));
}


template<class Thermo>
inline tnbLib::scalar tnbLib::WLFTransport<Thermo>::kappa
(
	const scalar p, const scalar T
) const
{
	return this->Cp(p, T)*mu(p, T)*rPr_;
}


template<class Thermo>
inline tnbLib::scalar tnbLib::WLFTransport<Thermo>::alphah
(
	const scalar p,
	const scalar T
) const
{

	return mu(p, T)*rPr_;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Thermo>
inline void tnbLib::WLFTransport<Thermo>::operator+=
(
	const WLFTransport<Thermo>& wlft
	)
{
	scalar Y1 = this->Y();

	Thermo::operator+=(wlft);

	if (mag(this->Y()) > small)
	{
		Y1 /= this->Y();
		scalar Y2 = wlft.Y() / this->Y();

		mu0_ = Y1 * mu0_ + Y2 * wlft.mu0_;
		Tr_ = Y1 * Tr_ + Y2 * wlft.Tr_;
		C1_ = Y1 * C1_ + Y2 * wlft.C1_;
		C2_ = Y1 * C2_ + Y2 * wlft.C2_;
		rPr_ = 1.0 / (Y1 / rPr_ + Y2 / wlft.rPr_);
	}
}


template<class Thermo>
inline void tnbLib::WLFTransport<Thermo>::operator*=
(
	const scalar s
	)
{
	Thermo::operator*=(s);
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

template<class Thermo>
inline tnbLib::WLFTransport<Thermo> tnbLib::operator+
(
	const WLFTransport<Thermo>& wlft1,
	const WLFTransport<Thermo>& wlft2
	)
{
	Thermo t
	(
		static_cast<const Thermo&>(wlft1) + static_cast<const Thermo&>(wlft2)
	);

	if (mag(t.Y()) < small)
	{
		return WLFTransport<Thermo>
			(
				t,
				0,
				wlft1.mu0_,
				wlft1.Tr_,
				wlft1.C1_,
				wlft1.C2_,
				wlft1.rPr_
				);
	}
	else
	{
		scalar Y1 = wlft1.Y() / t.Y();
		scalar Y2 = wlft2.Y() / t.Y();

		return WLFTransport<Thermo>
			(
				t,
				Y1*wlft1.mu0_ + Y2 * wlft2.mu0_,
				Y1*wlft1.Tr_ + Y2 * wlft2.Tr_,
				Y1*wlft1.C1_ + Y2 * wlft2.C1_,
				Y1*wlft1.C2_ + Y2 * wlft2.C2_,
				1.0 / (Y1 / wlft1.rPr_ + Y2 / wlft2.rPr_)
				);
	}
}


template<class Thermo>
inline tnbLib::WLFTransport<Thermo> tnbLib::operator*
(
	const scalar s,
	const WLFTransport<Thermo>& wlft
	)
{
	return WLFTransport<Thermo>
		(
			s*static_cast<const Thermo&>(wlft),
			wlft.mu0_,
			wlft.Tr_,
			wlft.C1_,
			wlft.C2_,
			1.0 / wlft.rPr_
			);
}


// ************************************************************************* //