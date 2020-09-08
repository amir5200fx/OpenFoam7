#pragma once
inline tnbLib::scalar tnbLib::liquidProperties::limit(const scalar T) const
{
	return T;
}


inline tnbLib::scalar tnbLib::liquidProperties::Y() const
{
	return 1;
}


inline tnbLib::scalar tnbLib::liquidProperties::Tc() const
{
	return Tc_;
}


inline tnbLib::scalar tnbLib::liquidProperties::Pc() const
{
	return Pc_;
}


inline tnbLib::scalar tnbLib::liquidProperties::Vc() const
{
	return Vc_;
}


inline tnbLib::scalar tnbLib::liquidProperties::Zc() const
{
	return Zc_;
}


inline tnbLib::scalar tnbLib::liquidProperties::Tt() const
{
	return Tt_;
}


inline tnbLib::scalar tnbLib::liquidProperties::Pt() const
{
	return Pt_;
}


inline tnbLib::scalar tnbLib::liquidProperties::Tb() const
{
	return Tb_;
}


inline tnbLib::scalar tnbLib::liquidProperties::dipm() const
{
	return dipm_;
}


inline tnbLib::scalar tnbLib::liquidProperties::omega() const
{
	return omega_;
}


inline tnbLib::scalar tnbLib::liquidProperties::delta() const
{
	return delta_;
}


inline tnbLib::scalar tnbLib::liquidProperties::psi(scalar p, scalar T) const
{
	return 0;
}


inline tnbLib::scalar tnbLib::liquidProperties::CpMCv(scalar p, scalar T) const
{
	return 0;
}


inline tnbLib::scalar tnbLib::liquidProperties::Ha(scalar p, scalar T) const
{
	return h(p, T);
}


inline tnbLib::scalar tnbLib::liquidProperties::Hs(scalar p, scalar T) const
{
	return h(p, T);
}


inline tnbLib::scalar tnbLib::liquidProperties::Hc() const
{
	return 0;
}


inline tnbLib::scalar tnbLib::liquidProperties::alphah(scalar p, scalar T) const
{
	return kappa(p, T) / Cp(p, T);
}


template<class Func>
inline void tnbLib::liquidProperties::readIfPresent
(
	Func& f,
	const word& name,
	const dictionary& dict
)
{
	if (dict.found(name))
	{
		f = Func(dict.subDict(name));
	}
}


template<class Liquid>
inline void tnbLib::liquidProperties::readIfPresent
(
	Liquid& l,
	const dictionary& dict
)
{
	l.liquidProperties::readIfPresent(dict);
	readIfPresent(l.rho_, "rho", dict);
	readIfPresent(l.pv_, "pv", dict);
	readIfPresent(l.hl_, "hl", dict);
	readIfPresent(l.Cp_, "Cp", dict);
	readIfPresent(l.h_, "h", dict);
	readIfPresent(l.Cpg_, "Cpg", dict);
	readIfPresent(l.B_, "B", dict);
	readIfPresent(l.mu_, "mu", dict);
	readIfPresent(l.mug_, "mug", dict);
	readIfPresent(l.kappa_, "K", dict);
	readIfPresent(l.kappag_, "kappag", dict);
	readIfPresent(l.sigma_, "sigma", dict);
	readIfPresent(l.D_, "D", dict);
}


template<class Liquid>
inline void tnbLib::liquidProperties::writeData
(
	const Liquid& l,
	Ostream& os
) const
{
	l.liquidProperties::writeData(os); os << nl;
	l.rho_.writeData(os); os << nl;
	l.pv_.writeData(os); os << nl;
	l.hl_.writeData(os); os << nl;
	l.Cp_.writeData(os); os << nl;
	l.h_.writeData(os); os << nl;
	l.Cpg_.writeData(os); os << nl;
	l.B_.writeData(os); os << nl;
	l.mu_.writeData(os); os << nl;
	l.mug_.writeData(os); os << nl;
	l.kappa_.writeData(os); os << nl;
	l.kappag_.writeData(os); os << nl;
	l.sigma_.writeData(os); os << nl;
	l.D_.writeData(os); os << endl;
}


// ************************************************************************* //