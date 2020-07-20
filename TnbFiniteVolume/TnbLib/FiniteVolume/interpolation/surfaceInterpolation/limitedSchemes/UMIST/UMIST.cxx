#include <UMIST.hxx>

#include <LimitedScheme.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeLimitedSurfaceInterpolationScheme(UMIST, UMISTLimiter)
		makeLimitedVSurfaceInterpolationScheme(UMISTV, UMISTLimiter)
}

// ************************************************************************* //