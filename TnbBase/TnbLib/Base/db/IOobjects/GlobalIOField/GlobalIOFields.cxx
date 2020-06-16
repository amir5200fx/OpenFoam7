#include <GlobalIOField.hxx>

// added by amir
#include <vector.hxx>
#include <sphericalTensor.hxx>
#include <symmTensor.hxx>
#include <tensor.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTemplateTypeNameAndDebugWithName
	(
		GlobalIOField<scalar>,
		"scalarField",
		0
	);
	defineTemplateTypeNameAndDebugWithName
	(
		GlobalIOField<vector>,
		"vectorField",
		0
	);
	defineTemplateTypeNameAndDebugWithName
	(
		GlobalIOField<sphericalTensor>,
		"sphericalTensorField",
		0
	);
	defineTemplateTypeNameAndDebugWithName
	(
		GlobalIOField<symmTensor>,
		"symmTensorField",
		0
	);
	defineTemplateTypeNameAndDebugWithName
	(
		GlobalIOField<tensor>,
		"tensorField",
		0
	);
}


// ************************************************************************* //