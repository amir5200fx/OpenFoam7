#include <ReactionProxy.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ReactionThermo>
tnbLib::ReactionProxy<ReactionThermo>::ReactionProxy
(
	const speciesTable& species,
	const List<specieCoeffs>& lhs,
	const List<specieCoeffs>& rhs,
	const HashPtrTable<ReactionThermo>& thermoDatabase
)
	:
	Reaction<ReactionThermo>
	(
		species,
		lhs,
		rhs,
		thermoDatabase
		)
{}


template<class ReactionThermo>
tnbLib::ReactionProxy<ReactionThermo>::ReactionProxy
(
	const Reaction<ReactionThermo>& r,
	const speciesTable& species
)
	:
	Reaction<ReactionThermo>
	(
		r,
		species
		)
{}


template<class ReactionThermo>
tnbLib::ReactionProxy<ReactionThermo>::ReactionProxy
(
	const speciesTable& species,
	const HashPtrTable<ReactionThermo>& thermoDatabase,
	const dictionary& dict
)
	:
	Reaction<ReactionThermo>
	(
		species,
		thermoDatabase,
		dict
		)
{}


template<class ReactionThermo>
tnbLib::autoPtr<tnbLib::Reaction<ReactionThermo>>
tnbLib::ReactionProxy<ReactionThermo>::clone() const
{
	NotImplemented;
	return autoPtr<tnbLib::Reaction<ReactionThermo>>();
}


template<class ReactionThermo>
tnbLib::autoPtr<tnbLib::Reaction<ReactionThermo>>
tnbLib::ReactionProxy<ReactionThermo>::clone
(
	const speciesTable& species
) const
{
	NotImplemented;
	return autoPtr<Reaction<ReactionThermo>>();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class ReactionThermo>
tnbLib::scalar tnbLib::ReactionProxy<ReactionThermo>::kf
(
	const scalar p,
	const scalar T,
	const scalarField& c
) const
{
	NotImplemented;
	return 0;
}


template<class ReactionThermo>
tnbLib::scalar tnbLib::ReactionProxy<ReactionThermo>::kr
(
	const scalar kfwd,
	const scalar p,
	const scalar T,
	const scalarField& c
) const
{
	NotImplemented;
	return 0;
}


template<class ReactionThermo>
tnbLib::scalar tnbLib::ReactionProxy<ReactionThermo>::kr
(
	const scalar p,
	const scalar T,
	const scalarField& c
) const
{
	NotImplemented;
	return 0;
}


template<class ReactionThermo>
tnbLib::scalar tnbLib::ReactionProxy<ReactionThermo>::dkfdT
(
	const scalar p,
	const scalar T,
	const scalarField& c
) const
{
	NotImplemented;
	return 0;
}


template<class ReactionThermo>
tnbLib::scalar tnbLib::ReactionProxy<ReactionThermo>::dkrdT
(
	const scalar p,
	const scalar T,
	const scalarField& c,
	const scalar dkfdT,
	const scalar kr
) const
{
	NotImplemented;
	return 0;
}


template<class ReactionThermo>
const tnbLib::List<tnbLib::Tuple2<tnbLib::label, tnbLib::scalar>>&
tnbLib::ReactionProxy<ReactionThermo>::beta() const
{
	NotImplemented;
	return NullObjectRef<List<Tuple2<label, scalar>>>();
}


template<class ReactionThermo>
void tnbLib::ReactionProxy<ReactionThermo>::dcidc
(
	const scalar p,
	const scalar T,
	const scalarField& c,
	scalarField& dcidc
) const
{
	NotImplemented;
}


template<class ReactionThermo>
tnbLib::scalar tnbLib::ReactionProxy<ReactionThermo>::dcidT
(
	const scalar p,
	const scalar T,
	const scalarField& c
) const
{
	NotImplemented;
	return 0;
}


// ************************************************************************* //