#include <Minmod.hxx>

#include <LimitedScheme.hxx>

#include <surfaceFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeLimitedSurfaceInterpolationScheme(Minmod, MinmodLimiter)
		makeLimitedVSurfaceInterpolationScheme(MinmodV, MinmodLimiter)
}

// ************************************************************************* //