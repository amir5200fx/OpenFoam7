#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Thermo>
inline tnbLib::exponentialSolidTransport<Thermo>::exponentialSolidTransport
(
	const Thermo& t,
	const scalar kappa0,
	const scalar n0,
	const scalar Tref
)
	:
	Thermo(t),
	kappa0_(kappa0),
	n0_(n0),
	Tref_(Tref)
{}


template<class Thermo>
inline tnbLib::exponentialSolidTransport<Thermo>::exponentialSolidTransport
(
	const word& name,
	const exponentialSolidTransport& ct
)
	:
	Thermo(name, ct),
	kappa0_(ct.kappa0_),
	n0_(ct.n0_),
	Tref_(ct.Tref_)
{}


template<class Thermo>
inline tnbLib::autoPtr<tnbLib::exponentialSolidTransport<Thermo>>
tnbLib::exponentialSolidTransport<Thermo>::New
(
	const dictionary& dict
)
{
	return autoPtr<exponentialSolidTransport<Thermo>>
		(
			new exponentialSolidTransport<Thermo>(dict)
			);
}

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Thermo>
inline tnbLib::scalar tnbLib::exponentialSolidTransport<Thermo>::kappa
(
	const scalar p, const scalar T
) const
{
	return (kappa0_*pow(T / Tref_, n0_));
}


template<class Thermo>
inline tnbLib::vector tnbLib::exponentialSolidTransport<Thermo>::Kappa
(
	const scalar p, const scalar T
) const
{
	const scalar kappa(kappa0_*pow(T / Tref_, n0_));
	return vector(kappa, kappa, kappa);
}


template<class Thermo>
inline tnbLib::scalar tnbLib::exponentialSolidTransport<Thermo>::
mu(const scalar p, const scalar T) const
{
	NotImplemented;
	return scalar(0);
}


template<class Thermo>
inline tnbLib::scalar tnbLib::exponentialSolidTransport<Thermo>::
alphah(const scalar p, const scalar T) const
{
	return kappa(p, T) / this->Cp(p, T);
}

// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Thermo>
inline void tnbLib::exponentialSolidTransport<Thermo>::operator+=
(
	const exponentialSolidTransport<Thermo>& ct
	)
{
	scalar Y1 = this->Y();

	Y1 /= this->Y();
	scalar Y2 = ct.Y() / this->Y();

	kappa0_ = Y1 * kappa0_ + Y2 * ct.kappa0_;
	n0_ = (Y1*n0_ + Y2 * ct.n0_);
	Tref_ = (Y1*Tref_ + Y2 * ct.Tref_);
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

template<class Thermo>
inline tnbLib::exponentialSolidTransport<Thermo> tnbLib::operator*
(
	const scalar s,
	const exponentialSolidTransport<Thermo>& ct
	)
{
	return exponentialSolidTransport<Thermo>
		(
			s*static_cast<const Thermo&>(ct),
			ct.kappa0_,
			ct.n0_,
			ct.Tref_
			);
}

// ************************************************************************* //