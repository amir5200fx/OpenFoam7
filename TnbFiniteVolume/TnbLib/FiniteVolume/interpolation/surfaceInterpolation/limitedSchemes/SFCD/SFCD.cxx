#include <SFCD.hxx>

#include <LimitedScheme.hxx>

#include <surfaceFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeLimitedSurfaceInterpolationScheme(SFCD, SFCDLimiter)
		makeLimitedVSurfaceInterpolationScheme(SFCDV, SFCDLimiter)
}

// ************************************************************************* //