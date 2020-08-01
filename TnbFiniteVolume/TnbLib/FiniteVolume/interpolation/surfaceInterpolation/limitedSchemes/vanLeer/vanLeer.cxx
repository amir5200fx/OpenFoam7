#include <vanLeer.hxx>

#include <LimitedScheme.hxx>
#include <Limited01.hxx>

#include <surfaceFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeLimitedSurfaceInterpolationScheme(vanLeer, vanLeerLimiter)
		makeLimitedVSurfaceInterpolationScheme(vanLeerV, vanLeerLimiter)

		makeLLimitedSurfaceInterpolationTypeScheme
		(
			limitedVanLeer,
			LimitedLimiter,
			vanLeerLimiter,
			NVDTVD,
			magSqr,
			scalar
		)

		makeLLimitedSurfaceInterpolationTypeScheme
		(
			vanLeer01,
			Limited01Limiter,
			vanLeerLimiter,
			NVDTVD,
			magSqr,
			scalar
		)
}

// ************************************************************************* //