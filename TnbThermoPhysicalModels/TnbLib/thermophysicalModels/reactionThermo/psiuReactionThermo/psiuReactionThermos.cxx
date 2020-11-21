#define FoamRegisterDebugSwitch_EXPORT_DEFINE

#include <makeReactionThermo.hxx>

#include <psiuReactionThermo.hxx>
#include <heheuPsiThermo.hxx>

#include <addToRunTimeSelectionTable.hxx>

#include <specie.hxx>
#include <perfectGas.hxx>
#include <hConstThermo.hxx>
#include <janafThermo.hxx>
#include <thermo.hxx>
#include <constTransport.hxx>
#include <sutherlandTransport.hxx>

#include <absoluteEnthalpy.hxx>
#include <absoluteInternalEnergy.hxx>

#include <homogeneousMixture.hxx>
#include <inhomogeneousMixture.hxx>
#include <veryInhomogeneousMixture.hxx>
#include <multiComponentMixture.hxx>
#include <egrMixture.hxx>


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * h-hu-Thermos * * * * * * * * * * * * * * * //

	makeReactionThermos
	(
		psiThermo,
		psiuReactionThermo,
		heheuPsiThermo,
		homogeneousMixture,
		constTransport,
		absoluteEnthalpy,
		hConstThermo,
		perfectGas,
		specie
	);

	makeReactionThermos
	(
		psiThermo,
		psiuReactionThermo,
		heheuPsiThermo,
		inhomogeneousMixture,
		constTransport,
		absoluteEnthalpy,
		hConstThermo,
		perfectGas,
		specie
	);

	makeReactionThermos
	(
		psiThermo,
		psiuReactionThermo,
		heheuPsiThermo,
		veryInhomogeneousMixture,
		constTransport,
		absoluteEnthalpy,
		hConstThermo,
		perfectGas,
		specie
	);

	makeReactionThermos
	(
		psiThermo,
		psiuReactionThermo,
		heheuPsiThermo,
		egrMixture,
		constTransport,
		absoluteEnthalpy,
		hConstThermo,
		perfectGas,
		specie
	);


	makeReactionThermos
	(
		psiThermo,
		psiuReactionThermo,
		heheuPsiThermo,
		homogeneousMixture,
		constTransport,
		absoluteEnthalpy,
		janafThermo,
		perfectGas,
		specie
	);

	makeReactionThermos
	(
		psiThermo,
		psiuReactionThermo,
		heheuPsiThermo,
		homogeneousMixture,
		sutherlandTransport,
		absoluteEnthalpy,
		janafThermo,
		perfectGas,
		specie
	);

	makeReactionThermos
	(
		psiThermo,
		psiuReactionThermo,
		heheuPsiThermo,
		inhomogeneousMixture,
		sutherlandTransport,
		absoluteEnthalpy,
		janafThermo,
		perfectGas,
		specie
	);

	makeReactionThermos
	(
		psiThermo,
		psiuReactionThermo,
		heheuPsiThermo,
		veryInhomogeneousMixture,
		sutherlandTransport,
		absoluteEnthalpy,
		janafThermo,
		perfectGas,
		specie
	);

	makeReactionThermos
	(
		psiThermo,
		psiuReactionThermo,
		heheuPsiThermo,
		egrMixture,
		sutherlandTransport,
		absoluteEnthalpy,
		janafThermo,
		perfectGas,
		specie
	);


	makeReactionThermos
	(
		psiThermo,
		psiuReactionThermo,
		heheuPsiThermo,
		homogeneousMixture,
		sutherlandTransport,
		absoluteInternalEnergy,
		janafThermo,
		perfectGas,
		specie
	);

	makeReactionThermos
	(
		psiThermo,
		psiuReactionThermo,
		heheuPsiThermo,
		inhomogeneousMixture,
		sutherlandTransport,
		absoluteInternalEnergy,
		janafThermo,
		perfectGas,
		specie
	);

	makeReactionThermos
	(
		psiThermo,
		psiuReactionThermo,
		heheuPsiThermo,
		veryInhomogeneousMixture,
		sutherlandTransport,
		absoluteInternalEnergy,
		janafThermo,
		perfectGas,
		specie
	);

	makeReactionThermos
	(
		psiThermo,
		psiuReactionThermo,
		heheuPsiThermo,
		egrMixture,
		sutherlandTransport,
		absoluteInternalEnergy,
		janafThermo,
		perfectGas,
		specie
	);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //