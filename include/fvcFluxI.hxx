#pragma once
#include <fvMesh.hxx>
#include <convectionScheme.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fvc
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<class Type>
		tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
			flux
			(
				const surfaceScalarField& phi,
				const GeometricField<Type, fvPatchField, volMesh>& vf,
				const word& name
			)
		{
			return fv::convectionScheme<Type>::New
			(
				vf.mesh(),
				phi,
				vf.mesh().divScheme(name)
			)().flux(phi, vf);
		}


		template<class Type>
		tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
			flux
			(
				const tmp<surfaceScalarField>& tphi,
				const GeometricField<Type, fvPatchField, volMesh>& vf,
				const word& name
			)
		{
			tmp<GeometricField<Type, fvsPatchField, surfaceMesh>> Flux
			(
				fvc::flux(tphi(), vf, name)
			);
			tphi.clear();
			return Flux;
		}


		template<class Type>
		tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
			flux
			(
				const surfaceScalarField& phi,
				const tmp<GeometricField<Type, fvPatchField, volMesh>>& tvf,
				const word& name
			)
		{
			tmp<GeometricField<Type, fvsPatchField, surfaceMesh>> Flux
			(
				fvc::flux(phi, tvf(), name)
			);
			tvf.clear();
			return Flux;
		}


		template<class Type>
		tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
			flux
			(
				const tmp<surfaceScalarField>& tphi,
				const tmp<GeometricField<Type, fvPatchField, volMesh>>& tvf,
				const word& name
			)
		{
			tmp<GeometricField<Type, fvsPatchField, surfaceMesh>> Flux
			(
				fvc::flux(tphi(), tvf(), name)
			);
			tphi.clear();
			tvf.clear();
			return Flux;
		}


		template<class Type>
		tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
			flux
			(
				const surfaceScalarField& phi,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return fvc::flux
			(
				phi, vf, "flux(" + phi.name() + ',' + vf.name() + ')'
			);
		}


		template<class Type>
		tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
			flux
			(
				const tmp<surfaceScalarField>& tphi,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			tmp<GeometricField<Type, fvsPatchField, surfaceMesh>> Flux
			(
				fvc::flux(tphi(), vf)
			);
			tphi.clear();
			return Flux;
		}


		template<class Type>
		tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
			flux
			(
				const surfaceScalarField& phi,
				const tmp<GeometricField<Type, fvPatchField, volMesh>>& tvf
			)
		{
			tmp<GeometricField<Type, fvsPatchField, surfaceMesh>> Flux
			(
				fvc::flux(phi, tvf())
			);
			tvf.clear();
			return Flux;
		}


		template<class Type>
		tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
			flux
			(
				const tmp<surfaceScalarField>& tphi,
				const tmp<GeometricField<Type, fvPatchField, volMesh>>& tvf
			)
		{
			tmp<GeometricField<Type, fvsPatchField, surfaceMesh>> Flux
			(
				fvc::flux(tphi(), tvf())
			);
			tphi.clear();
			tvf.clear();
			return Flux;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fvc

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //