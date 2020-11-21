#define FoamRegisterDebugSwitch_EXPORT_DEFINE

#include <reactionTypes.hxx>
#include <makeReaction.hxx>

#include <ArrheniusReactionRate.hxx>
#include <infiniteReactionRate.hxx>
#include <LandauTellerReactionRate.hxx>
#include <thirdBodyArrheniusReactionRate.hxx>

#include <ChemicallyActivatedReactionRate.hxx>
#include <JanevReactionRate.hxx>
#include <powerSeriesReactionRate.hxx>

#include <FallOffReactionRate.hxx>
#include <LindemannFallOffFunction.hxx>
#include <SRIFallOffFunction.hxx>
#include <TroeFallOffFunction.hxx>


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makeReactions(Thermo, Reaction)                                        \
                                                                               \
    defineTemplateTypeNameAndDebug(Reaction, 0);                               \
    defineTemplateRunTimeSelectionTable(Reaction, dictionary);                 \
                                                                               \
    makeIRNReactions(Thermo, ArrheniusReactionRate)                            \
    makeIRNReactions(Thermo, infiniteReactionRate)                             \
    makeIRNReactions(Thermo, LandauTellerReactionRate)                         \
    makeIRNReactions(Thermo, thirdBodyArrheniusReactionRate)                   \
                                                                               \
    makeIRReactions(Thermo, JanevReactionRate)                                 \
    makeIRReactions(Thermo, powerSeriesReactionRate)                           \
                                                                               \
    makePressureDependentReactions                                             \
    (                                                                          \
       Thermo,                                                                 \
       ArrheniusReactionRate,                                                  \
       LindemannFallOffFunction                                                \
    )                                                                          \
                                                                               \
    makePressureDependentReactions                                             \
    (                                                                          \
       Thermo,                                                                 \
       ArrheniusReactionRate,                                                  \
       TroeFallOffFunction                                                     \
    )                                                                          \
                                                                               \
    makePressureDependentReactions                                             \
    (                                                                          \
       Thermo,                                                                 \
       ArrheniusReactionRate,                                                  \
       SRIFallOffFunction                                                      \
    )


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	// sensible enthalpy based reactions
	makeReactions(constGasHThermoPhysics, constGasHReaction)
		makeReactions(gasHThermoPhysics, gasHReaction)
		makeReactions
		(
			constIncompressibleGasHThermoPhysics,
			constIncompressibleGasHReaction
		)
		makeReactions(incompressibleGasHThermoPhysics, incompressibleGasHReaction)
		makeReactions(icoPoly8HThermoPhysics, icoPoly8HReaction)
		makeReactions(constFluidHThermoPhysics, constFluidHReaction)
		makeReactions
		(
			constAdiabaticFluidHThermoPhysics,
			constAdiabaticFluidHReaction
		)
		makeReactions(constHThermoPhysics, constHReaction)

		makeReactions(constGasEThermoPhysics, constGasEReaction)
		makeReactions(gasEThermoPhysics, gasEReaction)
		makeReactions
		(
			constIncompressibleGasEThermoPhysics,
			constIncompressibleGasEReaction
		)
		makeReactions(incompressibleGasEThermoPhysics, incompressibleGasEReaction)
		makeReactions(icoPoly8EThermoPhysics, icoPoly8EReaction)
		makeReactions(constFluidEThermoPhysics, constFluidEReaction)
		makeReactions
		(
			constAdiabaticFluidEThermoPhysics,
			constAdiabaticFluidEReaction
		)
		makeReactions(constEThermoPhysics, constEReaction)
}

// ************************************************************************* //