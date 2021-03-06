#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <multivariateScheme.hxx>

#include <LimitedScheme.hxx>
#include <Limited01.hxx>
#include <vanLeer.hxx>

#include <volMesh.hxx>  // added by amir
#include <fvPatchFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeLimitedMultivariateSurfaceInterpolationScheme
	(
		vanLeer,
		vanLeerLimiter
	)
}

// ************************************************************************* //