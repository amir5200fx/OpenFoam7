#pragma once
// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class EquationOfState, int PolySize>
inline tnbLib::hPolynomialThermo<EquationOfState, PolySize>::hPolynomialThermo
(
	const EquationOfState& pt,
	const scalar Hf,
	const scalar Sf,
	const Polynomial<PolySize>& CpCoeffs,
	const typename Polynomial<PolySize>::intPolyType& hCoeffs,
	const Polynomial<PolySize>& sCoeffs
)
	:
	EquationOfState(pt),
	Hf_(Hf),
	Sf_(Sf),
	CpCoeffs_(CpCoeffs),
	hCoeffs_(hCoeffs),
	sCoeffs_(sCoeffs)
{}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class EquationOfState, int PolySize>
inline tnbLib::hPolynomialThermo<EquationOfState, PolySize>::hPolynomialThermo
(
	const word& name,
	const hPolynomialThermo& pt
)
	:
	EquationOfState(name, pt),
	Hf_(pt.Hf_),
	Sf_(pt.Sf_),
	CpCoeffs_(pt.CpCoeffs_),
	hCoeffs_(pt.hCoeffs_),
	sCoeffs_(pt.sCoeffs_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class EquationOfState, int PolySize>
inline tnbLib::scalar tnbLib::hPolynomialThermo<EquationOfState, PolySize>::limit
(
	const scalar T
) const
{
	return T;
}


template<class EquationOfState, int PolySize>
inline tnbLib::scalar tnbLib::hPolynomialThermo<EquationOfState, PolySize>::Cp
(
	const scalar p, const scalar T
) const
{
	return CpCoeffs_.value(T) + EquationOfState::Cp(p, T);
}


template<class EquationOfState, int PolySize>
inline tnbLib::scalar tnbLib::hPolynomialThermo<EquationOfState, PolySize>::Ha
(
	const scalar p, const scalar T
) const
{
	return hCoeffs_.value(T) + EquationOfState::H(p, T);
}


template<class EquationOfState, int PolySize>
inline tnbLib::scalar tnbLib::hPolynomialThermo<EquationOfState, PolySize>::Hs
(
	const scalar p, const scalar T
) const
{
	return Ha(p, T) - Hc();
}


template<class EquationOfState, int PolySize>
inline tnbLib::scalar tnbLib::hPolynomialThermo<EquationOfState, PolySize>::Hc()
const
{
	return Hf_;
}


template<class EquationOfState, int PolySize>
inline tnbLib::scalar tnbLib::hPolynomialThermo<EquationOfState, PolySize>::S
(
	const scalar p,
	const scalar T
) const
{
	return sCoeffs_.value(T) + EquationOfState::S(p, T);
}


template<class EquationOfState, int PolySize>
inline tnbLib::scalar tnbLib::hPolynomialThermo<EquationOfState, PolySize>::dGdT
(
	const scalar p,
	const scalar T
) const
{
	return
		(
			hCoeffs_.derivative(T)
			- T * sCoeffs_.derivative(T)
			- sCoeffs_.value(T)
			);
}


template<class EquationOfState, int PolySize>
inline tnbLib::scalar tnbLib::hPolynomialThermo<EquationOfState, PolySize>::dCpdT
(
	const scalar p,
	const scalar T
) const
{
	return
		(
			CpCoeffs_.derivative(T)
			);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class EquationOfState, int PolySize>
inline void tnbLib::hPolynomialThermo<EquationOfState, PolySize>::operator+=
(
	const hPolynomialThermo<EquationOfState, PolySize>& pt
	)
{
	scalar Y1 = this->Y();

	EquationOfState::operator+=(pt);

	if (mag(this->Y()) > small)
	{
		Y1 /= this->Y();
		const scalar Y2 = pt.Y() / this->Y();

		Hf_ = Y1 * Hf_ + Y2 * pt.Hf_;
		Sf_ = Y1 * Sf_ + Y2 * pt.Sf_;
		CpCoeffs_ = Y1 * CpCoeffs_ + Y2 * pt.CpCoeffs_;
		hCoeffs_ = Y1 * hCoeffs_ + Y2 * pt.hCoeffs_;
		sCoeffs_ = Y1 * sCoeffs_ + Y2 * pt.sCoeffs_;
	}
}


template<class EquationOfState, int PolySize>
inline void tnbLib::hPolynomialThermo<EquationOfState, PolySize>::operator*=
(
	const scalar s
	)
{
	EquationOfState::operator*=(s);
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

template<class EquationOfState, int PolySize>
inline tnbLib::hPolynomialThermo<EquationOfState, PolySize> tnbLib::operator+
(
	const hPolynomialThermo<EquationOfState, PolySize>& pt1,
	const hPolynomialThermo<EquationOfState, PolySize>& pt2
	)
{
	EquationOfState eofs = pt1;
	eofs += pt2;

	if (mag(eofs.Y()) < small)
	{
		return hPolynomialThermo<EquationOfState, PolySize>
			(
				eofs,
				pt1.Hf_,
				pt1.Sf_,
				pt1.CpCoeffs_,
				pt1.hCoeffs_,
				pt1.sCoeffs_
				);
	}
	{
		const scalar Y1 = pt1.Y() / eofs.Y();
		const scalar Y2 = pt2.Y() / eofs.Y();

		return hPolynomialThermo<EquationOfState, PolySize>
			(
				eofs,
				Y1*pt1.Hf_ + Y2 * pt2.Hf_,
				Y1*pt1.Sf_ + Y2 * pt2.Sf_,
				Y1*pt1.CpCoeffs_ + Y2 * pt2.CpCoeffs_,
				Y1*pt1.hCoeffs_ + Y2 * pt2.hCoeffs_,
				Y1*pt1.sCoeffs_ + Y2 * pt2.sCoeffs_
				);
	}
}


template<class EquationOfState, int PolySize>
inline tnbLib::hPolynomialThermo<EquationOfState, PolySize> tnbLib::operator*
(
	const scalar s,
	const hPolynomialThermo<EquationOfState, PolySize>& pt
	)
{
	return hPolynomialThermo<EquationOfState, PolySize>
		(
			s*static_cast<const EquationOfState&>(pt),
			pt.Hf_,
			pt.Sf_,
			pt.CpCoeffs_,
			pt.hCoeffs_,
			pt.sCoeffs_
			);
}


template<class EquationOfState, int PolySize>
inline tnbLib::hPolynomialThermo<EquationOfState, PolySize> tnbLib::operator==
(
	const hPolynomialThermo<EquationOfState, PolySize>& pt1,
	const hPolynomialThermo<EquationOfState, PolySize>& pt2
	)
{
	EquationOfState eofs
	(
		static_cast<const EquationOfState&>(pt1)
		== static_cast<const EquationOfState&>(pt2)
	);

	const scalar Y1 = pt1.Y() / eofs.Y();
	const scalar Y2 = pt2.Y() / eofs.Y();

	return hPolynomialThermo<EquationOfState, PolySize>
		(
			eofs,
			Y2*pt2.Hf_ - Y1 * pt1.Hf_,
			Y2*pt2.Sf_ - Y1 * pt1.Sf_,
			Y2*pt2.CpCoeffs_ - Y1 * pt1.CpCoeffs_,
			Y2*pt2.hCoeffs_ - Y1 * pt1.hCoeffs_,
			Y2*pt2.sCoeffs_ - Y1 * pt1.sCoeffs_
			);
}


// ************************************************************************* //

#include <IOstreams.hxx>
#include <dictionary.hxx>
#include <thermodynamicConstants.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class EquationOfState, int PolySize>
tnbLib::hPolynomialThermo<EquationOfState, PolySize>::hPolynomialThermo
(
	const dictionary& dict
)
	:
	EquationOfState(dict),
	Hf_(readScalar(dict.subDict("thermodynamics").lookup("Hf"))),
	Sf_(readScalar(dict.subDict("thermodynamics").lookup("Sf"))),
	CpCoeffs_
	(
		dict.subDict("thermodynamics").lookup
		(
			"CpCoeffs<" + tnbLib::name(PolySize) + '>'
		)
	),
	hCoeffs_(),
	sCoeffs_()
{
	hCoeffs_ = CpCoeffs_.integral();
	sCoeffs_ = CpCoeffs_.integralMinus1();

	// Offset h poly so that it is relative to the enthalpy at Tstd
	hCoeffs_[0] += Hf_ - hCoeffs_.value(constant::thermodynamic::Tstd);

	// Offset s poly so that it is relative to the entropy at Tstd
	sCoeffs_[0] += Sf_ - sCoeffs_.value(constant::thermodynamic::Tstd);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class EquationOfState, int PolySize>
void tnbLib::hPolynomialThermo<EquationOfState, PolySize>::write
(
	Ostream& os
) const
{
	EquationOfState::write(os);

	dictionary dict("thermodynamics");
	dict.add("Hf", Hf_);
	dict.add("Sf", Sf_);
	dict.add
	(
		word("CpCoeffs<" + tnbLib::name(PolySize) + '>'),
		CpCoeffs_
	);
	os << indent << dict.dictName() << dict;
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

template<class EquationOfState, int PolySize>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const hPolynomialThermo<EquationOfState, PolySize>& pt
	)
{
	pt.write(os);
	return os;
}


// ************************************************************************* //