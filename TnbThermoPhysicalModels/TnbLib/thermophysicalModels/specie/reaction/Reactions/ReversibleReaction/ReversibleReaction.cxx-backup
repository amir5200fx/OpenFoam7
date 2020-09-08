#include <ReversibleReaction.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template
<
	template<class> class ReactionType,
	class ReactionThermo,
	class ReactionRate
>
tnbLib::ReversibleReaction<ReactionType, ReactionThermo, ReactionRate>::
ReversibleReaction
(
	const ReactionType<ReactionThermo>& reaction,
	const ReactionRate& k
)
	:
	ReactionType<ReactionThermo>(reaction),
	k_(k)
{}


template
<
	template<class> class ReactionType,
	class ReactionThermo,
	class ReactionRate
>
tnbLib::ReversibleReaction<ReactionType, ReactionThermo, ReactionRate>::
ReversibleReaction
(
	const speciesTable& species,
	const HashPtrTable<ReactionThermo>& thermoDatabase,
	const dictionary& dict
)
	:
	ReactionType<ReactionThermo>(species, thermoDatabase, dict),
	k_(species, dict)
{}


template
<
	template<class> class ReactionType,
	class ReactionThermo,
	class ReactionRate
>
tnbLib::ReversibleReaction<ReactionType, ReactionThermo, ReactionRate>::
ReversibleReaction
(
	const ReversibleReaction<ReactionType, ReactionThermo, ReactionRate>& rr,
	const speciesTable& species
)
	:
	ReactionType<ReactionThermo>(rr, species),
	k_(rr.k_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template
<
	template<class> class ReactionType,
	class ReactionThermo,
	class ReactionRate
>
tnbLib::scalar tnbLib::ReversibleReaction
<
	ReactionType,
	ReactionThermo,
	ReactionRate
>::kf
(
	const scalar p,
	const scalar T,
	const scalarField& c
) const
{
	return k_(p, T, c);
}


template
<
	template<class> class ReactionType,
	class ReactionThermo,
	class ReactionRate
>
tnbLib::scalar tnbLib::ReversibleReaction
<
	ReactionType,
	ReactionThermo,
	ReactionRate
>::kr
(
	const scalar kfwd,
	const scalar p,
	const scalar T,
	const scalarField& c
) const
{
	return kfwd / max(this->Kc(p, T), rootSmall);
}


template
<
	template<class> class ReactionType,
	class ReactionThermo,
	class ReactionRate
>
tnbLib::scalar tnbLib::ReversibleReaction
<
	ReactionType,
	ReactionThermo,
	ReactionRate
>::kr
(
	const scalar p,
	const scalar T,
	const scalarField& c
) const
{
	return kr(kf(p, T, c), p, T, c);
}


template
<
	template<class> class ReactionType,
	class ReactionThermo,
	class ReactionRate
>
tnbLib::scalar tnbLib::ReversibleReaction
<
	ReactionType,
	ReactionThermo,
	ReactionRate
>::dkfdT
(
	const scalar p,
	const scalar T,
	const scalarField& c
) const
{
	return k_.ddT(p, T, c);
}


template
<
	template<class> class ReactionType,
	class ReactionThermo,
	class ReactionRate
>
tnbLib::scalar tnbLib::ReversibleReaction
<
	ReactionType,
	ReactionThermo,
	ReactionRate
>::dkrdT
(
	const scalar p,
	const scalar T,
	const scalarField& c,
	const scalar dkfdT,
	const scalar kr
) const
{
	scalar Kc = max(this->Kc(p, T), rootSmall);

	return dkfdT / Kc - kr * this->dKcdTbyKc(p, T);
}


template
<
	template<class> class ReactionType,
	class ReactionThermo,
	class ReactionRate
>
const tnbLib::List<tnbLib::Tuple2<tnbLib::label, tnbLib::scalar>>&
tnbLib::ReversibleReaction
<
	ReactionType,
	ReactionThermo,
	ReactionRate
>::beta() const
{
	return k_.beta();
}


template
<
	template<class> class ReactionType,
	class ReactionThermo,
	class ReactionRate
>
void tnbLib::ReversibleReaction
<
	ReactionType,
	ReactionThermo,
	ReactionRate
>::dcidc
(
	const scalar p,
	const scalar T,
	const scalarField& c,
	scalarField& dcidc
) const
{
	k_.dcidc(p, T, c, dcidc);
}


template
<
	template<class> class ReactionType,
	class ReactionThermo,
	class ReactionRate
>
tnbLib::scalar tnbLib::ReversibleReaction
<
	ReactionType,
	ReactionThermo,
	ReactionRate
>::dcidT
(
	const scalar p,
	const scalar T,
	const scalarField& c
) const
{
	return k_.dcidT(p, T, c);
}


template
<
	template<class> class ReactionType,
	class ReactionThermo,
	class ReactionRate
>
void tnbLib::ReversibleReaction
<
	ReactionType,
	ReactionThermo,
	ReactionRate
>::write
(
	Ostream& os
) const
{
	Reaction<ReactionThermo>::write(os);
	k_.write(os);
}


// ************************************************************************* //