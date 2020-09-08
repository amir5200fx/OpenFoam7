#pragma once
#include <dictionary.hxx>  // added by amir
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::solidArrheniusReactionRate::solidArrheniusReactionRate
(
	const scalar A,
	const scalar Ta,
	const scalar Tcrit
	// const scalar nReact
)
	:
	A_(A),
	Ta_(Ta),
	Tcrit_(Tcrit)
{}


inline tnbLib::solidArrheniusReactionRate::solidArrheniusReactionRate
(
	const speciesTable&,
	const dictionary& dict
)
	:
	A_(readScalar(dict.lookup("A"))),
	Ta_(readScalar(dict.lookup("Ta"))),
	Tcrit_(readScalar(dict.lookup("Tcrit")))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::scalar tnbLib::solidArrheniusReactionRate::operator()
(
	const scalar,
	const scalar T,
	const scalarField&
	) const
{
	if (T < Tcrit_)
	{
		return 0;
	}
	else
	{
		return A_ * exp(-Ta_ / T);
	}
}


inline tnbLib::scalar tnbLib::solidArrheniusReactionRate::ddT
(
	const scalar p,
	const scalar T,
	const scalarField&
) const
{
	if (T < Tcrit_)
	{
		return 0;
	}
	else
	{
		return A_ * exp(-Ta_ / T)*Ta_ / sqr(T);
	}
}


inline const tnbLib::List<tnbLib::Tuple2<tnbLib::label, tnbLib::scalar>>&
tnbLib::solidArrheniusReactionRate::beta() const
{
	return NullObjectRef<List<Tuple2<label, scalar>>>();
}


inline void tnbLib::solidArrheniusReactionRate::dcidc
(
	const scalar p,
	const scalar T,
	const scalarField& c,
	scalarField& dcidc
) const
{}


inline tnbLib::scalar tnbLib::solidArrheniusReactionRate::dcidT
(
	const scalar p,
	const scalar T,
	const scalarField& c
) const
{
	return 0;
}


inline void tnbLib::solidArrheniusReactionRate::write(Ostream& os) const
{
	writeEntry(os, "A", A_);
	writeEntry(os, "Ta", Ta_);
	writeEntry(os, "Tcrit", Tcrit_);
}


inline tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const solidArrheniusReactionRate& arr
	)
{
	arr.write(os);
	return os;
}


// ************************************************************************* //