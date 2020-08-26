#include <mixtureFraction.hxx>

#include <makeSootTypes.hxx>
#include <thermoPhysicsTypes.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	makeSootTypesThermo(mixtureFraction, gasHThermoPhysics);
	makeSootTypesThermo(mixtureFraction, gasEThermoPhysics);
}

// ************************************************************************* //