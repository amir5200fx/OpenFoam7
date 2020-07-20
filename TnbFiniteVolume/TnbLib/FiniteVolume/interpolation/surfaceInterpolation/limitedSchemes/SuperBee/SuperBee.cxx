#include <SuperBee.hxx>

#include <LimitedScheme.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeLimitedSurfaceInterpolationScheme(SuperBee, SuperBeeLimiter)
		makeLimitedVSurfaceInterpolationScheme(SuperBeeV, SuperBeeLimiter)
}

// ************************************************************************* //