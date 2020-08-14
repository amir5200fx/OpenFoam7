#pragma once
#include <dictionary.hxx>  // added by amir
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::MichaelisMentenReactionRate::MichaelisMentenReactionRate
(
	const speciesTable& st,
	const dictionary& dict
)
	:
	species_(st),
	Vmax_(readScalar(dict.lookup("Vmax"))),
	Km_(readScalar(dict.lookup("Km"))),
	s_(st[dict.lookup("S")])
{
	beta_.append(Tuple2<label, scalar>(s_, 1.0));
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::scalar tnbLib::MichaelisMentenReactionRate::operator()
(
	const scalar p,
	const scalar T,
	const scalarField& c
	) const
{
	return Vmax_ / (Km_ + c[s_]);
}


inline tnbLib::scalar tnbLib::MichaelisMentenReactionRate::ddT
(
	const scalar p,
	const scalar T,
	const scalarField& c
) const
{
	return 0;
}


inline const tnbLib::List<tnbLib::Tuple2<tnbLib::label, tnbLib::scalar>>&
tnbLib::MichaelisMentenReactionRate::beta() const
{
	return beta_;
}


inline void tnbLib::MichaelisMentenReactionRate::dcidc
(
	const scalar p,
	const scalar T,
	const scalarField& c,
	scalarField& dcidc
) const
{
	dcidc[0] = -1.0 / (Km_ + c[s_]);
}


inline tnbLib::scalar tnbLib::MichaelisMentenReactionRate::dcidT
(
	const scalar p,
	const scalar T,
	const scalarField& c
) const
{
	return 0;
}


inline void tnbLib::MichaelisMentenReactionRate::write(Ostream& os) const
{
	writeEntry(os, "Vmax", Vmax_);
	writeEntry(os, "Km", Km_);
	writeEntry(os, "S", species_[s_]);
}


inline tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const MichaelisMentenReactionRate& mmrr
	)
{
	mmrr.write(os);
	return os;
}


// ************************************************************************* //