#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <Gamma.hxx>

#include <Limited01.hxx>
#include <LimitedScheme.hxx>

#include <surfaceFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeLimitedSurfaceInterpolationScheme(Gamma, GammaLimiter)
		makeLimitedVSurfaceInterpolationScheme(GammaV, GammaLimiter)

		makeLLimitedSurfaceInterpolationTypeScheme
		(
			limitedGamma,
			LimitedLimiter,
			GammaLimiter,
			NVDTVD,
			magSqr,
			scalar
		)

		makeLLimitedSurfaceInterpolationTypeScheme
		(
			Gamma01,
			Limited01Limiter,
			GammaLimiter,
			NVDTVD,
			magSqr,
			scalar
		)
}

// ************************************************************************* //