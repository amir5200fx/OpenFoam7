#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <EDC.hxx>

#include <makeCombustionTypes.hxx>

#include <psiReactionThermo.hxx>
#include <rhoReactionThermo.hxx>



// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	makeCombustionTypes(EDC, psiReactionThermo);
	makeCombustionTypes(EDC, rhoReactionThermo);

}

// ************************************************************************* //