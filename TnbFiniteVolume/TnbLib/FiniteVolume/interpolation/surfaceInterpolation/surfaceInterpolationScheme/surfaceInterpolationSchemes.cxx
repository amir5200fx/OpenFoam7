#include <surfaceInterpolationScheme.hxx>

#include <GeometricField.hxx>  // added by amir
#include <fvBoundaryMesh.hxx>  // added by amir
#include <surfaceMesh.hxx>     // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makeBaseSurfaceInterpolationScheme(Type)                               \
                                                                               \
defineNamedTemplateTypeNameAndDebug(surfaceInterpolationScheme<Type>, 0);      \
                                                                               \
defineTemplateRunTimeSelectionTable                                            \
(                                                                              \
    surfaceInterpolationScheme<Type>,                                          \
    Mesh                                                                       \
);                                                                             \
                                                                               \
defineTemplateRunTimeSelectionTable                                            \
(                                                                              \
    surfaceInterpolationScheme<Type>,                                          \
    MeshFlux                                                                   \
);

	makeBaseSurfaceInterpolationScheme(scalar)
		makeBaseSurfaceInterpolationScheme(vector)
		makeBaseSurfaceInterpolationScheme(sphericalTensor)
		makeBaseSurfaceInterpolationScheme(symmTensor)
		makeBaseSurfaceInterpolationScheme(tensor)

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<>
tnbLib::tmp
<
	tnbLib::GeometricField
	<
	typename tnbLib::innerProduct<tnbLib::vector, tnbLib::scalar>::type,
	tnbLib::fvsPatchField,
	tnbLib::surfaceMesh
	>
>
tnbLib::surfaceInterpolationScheme<tnbLib::scalar>::dotInterpolate
(
	const surfaceVectorField& Sf,
	const GeometricField<scalar, fvPatchField, volMesh>&
) const
{
	NotImplemented;

	return
		tmp
		<
		GeometricField
		<
		typename innerProduct<vector, scalar>::type,
		fvsPatchField,
		surfaceMesh
		>
		>
		(
			GeometricField
			<
			typename innerProduct<vector, scalar>::type,
			fvsPatchField,
			surfaceMesh
			>::null()
			);
}


// ************************************************************************* //