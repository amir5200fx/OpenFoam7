#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <FSD.hxx>

#include <makeCombustionTypes.hxx>

#include <thermoPhysicsTypes.hxx>
#include <psiReactionThermo.hxx>
#include <rhoReactionThermo.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Combustion models based on sensibleEnthalpy
	makeCombustionTypesThermo
	(
		FSD,
		psiReactionThermo,
		gasHThermoPhysics
	);

	makeCombustionTypesThermo
	(
		FSD,
		psiReactionThermo,
		constGasHThermoPhysics
	);

	makeCombustionTypesThermo
	(
		FSD,
		rhoReactionThermo,
		gasHThermoPhysics
	);

	makeCombustionTypesThermo
	(
		FSD,
		rhoReactionThermo,
		constGasHThermoPhysics
	);

	// Combustion models based on sensibleInternalEnergy
	makeCombustionTypesThermo
	(
		FSD,
		psiReactionThermo,
		gasEThermoPhysics
	);

	makeCombustionTypesThermo
	(
		FSD,
		psiReactionThermo,
		constGasEThermoPhysics
	);

	makeCombustionTypesThermo
	(
		FSD,
		rhoReactionThermo,
		gasEThermoPhysics
	);

	makeCombustionTypesThermo
	(
		FSD,
		rhoReactionThermo,
		constGasEThermoPhysics
	);

}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //