#pragma once
#include <dictionary.hxx>  // added by amir
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::ArrheniusReactionRate::ArrheniusReactionRate
(
	const scalar A,
	const scalar beta,
	const scalar Ta
)
	:
	A_(A),
	beta_(beta),
	Ta_(Ta)
{}


inline tnbLib::ArrheniusReactionRate::ArrheniusReactionRate
(
	const speciesTable&,
	const dictionary& dict
)
	:
	A_(readScalar(dict.lookup("A"))),
	beta_(readScalar(dict.lookup("beta"))),
	Ta_(readScalar(dict.lookup("Ta")))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::scalar tnbLib::ArrheniusReactionRate::operator()
(
	const scalar p,
	const scalar T,
	const scalarField&
	) const
{
	scalar ak = A_;

	if (mag(beta_) > vSmall)
	{
		ak *= pow(T, beta_);
	}

	if (mag(Ta_) > vSmall)
	{
		ak *= exp(-Ta_ / T);
	}

	return ak;
}


inline tnbLib::scalar tnbLib::ArrheniusReactionRate::ddT
(
	const scalar p,
	const scalar T,
	const scalarField&
) const
{
	scalar ak = A_;

	if (mag(beta_) > vSmall)
	{
		ak *= pow(T, beta_);
	}

	if (mag(Ta_) > vSmall)
	{
		ak *= exp(-Ta_ / T);
	}

	return ak * (beta_ + Ta_ / T) / T;
}


inline const tnbLib::List<tnbLib::Tuple2<tnbLib::label, tnbLib::scalar>>&
tnbLib::ArrheniusReactionRate::beta() const
{
	return NullObjectRef<List<Tuple2<label, scalar>>>();
}


inline void tnbLib::ArrheniusReactionRate::dcidc
(
	const scalar p,
	const scalar T,
	const scalarField& c,
	scalarField& dcidc
) const
{}


inline tnbLib::scalar tnbLib::ArrheniusReactionRate::dcidT
(
	const scalar p,
	const scalar T,
	const scalarField& c
) const
{
	return 0;
}


inline void tnbLib::ArrheniusReactionRate::write(Ostream& os) const
{
	writeEntry(os, "A", A_);
	writeEntry(os, "beta", beta_);
	writeEntry(os, "Ta", Ta_);
}


inline tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const ArrheniusReactionRate& arr
	)
{
	arr.write(os);
	return os;
}


// ************************************************************************* //