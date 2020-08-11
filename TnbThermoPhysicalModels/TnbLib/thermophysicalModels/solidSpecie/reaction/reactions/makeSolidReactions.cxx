#include <makeSolidReaction.hxx>

#include <solidArrheniusReactionRate.hxx>
#include <solidThermoPhysicsTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * Make Solid reactions  * * * * * * * * * * * * //

	makeSolidIRReactions(hConstSolidThermoPhysics, solidArrheniusReactionRate)

		makeSolidIRReactions
		(
			hPowerSolidThermoPhysics,
			solidArrheniusReactionRate
		)

		makeSolidIRReactions
		(
			hExpKappaConstSolidThermoPhysics,
			solidArrheniusReactionRate
		)

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //