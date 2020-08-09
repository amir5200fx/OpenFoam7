#include <PureUpwindFitScheme.hxx>

#include <linearFitPolynomial.hxx>
#include <pureUpwindCFCCellToFaceStencilObject.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTemplateTypeNameAndDebug
	(
		UpwindFitData<linearFitPolynomial>,
		0
	);

	makePureUpwindFitSurfaceInterpolationScheme
	(
		linearPureUpwindFit,
		linearFitPolynomial,
		pureUpwindCFCCellToFaceStencilObject
	);
}

// ************************************************************************* //