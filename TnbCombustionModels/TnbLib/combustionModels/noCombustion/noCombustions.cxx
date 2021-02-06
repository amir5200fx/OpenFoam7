#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <noCombustion.hxx>

#include <makeCombustionTypes.hxx>

#include <psiReactionThermo.hxx>
#include <rhoReactionThermo.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	makeCombustionTypes(noCombustion, psiReactionThermo);
	makeCombustionTypes(noCombustion, rhoReactionThermo);

}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //