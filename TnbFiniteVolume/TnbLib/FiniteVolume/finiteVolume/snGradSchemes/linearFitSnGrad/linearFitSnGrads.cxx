#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <CentredFitSnGradScheme.hxx>
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