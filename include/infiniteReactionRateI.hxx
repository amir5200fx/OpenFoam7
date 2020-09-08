#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::infiniteReactionRate::infiniteReactionRate()
{}


inline tnbLib::infiniteReactionRate::infiniteReactionRate
(
	const speciesTable&,
	const dictionary&
)
{}


inline void tnbLib::infiniteReactionRate::write(Ostream& os) const
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::scalar tnbLib::infiniteReactionRate::operator()
(
	const scalar p,
	const scalar,
	const scalarField&
	) const
{
	return (1);
}

inline tnbLib::scalar tnbLib::infiniteReactionRate::ddT
(
	const scalar p,
	const scalar,
	const scalarField&
) const
{
	return (0);
}


inline const tnbLib::List<tnbLib::Tuple2<tnbLib::label, tnbLib::scalar>>&
tnbLib::infiniteReactionRate::beta() const
{
	return NullObjectRef<List<Tuple2<label, scalar>>>();
}


inline void tnbLib::infiniteReactionRate::dcidc
(
	const scalar p,
	const scalar T,
	const scalarField& c,
	scalarField& dcidc
) const
{}


inline tnbLib::scalar tnbLib::infiniteReactionRate::dcidT
(
	const scalar p,
	const scalar T,
	const scalarField& c
) const
{
	return 0;
}


inline tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const infiniteReactionRate& rr
	)
{
	rr.write(os);
	return os;
}


// ************************************************************************* //