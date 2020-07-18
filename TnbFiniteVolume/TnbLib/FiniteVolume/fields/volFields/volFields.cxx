#include <volFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	defineTemplate2TypeNameAndDebug(volScalarField::Internal, 0);
	defineTemplate2TypeNameAndDebug(volVectorField::Internal, 0);
	defineTemplate2TypeNameAndDebug
	(
		volSphericalTensorField::Internal,
		0
	);
	defineTemplate2TypeNameAndDebug
	(
		volSymmTensorField::Internal,
		0
	);
	defineTemplate2TypeNameAndDebug(volTensorField::Internal, 0);

	defineTemplateTypeNameAndDebug(volScalarField, 0);
	defineTemplateTypeNameAndDebug(volVectorField, 0);
	defineTemplateTypeNameAndDebug(volSphericalTensorField, 0);
	defineTemplateTypeNameAndDebug(volSymmTensorField, 0);
	defineTemplateTypeNameAndDebug(volTensorField, 0);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	// specialization for scalar fields
	template<>
	tmp<GeometricField<scalar, fvPatchField, volMesh>>
		GeometricField<scalar, fvPatchField, volMesh>::component
		(
			const direction
		) const
	{
		return *this;
	}


	// specialization for scalar fields
	template<>
	void GeometricField<scalar, fvPatchField, volMesh>::replace
	(
		const direction,
		const GeometricField<scalar, fvPatchField, volMesh>& gsf
	)
	{
		*this == gsf;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //