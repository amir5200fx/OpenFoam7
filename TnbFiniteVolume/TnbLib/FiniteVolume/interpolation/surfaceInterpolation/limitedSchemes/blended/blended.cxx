#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <blended.hxx>

#include <fvMesh.hxx>

#include <volMesh.hxx>  // added by amir
#include <fvPatchFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makelimitedSurfaceInterpolationScheme(blended)
}

// ************************************************************************* //