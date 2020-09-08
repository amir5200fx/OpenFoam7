#pragma once
#include <fvcSurfaceIntegrate.hxx>
#include <fvMatrices.hxx>
#include <fvmSup.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<class Type>
		tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
			boundedConvectionScheme<Type>::interpolate
			(
				const surfaceScalarField& phi,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			) const
		{
			return scheme_().interpolate(phi, vf);
		}


		template<class Type>
		tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
			boundedConvectionScheme<Type>::flux
			(
				const surfaceScalarField& faceFlux,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			) const
		{
			return scheme_().flux(faceFlux, vf);
		}


		template<class Type>
		tmp<fvMatrix<Type>>
			boundedConvectionScheme<Type>::fvmDiv
			(
				const surfaceScalarField& faceFlux,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			) const
		{
			return
				scheme_().fvmDiv(faceFlux, vf)
				- fvm::Sp(fvc::surfaceIntegrate(faceFlux), vf);
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>>
			boundedConvectionScheme<Type>::fvcDiv
			(
				const surfaceScalarField& faceFlux,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			) const
		{
			return
				scheme_().fvcDiv(faceFlux, vf)
				- fvc::surfaceIntegrate(faceFlux)*vf;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //