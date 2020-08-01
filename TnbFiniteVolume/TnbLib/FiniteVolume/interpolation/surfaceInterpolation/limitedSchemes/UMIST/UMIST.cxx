#include <UMIST.hxx>

#include <LimitedScheme.hxx>

#include <surfaceFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeLimitedSurfaceInterpolationScheme(UMIST, UMISTLimiter)
		makeLimitedVSurfaceInterpolationScheme(UMISTV, UMISTLimiter)
}

// ************************************************************************* //