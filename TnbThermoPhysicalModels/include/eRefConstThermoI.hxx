#pragma once
#include <thermodynamicConstants.hxx>  // added by amir
// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class EquationOfState>
inline tnbLib::eRefConstThermo<EquationOfState>::eRefConstThermo
(
	const EquationOfState& st,
	const scalar cv,
	const scalar hf,
	const scalar tref,
	const scalar eref
)
	:
	EquationOfState(st),
	Cv_(cv),
	Hf_(hf),
	Tref_(tref),
	Eref_(eref)
{}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class EquationOfState>
inline tnbLib::eRefConstThermo<EquationOfState>::eRefConstThermo
(
	const word& name,
	const eRefConstThermo& ct
)
	:
	EquationOfState(name, ct),
	Cv_(ct.Cv_),
	Hf_(ct.Hf_),
	Tref_(ct.Tref_),
	Eref_(ct.Eref_)
{}


template<class EquationOfState>
inline tnbLib::autoPtr<tnbLib::eRefConstThermo<EquationOfState>>
tnbLib::eRefConstThermo<EquationOfState>::clone() const
{
	return autoPtr<eRefConstThermo<EquationOfState>>
		(
			new eRefConstThermo<EquationOfState>(*this)
			);
}


template<class EquationOfState>
inline tnbLib::autoPtr<tnbLib::eRefConstThermo<EquationOfState>>
tnbLib::eRefConstThermo<EquationOfState>::New(const dictionary& dict)
{
	return autoPtr<eRefConstThermo<EquationOfState>>
		(
			new eRefConstThermo<EquationOfState>(dict)
			);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class EquationOfState>
inline tnbLib::scalar tnbLib::eRefConstThermo<EquationOfState>::limit
(
	const scalar T
) const
{
	return T;
}


template<class EquationOfState>
inline tnbLib::scalar tnbLib::eRefConstThermo<EquationOfState>::Cv
(
	const scalar p,
	const scalar T
) const
{
	return Cv_ + EquationOfState::Cv(p, T);
}


template<class EquationOfState>
inline tnbLib::scalar tnbLib::eRefConstThermo<EquationOfState>::Es
(
	const scalar p, const scalar T
) const
{
	return Cv_ * (T - Tref_) + Eref_ + EquationOfState::E(p, T);
}


template<class EquationOfState>
inline tnbLib::scalar tnbLib::eRefConstThermo<EquationOfState>::Hc() const
{
	return Hf_;
}


template<class EquationOfState>
inline tnbLib::scalar tnbLib::eRefConstThermo<EquationOfState>::Ea
(
	const scalar p, const scalar T
) const
{
	return Es(p, T) + Hc();
}


template<class EquationOfState>
inline tnbLib::scalar tnbLib::eRefConstThermo<EquationOfState>::S
(
	const scalar p, const scalar T
) const
{
	return Cp(p, T)*log(T / constant::thermodynamic::Tstd) + EquationOfState::S(p, T);
}


template<class EquationOfState>
inline tnbLib::scalar tnbLib::eRefConstThermo<EquationOfState>::dGdT
(
	const scalar p, const scalar T
) const
{
	return 0;
}


template<class EquationOfState>
inline tnbLib::scalar tnbLib::eRefConstThermo<EquationOfState>::dCpdT
(
	const scalar p, const scalar T
) const
{
	return 0;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class EquationOfState>
inline void tnbLib::eRefConstThermo<EquationOfState>::operator+=
(
	const eRefConstThermo<EquationOfState>& ct
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
inline tnbLib::eRefConstThermo<EquationOfState> tnbLib::operator+
(
	const eRefConstThermo<EquationOfState>& ct1,
	const eRefConstThermo<EquationOfState>& ct2
	)
{
	EquationOfState eofs
	(
		static_cast<const EquationOfState&>(ct1)
		+ static_cast<const EquationOfState&>(ct2)
	);

	if (mag(eofs.Y()) < small)
	{
		return eRefConstThermo<EquationOfState>
			(
				eofs,
				ct1.Cv_,
				ct1.Hf_,
				ct1.Tref_,
				ct1.Eref_
				);
	}
	else
	{
		return eRefConstThermo<EquationOfState>
			(
				eofs,
				ct1.Y() / eofs.Y()*ct1.Cv_
				+ ct2.Y() / eofs.Y()*ct2.Cv_,
				ct1.Y() / eofs.Y()*ct1.Hf_
				+ ct2.Y() / eofs.Y()*ct2.Hf_,
				ct1.Y() / eofs.Y()*ct1.Tref_
				+ ct2.Y() / eofs.Y()*ct2.Tref_,
				ct1.Y() / eofs.Y()*ct1.Eref_
				+ ct2.Y() / eofs.Y()*ct2.Eref_
				);
	}
}


template<class EquationOfState>
inline tnbLib::eRefConstThermo<EquationOfState> tnbLib::operator*
(
	const scalar s,
	const eRefConstThermo<EquationOfState>& ct
	)
{
	return eRefConstThermo<EquationOfState>
		(
			s*static_cast<const EquationOfState&>(ct),
			ct.Cv_,
			ct.Hf_,
			ct.Tref_,
			ct.Eref_
			);
}


template<class EquationOfState>
inline tnbLib::eRefConstThermo<EquationOfState> tnbLib::operator==
(
	const eRefConstThermo<EquationOfState>& ct1,
	const eRefConstThermo<EquationOfState>& ct2
	)
{
	EquationOfState eofs
	(
		static_cast<const EquationOfState&>(ct1)
		== static_cast<const EquationOfState&>(ct2)
	);

	return eRefConstThermo<EquationOfState>
		(
			eofs,
			ct2.Y() / eofs.Y()*ct2.Cv_
			- ct1.Y() / eofs.Y()*ct1.Cv_,
			ct2.Y() / eofs.Y()*ct2.Hf_
			- ct1.Y() / eofs.Y()*ct1.Hf_
			);
}


// ************************************************************************* //

#include <IOstreams.hxx>
#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class EquationOfState>
tnbLib::eRefConstThermo<EquationOfState>::eRefConstThermo(const dictionary& dict)
	:
	EquationOfState(dict),
	Cv_(readScalar(dict.subDict("thermodynamics").lookup("Cv"))),
	Hf_(readScalar(dict.subDict("thermodynamics").lookup("Hf"))),
	Tref_(readScalar(dict.subDict("thermodynamics").lookup("Tref"))),
	Eref_(readScalar(dict.subDict("thermodynamics").lookup("Eref")))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class EquationOfState>
void tnbLib::eRefConstThermo<EquationOfState>::write(Ostream& os) const
{
	EquationOfState::write(os);

	dictionary dict("thermodynamics");
	dict.add("Cv", Cv_);
	dict.add("Hf", Hf_);
	dict.add("Tref", Tref_);
	dict.add("Eref", Eref_);
	os << indent << dict.dictName() << dict;
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

template<class EquationOfState>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const eRefConstThermo<EquationOfState>& ct
	)
{
	ct.write(os);
	return os;
}


// ************************************************************************* //