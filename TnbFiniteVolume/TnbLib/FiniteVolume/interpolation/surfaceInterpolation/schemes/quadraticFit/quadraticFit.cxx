#include <CentredFitScheme.hxx>
#include <quadraticFitPolynomial.hxx>
#include <centredCFCCellToFaceStencilObject.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTemplateTypeNameAndDebug
	(
		CentredFitData<quadraticFitPolynomial>,
		0
	);

	makeCentredFitSurfaceInterpolationScheme
	(
		quadraticFit,
		quadraticFitPolynomial,
		centredCFCCellToFaceStencilObject
	);
}

// ************************************************************************* //