#include <biLinearFitPolynomial.hxx>

#include <CentredFitScheme.hxx>
#include <centredCFCCellToFaceStencilObject.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTemplateTypeNameAndDebug
	(
		CentredFitData<biLinearFitPolynomial>,
		0
	);

	makeCentredFitSurfaceInterpolationScheme
	(
		biLinearFit,
		biLinearFitPolynomial,
		centredCFCCellToFaceStencilObject
	);
}

// ************************************************************************* //