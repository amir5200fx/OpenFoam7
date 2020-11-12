#define FoamRegisterDebugSwitch_EXPORT_DEFINE

#include <basicThermoCloud.hxx>

#include <makeParcelTurbulenceDispersionModels.hxx>
#include <makeThermoParcelTurbulenceForces.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeThermoParcelTurbulenceForces(basicThermoCloud);
	makeParcelTurbulenceDispersionModels(basicThermoCloud);
}


// ************************************************************************* //