#pragma once
// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class EquationOfState>
inline tnbLib::eConstThermo<EquationOfState>::eConstThermo
(
	const EquationOfState& st,
	const scalar cv,
	const scalar hf
)
	:
	EquationOfState(st),
	Cv_(cv),
	Hf_(hf)
{}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class EquationOfState>
inline tnbLib::eConstThermo<EquationOfState>::eConstThermo
(
	const word& name,
	const eConstThermo<EquationOfState>& ct
)
	:
	EquationOfState(name, ct),
	Cv_(ct.Cv_),
	Hf_(ct.Hf_)
{}


template<class EquationOfState>
inline tnbLib::autoPtr<tnbLib::eConstThermo<EquationOfState>>
tnbLib::eConstThermo<EquationOfState>::clone() const
{
	return autoPtr<eConstThermo<EquationOfState>>
		(
			new eConstThermo<EquationOfState>(*this)
			);
}


template<class EquationOfState>
inline tnbLib::autoPtr<tnbLib::eConstThermo<EquationOfState>>
tnbLib::eConstThermo<EquationOfState>::New(const dictionary& dict)
{
	return autoPtr<eConstThermo<EquationOfState>>
		(
			new eConstThermo<EquationOfState>(dict)
			);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class EquationOfState>
inline tnbLib::scalar tnbLib::eConstThermo<EquationOfState>::limit
(
	const scalar T
) const
{
	return T;
}


template<class EquationOfState>
inline tnbLib::scalar tnbLib::eConstThermo<EquationOfState>::Cv
(
	const scalar p,
	const scalar T
) const
{
	return Cv_ + EquationOfState::Cv(p, T);
}


template<class EquationOfState>
inline tnbLib::scalar tnbLib::eConstThermo<EquationOfState>::Es
(
	const scalar p,
	const scalar T
) const
{
	return Cv_ * T + EquationOfState::E(p, T);
}


template<class EquationOfState>
inline tnbLib::scalar tnbLib::eConstThermo<EquationOfState>::Hc() const
{
	return Hf_;
}


template<class EquationOfState>
inline tnbLib::scalar tnbLib::eConstThermo<EquationOfState>::Ea
(
	const scalar p,
	const scalar T
) const
{
	return Es(p, T) + Hc();
}


template<class EquationOfState>
inline tnbLib::scalar tnbLib::eConstThermo<EquationOfState>::S
(
	const scalar p,
	const scalar T
) const
{
	return Cp(p, T)*log(T / Tstd) + EquationOfState::S(p, T);
}


template<class EquationOfState>
inline tnbLib::scalar tnbLib::eConstThermo<EquationOfState>::dGdT
(
	const scalar p,
	const scalar T
) const
{
	return 0;
}


template<class EquationOfState>
inline tnbLib::scalar tnbLib::eConstThermo<EquationOfState>::dCpdT
(
	const scalar p,
	const scalar T
) const
{
	return 0;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class EquationOfState>
inline void tnbLib::eConstThermo<EquationOfState>::operator+=
(
	const eConstThermo<EquationOfState>& ct
	)
{
	scalar Y1 = this->Y();

	EquationOfState::operator+=(ct);

	if (mag(this->Y()) > small)
	{
		Y1 /= this->Y();
		const scalar Y2 = ct.Y() / this->Y();

		Cv_ = Y1 * Cv_ + Y2 * ct.Cv_;
		Hf_ = Y1 * Hf_ + Y2 * ct.Hf_;
	}
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

template<class EquationOfState>
inline tnbLib::eConstThermo<EquationOfState> tnbLib::operator+
(
	const eConstThermo<EquationOfState>& ct1,
	const eConstThermo<EquationOfState>& ct2
	)
{
	EquationOfState eofs
	(
		static_cast<const EquationOfState&>(ct1)
		+ static_cast<const EquationOfState&>(ct2)
	);

	if (mag(eofs.Y()) < small)
	{
		return eConstThermo<EquationOfState>
			(
				eofs,
				ct1.Cv_,
				ct1.Hf_
				);
	}
	else
	{
		return eConstThermo<EquationOfState>
			(
				eofs,
				ct1.Y() / eofs.Y()*ct1.Cv_
				+ ct2.Y() / eofs.Y()*ct2.Cv_,
				ct1.Y() / eofs.Y()*ct1.Hf_
				+ ct2.Y() / eofs.Y()*ct2.Hf_
				);
	}
}


template<class EquationOfState>
inline tnbLib::eConstThermo<EquationOfState> tnbLib::operator*
(
	const scalar s,
	const eConstThermo<EquationOfState>& ct
	)
{
	return eConstThermo<EquationOfState>
		(
			s*static_cast<const EquationOfState&>(ct),
			ct.Cv_,
			ct.Hf_
			);
}


template<class EquationOfState>
inline tnbLib::eConstThermo<EquationOfState> tnbLib::operator==
(
	const eConstThermo<EquationOfState>& ct1,
	const eConstThermo<EquationOfState>& ct2
	)
{
	EquationOfState eofs
	(
		static_cast<const EquationOfState&>(ct1)
		== static_cast<const EquationOfState&>(ct2)
	);

	return eConstThermo<EquationOfState>
		(
			eofs,
			ct2.Y() / eofs.Y()*ct2.Cv_
			- ct1.Y() / eofs.Y()*ct1.Cv_,
			ct2.Y() / eofs.Y()*ct2.Hf_
			- ct1.Y() / eofs.Y()*ct1.Hf_
			);
}


// ************************************************************************* //