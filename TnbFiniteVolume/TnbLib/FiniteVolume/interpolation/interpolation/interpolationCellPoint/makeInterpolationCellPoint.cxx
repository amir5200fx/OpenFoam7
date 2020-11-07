#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <interpolationCellPoint.hxx>

#include <volMesh.hxx>  // added by amir
#include <fvBoundaryMesh.hxx>  // added by amir
#include <fvPatchFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeInterpolation(interpolationCellPoint);
}

// ************************************************************************* //