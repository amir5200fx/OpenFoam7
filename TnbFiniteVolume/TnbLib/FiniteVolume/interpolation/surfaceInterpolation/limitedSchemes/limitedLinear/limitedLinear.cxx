#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <limitedLinear.hxx>

#include <Limited01.hxx>
#include <LimitedScheme.hxx>

#include <surfaceFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeLimitedSurfaceInterpolationScheme(limitedLinear, limitedLinearLimiter)

		makeLimitedVSurfaceInterpolationScheme
		(
			limitedLinearV,
			limitedLinearLimiter
		)

		makeLLimitedSurfaceInterpolationTypeScheme
		(
			limitedLimitedLinear,
			LimitedLimiter,
			limitedLinearLimiter,
			NVDTVD,
			magSqr,
			scalar
		)

		makeLLimitedSurfaceInterpolationTypeScheme
		(
			limitedLinear01,
			Limited01Limiter,
			limitedLinearLimiter,
			NVDTVD,
			magSqr,
			scalar
		)
}

// ************************************************************************* //