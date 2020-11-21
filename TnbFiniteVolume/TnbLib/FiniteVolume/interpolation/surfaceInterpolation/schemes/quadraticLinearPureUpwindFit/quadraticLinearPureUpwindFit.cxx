#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <PureUpwindFitScheme.hxx>
#include <quadraticLinearUpwindFitPolynomial.hxx>
#include <upwindCFCCellToFaceStencilObject.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Use stencil with three upwind cells:
	// upwindCFCCellToFaceStencilObject + pureUpwind
	makePureUpwindFitSurfaceInterpolationScheme
	(
		quadraticLinearPureUpwindFit,
		quadraticLinearUpwindFitPolynomial,
		upwindCFCCellToFaceStencilObject
	);
}

// ************************************************************************* //