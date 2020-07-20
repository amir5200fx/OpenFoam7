#include <Minmod.hxx>

#include <LimitedScheme.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeLimitedSurfaceInterpolationScheme(Minmod, MinmodLimiter)
		makeLimitedVSurfaceInterpolationScheme(MinmodV, MinmodLimiter)
}

// ************************************************************************* //