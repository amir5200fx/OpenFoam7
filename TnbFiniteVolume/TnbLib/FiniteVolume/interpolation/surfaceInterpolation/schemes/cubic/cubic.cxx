#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <cubic.hxx>

#include <fvMesh.hxx>
#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeSurfaceInterpolationScheme(cubic)
}

// ************************************************************************* //