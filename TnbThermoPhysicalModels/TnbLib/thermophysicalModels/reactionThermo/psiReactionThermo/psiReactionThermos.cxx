#include <makeReactionThermo.hxx>

#include <psiReactionThermo.hxx>
#include <hePsiThermo.hxx>

#include <specie.hxx>
#include <perfectGas.hxx>
#include <hConstThermo.hxx>
#include <janafThermo.hxx>
#include <sensibleEnthalpy.hxx>
#include <thermo.hxx>
#include <constTransport.hxx>
#include <sutherlandTransport.hxx>

#include <homogeneousMixture.hxx>
#include <inhomogeneousMixture.hxx>
#include <veryInhomogeneousMixture.hxx>
#include <multiComponentMixture.hxx>
#include <reactingMixture.hxx>
#include <singleStepReactingMixture.hxx>
#include <singleComponentMixture.hxx>

#include <thermoPhysicsTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	// constTransport, hConstThermo

	makeReactionThermos
	(
		psiThermo,
		psiReactionThermo,
		hePsiThermo,
		homogeneousMixture,
		constTransport,
		sensibleEnthalpy,
		hConstThermo,
		perfectGas,
		specie
	);

	makeReactionThermos
	(
		psiThermo,
		psiReactionThermo,
		hePsiThermo,
		inhomogeneousMixture,
		constTransport,
		sensibleEnthalpy,
		hConstThermo,
		perfectGas,
		specie
	);

	makeReactionThermos
	(
		psiThermo,
		psiReactionThermo,
		hePsiThermo,
		veryInhomogeneousMixture,
		constTransport,
		sensibleEnthalpy,
		hConstThermo,
		perfectGas,
		specie
	);


	// sutherlandTransport, hConstThermo

	makeReactionThermos
	(
		psiThermo,
		psiReactionThermo,
		hePsiThermo,
		homogeneousMixture,
		sutherlandTransport,
		sensibleEnthalpy,
		hConstThermo,
		perfectGas,
		specie
	);

	makeReactionThermos
	(
		psiThermo,
		psiReactionThermo,
		hePsiThermo,
		inhomogeneousMixture,
		sutherlandTransport,
		sensibleEnthalpy,
		hConstThermo,
		perfectGas,
		specie
	);

	makeReactionThermos
	(
		psiThermo,
		psiReactionThermo,
		hePsiThermo,
		veryInhomogeneousMixture,
		sutherlandTransport,
		sensibleEnthalpy,
		hConstThermo,
		perfectGas,
		specie
	);


	// sutherlandTransport, janafThermo

	makeReactionThermos
	(
		psiThermo,
		psiReactionThermo,
		hePsiThermo,
		homogeneousMixture,
		sutherlandTransport,
		sensibleEnthalpy,
		janafThermo,
		perfectGas,
		specie
	);

	makeReactionThermos
	(
		psiThermo,
		psiReactionThermo,
		hePsiThermo,
		inhomogeneousMixture,
		sutherlandTransport,
		sensibleEnthalpy,
		janafThermo,
		perfectGas,
		specie
	);

	makeReactionThermos
	(
		psiThermo,
		psiReactionThermo,
		hePsiThermo,
		veryInhomogeneousMixture,
		sutherlandTransport,
		sensibleEnthalpy,
		janafThermo,
		perfectGas,
		specie
	);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	// Multi-component thermo for sensible enthalpy

	makeThermoPhysicsReactionThermos
	(
		psiThermo,
		psiReactionThermo,
		hePsiThermo,
		multiComponentMixture,
		constGasHThermoPhysics
	);

	makeThermoPhysicsReactionThermos
	(
		psiThermo,
		psiReactionThermo,
		hePsiThermo,
		multiComponentMixture,
		gasHThermoPhysics
	);


	// Multi-component thermo for internal energy

	makeThermoPhysicsReactionThermos
	(
		psiThermo,
		psiReactionThermo,
		hePsiThermo,
		multiComponentMixture,
		constGasEThermoPhysics
	);

	makeThermoPhysicsReactionThermos
	(
		psiThermo,
		psiReactionThermo,
		hePsiThermo,
		multiComponentMixture,
		gasEThermoPhysics
	);


	// Reaction thermo for sensible enthalpy

	makeThermoPhysicsReactionThermos
	(
		psiThermo,
		psiReactionThermo,
		hePsiThermo,
		reactingMixture,
		constGasHThermoPhysics
	);

	makeThermoPhysicsReactionThermos
	(
		psiThermo,
		psiReactionThermo,
		hePsiThermo,
		reactingMixture,
		gasHThermoPhysics
	);


	// Single-step reaction thermo for sensible enthalpy

	makeThermoPhysicsReactionThermos
	(
		psiThermo,
		psiReactionThermo,
		hePsiThermo,
		singleStepReactingMixture,
		gasHThermoPhysics
	);


	// Reaction thermo for internal energy

	makeThermoPhysicsReactionThermos
	(
		psiThermo,
		psiReactionThermo,
		hePsiThermo,
		reactingMixture,
		constGasEThermoPhysics
	);

	makeThermoPhysicsReactionThermos
	(
		psiThermo,
		psiReactionThermo,
		hePsiThermo,
		reactingMixture,
		gasEThermoPhysics
	);


	// Single-step reaction thermo for internal energy

	makeThermoPhysicsReactionThermos
	(
		psiThermo,
		psiReactionThermo,
		hePsiThermo,
		singleStepReactingMixture,
		gasEThermoPhysics
	);


	// Single-component thermo for sensible enthalpy

	makeThermoPhysicsReactionThermo
	(
		psiReactionThermo,
		hePsiThermo,
		singleComponentMixture,
		constGasHThermoPhysics
	);

	makeThermoPhysicsReactionThermo
	(
		psiReactionThermo,
		hePsiThermo,
		singleComponentMixture,
		gasHThermoPhysics
	);


	// Single-component thermo for internal energy

	makeThermoPhysicsReactionThermo
	(
		psiReactionThermo,
		hePsiThermo,
		singleComponentMixture,
		constGasEThermoPhysics
	);

	makeThermoPhysicsReactionThermo
	(
		psiReactionThermo,
		hePsiThermo,
		singleComponentMixture,
		gasEThermoPhysics
	);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //