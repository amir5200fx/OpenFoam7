#include <multivariateScheme.hxx>

#include <LimitedScheme.hxx>
#include <Limited01.hxx>
#include <MUSCL.hxx>

#include <volMesh.hxx>  // added by amir
#include <fvPatchFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeLimitedMultivariateSurfaceInterpolationScheme
	(
		MUSCL,
		MUSCLLimiter
	)
}

// ************************************************************************* //