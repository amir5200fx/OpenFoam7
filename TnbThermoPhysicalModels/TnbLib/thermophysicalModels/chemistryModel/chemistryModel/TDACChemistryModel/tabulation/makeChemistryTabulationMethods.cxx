#define FoamRegisterDebugSwitch_EXPORT_DEFINE

#include <makeChemistryTabulationMethods.hxx>

#include <thermoPhysicsTypes.hxx>

#include <psiReactionThermo.hxx>
#include <rhoReactionThermo.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    // Chemistry solvers based on sensibleEnthalpy
    makeChemistryTabulationMethods(psiReactionThermo, constGasHThermoPhysics);
    makeChemistryTabulationMethods(psiReactionThermo, gasHThermoPhysics);
    makeChemistryTabulationMethods
    (
        psiReactionThermo,
        constIncompressibleGasHThermoPhysics
    );
    makeChemistryTabulationMethods
    (
        psiReactionThermo,
        incompressibleGasHThermoPhysics
    );
    makeChemistryTabulationMethods(psiReactionThermo, icoPoly8HThermoPhysics);
    makeChemistryTabulationMethods(psiReactionThermo, constFluidHThermoPhysics);
    makeChemistryTabulationMethods
    (
        psiReactionThermo,
        constAdiabaticFluidHThermoPhysics
    );
    makeChemistryTabulationMethods(psiReactionThermo, constHThermoPhysics);

    makeChemistryTabulationMethods(rhoReactionThermo, constGasHThermoPhysics);
    makeChemistryTabulationMethods(rhoReactionThermo, gasHThermoPhysics);
    makeChemistryTabulationMethods
    (
        rhoReactionThermo,
        constIncompressibleGasHThermoPhysics
    );
    makeChemistryTabulationMethods
    (
        rhoReactionThermo,
        incompressibleGasHThermoPhysics
    );
    makeChemistryTabulationMethods(rhoReactionThermo, icoPoly8HThermoPhysics);
    makeChemistryTabulationMethods(rhoReactionThermo, constFluidHThermoPhysics);
    makeChemistryTabulationMethods
    (
        rhoReactionThermo,
        constAdiabaticFluidHThermoPhysics
    );
    makeChemistryTabulationMethods(rhoReactionThermo, constHThermoPhysics);

    // Chemistry solvers based on sensibleInternalEnergy

    makeChemistryTabulationMethods(psiReactionThermo, constGasEThermoPhysics);
    makeChemistryTabulationMethods(psiReactionThermo, gasEThermoPhysics);
    makeChemistryTabulationMethods
    (
        psiReactionThermo,
        constIncompressibleGasEThermoPhysics
    );
    makeChemistryTabulationMethods
    (
        psiReactionThermo,
        incompressibleGasEThermoPhysics
    );
    makeChemistryTabulationMethods(psiReactionThermo, icoPoly8EThermoPhysics);
    makeChemistryTabulationMethods(psiReactionThermo, constFluidEThermoPhysics);
    makeChemistryTabulationMethods
    (
        psiReactionThermo,
        constAdiabaticFluidEThermoPhysics
    );
    makeChemistryTabulationMethods(psiReactionThermo, constEThermoPhysics);

    makeChemistryTabulationMethods(rhoReactionThermo, constGasEThermoPhysics);
    makeChemistryTabulationMethods(rhoReactionThermo, gasEThermoPhysics);
    makeChemistryTabulationMethods
    (
        rhoReactionThermo,
        constIncompressibleGasEThermoPhysics
    );
    makeChemistryTabulationMethods
    (
        rhoReactionThermo,
        incompressibleGasEThermoPhysics
    );
    makeChemistryTabulationMethods(rhoReactionThermo, icoPoly8EThermoPhysics);
    makeChemistryTabulationMethods(rhoReactionThermo, constFluidEThermoPhysics);
    makeChemistryTabulationMethods
    (
        rhoReactionThermo,
        constAdiabaticFluidEThermoPhysics
    );
    makeChemistryTabulationMethods(rhoReactionThermo, constEThermoPhysics);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
