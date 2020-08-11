#include <ReactionList.hxx>

#include <IFstream.hxx>
#include <SLPtrList.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ThermoType>
tnbLib::ReactionList<ThermoType>::ReactionList
(
	const speciesTable& species,
	const HashPtrTable<ThermoType>& thermoDb
)
	:
	SLPtrList<Reaction<ThermoType>>(),
	species_(species),
	thermoDb_(thermoDb),
	dict_(dictionary::null)
{}


template<class ThermoType>
tnbLib::ReactionList<ThermoType>::ReactionList
(
	const speciesTable& species,
	const HashPtrTable<ThermoType>& thermoDb,
	const dictionary& dict
)
	:
	SLPtrList<Reaction<ThermoType>>(),
	species_(species),
	thermoDb_(thermoDb),
	dict_(dict)
{
	readReactionDict();
}


template<class ThermoType>
tnbLib::ReactionList<ThermoType>::ReactionList(const ReactionList& reactions)
	:
	SLPtrList<Reaction<ThermoType>>(reactions),
	species_(reactions.species_),
	thermoDb_(reactions.thermoDb_),
	dict_(reactions.dict_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class ThermoType>
tnbLib::ReactionList<ThermoType>::~ReactionList()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class ThermoType>
bool tnbLib::ReactionList<ThermoType>::readReactionDict()
{
	const dictionary& reactions(dict_.subDict("reactions"));

	// Set general temperature limits from the dictionary
	Reaction<ThermoType>::TlowDefault =
		dict_.lookupOrDefault<scalar>("Tlow", 0);

	Reaction<ThermoType>::ThighDefault =
		dict_.lookupOrDefault<scalar>("Thigh", great);

	forAllConstIter(dictionary, reactions, iter)
	{
		const word reactionName = iter().keyword();

		this->append
		(
			Reaction<ThermoType>::New
			(
				species_,
				thermoDb_,
				reactions.subDict(reactionName)
			).ptr()
		);
	}

	return true;
}


template<class ThermoType>
void tnbLib::ReactionList<ThermoType>::write(Ostream& os) const
{
	os << "reactions" << nl;
	os << token::BEGIN_BLOCK << incrIndent << nl;

	forAllConstIter(typename SLPtrList<Reaction<ThermoType>>, *this, iter)
	{
		const Reaction<ThermoType>& r = iter();
		os << indent << r.name() << nl
			<< indent << token::BEGIN_BLOCK << incrIndent << nl;
		writeEntry(os, "type", r.type());
		r.write(os);
		os << decrIndent << indent << token::END_BLOCK << nl;
	}

	os << decrIndent << token::END_BLOCK << nl;
}


// ************************************************************************* //