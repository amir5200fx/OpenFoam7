#include <multivariateScheme.hxx>

#include <LimitedScheme.hxx>
#include <Limited01.hxx>
#include <limitedLinear.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeLimitedMultivariateSurfaceInterpolationScheme
	(
		limitedLinear,
		limitedLinearLimiter
	)

		makeLLimitedMultivariateSurfaceInterpolationScheme
		(
			limitedLimitedLinear,
			LimitedLimiter,
			limitedLinearLimiter,
			NVDTVD,
			magSqr
		)

		makeLLimitedMultivariateSurfaceInterpolationScheme
		(
			limitedLinear01,
			Limited01Limiter,
			limitedLinearLimiter,
			NVDTVD,
			magSqr
		)
}

// ************************************************************************* //