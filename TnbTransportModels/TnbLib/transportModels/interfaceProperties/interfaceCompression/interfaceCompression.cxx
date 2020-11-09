#define FoamPhiScheme_EXPORT_DEFINE
#define FoamRegisterDebugSwitch_EXPORT_DEFINE

#include <interfaceCompression.hxx>

#include <PhiScheme.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePhiSurfaceInterpolationScheme
	(
		interfaceCompression,
		interfaceCompressionLimiter,
		scalar
	)
}

// ************************************************************************* //