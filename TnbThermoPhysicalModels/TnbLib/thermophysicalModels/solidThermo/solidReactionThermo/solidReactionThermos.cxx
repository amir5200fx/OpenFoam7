#include <makeReactingSolidThermo.hxx>
#include <solidReactionThermo.hxx>
#include <heSolidThermo.hxx>

#include <specie.hxx>
#include <rhoConst.hxx>
#include <hConstThermo.hxx>
#include <hPowerThermo.hxx>
#include <constIsoSolidTransport.hxx>
#include <constAnIsoSolidTransport.hxx>
#include <exponentialSolidTransport.hxx>

#include <reactingMixture.hxx>
#include <multiComponentMixture.hxx>

#include <sensibleEnthalpy.hxx>
#include <thermo.hxx>


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/* * * * * * * * * * * * * * * * * Enthalpy-based * * * * * * * * * * * * * */

	makeReactingSolidThermo
	(
		solidReactionThermo,
		heSolidThermo,
		reactingMixture,
		constIsoSolidTransport,
		sensibleEnthalpy,
		hConstThermo,
		rhoConst,
		specie
	);


	makeReactingSolidThermo
	(
		solidReactionThermo,
		heSolidThermo,
		reactingMixture,
		constIsoSolidTransport,
		sensibleEnthalpy,
		hPowerThermo,
		rhoConst,
		specie
	);


	makeReactingSolidThermo
	(
		solidThermo,
		heSolidThermo,
		multiComponentMixture,
		constIsoSolidTransport,
		sensibleEnthalpy,
		hConstThermo,
		rhoConst,
		specie
	);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //