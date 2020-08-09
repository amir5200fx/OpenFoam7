#include <CentredFitSnGradScheme.hxx>
#include <quadraticFitPolynomial.hxx>
#include <centredCFCCellToFaceStencilObject.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTemplateTypeNameAndDebug
	(
		CentredFitSnGradData<quadraticFitPolynomial>,
		0
	);
}

makeCentredFitSnGradScheme
(
	quadraticFit,
	quadraticFitPolynomial,
	centredCFCCellToFaceStencilObject
);


// ************************************************************************* //