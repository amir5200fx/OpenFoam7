#define FoamRegisterDebugSwitch_EXPORT_DEFINE

#include <basicReactingCloud.hxx>

#include <makeParcelTurbulenceDispersionModels.hxx>
#include <makeThermoParcelTurbulenceForces.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeThermoParcelTurbulenceForces(basicReactingCloud);
	makeParcelTurbulenceDispersionModels(basicReactingCloud);
}


// ************************************************************************* //