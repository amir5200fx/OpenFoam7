#pragma once
#include <thermodynamicConstants.hxx>
// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class EquationOfState>
inline tnbLib::hRefConstThermo<EquationOfState>::hRefConstThermo
(
	const EquationOfState& st,
	const scalar cp,
	const scalar hf,
	const scalar tref,
	const scalar href
)
	:
	EquationOfState(st),
	Cp_(cp),
	Hf_(hf),
	Tref_(tref),
	Href_(href)
{}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class EquationOfState>
inline tnbLib::hRefConstThermo<EquationOfState>::hRefConstThermo
(
	const word& name,
	const hRefConstThermo& ct
)
	:
	EquationOfState(name, ct),
	Cp_(ct.Cp_),
	Hf_(ct.Hf_),
	Tref_(ct.Tref_),
	Href_(ct.Href_)
{}


template<class EquationOfState>
inline tnbLib::autoPtr<tnbLib::hRefConstThermo<EquationOfState>>
tnbLib::hRefConstThermo<EquationOfState>::clone() const
{
	return autoPtr<hRefConstThermo<EquationOfState>>
		(
			new hRefConstThermo<EquationOfState>(*this)
			);
}


template<class EquationOfState>
inline tnbLib::autoPtr<tnbLib::hRefConstThermo<EquationOfState>>
tnbLib::hRefConstThermo<EquationOfState>::New(const dictionary& dict)
{
	return autoPtr<hRefConstThermo<EquationOfState>>
		(
			new hRefConstThermo<EquationOfState>(dict)
			);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class EquationOfState>
inline tnbLib::scalar tnbLib::hRefConstThermo<EquationOfState>::limit
(
	const scalar T
) const
{
	return T;
}


template<class EquationOfState>
inline tnbLib::scalar tnbLib::hRefConstThermo<EquationOfState>::Cp
(
	const scalar p,
	const scalar T
) const
{
	return Cp_ + EquationOfState::Cp(p, T);
}


template<class EquationOfState>
inline tnbLib::scalar tnbLib::hRefConstThermo<EquationOfState>::Hs
(
	const scalar p, const scalar T
) const
{
	return Cp_ * (T - Tref_) + Href_ + EquationOfState::H(p, T);
}


template<class EquationOfState>
inline tnbLib::scalar tnbLib::hRefConstThermo<EquationOfState>::Hc() const
{
	return Hf_;
}


template<class EquationOfState>
inline tnbLib::scalar tnbLib::hRefConstThermo<EquationOfState>::Ha
(
	const scalar p, const scalar T
) const
{
	return Hs(p, T) + Hc();
}


template<class EquationOfState>
inline tnbLib::scalar tnbLib::hRefConstThermo<EquationOfState>::S
(
	const scalar p, const scalar T
) const
{
	return Cp_ * log(T / constant::thermodynamic::Tstd) + EquationOfState::S(p, T);
}


template<class EquationOfState>
inline tnbLib::scalar tnbLib::hRefConstThermo<EquationOfState>::dGdT
(
	const scalar p, const scalar T
) const
{
	return 0;
}


template<class EquationOfState>
inline tnbLib::scalar tnbLib::hRefConstThermo<EquationOfState>::dCpdT
(
	const scalar p, const scalar T
) const
{
	return 0;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class EquationOfState>
inline void tnbLib::hRefConstThermo<EquationOfState>::operator+=
(
	const hRefConstThermo<EquationOfState>& ct
	)
{
	scalar Y1 = this->Y();

	EquationOfState::operator+=(ct);

	if (mag(this->Y()) > small)
	{
		Y1 /= this->Y();
		const scalar Y2 = ct.Y() / this->Y();

		Cp_ = Y1 * Cp_ + Y2 * ct.Cp_;
		Hf_ = Y1 * Hf_ + Y2 * ct.Hf_;
	}
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

template<class EquationOfState>
inline tnbLib::hRefConstThermo<EquationOfState> tnbLib::operator+
(
	const hRefConstThermo<EquationOfState>& ct1,
	const hRefConstThermo<EquationOfState>& ct2
	)
{
	EquationOfState eofs
	(
		static_cast<const EquationOfState&>(ct1)
		+ static_cast<const EquationOfState&>(ct2)
	);

	if (mag(eofs.Y()) < small)
	{
		return hRefConstThermo<EquationOfState>
			(
				eofs,
				ct1.Cp_,
				ct1.Hf_,
				ct1.Tref_,
				ct1.Href_
				);
	}
	else
	{
		return hRefConstThermo<EquationOfState>
			(
				eofs,
				ct1.Y() / eofs.Y()*ct1.Cp_
				+ ct2.Y() / eofs.Y()*ct2.Cp_,
				ct1.Y() / eofs.Y()*ct1.Hf_
				+ ct2.Y() / eofs.Y()*ct2.Hf_,
				ct1.Y() / eofs.Y()*ct1.Tref_
				+ ct2.Y() / eofs.Y()*ct2.Tref_,
				ct1.Y() / eofs.Y()*ct1.Href_
				+ ct2.Y() / eofs.Y()*ct2.Href_
				);
	}
}


template<class EquationOfState>
inline tnbLib::hRefConstThermo<EquationOfState> tnbLib::operator*
(
	const scalar s,
	const hRefConstThermo<EquationOfState>& ct
	)
{
	return hRefConstThermo<EquationOfState>
		(
			s*static_cast<const EquationOfState&>(ct),
			ct.Cp_,
			ct.Hf_,
			ct.Tref_,
			ct.Href_
			);
}


template<class EquationOfState>
inline tnbLib::hRefConstThermo<EquationOfState> tnbLib::operator==
(
	const hRefConstThermo<EquationOfState>& ct1,
	const hRefConstThermo<EquationOfState>& ct2
	)
{
	EquationOfState eofs
	(
		static_cast<const EquationOfState&>(ct1)
		== static_cast<const EquationOfState&>(ct2)
	);

	return hRefConstThermo<EquationOfState>
		(
			eofs,
			ct2.Y() / eofs.Y()*ct2.Cp_
			- ct1.Y() / eofs.Y()*ct1.Cp_,
			ct2.Y() / eofs.Y()*ct2.Hf_
			- ct1.Y() / eofs.Y()*ct1.Hf_
			);
}


// ************************************************************************* //