#include <fvmDiv.hxx>

#include <fvMesh.hxx>
#include <fvMatrix.hxx>
#include <convectionScheme.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fvm
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<class Type>
		tmp<fvMatrix<Type>>
			div
			(
				const surfaceScalarField& flux,
				const GeometricField<Type, fvPatchField, volMesh>& vf,
				const word& name
			)
		{
			return fv::convectionScheme<Type>::New
			(
				vf.mesh(),
				flux,
				vf.mesh().divScheme(name)
			)().fvmDiv(flux, vf);
		}

		template<class Type>
		tmp<fvMatrix<Type>>
			div
			(
				const tmp<surfaceScalarField>& tflux,
				const GeometricField<Type, fvPatchField, volMesh>& vf,
				const word& name
			)
		{
			tmp<fvMatrix<Type>> Div(fvm::div(tflux(), vf, name));
			tflux.clear();
			return Div;
		}


		template<class Type>
		tmp<fvMatrix<Type>>
			div
			(
				const surfaceScalarField& flux,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return fvm::div(flux, vf, "div(" + flux.name() + ',' + vf.name() + ')');
		}

		template<class Type>
		tmp<fvMatrix<Type>>
			div
			(
				const tmp<surfaceScalarField>& tflux,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			tmp<fvMatrix<Type>> Div(fvm::div(tflux(), vf));
			tflux.clear();
			return Div;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fvm

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //