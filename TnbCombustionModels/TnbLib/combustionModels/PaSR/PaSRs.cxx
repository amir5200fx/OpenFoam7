#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <PaSR.hxx>

#include <makeCombustionTypes.hxx>

#include <psiReactionThermo.hxx>
#include <rhoReactionThermo.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	makeCombustionTypes(PaSR, psiReactionThermo);
	makeCombustionTypes(PaSR, rhoReactionThermo);

}

// ************************************************************************* //