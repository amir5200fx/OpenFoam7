#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <UpwindFitScheme.hxx>
#include <quadraticUpwindFitPolynomial.hxx>
#include <upwindFECCellToFaceStencilObject.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTemplateTypeNameAndDebug
	(
		UpwindFitData<quadraticUpwindFitPolynomial>,
		0
	);

	makeUpwindFitSurfaceInterpolationScheme
	(
		quadraticUpwindFit,
		quadraticUpwindFitPolynomial,
		upwindFECCellToFaceStencilObject
	);
}

// ************************************************************************* //