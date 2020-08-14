#pragma once
#include <Tuple2.hxx>
#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::LangmuirHinshelwoodReactionRate::LangmuirHinshelwoodReactionRate
(
	const speciesTable& st,
	const dictionary& dict
)
	:
	reactantNames_(dict.lookup("reactants")),
	a_(dict.lookupOrDefault<scalar>("a", 1)),
	A_(dict.lookup("A")),
	Ta_(dict.lookup("Ta")),
	beta_
	(
		dict.lookupOrDefault<FixedList<scalar, 3>>
		(
			"beta",
			FixedList<scalar, 3>({ 0, 0, 0 })
			)
	),
	m_
	(
		dict.lookupOrDefault<FixedList<scalar, 3>>
		(
			"m",
			FixedList<scalar, 3>({ 1, 1, 2 })
			)
	)
{
	forAll(reactantNames_, i)
	{
		r_[i] = st[reactantNames_[i]];
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::scalar tnbLib::LangmuirHinshelwoodReactionRate::operator()
(
	const scalar p,
	const scalar T,
	const scalarField& c
	) const
{
	const scalar c0m = pow(c[r_[0]], m_[0]);
	const scalar c1m = pow(c[r_[1]], m_[1]);

	const scalar TaByT0 = Ta_[0] / T;
	const scalar TaByT1 = Ta_[1] / T;
	const scalar TaByT2 = Ta_[2] / T;

	const scalar k0 = A_[0] * pow(T, beta_[0])*exp(-TaByT0);
	const scalar k1 = A_[1] * pow(T, beta_[1])*exp(-TaByT1);
	const scalar k2 = A_[2] * pow(T, beta_[2])*exp(-TaByT2);

	return k0 / pow(a_ + k1 * c0m + k2 * c1m, m_[2]);
}


inline tnbLib::scalar tnbLib::LangmuirHinshelwoodReactionRate::ddT
(
	const scalar p,
	const scalar T,
	const scalarField& c
) const
{
	const scalar c0m = pow(c[r_[0]], m_[0]);
	const scalar c1m = pow(c[r_[1]], m_[1]);

	const scalar TaByT0 = Ta_[0] / T;
	const scalar TaByT1 = Ta_[1] / T;
	const scalar TaByT2 = Ta_[2] / T;

	const scalar k0 = A_[0] * pow(T, beta_[0])*exp(-TaByT0);
	const scalar k1 = A_[1] * pow(T, beta_[1])*exp(-TaByT1);
	const scalar k2 = A_[2] * pow(T, beta_[2])*exp(-TaByT2);

	return
		(
		(beta_[0] + TaByT0)*k0
			- m_[2] * k0*((beta_[1] + TaByT1)*k1*c0m + (beta_[2] + TaByT2)*k2*c1m)
			/ (a_ + k1 * c0m + k2 * c1m)
			) / (pow(a_ + k1 * c0m + k2 * c1m, m_[2])*T);
}


inline const tnbLib::List<tnbLib::Tuple2<tnbLib::label, tnbLib::scalar>>&
tnbLib::LangmuirHinshelwoodReactionRate::beta() const
{
	return NullObjectRef<List<Tuple2<label, scalar>>>();
}


inline void tnbLib::LangmuirHinshelwoodReactionRate::dcidc
(
	const scalar p,
	const scalar T,
	const scalarField& c,
	scalarField& dcidc
) const
{}


inline tnbLib::scalar tnbLib::LangmuirHinshelwoodReactionRate::dcidT
(
	const scalar p,
	const scalar T,
	const scalarField& c
) const
{
	return 0;
}


inline void tnbLib::LangmuirHinshelwoodReactionRate::write(Ostream& os) const
{
	writeEntry(os, "reactants", reactantNames_);
	writeEntry(os, "a", a_);
	writeEntry(os, "A", A_);
	writeEntry(os, "Ta", Ta_);
	writeEntry(os, "beta", beta_);
	writeEntry(os, "m", m_);
}


inline tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const LangmuirHinshelwoodReactionRate& lhrr
	)
{
	lhrr.write(os);
	return os;
}


// ************************************************************************* //