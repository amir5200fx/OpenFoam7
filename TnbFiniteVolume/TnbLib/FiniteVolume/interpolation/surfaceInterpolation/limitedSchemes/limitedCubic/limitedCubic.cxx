#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <limitedCubic.hxx>

#include <LimitedScheme.hxx>
#include <Limited01.hxx>
#include <limitedCubicV.hxx>

#include <surfaceFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeLimitedSurfaceInterpolationScheme(limitedCubic, limitedCubicLimiter)
		makeLimitedVSurfaceInterpolationScheme(limitedCubicV, limitedCubicVLimiter)

		makeLLimitedSurfaceInterpolationTypeScheme
		(
			limitedLimitedCubic,
			LimitedLimiter,
			limitedCubicLimiter,
			NVDTVD,
			magSqr,
			scalar
		)

		makeLLimitedSurfaceInterpolationTypeScheme
		(
			limitedCubic01,
			Limited01Limiter,
			limitedCubicLimiter,
			NVDTVD,
			magSqr,
			scalar
		)
}

// ************************************************************************* //