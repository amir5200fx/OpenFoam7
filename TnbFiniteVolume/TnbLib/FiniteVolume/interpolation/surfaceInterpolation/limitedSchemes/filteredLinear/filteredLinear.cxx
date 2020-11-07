#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <filteredLinear.hxx>

#include <LimitedScheme.hxx>
#include <surfaceFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeLimitedSurfaceInterpolationScheme
	(
		filteredLinear,
		filteredLinearLimiter
	)
}

// ************************************************************************* //