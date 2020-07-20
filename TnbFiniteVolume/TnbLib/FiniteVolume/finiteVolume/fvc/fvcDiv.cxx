#include <fvcDiv.hxx>

#include <fvMesh.hxx>
#include <fvcSurfaceIntegrate.hxx>
#include <divScheme.hxx>
#include <convectionScheme.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fvc
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>>
			div
			(
				const GeometricField<Type, fvsPatchField, surfaceMesh>& ssf
			)
		{
			return tmp<GeometricField<Type, fvPatchField, volMesh>>
				(
					new GeometricField<Type, fvPatchField, volMesh>
					(
						"div(" + ssf.name() + ')',
						fvc::surfaceIntegrate(ssf)
						)
					);
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>>
			div
			(
				const tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>& tssf
			)
		{
			tmp<GeometricField<Type, fvPatchField, volMesh>> Div(fvc::div(tssf()));
			tssf.clear();
			return Div;
		}


		template<class Type>
		tmp
			<
			GeometricField
			<
			typename innerProduct<vector, Type>::type, fvPatchField, volMesh
			>
			>
			div
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf,
				const word& name
			)
		{
			return fv::divScheme<Type>::New
			(
				vf.mesh(), vf.mesh().divScheme(name)
			).ref().fvcDiv(vf);
		}


		template<class Type>
		tmp
			<
			GeometricField
			<
			typename innerProduct<vector, Type>::type, fvPatchField, volMesh
			>
			>
			div
			(
				const tmp<GeometricField<Type, fvPatchField, volMesh>>& tvvf,
				const word& name
			)
		{
			typedef typename innerProduct<vector, Type>::type DivType;
			tmp<GeometricField<DivType, fvPatchField, volMesh>> Div
			(
				fvc::div(tvvf(), name)
			);
			tvvf.clear();
			return Div;
		}

		template<class Type>
		tmp
			<
			GeometricField
			<
			typename innerProduct<vector, Type>::type, fvPatchField, volMesh
			>
			>
			div
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return fvc::div(vf, "div(" + vf.name() + ')');
		}


		template<class Type>
		tmp
			<
			GeometricField
			<
			typename innerProduct<vector, Type>::type, fvPatchField, volMesh
			>
			>
			div
			(
				const tmp<GeometricField<Type, fvPatchField, volMesh>>& tvvf
			)
		{
			typedef typename innerProduct<vector, Type>::type DivType;
			tmp<GeometricField<DivType, fvPatchField, volMesh>> Div(fvc::div(tvvf()));
			tvvf.clear();
			return Div;
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>>
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
			).ref().fvcDiv(flux, vf);
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>>
			div
			(
				const tmp<surfaceScalarField>& tflux,
				const GeometricField<Type, fvPatchField, volMesh>& vf,
				const word& name
			)
		{
			tmp<GeometricField<Type, fvPatchField, volMesh>> Div
			(
				fvc::div(tflux(), vf, name)
			);
			tflux.clear();
			return Div;
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>>
			div
			(
				const surfaceScalarField& flux,
				const tmp<GeometricField<Type, fvPatchField, volMesh>>& tvf,
				const word& name
			)
		{
			tmp<GeometricField<Type, fvPatchField, volMesh>> Div
			(
				fvc::div(flux, tvf(), name)
			);
			tvf.clear();
			return Div;
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>>
			div
			(
				const tmp<surfaceScalarField>& tflux,
				const tmp<GeometricField<Type, fvPatchField, volMesh>>& tvf,
				const word& name
			)
		{
			tmp<GeometricField<Type, fvPatchField, volMesh>> Div
			(
				fvc::div(tflux(), tvf(), name)
			);
			tflux.clear();
			tvf.clear();
			return Div;
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>>
			div
			(
				const surfaceScalarField& flux,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return fvc::div
			(
				flux, vf, "div(" + flux.name() + ',' + vf.name() + ')'
			);
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>>
			div
			(
				const tmp<surfaceScalarField>& tflux,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			tmp<GeometricField<Type, fvPatchField, volMesh>> Div
			(
				fvc::div(tflux(), vf)
			);
			tflux.clear();
			return Div;
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>>
			div
			(
				const surfaceScalarField& flux,
				const tmp<GeometricField<Type, fvPatchField, volMesh>>& tvf
			)
		{
			tmp<GeometricField<Type, fvPatchField, volMesh>> Div
			(
				fvc::div(flux, tvf())
			);
			tvf.clear();
			return Div;
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>>
			div
			(
				const tmp<surfaceScalarField>& tflux,
				const tmp<GeometricField<Type, fvPatchField, volMesh>>& tvf
			)
		{
			tmp<GeometricField<Type, fvPatchField, volMesh>> Div
			(
				fvc::div(tflux(), tvf())
			);
			tflux.clear();
			tvf.clear();
			return Div;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fvc

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
