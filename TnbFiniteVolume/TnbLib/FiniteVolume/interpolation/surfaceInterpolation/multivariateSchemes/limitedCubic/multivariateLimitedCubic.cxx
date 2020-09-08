#include <multivariateScheme.hxx>

#include <LimitedScheme.hxx>
#include <Limited01.hxx>
#include <limitedCubic.hxx>

#include <volMesh.hxx>  // added by amir
#include <fvBoundaryMesh.hxx>  // added by amir
#include <fvPatchFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeLimitedMultivariateSurfaceInterpolationScheme
	(
		limitedCubic,
		limitedCubicLimiter
	)
}


// ************************************************************************* //