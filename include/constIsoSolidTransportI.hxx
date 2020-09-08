#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class thermo>
inline tnbLib::constIsoSolidTransport<thermo>::constIsoSolidTransport
(
	const thermo& t,
	const scalar kappa
)
	:
	thermo(t),
	kappa_(kappa)
{}


template<class thermo>
inline tnbLib::constIsoSolidTransport<thermo>::constIsoSolidTransport
(
	const word& name,
	const constIsoSolidTransport& ct
)
	:
	thermo(name, ct),
	kappa_(ct.kappa_)
{}


template<class Thermo>
inline tnbLib::autoPtr<tnbLib::constIsoSolidTransport<Thermo>>
tnbLib::constIsoSolidTransport<Thermo>::New
(
	const dictionary& dict
)
{
	return autoPtr<constIsoSolidTransport<Thermo>>
		(
			new constIsoSolidTransport<Thermo>(dict)
			);
}

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class thermo>
inline tnbLib::scalar tnbLib::constIsoSolidTransport<thermo>::
kappa(const scalar p, const scalar T) const
{
	return kappa_;
}

template<class thermo>
inline tnbLib::vector tnbLib::constIsoSolidTransport<thermo>::
Kappa(const scalar p, const scalar T) const
{
	return vector(kappa_, kappa_, kappa_);
}


template<class thermo>
inline tnbLib::scalar tnbLib::constIsoSolidTransport<thermo>::
mu(const scalar p, const scalar T) const
{
	NotImplemented;
	return scalar(0);
}


template<class thermo>
inline tnbLib::scalar tnbLib::constIsoSolidTransport<thermo>::
alphah(const scalar p, const scalar T) const
{
	return kappa_ / this->Cp(p, T);
}

// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class thermo>
inline void tnbLib::constIsoSolidTransport<thermo>::operator+=
(
	const constIsoSolidTransport<thermo>& ct
	)
{
	scalar Y1 = this->Y();
	thermo::operator+=(ct);

	Y1 /= this->Y();
	scalar Y2 = ct.Y() / this->Y();

	kappa_ = Y1 * kappa_ + Y2 * ct.kappa_;
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //


template<class thermo>
inline tnbLib::constIsoSolidTransport<thermo> tnbLib::operator*
(
	const scalar s,
	const constIsoSolidTransport<thermo>& ct
	)
{
	return constIsoSolidTransport<thermo>
		(
			s*static_cast<const thermo&>(ct),
			ct.kappa_
			);
}


// ************************************************************************* //