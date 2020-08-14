#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Thermo>
inline tnbLib::constTransport<Thermo>::constTransport
(
	const Thermo& t,
	const scalar mu,
	const scalar Pr
)
	:
	Thermo(t),
	mu_(mu),
	rPr_(1.0 / Pr)
{}


template<class Thermo>
inline tnbLib::constTransport<Thermo>::constTransport
(
	const word& name,
	const constTransport& ct
)
	:
	Thermo(name, ct),
	mu_(ct.mu_),
	rPr_(ct.rPr_)
{}


template<class Thermo>
inline tnbLib::autoPtr<tnbLib::constTransport<Thermo>>
tnbLib::constTransport<Thermo>::clone() const
{
	return autoPtr<constTransport<Thermo>>
		(
			new constTransport<Thermo>(*this)
			);
}


template<class Thermo>
inline tnbLib::autoPtr<tnbLib::constTransport<Thermo>>
tnbLib::constTransport<Thermo>::New
(
	const dictionary& dict
)
{
	return autoPtr<constTransport<Thermo>>
		(
			new constTransport<Thermo>(dict)
			);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Thermo>
inline tnbLib::scalar tnbLib::constTransport<Thermo>::mu
(
	const scalar p,
	const scalar T
) const
{
	return mu_;
}


template<class Thermo>
inline tnbLib::scalar tnbLib::constTransport<Thermo>::kappa
(
	const scalar p,
	const scalar T
) const
{
	return this->Cp(p, T)*mu(p, T)*rPr_;
}


template<class Thermo>
inline tnbLib::scalar tnbLib::constTransport<Thermo>::alphah
(
	const scalar p,
	const scalar T
) const
{
	return mu(p, T)*rPr_;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Thermo>
inline void tnbLib::constTransport<Thermo>::operator+=
(
	const constTransport<Thermo>& st
	)
{
	scalar Y1 = this->Y();

	Thermo::operator+=(st);

	if (mag(this->Y()) > small)
	{
		Y1 /= this->Y();
		scalar Y2 = st.Y() / this->Y();

		mu_ = Y1 * mu_ + Y2 * st.mu_;
		rPr_ = 1.0 / (Y1 / rPr_ + Y2 / st.rPr_);
	}
}


template<class Thermo>
inline void tnbLib::constTransport<Thermo>::operator*=
(
	const scalar s
	)
{
	Thermo::operator*=(s);
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

template<class Thermo>
inline tnbLib::constTransport<Thermo> tnbLib::operator+
(
	const constTransport<Thermo>& ct1,
	const constTransport<Thermo>& ct2
	)
{
	Thermo t
	(
		static_cast<const Thermo&>(ct1) + static_cast<const Thermo&>(ct2)
	);

	if (mag(t.Y()) < small)
	{
		return constTransport<Thermo>
			(
				t,
				0,
				ct1.rPr_
				);
	}
	else
	{
		scalar Y1 = ct1.Y() / t.Y();
		scalar Y2 = ct2.Y() / t.Y();

		return constTransport<Thermo>
			(
				t,
				Y1*ct1.mu_ + Y2 * ct2.mu_,
				1.0 / (Y1 / ct1.rPr_ + Y2 / ct2.rPr_)
				);
	}
}


template<class Thermo>
inline tnbLib::constTransport<Thermo> tnbLib::operator*
(
	const scalar s,
	const constTransport<Thermo>& ct
	)
{
	return constTransport<Thermo>
		(
			s*static_cast<const Thermo&>(ct),
			ct.mu_,
			1.0 / ct.rPr_
			);
}


// ************************************************************************* //