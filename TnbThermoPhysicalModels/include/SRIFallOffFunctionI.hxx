#pragma once
#include <dictionary.hxx>  // added by amir
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::SRIFallOffFunction::SRIFallOffFunction
(
	const scalar a,
	const scalar b,
	const scalar c,
	const scalar d,
	const scalar e
)
	:
	a_(a),
	b_(b),
	c_(c),
	d_(d),
	e_(e)
{}


inline tnbLib::SRIFallOffFunction::SRIFallOffFunction(const dictionary& dict)
	:
	a_(readScalar(dict.lookup("a"))),
	b_(readScalar(dict.lookup("b"))),
	c_(readScalar(dict.lookup("c"))),
	d_(readScalar(dict.lookup("d"))),
	e_(readScalar(dict.lookup("e")))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::scalar tnbLib::SRIFallOffFunction::operator()
(
	const scalar T,
	const scalar Pr
	) const
{
	scalar X = 1.0 / (1 + sqr(log10(max(Pr, small))));
	return d_ * pow(a_*exp(-b_ / T) + exp(-T / c_), X)*pow(T, e_);
}


inline tnbLib::scalar tnbLib::SRIFallOffFunction::ddT
(
	const scalar Pr,
	const scalar F,
	const scalar dPrdT,
	const scalar T
) const
{
	scalar X = 1.0 / (1 + sqr(log10(max(Pr, small))));
	scalar dXdPr = -X * X * 2 * log10(Pr) / Pr / log(10.0);
	return
		F
		* (
			e_ / T
			+ X
			* (a_*b_*exp(-b_ / T) / sqr(T) - exp(-T / c_) / c_)
			/ (a_*exp(-b_ / T) + exp(-T / c_))
			+ dXdPr * dPrdT*log(a_*exp(-b_ / T) + exp(-T / c_))
			);
}


inline tnbLib::scalar tnbLib::SRIFallOffFunction::ddc
(
	const scalar Pr,
	const scalar F,
	const scalar dPrdc,
	const scalar T
) const
{
	scalar X = 1.0 / (1 + sqr(log10(max(Pr, small))));
	scalar dXdPr = -X * X * 2 * log10(Pr) / Pr / log(10.0);
	scalar dXdc = dXdPr * dPrdc;
	return F * dXdc*log(a_*exp(-b_ / T) + exp(-T / c_));
}


inline void tnbLib::SRIFallOffFunction::write(Ostream& os) const
{
	writeEntry(os, "a", a_);
	writeEntry(os, "b", b_);
	writeEntry(os, "c", c_);
	writeEntry(os, "d", d_);
	writeEntry(os, "e", e_);
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

inline tnbLib::Ostream& tnbLib::operator<<
(
	tnbLib::Ostream& os,
	const tnbLib::SRIFallOffFunction& srifof
	)
{
	srifof.write(os);
	return os;
}


// ************************************************************************* //