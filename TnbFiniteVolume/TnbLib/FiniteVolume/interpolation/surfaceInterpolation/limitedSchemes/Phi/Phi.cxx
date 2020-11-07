#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <Phi.hxx>

#include <PhiScheme.hxx>

#include <surfaceFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePhiSurfaceInterpolationScheme(Phi, PhiLimiter, vector)
}

// ************************************************************************* //