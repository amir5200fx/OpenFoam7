#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Thermo>
inline tnbLib::constAnIsoSolidTransport<Thermo>::constAnIsoSolidTransport
(
	const Thermo& t,
	const vector kappa
)
	:
	Thermo(t),
	kappa_(kappa)
{}


template<class Thermo>
inline tnbLib::constAnIsoSolidTransport<Thermo>::constAnIsoSolidTransport
(
	const word& name,
	const constAnIsoSolidTransport& ct
)
	:
	Thermo(name, ct),
	kappa_(ct.kappa_)
{}


template<class Thermo>
inline tnbLib::autoPtr<tnbLib::constAnIsoSolidTransport<Thermo>>
tnbLib::constAnIsoSolidTransport<Thermo>::New
(
	const dictionary& dict
)
{
	return autoPtr<constAnIsoSolidTransport<Thermo>>
		(
			new constAnIsoSolidTransport<Thermo>(dict)
			);
}

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Thermo>
inline tnbLib::scalar tnbLib::constAnIsoSolidTransport<Thermo>::
kappa(const scalar p, const scalar T) const
{
	return mag(kappa_);
}

template<class Thermo>
inline tnbLib::vector tnbLib::constAnIsoSolidTransport<Thermo>::
Kappa(const scalar p, const scalar T) const
{
	return kappa_;
}


template<class Thermo>
inline tnbLib::scalar tnbLib::constAnIsoSolidTransport<Thermo>::
mu(const scalar p, const scalar T) const
{
	NotImplemented;
	return scalar(0);
}


template<class Thermo>
inline tnbLib::vector tnbLib::constAnIsoSolidTransport<Thermo>::
alphah(const scalar p, const scalar T) const
{
	return kappa_ / this->Cp(p, T);
}

// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Thermo>
inline void tnbLib::constAnIsoSolidTransport<Thermo>::operator+=
(
	const constAnIsoSolidTransport<Thermo>& ct
	)
{
	scalar Y1 = this->Y();

	Y1 /= this->Y();
	scalar Y2 = ct.Y() / this->Y();

	kappa_ = Y1 * kappa_ + Y2 * ct.kappa_;
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //


template<class Thermo>
inline tnbLib::constAnIsoSolidTransport<Thermo> tnbLib::operator*
(
	const scalar s,
	const constAnIsoSolidTransport<Thermo>& ct
	)
{
	return constAnIsoSolidTransport<Thermo>
		(
			s*static_cast<const Thermo&>(ct),
			ct.kappa_
			);
}

// ************************************************************************* //