#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class ReactionRate, class ChemicallyActivationFunction>
inline tnbLib::ChemicallyActivatedReactionRate
<
	ReactionRate,
	ChemicallyActivationFunction
>::ChemicallyActivatedReactionRate
(
	const ReactionRate& k0,
	const ReactionRate& kInf,
	const ChemicallyActivationFunction& F,
	const thirdBodyEfficiencies& tbes
)
	:
	k0_(k0),
	kInf_(kInf),
	F_(F),
	thirdBodyEfficiencies_(tbes)
{
	forAll(tbes, i)
	{
		beta_.append(Tuple2<label, scalar>(i, tbes[i]));
	}
}


template<class ReactionRate, class ChemicallyActivationFunction>
inline tnbLib::ChemicallyActivatedReactionRate
<
	ReactionRate,
	ChemicallyActivationFunction
>::ChemicallyActivatedReactionRate
(
	const speciesTable& species,
	const dictionary& dict
)
	:
	k0_(species, dict),
	kInf_(species, dict),
	F_(dict),
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

template<class ReactionRate, class ChemicallyActivationFunction>
inline tnbLib::scalar tnbLib::ChemicallyActivatedReactionRate
<
	ReactionRate,
	ChemicallyActivationFunction
>::operator()
(
	const scalar p,
	const scalar T,
	const scalarField& c
	) const
{
	const scalar k0 = k0_(p, T, c);
	const scalar kInf = kInf_(p, T, c);
	const scalar Pr = k0 * thirdBodyEfficiencies_.M(c) / kInf;

	return k0 * (1 / (1 + Pr))*F_(T, Pr);
}


template<class ReactionRate, class ChemicallyActivationFunction>
inline tnbLib::scalar tnbLib::ChemicallyActivatedReactionRate
<
	ReactionRate,
	ChemicallyActivationFunction
>::ddT
(
	const scalar p,
	const scalar T,
	const scalarField& c
) const
{
	const scalar k0 = k0_(p, T, c);
	const scalar kInf = kInf_(p, T, c);
	const scalar Pr = k0 * thirdBodyEfficiencies_.M(c) / kInf;

	return (1 / (1 + Pr))*F_(T, Pr)*k0_.ddT(p, T, c);
}


template<class ReactionRate, class ChemicallyActivationFunction>
inline void tnbLib::ChemicallyActivatedReactionRate
<
	ReactionRate,
	ChemicallyActivationFunction
>::dcidc
(
	const scalar p,
	const scalar T,
	const scalarField& c,
	scalarField& dcidc
) const
{
	const scalar M = thirdBodyEfficiencies_.M(c);

	if (M > small)
	{
		const scalar k0 = k0_(p, T, c);
		const scalar kInf = kInf_(p, T, c);

		const scalar Pr = k0 * M / kInf;
		const scalar F = F_(T, Pr);

		forAll(beta_, i)
		{
			const scalar dPrdci = -beta_[i].second()*k0 / kInf;
			const scalar dFdci = F_.ddc(Pr, F, dPrdci, T);
			dcidc[i] = (-dPrdci / (1 + Pr) + dFdci / F);
		}
	}
	else
	{
		forAll(beta_, i)
		{
			dcidc[i] = 0;
		}
	}
}


template<class ReactionRate, class ChemicallyActivationFunction>
inline tnbLib::scalar tnbLib::ChemicallyActivatedReactionRate
<
	ReactionRate,
	ChemicallyActivationFunction
>::dcidT
(
	const scalar p,
	const scalar T,
	const scalarField& c
) const
{
	const scalar M = thirdBodyEfficiencies_.M(c);

	if (M > small)
	{
		const scalar k0 = k0_(p, T, c);
		const scalar kInf = kInf_(p, T, c);

		const scalar Pr = k0 * thirdBodyEfficiencies_.M(c) / kInf;
		const scalar F = F_(T, Pr);
		const scalar dPrdT =
			Pr * (k0_.ddT(p, T, c) / k0 - kInf_.ddT(p, T, c) / kInf - 1 / T);
		const scalar dFdT = F_.ddT(Pr, F, dPrdT, T);

		return (-dPrdT / (1 + Pr) + dFdT / F);
	}
	else
	{
		return 0;
	}
}


template<class ReactionRate, class ChemicallyActivationFunction>
inline void tnbLib::ChemicallyActivatedReactionRate
<
	ReactionRate,
	ChemicallyActivationFunction
>::write(Ostream& os) const
{
	k0_.write(os);
	kInf_.write(os);
	F_.write(os);
	thirdBodyEfficiencies_.write(os);
}


template<class ReactionRate, class ChemicallyActivationFunction>
inline tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const ChemicallyActivatedReactionRate
	<ReactionRate, ChemicallyActivationFunction>& carr
	)
{
	carr.write(os);
	return os;
}


// ************************************************************************* //