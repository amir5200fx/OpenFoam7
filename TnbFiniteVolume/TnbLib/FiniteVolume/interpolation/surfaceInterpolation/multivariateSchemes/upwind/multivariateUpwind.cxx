#include <multivariateUpwind.hxx>

#include <fvMesh.hxx>

#include <volMesh.hxx>  // added by amir
#include <fvPatchFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeMultivariateSurfaceInterpolationScheme(multivariateUpwind)
}

// ************************************************************************* //