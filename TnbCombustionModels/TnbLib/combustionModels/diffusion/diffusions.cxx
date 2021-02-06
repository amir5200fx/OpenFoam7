#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <diffusion.hxx>

#include <thermoPhysicsTypes.hxx>
#include <psiReactionThermo.hxx>
#include <rhoReactionThermo.hxx>

#include <makeCombustionTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Combustion models based on sensibleEnthalpy
	makeCombustionTypesThermo
	(
		diffusion,
		psiReactionThermo,
		gasHThermoPhysics
	);

	makeCombustionTypesThermo
	(
		diffusion,
		psiReactionThermo,
		constGasHThermoPhysics
	);

	makeCombustionTypesThermo
	(
		diffusion,
		rhoReactionThermo,
		gasHThermoPhysics
	);

	makeCombustionTypesThermo
	(
		diffusion,
		rhoReactionThermo,
		constGasHThermoPhysics
	);


	// Combustion models based on sensibleInternalEnergy

	makeCombustionTypesThermo
	(
		diffusion,
		psiReactionThermo,
		gasEThermoPhysics
	);

	makeCombustionTypesThermo
	(
		diffusion,
		psiReactionThermo,
		constGasEThermoPhysics
	);

	makeCombustionTypesThermo
	(
		diffusion,
		rhoReactionThermo,
		gasEThermoPhysics
	);

	makeCombustionTypesThermo
	(
		diffusion,
		rhoReactionThermo,
		constGasEThermoPhysics
	);

}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //