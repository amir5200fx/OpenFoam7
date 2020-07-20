#include <CentredFitSnGradData.hxx>
#include <linearFitPolynomial.hxx>
#include <centredFECCellToFaceStencilObject.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTemplateTypeNameAndDebug
	(
		CentredFitSnGradData<linearFitPolynomial>,
		0
	);
}

makeCentredFitSnGradScheme
(
	linearFit,
	linearFitPolynomial,
	centredFECCellToFaceStencilObject
);

// ************************************************************************* //