#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#define FoamDimensionedField_EXPORT_DEFINE
#define FoamGeometricField_EXPORT_DEFINE
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	defineTemplate2TypeNameAndDebug
	(
		surfaceScalarField::Internal,
		0
	);
	defineTemplate2TypeNameAndDebug
	(
		surfaceVectorField::Internal,
		0
	);
	defineTemplate2TypeNameAndDebug
	(
		surfaceSphericalTensorField::Internal,
		0
	);
	defineTemplate2TypeNameAndDebug
	(
		surfaceSymmTensorField::Internal,
		0
	);
	defineTemplate2TypeNameAndDebug
	(
		surfaceTensorField::Internal,
		0
	);

}

namespace tnbLib
{
	defineTemplateTypeNameAndDebug(surfaceScalarField, 0);
	defineTemplateTypeNameAndDebug(surfaceVectorField, 0);
	defineTemplateTypeNameAndDebug(surfaceSphericalTensorField, 0);
	defineTemplateTypeNameAndDebug(surfaceSymmTensorField, 0);
	defineTemplateTypeNameAndDebug(surfaceTensorField, 0);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //