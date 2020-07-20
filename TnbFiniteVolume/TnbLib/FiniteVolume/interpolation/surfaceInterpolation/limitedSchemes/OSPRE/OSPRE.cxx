#include <OSPRE.hxx>

#include <LimitedScheme.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeLimitedSurfaceInterpolationScheme(OSPRE, OSPRELimiter)
		makeLimitedVSurfaceInterpolationScheme(OSPREV, OSPRELimiter)
}

// ************************************************************************* //
