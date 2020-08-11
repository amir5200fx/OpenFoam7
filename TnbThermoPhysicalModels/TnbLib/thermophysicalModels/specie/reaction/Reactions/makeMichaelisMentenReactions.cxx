#include <makeReaction.hxx>

#include <reactionTypes.hxx>
#include <MichaelisMentenReactionRate.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeReaction
	(
		constFluidHThermoPhysics,
		IrreversibleReaction,
		MichaelisMentenReactionRate
	)

		makeReaction
		(
			constFluidEThermoPhysics,
			IrreversibleReaction,
			MichaelisMentenReactionRate
		)
}

// ************************************************************************* //