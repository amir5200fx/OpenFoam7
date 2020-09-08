#include <IrreversibleReaction.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template
<
	template<class> class ReactionType,
	class ReactionThermo,
	class ReactionRate
>
tnbLib::IrreversibleReaction<ReactionType, ReactionThermo, ReactionRate>::
IrreversibleReaction
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
tnbLib::IrreversibleReaction<ReactionType, ReactionThermo, ReactionRate>::
IrreversibleReaction
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
tnbLib::IrreversibleReaction<ReactionType, ReactionThermo, ReactionRate>::
IrreversibleReaction
(
	const IrreversibleReaction<ReactionType, ReactionThermo, ReactionRate>& irr,
	const speciesTable& species
)
	:
	ReactionType<ReactionThermo>(irr, species),
	k_(irr.k_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template
<
	template<class> class ReactionType,
	class ReactionThermo,
	class ReactionRate
>
tnbLib::scalar tnbLib::IrreversibleReaction
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
tnbLib::scalar tnbLib::IrreversibleReaction
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
	return 0;
}


template
<
	template<class> class ReactionType,
	class ReactionThermo,
	class ReactionRate
>
tnbLib::scalar tnbLib::IrreversibleReaction
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
	return 0;
}


template
<
	template<class> class ReactionType,
	class ReactionThermo,
	class ReactionRate
>
tnbLib::scalar tnbLib::IrreversibleReaction
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
tnbLib::scalar tnbLib::IrreversibleReaction
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
	return 0;
}


template
<
	template<class> class ReactionType,
	class ReactionThermo,
	class ReactionRate
>
const tnbLib::List<tnbLib::Tuple2<tnbLib::label, tnbLib::scalar>>&
tnbLib::IrreversibleReaction
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
void tnbLib::IrreversibleReaction
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
tnbLib::scalar tnbLib::IrreversibleReaction
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
void tnbLib::IrreversibleReaction<ReactionType, ReactionThermo, ReactionRate>::
write
(
	Ostream& os
) const
{
	ReactionType<ReactionThermo>::write(os);
	k_.write(os);
}


// ************************************************************************* //