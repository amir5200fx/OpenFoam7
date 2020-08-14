#pragma once
#include <thermodynamicConstants.hxx>
// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class EquationOfState>
inline tnbLib::hConstThermo<EquationOfState>::hConstThermo
(
	const EquationOfState& st,
	const scalar cp,
	const scalar hf
)
	:
	EquationOfState(st),
	Cp_(cp),
	Hf_(hf)
{}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class EquationOfState>
inline tnbLib::hConstThermo<EquationOfState>::hConstThermo
(
	const word& name,
	const hConstThermo& ct
)
	:
	EquationOfState(name, ct),
	Cp_(ct.Cp_),
	Hf_(ct.Hf_)
{}


template<class EquationOfState>
inline tnbLib::autoPtr<tnbLib::hConstThermo<EquationOfState>>
tnbLib::hConstThermo<EquationOfState>::clone() const
{
	return autoPtr<hConstThermo<EquationOfState>>
		(
			new hConstThermo<EquationOfState>(*this)
			);
}


template<class EquationOfState>
inline tnbLib::autoPtr<tnbLib::hConstThermo<EquationOfState>>
tnbLib::hConstThermo<EquationOfState>::New(const dictionary& dict)
{
	return autoPtr<hConstThermo<EquationOfState>>
		(
			new hConstThermo<EquationOfState>(dict)
			);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class EquationOfState>
inline tnbLib::scalar tnbLib::hConstThermo<EquationOfState>::limit
(
	const scalar T
) const
{
	return T;
}


template<class EquationOfState>
inline tnbLib::scalar tnbLib::hConstThermo<EquationOfState>::Cp
(
	const scalar p,
	const scalar T
) const
{
	return Cp_ + EquationOfState::Cp(p, T);
}


template<class EquationOfState>
inline tnbLib::scalar tnbLib::hConstThermo<EquationOfState>::Hs
(
	const scalar p, const scalar T
) const
{
	return Cp_ * T + EquationOfState::H(p, T);
}


template<class EquationOfState>
inline tnbLib::scalar tnbLib::hConstThermo<EquationOfState>::Hc() const
{
	return Hf_;
}


template<class EquationOfState>
inline tnbLib::scalar tnbLib::hConstThermo<EquationOfState>::Ha
(
	const scalar p, const scalar T
) const
{
	return Hs(p, T) + Hc();
}


template<class EquationOfState>
inline tnbLib::scalar tnbLib::hConstThermo<EquationOfState>::S
(
	const scalar p, const scalar T
) const
{
	return Cp_ * log(T / constant::thermodynamic::Tstd) + EquationOfState::S(p, T);
}


template<class EquationOfState>
inline tnbLib::scalar tnbLib::hConstThermo<EquationOfState>::dGdT
(
	const scalar p, const scalar T
) const
{
	return 0;
}


template<class EquationOfState>
inline tnbLib::scalar tnbLib::hConstThermo<EquationOfState>::dCpdT
(
	const scalar p, const scalar T
) const
{
	return 0;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class EquationOfState>
inline void tnbLib::hConstThermo<EquationOfState>::operator+=
(
	const hConstThermo<EquationOfState>& ct
	)
{
	scalar Y1 = this->Y();

	EquationOfState::operator+=(ct);

	if (mag(this->Y()) > small)
	{
		Y1 /= this->Y();
		scalar Y2 = ct.Y() / this->Y();

		Cp_ = Y1 * Cp_ + Y2 * ct.Cp_;
		Hf_ = Y1 * Hf_ + Y2 * ct.Hf_;
	}
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

template<class EquationOfState>
inline tnbLib::hConstThermo<EquationOfState> tnbLib::operator+
(
	const hConstThermo<EquationOfState>& ct1,
	const hConstThermo<EquationOfState>& ct2
	)
{
	EquationOfState eofs
	(
		static_cast<const EquationOfState&>(ct1)
		+ static_cast<const EquationOfState&>(ct2)
	);

	if (mag(eofs.Y()) < small)
	{
		return hConstThermo<EquationOfState>
			(
				eofs,
				ct1.Cp_,
				ct1.Hf_
				);
	}
	else
	{
		return hConstThermo<EquationOfState>
			(
				eofs,
				ct1.Y() / eofs.Y()*ct1.Cp_
				+ ct2.Y() / eofs.Y()*ct2.Cp_,
				ct1.Y() / eofs.Y()*ct1.Hf_
				+ ct2.Y() / eofs.Y()*ct2.Hf_
				);
	}
}


template<class EquationOfState>
inline tnbLib::hConstThermo<EquationOfState> tnbLib::operator*
(
	const scalar s,
	const hConstThermo<EquationOfState>& ct
	)
{
	return hConstThermo<EquationOfState>
		(
			s*static_cast<const EquationOfState&>(ct),
			ct.Cp_,
			ct.Hf_
			);
}


template<class EquationOfState>
inline tnbLib::hConstThermo<EquationOfState> tnbLib::operator==
(
	const hConstThermo<EquationOfState>& ct1,
	const hConstThermo<EquationOfState>& ct2
	)
{
	EquationOfState eofs
	(
		static_cast<const EquationOfState&>(ct1)
		== static_cast<const EquationOfState&>(ct2)
	);

	return hConstThermo<EquationOfState>
		(
			eofs,
			ct2.Y() / eofs.Y()*ct2.Cp_
			- ct1.Y() / eofs.Y()*ct1.Cp_,
			ct2.Y() / eofs.Y()*ct2.Hf_
			- ct1.Y() / eofs.Y()*ct1.Hf_
			);
}


// ************************************************************************* //