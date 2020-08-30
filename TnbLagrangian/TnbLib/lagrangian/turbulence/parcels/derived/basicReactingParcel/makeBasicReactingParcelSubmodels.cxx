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