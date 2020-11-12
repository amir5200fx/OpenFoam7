#define FoamRegisterDebugSwitch_EXPORT_DEFINE

#include <makeChemistryReductionMethods.hxx>

#include <thermoPhysicsTypes.hxx>

#include <psiReactionThermo.hxx>
#include <rhoReactionThermo.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    // Chemistry solvers based on sensibleEnthalpy
    makeChemistryReductionMethods(psiReactionThermo, constGasHThermoPhysics);
    makeChemistryReductionMethods(psiReactionThermo, gasHThermoPhysics);
    makeChemistryReductionMethods
    (
        psiReactionThermo,
        constIncompressibleGasHThermoPhysics
    );
    makeChemistryReductionMethods
    (
        psiReactionThermo,
        incompressibleGasHThermoPhysics
    );
    makeChemistryReductionMethods(psiReactionThermo, icoPoly8HThermoPhysics);
    makeChemistryReductionMethods(psiReactionThermo, constFluidHThermoPhysics);
    makeChemistryReductionMethods
    (
        psiReactionThermo,
        constAdiabaticFluidHThermoPhysics
    );
    makeChemistryReductionMethods(psiReactionThermo, constHThermoPhysics);

    makeChemistryReductionMethods(rhoReactionThermo, constGasHThermoPhysics);
    makeChemistryReductionMethods(rhoReactionThermo, gasHThermoPhysics);
    makeChemistryReductionMethods
    (
        rhoReactionThermo,
        constIncompressibleGasHThermoPhysics
    );
    makeChemistryReductionMethods
    (
        rhoReactionThermo,
        incompressibleGasHThermoPhysics
    );
    makeChemistryReductionMethods(rhoReactionThermo, icoPoly8HThermoPhysics);
    makeChemistryReductionMethods(rhoReactionThermo, constFluidHThermoPhysics);
    makeChemistryReductionMethods
    (
        rhoReactionThermo,
        constAdiabaticFluidHThermoPhysics
    );
    makeChemistryReductionMethods(rhoReactionThermo, constHThermoPhysics);


    // Chemistry solvers based on sensibleInternalEnergy
    makeChemistryReductionMethods(psiReactionThermo, constGasEThermoPhysics);
    makeChemistryReductionMethods(psiReactionThermo, gasEThermoPhysics);
    makeChemistryReductionMethods
    (
        psiReactionThermo,
        constIncompressibleGasEThermoPhysics
    );
    makeChemistryReductionMethods
    (
        psiReactionThermo,
        incompressibleGasEThermoPhysics
    );
    makeChemistryReductionMethods(psiReactionThermo, icoPoly8EThermoPhysics);
    makeChemistryReductionMethods(psiReactionThermo, constFluidEThermoPhysics);
    makeChemistryReductionMethods
    (
        psiReactionThermo,
        constAdiabaticFluidEThermoPhysics
    );
    makeChemistryReductionMethods(psiReactionThermo, constEThermoPhysics);

    makeChemistryReductionMethods(rhoReactionThermo, constGasEThermoPhysics);
    makeChemistryReductionMethods(rhoReactionThermo, gasEThermoPhysics);
    makeChemistryReductionMethods
    (
        rhoReactionThermo,
        constIncompressibleGasEThermoPhysics
    );
    makeChemistryReductionMethods
    (
        rhoReactionThermo,
        incompressibleGasEThermoPhysics
    );
    makeChemistryReductionMethods(rhoReactionThermo, icoPoly8EThermoPhysics);
    makeChemistryReductionMethods(rhoReactionThermo, constFluidEThermoPhysics);
    makeChemistryReductionMethods
    (
        rhoReactionThermo,
        constAdiabaticFluidEThermoPhysics
    );
    makeChemistryReductionMethods(rhoReactionThermo, constEThermoPhysics);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
