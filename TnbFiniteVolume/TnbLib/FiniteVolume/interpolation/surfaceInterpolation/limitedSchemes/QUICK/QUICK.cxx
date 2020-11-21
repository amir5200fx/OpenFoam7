#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <QUICK.hxx>

#include <LimitedScheme.hxx>
#include <QUICKV.hxx>

#include <surfaceFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeLimitedSurfaceInterpolationScheme(QUICK, QUICKLimiter)
		makeLimitedVSurfaceInterpolationScheme(QUICKV, QUICKVLimiter)
}

// ************************************************************************* //