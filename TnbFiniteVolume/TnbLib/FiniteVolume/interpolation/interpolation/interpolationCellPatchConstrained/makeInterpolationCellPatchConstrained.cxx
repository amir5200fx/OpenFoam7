#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <interpolationCellPatchConstrained.hxx>

#include <volMesh.hxx>  // added by amir
#include <fvPatchFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeInterpolation(interpolationCellPatchConstrained);
}

// ************************************************************************* //