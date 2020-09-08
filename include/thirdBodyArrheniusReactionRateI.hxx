#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::thirdBodyArrheniusReactionRate::thirdBodyArrheniusReactionRate
(
	const scalar A,
	const scalar beta,
	const scalar Ta,
	const thirdBodyEfficiencies& tbes
)
	:
	ArrheniusReactionRate(A, beta, Ta),
	thirdBodyEfficiencies_(tbes)
{
	forAll(tbes, i)
	{
		beta_.append(Tuple2<label, scalar>(i, tbes[i]));
	}
}


inline tnbLib::thirdBodyArrheniusReactionRate::thirdBodyArrheniusReactionRate
(
	const speciesTable& species,
	const dictionary& dict
)
	:
	ArrheniusReactionRate
	(
		species,
		dict
	),
	thirdBodyEfficiencies_(species, dict)
{
	forAll(thirdBodyEfficiencies_, i)
	{
		beta_.append
		(
			Tuple2<label, scalar>
			(
				i,
				thirdBodyEfficiencies_[i]
				)
		);
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::scalar tnbLib::thirdBodyArrheniusReactionRate::operator()
(
	const scalar p,
	const scalar T,
	const scalarField& c
	) const
{
	return
		thirdBodyEfficiencies_.M(c)
		*ArrheniusReactionRate::operator()(p, T, c);
}


inline tnbLib::scalar tnbLib::thirdBodyArrheniusReactionRate::ddT
(
	const scalar p,
	const scalar T,
	const scalarField& c
) const
{
	return
		thirdBodyEfficiencies_.M(c)
		*ArrheniusReactionRate::ddT(p, T, c);
}


inline void tnbLib::thirdBodyArrheniusReactionRate::dcidc
(
	const scalar p,
	const scalar T,
	const scalarField& c,
	scalarField& dcidc
) const
{
	scalar M = thirdBodyEfficiencies_.M(c);
	forAll(beta_, i)
	{
		dcidc[i] = beta_[i].second() / max(M, small);
	}
}


inline tnbLib::scalar tnbLib::thirdBodyArrheniusReactionRate::dcidT
(
	const scalar p,
	const scalar T,
	const scalarField& c
) const
{
	return -1.0 / T;
}


inline void tnbLib::thirdBodyArrheniusReactionRate::write(Ostream& os) const
{
	ArrheniusReactionRate::write(os);
	thirdBodyEfficiencies_.write(os);
}


inline tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const thirdBodyArrheniusReactionRate& arr
	)
{
	arr.write(os);
	return os;
}


// ************************************************************************* //