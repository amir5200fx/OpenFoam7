#pragma once
#include <dictionary.hxx>  // added by amir
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::JanevReactionRate::JanevReactionRate
(
	const scalar A,
	const scalar beta,
	const scalar Ta,
	const FixedList<scalar, nb_> b
)
	:
	A_(A),
	beta_(beta),
	Ta_(Ta),
	b_(b)
{}


inline tnbLib::JanevReactionRate::JanevReactionRate
(
	const speciesTable&,
	const dictionary& dict
)
	:
	A_(readScalar(dict.lookup("A"))),
	beta_(readScalar(dict.lookup("beta"))),
	Ta_(readScalar(dict.lookup("Ta"))),
	b_(dict.lookup("b"))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::scalar tnbLib::JanevReactionRate::operator()
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

	if (mag(Ta_) > vSmall)
	{
		expArg -= Ta_ / T;
	}

	scalar lnT = log(T);

	for (int n = 0; n < nb_; n++)
	{
		expArg += b_[n] * pow(lnT, n);
	}

	lta *= exp(expArg);

	return lta;
}


inline tnbLib::scalar tnbLib::JanevReactionRate::ddT
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

	if (mag(Ta_) > vSmall)
	{
		expArg -= Ta_ / T;
	}

	scalar lnT = log(T);

	for (int n = 0; n < nb_; n++)
	{
		expArg += b_[n] * pow(lnT, n);
	}

	scalar deriv = b_[1];

	for (int n = 2; n < nb_; n++)
	{
		deriv += n * b_[n] * pow(lnT, n - 1);
	}

	lta *= exp(expArg);

	return lta * (beta_ + Ta_ / T + deriv) / T;
}


inline const tnbLib::List<tnbLib::Tuple2<tnbLib::label, tnbLib::scalar>>&
tnbLib::JanevReactionRate::beta() const
{
	return NullObjectRef<List<Tuple2<label, scalar>>>();
}


inline void tnbLib::JanevReactionRate::dcidc
(
	const scalar p,
	const scalar T,
	const scalarField& c,
	scalarField& dcidc
) const
{}


inline tnbLib::scalar tnbLib::JanevReactionRate::dcidT
(
	const scalar p,
	const scalar T,
	const scalarField& c
) const
{
	return 0;
}


inline void tnbLib::JanevReactionRate::write(Ostream& os) const
{
	os.writeKeyword("A") << A_ << nl;
	os.writeKeyword("beta") << beta_ << nl;
	os.writeKeyword("Ta") << Ta_ << nl;
	os.writeKeyword("b") << b_ << nl;
}


inline tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const JanevReactionRate& jrr
	)
{
	jrr.write(os);
	return os;
}


// ************************************************************************* //