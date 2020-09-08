#include <CoBlended.hxx>

#include <fvMesh.hxx>
#include <volMesh.hxx>  // added by amir
#include <fvPatchFields.hxx>  // added by amir
#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeSurfaceInterpolationScheme(CoBlended);
}

// ************************************************************************* //