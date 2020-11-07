#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <interpolationCellPointFace.hxx>

#include <fvBoundaryMesh.hxx>  // added by amir
#include <surfaceMesh.hxx>  // added by amir
#include <volMesh.hxx>  // added by amir
#include <fvPatchFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeInterpolation(interpolationCellPointFace);
}

// ************************************************************************* //