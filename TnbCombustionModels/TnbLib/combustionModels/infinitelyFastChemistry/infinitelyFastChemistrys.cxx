#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <infinitelyFastChemistry.hxx>

#include <thermoPhysicsTypes.hxx>
#include <psiReactionThermo.hxx>
#include <rhoReactionThermo.hxx>
#include <infinitelyFastChemistry.hxx>

#include <makeCombustionTypes.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Combustion models based on sensibleEnthalpy

	makeCombustionTypesThermo
	(
		infinitelyFastChemistry,
		psiReactionThermo,
		gasHThermoPhysics
	);

	makeCombustionTypesThermo
	(
		infinitelyFastChemistry,
		psiReactionThermo,
		constGasHThermoPhysics
	);

	makeCombustionTypesThermo
	(
		infinitelyFastChemistry,
		rhoReactionThermo,
		gasHThermoPhysics
	);

	makeCombustionTypesThermo
	(
		infinitelyFastChemistry,
		rhoReactionThermo,
		constGasHThermoPhysics
	);

	// Combustion models based on sensibleInternalEnergy

	makeCombustionTypesThermo
	(
		infinitelyFastChemistry,
		psiReactionThermo,
		gasEThermoPhysics
	);

	makeCombustionTypesThermo
	(
		infinitelyFastChemistry,
		psiReactionThermo,
		constGasEThermoPhysics
	);

	makeCombustionTypesThermo
	(
		infinitelyFastChemistry,
		rhoReactionThermo,
		gasEThermoPhysics
	);

	makeCombustionTypesThermo
	(
		infinitelyFastChemistry,
		rhoReactionThermo,
		constGasEThermoPhysics
	);

}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //