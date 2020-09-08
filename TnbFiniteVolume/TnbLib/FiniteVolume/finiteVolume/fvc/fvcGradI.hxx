#pragma once
#include <fvcSurfaceIntegrate.hxx>
#include <fvMesh.hxx>
#include <gaussGrad.hxx>

#include <surfaceMesh.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fvc
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<class Type>
		tmp
			<
			GeometricField
			<
			typename outerProduct<vector, Type>::type, fvPatchField, volMesh
			>
			>
			grad
			(
				const GeometricField<Type, fvsPatchField, surfaceMesh>& ssf
			)
		{
			return fv::gaussGrad<Type>::gradf(ssf, "grad(" + ssf.name() + ')');
		}


		template<class Type>
		tmp
			<
			GeometricField
			<
			typename outerProduct<vector, Type>::type, fvPatchField, volMesh
			>
			>
			grad
			(
				const tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>& tssf
			)
		{
			typedef typename outerProduct<vector, Type>::type GradType;
			tmp<GeometricField<GradType, fvPatchField, volMesh>> Grad
			(
				fvc::grad(tssf())
			);
			tssf.clear();
			return Grad;
		}


		template<class Type>
		tmp
			<
			GeometricField
			<
			typename outerProduct<vector, Type>::type, fvPatchField, volMesh
			>
			>
			grad
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf,
				const word& name
			)
		{
			return fv::gradScheme<Type>::New
			(
				vf.mesh(),
				vf.mesh().gradScheme(name)
			)().grad(vf, name);
		}


		template<class Type>
		tmp
			<
			GeometricField
			<
			typename outerProduct<vector, Type>::type, fvPatchField, volMesh
			>
			>
			grad
			(
				const tmp<GeometricField<Type, fvPatchField, volMesh>>& tvf,
				const word& name
			)
		{
			tmp
				<
				GeometricField
				<
				typename outerProduct<vector, Type>::type, fvPatchField, volMesh
				>
				> tGrad
				(
					fvc::grad(tvf(), name)
				);
			tvf.clear();
			return tGrad;
		}


		template<class Type>
		tmp
			<
			GeometricField
			<
			typename outerProduct<vector, Type>::type, fvPatchField, volMesh
			>
			>
			grad
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return fvc::grad(vf, "grad(" + vf.name() + ')');
		}


		template<class Type>
		tmp
			<
			GeometricField
			<
			typename outerProduct<vector, Type>::type, fvPatchField, volMesh
			>
			>
			grad
			(
				const tmp<GeometricField<Type, fvPatchField, volMesh>>& tvf
			)
		{
			typedef typename outerProduct<vector, Type>::type GradType;
			tmp<GeometricField<GradType, fvPatchField, volMesh>> Grad
			(
				fvc::grad(tvf())
			);
			tvf.clear();
			return Grad;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fvc

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //