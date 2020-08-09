#include <UpwindFitScheme.hxx>

#include <cubicUpwindFitPolynomial.hxx>
#include <upwindCFCCellToFaceStencilObject.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTemplateTypeNameAndDebug
	(
		UpwindFitData<cubicUpwindFitPolynomial>,
		0
	);

	makeUpwindFitSurfaceInterpolationScheme
	(
		cubicUpwindFit,
		cubicUpwindFitPolynomial,
		upwindCFCCellToFaceStencilObject
	);
}

// ************************************************************************* //