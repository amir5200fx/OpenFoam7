#include <pointFields.hxx>

#include <polyMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	defineTemplate2TypeNameAndDebug(pointScalarField::Internal, 0);
	defineTemplate2TypeNameAndDebug(pointVectorField::Internal, 0);
	defineTemplate2TypeNameAndDebug
	(
		pointSphericalTensorField::Internal,
		0
	);
	defineTemplate2TypeNameAndDebug
	(
		pointSymmTensorField::Internal,
		0
	);
	defineTemplate2TypeNameAndDebug(pointTensorField::Internal, 0);


	defineTemplateTypeNameAndDebug(pointScalarField, 0);
	defineTemplateTypeNameAndDebug(pointVectorField, 0);
	defineTemplateTypeNameAndDebug(pointSphericalTensorField, 0);
	defineTemplateTypeNameAndDebug(pointSymmTensorField, 0);
	defineTemplateTypeNameAndDebug(pointTensorField, 0);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //