#include <CentredFitScheme.hxx>
#include <quadraticLinearFitPolynomial.hxx>
#include <centredCFCCellToFaceStencilObject.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTemplateTypeNameAndDebug
	(
		CentredFitData<quadraticLinearFitPolynomial>,
		0
	);

	makeCentredFitSurfaceInterpolationScheme
	(
		quadraticLinearFit,
		quadraticLinearFitPolynomial,
		centredCFCCellToFaceStencilObject
	);
}

// ************************************************************************* //