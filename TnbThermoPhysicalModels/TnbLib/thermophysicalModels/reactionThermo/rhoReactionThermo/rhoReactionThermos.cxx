#define FoamRegisterDebugSwitch_EXPORT_DEFINE

#include <makeReactionThermo.hxx>

#include <rhoReactionThermo.hxx>
#include <heRhoThermo.hxx>

#include <specie.hxx>
#include <perfectGas.hxx>
#include <incompressiblePerfectGas.hxx>
#include <hConstThermo.hxx>
#include <janafThermo.hxx>
#include <sensibleEnthalpy.hxx>
#include <thermo.hxx>
#include <rhoConst.hxx>
#include <perfectFluid.hxx>
#include <adiabaticPerfectFluid.hxx>
#include <Boussinesq.hxx>

#include <constTransport.hxx>
#include <sutherlandTransport.hxx>
#include <WLFTransport.hxx>

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

	makeReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		homogeneousMixture,
		constTransport,
		sensibleEnthalpy,
		hConstThermo,
		perfectGas,
		specie
	);

	makeReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		inhomogeneousMixture,
		constTransport,
		sensibleEnthalpy,
		hConstThermo,
		perfectGas,
		specie
	);

	makeReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		veryInhomogeneousMixture,
		constTransport,
		sensibleEnthalpy,
		hConstThermo,
		perfectGas,
		specie
	);

	makeReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		homogeneousMixture,
		sutherlandTransport,
		sensibleEnthalpy,
		janafThermo,
		perfectGas,
		specie
	);

	makeReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		inhomogeneousMixture,
		sutherlandTransport,
		sensibleEnthalpy,
		janafThermo,
		perfectGas,
		specie
	);

	makeReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		veryInhomogeneousMixture,
		sutherlandTransport,
		sensibleEnthalpy,
		janafThermo,
		perfectGas,
		specie
	);


	makeReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		homogeneousMixture,
		constTransport,
		sensibleEnthalpy,
		hConstThermo,
		incompressiblePerfectGas,
		specie
	);

	makeReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		inhomogeneousMixture,
		constTransport,
		sensibleEnthalpy,
		hConstThermo,
		incompressiblePerfectGas,
		specie
	);

	makeReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		veryInhomogeneousMixture,
		constTransport,
		sensibleEnthalpy,
		hConstThermo,
		incompressiblePerfectGas,
		specie
	);

	makeReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		homogeneousMixture,
		sutherlandTransport,
		sensibleEnthalpy,
		janafThermo,
		incompressiblePerfectGas,
		specie
	);

	makeReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		inhomogeneousMixture,
		sutherlandTransport,
		sensibleEnthalpy,
		janafThermo,
		incompressiblePerfectGas,
		specie
	);

	makeReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		veryInhomogeneousMixture,
		sutherlandTransport,
		sensibleEnthalpy,
		janafThermo,
		incompressiblePerfectGas,
		specie
	);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	// Multi-component thermo for internal energy

	makeThermoPhysicsReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		multiComponentMixture,
		constGasEThermoPhysics
	);

	makeThermoPhysicsReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		multiComponentMixture,
		gasEThermoPhysics
	);

	makeThermoPhysicsReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		multiComponentMixture,
		constIncompressibleGasEThermoPhysics
	);

	makeThermoPhysicsReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		multiComponentMixture,
		incompressibleGasEThermoPhysics
	);

	makeThermoPhysicsReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		multiComponentMixture,
		icoPoly8EThermoPhysics
	);

	makeThermoPhysicsReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		multiComponentMixture,
		constFluidEThermoPhysics
	);

	makeThermoPhysicsReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		multiComponentMixture,
		constAdiabaticFluidEThermoPhysics
	);

	makeThermoPhysicsReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		multiComponentMixture,
		constEThermoPhysics
	);


	// Reaction thermo for internal energy

	makeThermoPhysicsReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		reactingMixture,
		constGasEThermoPhysics
	);

	makeThermoPhysicsReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		reactingMixture,
		gasEThermoPhysics
	);

	makeThermoPhysicsReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		reactingMixture,
		constIncompressibleGasEThermoPhysics
	);

	makeThermoPhysicsReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		reactingMixture,
		incompressibleGasEThermoPhysics
	);

	makeThermoPhysicsReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		reactingMixture,
		icoPoly8EThermoPhysics
	);

	makeThermoPhysicsReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		reactingMixture,
		constFluidEThermoPhysics
	);

	makeThermoPhysicsReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		reactingMixture,
		constAdiabaticFluidEThermoPhysics
	);

	makeThermoPhysicsReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		reactingMixture,
		constEThermoPhysics
	);


	// Single-step reaction thermo for internal energy

	makeThermoPhysicsReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		singleStepReactingMixture,
		gasEThermoPhysics
	);


	// Single-component thermo for internal energy

	makeThermoPhysicsReactionThermo
	(
		rhoReactionThermo,
		heRhoThermo,
		singleComponentMixture,
		constGasEThermoPhysics
	);

	makeThermoPhysicsReactionThermo
	(
		rhoReactionThermo,
		heRhoThermo,
		singleComponentMixture,
		gasEThermoPhysics
	);

	makeThermoPhysicsReactionThermo
	(
		rhoReactionThermo,
		heRhoThermo,
		singleComponentMixture,
		constIncompressibleGasEThermoPhysics
	);

	makeThermoPhysicsReactionThermo
	(
		rhoReactionThermo,
		heRhoThermo,
		singleComponentMixture,
		incompressibleGasEThermoPhysics
	);

	makeThermoPhysicsReactionThermo
	(
		rhoReactionThermo,
		heRhoThermo,
		singleComponentMixture,
		icoPoly8EThermoPhysics
	);

	makeThermoPhysicsReactionThermo
	(
		rhoReactionThermo,
		heRhoThermo,
		singleComponentMixture,
		constFluidEThermoPhysics
	);

	makeThermoPhysicsReactionThermo
	(
		rhoReactionThermo,
		heRhoThermo,
		singleComponentMixture,
		constAdiabaticFluidEThermoPhysics
	);

	makeThermoPhysicsReactionThermo
	(
		rhoReactionThermo,
		heRhoThermo,
		singleComponentMixture,
		constEThermoPhysics
	);

	makeReactionThermo
	(
		rhoReactionThermo,
		heRhoThermo,
		singleComponentMixture,
		constTransport,
		sensibleInternalEnergy,
		hConstThermo,
		Boussinesq,
		specie
	);

	makeReactionThermo
	(
		rhoReactionThermo,
		heRhoThermo,
		singleComponentMixture,
		sutherlandTransport,
		sensibleInternalEnergy,
		janafThermo,
		Boussinesq,
		specie
	);

	makeReactionThermo
	(
		rhoReactionThermo,
		heRhoThermo,
		singleComponentMixture,
		WLFTransport,
		sensibleInternalEnergy,
		eConstThermo,
		rhoConst,
		specie
	);



	// Multi-component thermo for sensible enthalpy

	makeThermoPhysicsReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		multiComponentMixture,
		constGasHThermoPhysics
	);

	makeThermoPhysicsReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		multiComponentMixture,
		gasHThermoPhysics
	);

	makeThermoPhysicsReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		multiComponentMixture,
		constIncompressibleGasHThermoPhysics
	);

	makeThermoPhysicsReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		multiComponentMixture,
		incompressibleGasHThermoPhysics
	);

	makeThermoPhysicsReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		multiComponentMixture,
		icoPoly8HThermoPhysics
	);

	makeThermoPhysicsReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		multiComponentMixture,
		constFluidHThermoPhysics
	);

	makeThermoPhysicsReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		multiComponentMixture,
		constAdiabaticFluidHThermoPhysics
	);

	makeThermoPhysicsReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		multiComponentMixture,
		constHThermoPhysics
	);


	// Reaction thermo for sensible enthalpy

	makeThermoPhysicsReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		reactingMixture,
		constGasHThermoPhysics
	);

	makeThermoPhysicsReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		reactingMixture,
		gasHThermoPhysics
	);

	makeThermoPhysicsReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		reactingMixture,
		constIncompressibleGasHThermoPhysics
	);

	makeThermoPhysicsReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		reactingMixture,
		incompressibleGasHThermoPhysics
	);

	makeThermoPhysicsReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		reactingMixture,
		icoPoly8HThermoPhysics
	);

	makeThermoPhysicsReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		reactingMixture,
		constFluidHThermoPhysics
	);

	makeThermoPhysicsReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		reactingMixture,
		constAdiabaticFluidHThermoPhysics
	);

	makeThermoPhysicsReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		reactingMixture,
		constHThermoPhysics
	);


	// Single-step reaction thermo for sensible enthalpy

	makeThermoPhysicsReactionThermos
	(
		rhoThermo,
		rhoReactionThermo,
		heRhoThermo,
		singleStepReactingMixture,
		gasHThermoPhysics
	);


	// Single-component thermo for sensible enthalpy

	makeThermoPhysicsReactionThermo
	(
		rhoReactionThermo,
		heRhoThermo,
		singleComponentMixture,
		constGasHThermoPhysics
	);

	makeThermoPhysicsReactionThermo
	(
		rhoReactionThermo,
		heRhoThermo,
		singleComponentMixture,
		gasHThermoPhysics
	);

	makeThermoPhysicsReactionThermo
	(
		rhoReactionThermo,
		heRhoThermo,
		singleComponentMixture,
		constIncompressibleGasHThermoPhysics
	);

	makeThermoPhysicsReactionThermo
	(
		rhoReactionThermo,
		heRhoThermo,
		singleComponentMixture,
		incompressibleGasHThermoPhysics
	);

	makeThermoPhysicsReactionThermo
	(
		rhoReactionThermo,
		heRhoThermo,
		singleComponentMixture,
		icoPoly8HThermoPhysics
	);

	makeThermoPhysicsReactionThermo
	(
		rhoReactionThermo,
		heRhoThermo,
		singleComponentMixture,
		constFluidHThermoPhysics
	);

	makeThermoPhysicsReactionThermo
	(
		rhoReactionThermo,
		heRhoThermo,
		singleComponentMixture,
		constAdiabaticFluidHThermoPhysics
	);

	makeThermoPhysicsReactionThermo
	(
		rhoReactionThermo,
		heRhoThermo,
		singleComponentMixture,
		constHThermoPhysics
	);

	makeReactionThermo
	(
		rhoReactionThermo,
		heRhoThermo,
		singleComponentMixture,
		constTransport,
		sensibleEnthalpy,
		hConstThermo,
		Boussinesq,
		specie
	);

	makeReactionThermo
	(
		rhoReactionThermo,
		heRhoThermo,
		singleComponentMixture,
		sutherlandTransport,
		sensibleEnthalpy,
		janafThermo,
		Boussinesq,
		specie
	);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //