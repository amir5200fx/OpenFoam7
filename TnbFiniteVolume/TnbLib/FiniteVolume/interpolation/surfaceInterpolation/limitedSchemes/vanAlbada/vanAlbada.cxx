#include <vanAlbada.hxx>

#include <LimitedScheme.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeLimitedSurfaceInterpolationScheme(vanAlbada, vanAlbadaLimiter)
		makeLimitedVSurfaceInterpolationScheme(vanAlbadaV, vanAlbadaLimiter)
}

// ************************************************************************* //