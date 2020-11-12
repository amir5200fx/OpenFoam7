#define FoamRegisterDebugSwitch_EXPORT_DEFINE

#include <Field.hxx>
#include <fvcGrad.hxx>
#include <polyMeshTetDecomposition.hxx>

#include <Basic.hxx>
#include <Dual.hxx>
#include <Moment.hxx>

// Scalar interpolation
defineNamedTemplateTypeNameAndDebug(tnbLib::AveragingMethod<tnbLib::scalar>, 0);
namespace tnbLib
{
	defineTemplateRunTimeSelectionTable
	(
		AveragingMethod<tnbLib::scalar>,
		dictionary
	);
}

// Vector interpolation
defineNamedTemplateTypeNameAndDebug(tnbLib::AveragingMethod<tnbLib::vector>, 0);
namespace tnbLib
{
	defineTemplateRunTimeSelectionTable
	(
		tnbLib::AveragingMethod<tnbLib::vector>,
		dictionary
	);
}


// Basic interpolation
defineNamedTemplateTypeNameAndDebug
(
	tnbLib::AveragingMethods::Basic<tnbLib::scalar>,
	0
);
tnbLib::AveragingMethod<tnbLib::scalar>::
adddictionaryConstructorToTable<tnbLib::AveragingMethods::Basic<tnbLib::scalar>>
addBasicscalarConstructorToTable_;

defineNamedTemplateTypeNameAndDebug
(
	tnbLib::AveragingMethods::Basic<tnbLib::vector>,
	0
);
tnbLib::AveragingMethod<tnbLib::vector>::
adddictionaryConstructorToTable<tnbLib::AveragingMethods::Basic<tnbLib::vector>>
addBasicvectorConstructorToTable_;


// Dual interpolation
defineNamedTemplateTypeNameAndDebug
(
	tnbLib::AveragingMethods::Dual<tnbLib::scalar>,
	0
);
tnbLib::AveragingMethod<tnbLib::scalar>::
adddictionaryConstructorToTable<tnbLib::AveragingMethods::Dual<tnbLib::scalar>>
addDualscalarConstructorToTable_;

defineNamedTemplateTypeNameAndDebug
(
	tnbLib::AveragingMethods::Dual<tnbLib::vector>,
	0
);
tnbLib::AveragingMethod<tnbLib::vector>::
adddictionaryConstructorToTable<tnbLib::AveragingMethods::Dual<tnbLib::vector>>
addDualvectorConstructorToTable_;


// Moment interpolation
defineNamedTemplateTypeNameAndDebug
(
	tnbLib::AveragingMethods::Moment<tnbLib::scalar>,
	0
);
tnbLib::AveragingMethod<tnbLib::scalar>::
adddictionaryConstructorToTable<tnbLib::AveragingMethods::Moment<tnbLib::scalar>>
addMomentscalarConstructorToTable_;

defineNamedTemplateTypeNameAndDebug
(
	tnbLib::AveragingMethods::Moment<tnbLib::vector>,
	0
);
tnbLib::AveragingMethod<tnbLib::vector>::
adddictionaryConstructorToTable<tnbLib::AveragingMethods::Moment<tnbLib::vector>>
addMomentvectorConstructorToTable_;


// ************************************************************************* //