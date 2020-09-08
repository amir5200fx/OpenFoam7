#include <SolidReaction.hxx>

#include <DynamicList.hxx>
#include <OStringStream.hxx>  // added by amir
#include <IStringStream.hxx>  // added by amir
#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ReactionThermo>
tnbLib::SolidReaction<ReactionThermo>::SolidReaction
(
	const Reaction<ReactionThermo>& reaction,
	const speciesTable& pyrolisisGases,
	const List<specieCoeffs>& glhs,
	const List<specieCoeffs>& grhs
)
	:
	Reaction<ReactionThermo>(reaction),
	pyrolisisGases_(pyrolisisGases),
	glhs_(glhs),
	grhs_(grhs)
{}


template<class ReactionThermo>
tnbLib::SolidReaction<ReactionThermo>::SolidReaction
(
	const SolidReaction<ReactionThermo>& r,
	const speciesTable& pyrolisisGases
)
	:
	Reaction<ReactionThermo>(r),
	pyrolisisGases_(pyrolisisGases),
	glhs_(r.glhs_),
	grhs_(r.grhs_)
{}


template<class ReactionThermo>
tnbLib::SolidReaction<ReactionThermo>::SolidReaction
(
	const speciesTable& species,
	const HashPtrTable<ReactionThermo>& thermoDatabase,
	const dictionary& dict
)
	:
	Reaction<ReactionThermo>(species, thermoDatabase, dict),
	pyrolisisGases_(dict.parent().parent().lookup("gaseousSpecies")),
	glhs_(),
	grhs_()
{
	specieCoeffs::setLRhs
	(
		IStringStream(dict.lookup("reaction"))(),
		pyrolisisGases_,
		glhs_,
		grhs_
	);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class ReactionThermo>
const tnbLib::List<tnbLib::specieCoeffs>&
tnbLib::SolidReaction<ReactionThermo>::glhs() const
{
	return glhs_;
}


template<class ReactionThermo>
const tnbLib::List<tnbLib::specieCoeffs>&
tnbLib::SolidReaction<ReactionThermo>::grhs() const
{
	return grhs_;
}


template<class ReactionThermo>
const tnbLib::speciesTable& tnbLib::SolidReaction<ReactionThermo>::
gasSpecies() const
{
	return pyrolisisGases_;
}


template<class ReactionThermo>
void tnbLib::SolidReaction<ReactionThermo>::write(Ostream& os) const
{
	OStringStream reaction;
	writeEntry(os, "reaction", solidReactionStr(reaction));
}


template<class ReactionThermo>
tnbLib::string tnbLib::SolidReaction<ReactionThermo>::solidReactionStr
(
	OStringStream& reaction
) const
{
	specieCoeffs::reactionStr(reaction, this->species(), this->lhs());
	if (glhs().size() > 0)
	{
		reaction << " + ";
		solidReactionStrLeft(reaction);
	}
	reaction << " = ";
	specieCoeffs::reactionStr(reaction, this->species(), this->rhs());
	if (grhs().size() > 0)
	{
		reaction << " + ";
		solidReactionStrRight(reaction);
	}
	return reaction.str();

}


template<class ReactionThermo>
void tnbLib::SolidReaction<ReactionThermo>::solidReactionStrLeft
(
	OStringStream& reaction
) const
{
	for (label i = 0; i < glhs().size(); ++i)
	{
		if (i > 0)
		{
			reaction << " + ";
		}
		if (mag(glhs()[i].stoichCoeff - 1) > small)
		{
			reaction << glhs()[i].stoichCoeff;
		}
		reaction << gasSpecies()[glhs()[i].index];
		if (mag(glhs()[i].exponent - glhs()[i].stoichCoeff) > small)
		{
			reaction << "^" << glhs()[i].exponent;
		}
	}
}


template<class ReactionThermo>
void tnbLib::SolidReaction<ReactionThermo>::solidReactionStrRight
(
	OStringStream& reaction
) const
{

	for (label i = 0; i < grhs().size(); ++i)
	{
		if (i > 0)
		{
			reaction << " + ";
		}
		if (mag(grhs()[i].stoichCoeff - 1) > small)
		{
			reaction << grhs()[i].stoichCoeff;
		}
		reaction << gasSpecies()[grhs()[i].index];
		if (mag(grhs()[i].exponent - grhs()[i].stoichCoeff) > small)
		{
			reaction << "^" << grhs()[i].exponent;
		}
	}
}

// ************************************************************************* //