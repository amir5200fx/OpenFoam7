#include <MUSCL.hxx>

#include <LimitedScheme.hxx>
#include <Limited01.hxx>

#include <surfaceFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeLimitedSurfaceInterpolationScheme(MUSCL, MUSCLLimiter)
		makeLimitedVSurfaceInterpolationScheme(MUSCLV, MUSCLLimiter)

		makeLLimitedSurfaceInterpolationTypeScheme
		(
			limitedMUSCL,
			LimitedLimiter,
			MUSCLLimiter,
			NVDTVD,
			magSqr,
			scalar
		)

		makeLLimitedSurfaceInterpolationTypeScheme
		(
			MUSCL01,
			Limited01Limiter,
			MUSCLLimiter,
			NVDTVD,
			magSqr,
			scalar
		)

		/*
			makeLimitedSurfaceInterpolationTypeScheme
			(
				MUSCL,
				MUSCLLimiter,
				NVDTVD,
				rhoMagSqr,
				scalar
			)

			makeLimitedSurfaceInterpolationTypeScheme
			(
				MUSCL,
				MUSCLLimiter,
				NVDTVD,
				rhoMagSqr,
				vector
			)
		*/
}

// ************************************************************************* //