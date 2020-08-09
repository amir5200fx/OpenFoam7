#include <linearFitPolynomial.hxx>

#include <CentredFitScheme.hxx>
#include <centredCFCCellToFaceStencilObject.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTemplateTypeNameAndDebug
	(
		CentredFitData<linearFitPolynomial>,
		0
	);

	makeCentredFitSurfaceInterpolationScheme
	(
		linearFit,
		linearFitPolynomial,
		centredCFCCellToFaceStencilObject
	);
}

// ************************************************************************* //