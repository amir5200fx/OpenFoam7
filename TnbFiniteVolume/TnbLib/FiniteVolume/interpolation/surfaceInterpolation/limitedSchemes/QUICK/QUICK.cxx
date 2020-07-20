#include <QUICK.hxx>

#include <LimitedScheme.hxx>
#include <QUICKV.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeLimitedSurfaceInterpolationScheme(QUICK, QUICKLimiter)
		makeLimitedVSurfaceInterpolationScheme(QUICKV, QUICKVLimiter)
}

// ************************************************************************* //