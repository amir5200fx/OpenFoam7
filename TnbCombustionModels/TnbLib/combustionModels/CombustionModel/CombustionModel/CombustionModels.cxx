#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <CombustionModelTemplate.hxx>

#include <makeCombustionTypes.hxx>

#include <rhoReactionThermo.hxx>
#include <psiReactionThermo.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	makeCombustion(psiReactionThermo);
	makeCombustion(rhoReactionThermo);

}

// ************************************************************************* //