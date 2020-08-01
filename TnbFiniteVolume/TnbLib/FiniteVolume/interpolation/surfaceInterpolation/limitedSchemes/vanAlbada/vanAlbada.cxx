#include <vanAlbada.hxx>

#include <LimitedScheme.hxx>

#include <surfaceFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeLimitedSurfaceInterpolationScheme(vanAlbada, vanAlbadaLimiter)
		makeLimitedVSurfaceInterpolationScheme(vanAlbadaV, vanAlbadaLimiter)
}

// ************************************************************************* //