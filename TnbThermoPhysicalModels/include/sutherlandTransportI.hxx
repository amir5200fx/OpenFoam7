#pragma once
#include <specie.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Thermo>
inline void tnbLib::sutherlandTransport<Thermo>::calcCoeffs
(
	const scalar mu1, const scalar T1,
	const scalar mu2, const scalar T2
)
{
	scalar rootT1 = sqrt(T1);
	scalar mu1rootT2 = mu1 * sqrt(T2);
	scalar mu2rootT1 = mu2 * rootT1;

	Ts_ = (mu2rootT1 - mu1rootT2) / (mu1rootT2 / T1 - mu2rootT1 / T2);

	As_ = mu1 * (1.0 + Ts_ / T1) / rootT1;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Thermo>
inline tnbLib::sutherlandTransport<Thermo>::sutherlandTransport
(
	const Thermo& t,
	const scalar As,
	const scalar Ts
)
	:
	Thermo(t),
	As_(As),
	Ts_(Ts)
{}


template<class Thermo>
inline tnbLib::sutherlandTransport<Thermo>::sutherlandTransport
(
	const Thermo& t,
	const scalar mu1, const scalar T1,
	const scalar mu2, const scalar T2
)
	:
	Thermo(t)
{
	calcCoeffs(mu1, T1, mu2, T2);
}


template<class Thermo>
inline tnbLib::sutherlandTransport<Thermo>::sutherlandTransport
(
	const word& name,
	const sutherlandTransport& st
)
	:
	Thermo(name, st),
	As_(st.As_),
	Ts_(st.Ts_)
{}


template<class Thermo>
inline tnbLib::autoPtr<tnbLib::sutherlandTransport<Thermo>>
tnbLib::sutherlandTransport<Thermo>::clone() const
{
	return autoPtr<sutherlandTransport<Thermo>>
		(
			new sutherlandTransport<Thermo>(*this)
			);
}


template<class Thermo>
inline tnbLib::autoPtr<tnbLib::sutherlandTransport<Thermo>>
tnbLib::sutherlandTransport<Thermo>::New
(
	const dictionary& dict
)
{
	return autoPtr<sutherlandTransport<Thermo>>
		(
			new sutherlandTransport<Thermo>(dict)
			);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Thermo>
inline tnbLib::scalar tnbLib::sutherlandTransport<Thermo>::mu
(
	const scalar p,
	const scalar T
) const
{
	return As_ * ::sqrt(T) / (1.0 + Ts_ / T);
}


template<class Thermo>
inline tnbLib::scalar tnbLib::sutherlandTransport<Thermo>::kappa
(
	const scalar p, const scalar T
) const
{
	scalar Cv_ = this->Cv(p, T);
	return mu(p, T)*Cv_*(1.32 + 1.77*this->R() / Cv_);
}


template<class Thermo>
inline tnbLib::scalar tnbLib::sutherlandTransport<Thermo>::alphah
(
	const scalar p,
	const scalar T
) const
{

	return kappa(p, T) / this->Cp(p, T);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Thermo>
inline void tnbLib::sutherlandTransport<Thermo>::operator+=
(
	const sutherlandTransport<Thermo>& st
	)
{
	scalar Y1 = this->Y();

	Thermo::operator+=(st);

	if (mag(this->Y()) > small)
	{
		Y1 /= this->Y();
		scalar Y2 = st.Y() / this->Y();

		As_ = Y1 * As_ + Y2 * st.As_;
		Ts_ = Y1 * Ts_ + Y2 * st.Ts_;
	}
}


template<class Thermo>
inline void tnbLib::sutherlandTransport<Thermo>::operator*=
(
	const scalar s
	)
{
	Thermo::operator*=(s);
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

template<class Thermo>
inline tnbLib::sutherlandTransport<Thermo> tnbLib::operator+
(
	const sutherlandTransport<Thermo>& st1,
	const sutherlandTransport<Thermo>& st2
	)
{
	Thermo t
	(
		static_cast<const Thermo&>(st1) + static_cast<const Thermo&>(st2)
	);

	if (mag(t.Y()) < small)
	{
		return sutherlandTransport<Thermo>
			(
				t,
				0,
				st1.As_,
				st1.Ts_
				);
	}
	else
	{
		scalar Y1 = st1.Y() / t.Y();
		scalar Y2 = st2.Y() / t.Y();

		return sutherlandTransport<Thermo>
			(
				t,
				Y1*st1.As_ + Y2 * st2.As_,
				Y1*st1.Ts_ + Y2 * st2.Ts_
				);
	}
}


template<class Thermo>
inline tnbLib::sutherlandTransport<Thermo> tnbLib::operator*
(
	const scalar s,
	const sutherlandTransport<Thermo>& st
	)
{
	return sutherlandTransport<Thermo>
		(
			s*static_cast<const Thermo&>(st),
			st.As_,
			st.Ts_
			);
}


// ************************************************************************* //