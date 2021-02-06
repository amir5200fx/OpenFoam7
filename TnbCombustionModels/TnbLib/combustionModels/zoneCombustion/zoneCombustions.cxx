#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <zoneCombustion.hxx>

#include <makeCombustionTypes.hxx>

#include <psiReactionThermo.hxx>
#include <rhoReactionThermo.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	makeCombustionTypes(zoneCombustion, psiReactionThermo);
	makeCombustionTypes(zoneCombustion, rhoReactionThermo);

}

// ************************************************************************* //