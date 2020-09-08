#pragma once
#include <dictionary.hxx>  // added by amir
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::powerSeriesReactionRate::powerSeriesReactionRate
(
	const scalar A,
	const scalar beta,
	const scalar Ta,
	const FixedList<scalar, nCoeff_> coeffs
)
	:
	A_(A),
	beta_(beta),
	Ta_(Ta),
	coeffs_(coeffs)
{}


inline tnbLib::powerSeriesReactionRate::powerSeriesReactionRate
(
	const speciesTable&,
	const dictionary& dict
)
	:
	A_(readScalar(dict.lookup("A"))),
	beta_(readScalar(dict.lookup("beta"))),
	Ta_(readScalar(dict.lookup("Ta"))),
	coeffs_(dict.lookup("coeffs"))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::scalar tnbLib::powerSeriesReactionRate::operator()
(
	const scalar p,
	const scalar T,
	const scalarField&
	) const
{
	scalar lta = A_;

	if (mag(beta_) > vSmall)
	{
		lta *= pow(T, beta_);
	}

	scalar expArg = 0;

	forAll(coeffs_, n)
	{
		expArg += coeffs_[n] / pow(T, n + 1);
	}

	lta *= exp(expArg);

	return lta;
}


inline tnbLib::scalar tnbLib::powerSeriesReactionRate::ddT
(
	const scalar p,
	const scalar T,
	const scalarField&
) const
{
	scalar lta = A_;

	if (mag(beta_) > vSmall)
	{
		lta *= pow(T, beta_);
	}

	scalar expArg = 0;
	scalar deriv = 0;

	forAll(coeffs_, n)
	{
		scalar cT = coeffs_[n] / pow(T, n + 1);
		expArg += cT;
		deriv -= (n + 1)*cT;
	}

	lta *= exp(expArg);

	return lta * (beta_ + deriv) / T;
}


inline const tnbLib::List<tnbLib::Tuple2<tnbLib::label, tnbLib::scalar>>&
tnbLib::powerSeriesReactionRate::beta() const
{
	return NullObjectRef<List<Tuple2<label, scalar>>>();
}


inline void tnbLib::powerSeriesReactionRate::dcidc
(
	const scalar p,
	const scalar T,
	const scalarField& c,
	scalarField& dcidc
) const
{}


inline tnbLib::scalar tnbLib::powerSeriesReactionRate::dcidT
(
	const scalar p,
	const scalar T,
	const scalarField& c
) const
{
	return 0;
}


inline void tnbLib::powerSeriesReactionRate::write(Ostream& os) const
{
	writeEntry(os, "A", A_);
	writeEntry(os, "beta", beta_);
	writeEntry(os, "Ta", Ta_);
	writeEntry(os, "coeffs", coeffs_);
}


inline tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const powerSeriesReactionRate& psrr
	)
{
	psrr.write(os);
	return os;
}


// ************************************************************************* //