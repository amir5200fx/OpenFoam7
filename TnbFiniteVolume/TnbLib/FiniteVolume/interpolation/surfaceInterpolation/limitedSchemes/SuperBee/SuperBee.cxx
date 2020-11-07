#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <SuperBee.hxx>

#include <LimitedScheme.hxx>

#include <surfaceFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeLimitedSurfaceInterpolationScheme(SuperBee, SuperBeeLimiter)
		makeLimitedVSurfaceInterpolationScheme(SuperBeeV, SuperBeeLimiter)
}

// ************************************************************************* //