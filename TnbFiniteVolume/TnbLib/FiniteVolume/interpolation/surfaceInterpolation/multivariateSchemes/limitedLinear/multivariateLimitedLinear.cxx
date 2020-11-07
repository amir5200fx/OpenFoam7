#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <multivariateScheme.hxx>

#include <LimitedScheme.hxx>
#include <Limited01.hxx>
#include <limitedLinear.hxx>

#include <volMesh.hxx>  // added by amir
#include <fvPatchFields.hxx>  // added by amir

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