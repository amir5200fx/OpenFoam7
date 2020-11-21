#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <interpolationPointMVC.hxx>

#include <fvBoundaryMesh.hxx>  // added by amir
#include <volMesh.hxx>  // added by amir
#include <fvPatchFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeInterpolation(interpolationPointMVC);
}

// ************************************************************************* //