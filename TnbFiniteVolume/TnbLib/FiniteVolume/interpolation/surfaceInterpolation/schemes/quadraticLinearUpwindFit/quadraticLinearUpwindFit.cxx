#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <UpwindFitScheme.hxx>
#include <quadraticLinearUpwindFitPolynomial.hxx>
#include <upwindFECCellToFaceStencilObject.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTemplateTypeNameAndDebug
	(
		UpwindFitData<quadraticLinearUpwindFitPolynomial>,
		0
	);

	makeUpwindFitSurfaceInterpolationScheme
	(
		quadraticLinearUpwindFit,
		quadraticLinearUpwindFitPolynomial,
		upwindFECCellToFaceStencilObject
	);
}

// ************************************************************************* //