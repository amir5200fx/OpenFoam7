#include <multivariateGaussConvectionScheme.hxx>

#include <gaussConvectionScheme.hxx>
#include <fvMatrices.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<class Type>
		tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
			multivariateGaussConvectionScheme<Type>::interpolate
			(
				const surfaceScalarField& faceFlux,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			) const
		{
			return gaussConvectionScheme<Type>
				(
					this->mesh(),
					faceFlux,
					tinterpScheme_()(vf)
					).interpolate(faceFlux, vf);
		}


		template<class Type>
		tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
			multivariateGaussConvectionScheme<Type>::flux
			(
				const surfaceScalarField& faceFlux,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			) const
		{
			return gaussConvectionScheme<Type>
				(
					this->mesh(),
					faceFlux,
					tinterpScheme_()(vf)
					).flux(faceFlux, vf);
		}


		template<class Type>
		tmp<fvMatrix<Type>>
			multivariateGaussConvectionScheme<Type>::fvmDiv
			(
				const surfaceScalarField& faceFlux,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			) const
		{
			return gaussConvectionScheme<Type>
				(
					this->mesh(),
					faceFlux,
					tinterpScheme_()(vf)
					).fvmDiv(faceFlux, vf);
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>>
			multivariateGaussConvectionScheme<Type>::fvcDiv
			(
				const surfaceScalarField& faceFlux,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			) const
		{
			return gaussConvectionScheme<Type>
				(
					this->mesh(),
					faceFlux,
					tinterpScheme_()(vf)
					).fvcDiv(faceFlux, vf);
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //