#define FoamRegisterDebugSwitch_EXPORT_DEFINE

#include <makeSolidThermo.hxx>

#include <solidThermo.hxx>
#include <heSolidThermo.hxx>

#include <specie.hxx>
#include <rhoConst.hxx>
#include <hConstThermo.hxx>
#include <hPowerThermo.hxx>
#include <hPolynomialThermo.hxx>
#include <constIsoSolidTransport.hxx>
#include <constAnIsoSolidTransport.hxx>
#include <exponentialSolidTransport.hxx>
#include <polynomialSolidTransport.hxx>
#include <pureMixture.hxx>
#include <sensibleEnthalpy.hxx>
#include <sensibleInternalEnergy.hxx>
#include <thermo.hxx>

#include <solidThermoPhysicsTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/* * * * * * * * * * * * * * * * * Enthalpy-based * * * * * * * * * * * * * */

	makeSolidThermo
	(
		solidThermo,
		heSolidThermo,
		pureMixture,
		constIsoSolidTransport,
		sensibleEnthalpy,
		hConstThermo,
		rhoConst,
		specie
	);

	makeSolidThermo
	(
		solidThermo,
		heSolidThermo,
		pureMixture,
		constAnIsoSolidTransport,
		sensibleEnthalpy,
		hConstThermo,
		rhoConst,
		specie
	);

	makeSolidThermo
	(
		solidThermo,
		heSolidThermo,
		pureMixture,
		exponentialSolidTransport,
		sensibleEnthalpy,
		hPowerThermo,
		rhoConst,
		specie
	);

	makeSolidThermoPhysicsType
	(
		solidThermo,
		heSolidThermo,
		pureMixture,
		hTransportThermoPoly8SolidThermoPhysics
	);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //