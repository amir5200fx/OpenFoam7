#pragma once
#include <specie.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class EquationOfState>
inline void tnbLib::hPowerThermo<EquationOfState>::checkT
(
	const scalar T
) const
{
	if (T < 0)
	{
		FatalErrorInFunction
			<< "attempt to evaluate hPowerThermo<EquationOfState>"
			" for negative temperature " << T
			<< abort(FatalError);
	}
}


template<class EquationOfState>
inline tnbLib::hPowerThermo<EquationOfState>::hPowerThermo
(
	const word& name,
	const hPowerThermo& jt
)
	:
	EquationOfState(name, jt),
	c0_(jt.c0_),
	n0_(jt.n0_),
	Tref_(jt.Tref_),
	Hf_(jt.Hf_)
{}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class EquationOfState>
inline tnbLib::hPowerThermo<EquationOfState>::hPowerThermo
(
	const EquationOfState& st,
	const scalar c0,
	const scalar n0,
	const scalar Tref,
	const scalar Hf
)
	:
	EquationOfState(st),
	c0_(c0),
	n0_(n0),
	Tref_(Tref),
	Hf_(Hf)
{}


template<class EquationOfState>
inline tnbLib::autoPtr<tnbLib::hPowerThermo<EquationOfState>>
tnbLib::hPowerThermo<EquationOfState>::clone() const
{
	return autoPtr<hPowerThermo<EquationOfState>>
		(
			new hPowerThermo<EquationOfState>(*this)
			);
}


template<class EquationOfState>
inline tnbLib::autoPtr<tnbLib::hPowerThermo<EquationOfState>>
tnbLib::hPowerThermo<EquationOfState>::New(const dictionary& dict)
{
	return autoPtr<hPowerThermo<EquationOfState>>
		(
			new hPowerThermo<EquationOfState>(dict)
			);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class EquationOfState>
inline tnbLib::scalar tnbLib::hPowerThermo<EquationOfState>::limit
(
	const scalar T
) const
{
	return T;
}


template<class EquationOfState>
inline tnbLib::scalar tnbLib::hPowerThermo<EquationOfState>::Cp
(
	const scalar p, const scalar T
) const
{
	return c0_ * pow(T / Tref_, n0_) + EquationOfState::Cp(p, T);
}


template<class EquationOfState>
inline tnbLib::scalar tnbLib::hPowerThermo<EquationOfState>::Ha
(
	const scalar p, const scalar T
) const
{
	return Hs(p, T) + Hc();
}


template<class EquationOfState>
inline tnbLib::scalar tnbLib::hPowerThermo<EquationOfState>::Hs
(
	const scalar p, const scalar T
) const
{
	return
		c0_ * (pow(T, n0_ + 1) - pow(Tstd, n0_ + 1)) / (pow(Tref_, n0_)*(n0_ + 1))
		+ EquationOfState::H(p, T);
}


template<class EquationOfState>
inline tnbLib::scalar tnbLib::hPowerThermo<EquationOfState>::Hc() const
{
	return Hf_;
}


template<class EquationOfState>
inline tnbLib::scalar tnbLib::hPowerThermo<EquationOfState>::S
(
	const scalar p, const scalar T
) const
{
	return
		c0_ * (pow(T, n0_) - pow(Tstd, n0_)) / (pow(Tref_, n0_)*n0_)
		+ EquationOfState::S(p, T);
}


template<class EquationOfState>
inline tnbLib::scalar tnbLib::hPowerThermo<EquationOfState>::dGdT
(
	const scalar p, const scalar T
) const
{
	// To be implemented
	NotImplemented;
	return 0;
}


template<class EquationOfState>
inline tnbLib::scalar tnbLib::hPowerThermo<EquationOfState>::dCpdT
(
	const scalar p, const scalar T
) const
{
	// To be implemented
	NotImplemented;
	return 0;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class EquationOfState>
inline void tnbLib::hPowerThermo<EquationOfState>::operator+=
(
	const hPowerThermo<EquationOfState>& ct
	)
{
	scalar Y1 = this->Y();

	EquationOfState::operator+=(ct);

	if (mag(this->Y()) > small)
	{
		Y1 /= this->Y();
		const scalar Y2 = ct.Y() / this->Y();

		Hf_ = Y1 * Hf_ + Y2 * ct.Hf_;
		c0_ = Y1 * c0_ + Y2 * ct.c0_;
		n0_ = Y1 * n0_ + Y2 * ct.n0_;
		Tref_ = Y1 * Tref_ + Y2 * ct.Tref_;
	}
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

template<class EquationOfState>
inline tnbLib::hPowerThermo<EquationOfState> tnbLib::operator+
(
	const hPowerThermo<EquationOfState>& ct1,
	const hPowerThermo<EquationOfState>& ct2
	)
{
	EquationOfState eofs
	(
		static_cast<const EquationOfState&>(ct1)
		+ static_cast<const EquationOfState&>(ct2)
	);

	if (mag(eofs.Y()) < small)
	{
		return hPowerThermo<EquationOfState>
			(
				eofs,
				ct1.c0_,
				ct1.n0_,
				ct1.Tref_,
				ct1.Hf_
				);
	}
	else
	{
		return hPowerThermo<EquationOfState>
			(
				eofs,
				ct1.Y() / eofs.Y()*ct1.c0_
				+ ct2.Y() / eofs.Y()*ct2.c0_,
				ct1.Y() / eofs.Y()*ct1.n0_
				+ ct2.Y() / eofs.Y()*ct2.n0_,
				ct1.Y() / eofs.Y()*ct1.Tref_
				+ ct2.Y() / eofs.Y()*ct2.Tref_,
				ct1.Y() / eofs.Y()*ct1.Hf_
				+ ct2.Y() / eofs.Y()*ct2.Hf_
				);
	}
}


template<class EquationOfState>
inline tnbLib::hPowerThermo<EquationOfState> tnbLib::operator*
(
	const scalar s,
	const hPowerThermo<EquationOfState>& ct
	)
{
	return hPowerThermo<EquationOfState>
		(
			s*static_cast<const EquationOfState&>(ct),
			ct.c0_,
			ct.n0_,
			ct.Tref_,
			ct.Hf_
			);
}


template<class EquationOfState>
inline tnbLib::hPowerThermo<EquationOfState> tnbLib::operator==
(
	const hPowerThermo<EquationOfState>& ct1,
	const hPowerThermo<EquationOfState>& ct2
	)
{
	EquationOfState eofs
	(
		static_cast<const EquationOfState&>(ct1)
		== static_cast<const EquationOfState&>(ct2)
	);

	return hPowerThermo<EquationOfState>
		(
			eofs,
			ct2.Y() / eofs.Y()*ct2.c0_
			- ct1.Y() / eofs.Y()*ct1.c0_,
			ct2.Y() / eofs.Y()*ct2.n0_
			- ct1.Y() / eofs.Y()*ct1.n0_,
			ct2.Y() / eofs.Y()*ct2.Tref_
			- ct1.Y() / eofs.Y()*ct1.Tref_,
			ct2.Y() / eofs.Y()*ct2.Hf_
			- ct1.Y() / eofs.Y()*ct1.Hf_
			);
}


// ************************************************************************* //

#include <IOstreams.hxx>
#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class EquationOfState>
tnbLib::hPowerThermo<EquationOfState>::hPowerThermo
(
	const dictionary& dict
)
	:
	EquationOfState(dict),
	c0_(readScalar(dict.subDict("thermodynamics").lookup("C0"))),
	n0_(readScalar(dict.subDict("thermodynamics").lookup("n0"))),
	Tref_(readScalar(dict.subDict("thermodynamics").lookup("Tref"))),
	Hf_(readScalar(dict.subDict("thermodynamics").lookup("Hf")))
{}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

template<class EquationOfState>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const hPowerThermo<EquationOfState>& et
	)
{
	et.write(os);
	return os;
}


// ************************************************************************* //