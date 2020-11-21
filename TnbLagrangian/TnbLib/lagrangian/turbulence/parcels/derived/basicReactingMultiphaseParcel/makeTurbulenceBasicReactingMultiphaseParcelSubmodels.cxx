#define FoamRegisterDebugSwitch_EXPORT_DEFINE

#include <basicReactingMultiphaseCloud.hxx>

#include <makeParcelTurbulenceDispersionModels.hxx>
#include <makeThermoParcelTurbulenceForces.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeThermoParcelTurbulenceForces(basicReactingMultiphaseCloud);
	makeParcelTurbulenceDispersionModels(basicReactingMultiphaseCloud);
}


// ************************************************************************* //