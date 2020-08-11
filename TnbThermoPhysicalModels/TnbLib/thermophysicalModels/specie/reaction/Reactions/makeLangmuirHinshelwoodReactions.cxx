#include <makeReaction.hxx>

#include <reactionTypes.hxx>
#include <LangmuirHinshelwoodReactionRate.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<>
const char* const tnbLib::Tuple2<tnbLib::word, tnbLib::scalar>::typeName
(
	"Tuple2<word,scalar>"
);

namespace tnbLib
{
	makeIRReactions(gasHThermoPhysics, LangmuirHinshelwoodReactionRate)
		makeIRReactions(icoPoly8HThermoPhysics, LangmuirHinshelwoodReactionRate)

		makeIRReactions(gasEThermoPhysics, LangmuirHinshelwoodReactionRate)
		makeIRReactions(icoPoly8EThermoPhysics, LangmuirHinshelwoodReactionRate)
}

// ************************************************************************* //