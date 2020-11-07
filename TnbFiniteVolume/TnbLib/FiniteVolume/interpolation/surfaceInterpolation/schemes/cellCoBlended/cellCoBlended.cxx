#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <cellCoBlended.hxx>

#include <fvMesh.hxx>
#include <fvBoundaryMesh.hxx>  // added by amir
#include <volMesh.hxx>  // added by amir
#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeSurfaceInterpolationScheme(cellCoBlended);
}

// ************************************************************************* //