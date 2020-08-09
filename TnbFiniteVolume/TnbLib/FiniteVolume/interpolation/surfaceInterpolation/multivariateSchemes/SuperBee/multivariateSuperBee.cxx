#include <multivariateScheme.hxx>

#include <LimitedScheme.hxx>
#include <Limited01.hxx>
#include <SuperBee.hxx>

#include <volMesh.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeLimitedMultivariateSurfaceInterpolationScheme
	(
		SuperBee,
		SuperBeeLimiter
	)
}


// ************************************************************************* //