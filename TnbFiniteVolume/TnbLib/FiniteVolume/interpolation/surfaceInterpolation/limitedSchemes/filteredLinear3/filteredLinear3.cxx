#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <filteredLinear3.hxx>

#include <LimitedScheme.hxx>
#include <filteredLinear3V.hxx>

#include <surfaceFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeLimitedSurfaceInterpolationScheme
	(
		filteredLinear3,
		filteredLinear3Limiter
	)

		makeLimitedVSurfaceInterpolationScheme
		(
			filteredLinear3V,
			filteredLinear3VLimiter
		)
}

// ************************************************************************* //