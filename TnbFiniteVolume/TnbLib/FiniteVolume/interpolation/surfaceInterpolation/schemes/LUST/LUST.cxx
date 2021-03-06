#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <LUST.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	// makeSurfaceInterpolationScheme(LUST);
	makeSurfaceInterpolationTypeScheme(LUST, scalar);
	makeSurfaceInterpolationTypeScheme(LUST, vector);
}

// ************************************************************************* //