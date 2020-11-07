#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <OSPRE.hxx>

#include <LimitedScheme.hxx>

#include <surfaceFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeLimitedSurfaceInterpolationScheme(OSPRE, OSPRELimiter)
		makeLimitedVSurfaceInterpolationScheme(OSPREV, OSPRELimiter)
}

// ************************************************************************* //
