#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <laminarTemplate.hxx>

#include <makeCombustionTypes.hxx>

#include <psiReactionThermo.hxx>
#include <rhoReactionThermo.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	makeCombustionTypes(laminar, psiReactionThermo);
	makeCombustionTypes(laminar, rhoReactionThermo);

}

// ************************************************************************* //