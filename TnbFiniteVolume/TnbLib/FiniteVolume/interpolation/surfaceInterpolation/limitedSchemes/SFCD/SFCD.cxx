#include <SFCD.hxx>

#include <LimitedScheme.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeLimitedSurfaceInterpolationScheme(SFCD, SFCDLimiter)
		makeLimitedVSurfaceInterpolationScheme(SFCDV, SFCDLimiter)
}

// ************************************************************************* //