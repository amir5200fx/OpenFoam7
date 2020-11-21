#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <outletStabilised.hxx>

#include <fvMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeSurfaceInterpolationScheme(outletStabilised);
}

// ************************************************************************* //