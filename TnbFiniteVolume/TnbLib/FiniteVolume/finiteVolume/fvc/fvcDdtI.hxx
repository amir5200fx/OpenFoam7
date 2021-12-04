#pragma once
#include <fvMesh.hxx>
#include <ddtScheme.hxx>

#include <GeometricFields.hxx>  // added by amir
#include <volMesh.hxx>  // added by amir
#include <fvBoundaryMesh.hxx>  // added by amir
#include <fvPatchFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fvc
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>>
			ddt
			(
				const dimensioned<Type> dt,
				const fvMesh& mesh
			)
		{
			return fv::ddtScheme<Type>::New
			(
				mesh,
				mesh.ddtScheme("ddt(" + dt.name() + ')')
			).ref().fvcDdt(dt);
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>>
			ddt
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return fv::ddtScheme<Type>::New
			(
				vf.mesh(),
				vf.mesh().ddtScheme("ddt(" + vf.name() + ')')
			).ref().fvcDdt(vf);
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>>
			ddt
			(
				const dimensionedScalar& rho,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return fv::ddtScheme<Type>::New
			(
				vf.mesh(),
				vf.mesh().ddtScheme("ddt(" + rho.name() + ',' + vf.name() + ')')
			).ref().fvcDdt(rho, vf);
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>>
			ddt
			(
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return fv::ddtScheme<Type>::New
			(
				vf.mesh(),
				vf.mesh().ddtScheme("ddt(" + rho.name() + ',' + vf.name() + ')')
			).ref().fvcDdt(rho, vf);
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>>
			ddt
			(
				const volScalarField& alpha,
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return fv::ddtScheme<Type>::New
			(
				vf.mesh(),
				vf.mesh().ddtScheme
				(
					"ddt("
					+ alpha.name() + ','
					+ rho.name() + ','
					+ vf.name() + ')'
				)
			).ref().fvcDdt(alpha, rho, vf);
		}


		template<class Type>
		tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
			ddt
			(
				const GeometricField<Type, fvsPatchField, surfaceMesh>& sf
			)
		{
			return fv::ddtScheme<Type>::New
			(
				sf.mesh(),
				sf.mesh().ddtScheme("ddt(" + sf.name() + ')')
			).ref().fvcDdt(sf);
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>>
			ddt
			(
				const one&,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return ddt(vf);
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>>
			ddt
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf,
				const one&
			)
		{
			return ddt(vf);
		}


		template<class Type>
		tmp<GeometricField<typename tnbLib::flux<Type>::type, fvsPatchField, surfaceMesh>>
			ddtCorr
			(
				const GeometricField<Type, fvPatchField, volMesh>& U,
				const GeometricField<Type, fvsPatchField, surfaceMesh>& Uf
			)
		{
			return fv::ddtScheme<Type>::New
			(
				U.mesh(),
				U.mesh().ddtScheme("ddt(" + U.name() + ')')
			).ref().fvcDdtUfCorr(U, Uf);
		}


		template<class Type>
		tmp<GeometricField<typename tnbLib::flux<Type>::type, fvsPatchField, surfaceMesh>>
			ddtCorr
			(
				const GeometricField<Type, fvPatchField, volMesh>& U,
				const GeometricField
				<
				typename tnbLib::flux<Type>::type,
				fvsPatchField,
				surfaceMesh
				>& phi
			)
		{
			return fv::ddtScheme<Type>::New
			(
				U.mesh(),
				U.mesh().ddtScheme("ddt(" + U.name() + ')')
			).ref().fvcDdtPhiCorr(U, phi);
		}


		template<class Type>
		tmp<GeometricField<typename tnbLib::flux<Type>::type, fvsPatchField, surfaceMesh>>
			ddtCorr
			(
				const GeometricField<Type, fvPatchField, volMesh>& U,
				const GeometricField
				<
				typename tnbLib::flux<Type>::type,
				fvsPatchField,
				surfaceMesh
				>& phi,
				const autoPtr<GeometricField<Type, fvsPatchField, surfaceMesh>>& Uf
			)
		{
			if (U.mesh().dynamic())
			{
				return ddtCorr(U, Uf());
			}
			else
			{
				return ddtCorr(U, phi);
			}
		}


		template<class Type>
		tmp<GeometricField<typename tnbLib::flux<Type>::type, fvsPatchField, surfaceMesh>>
			ddtCorr
			(
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& U,
				const GeometricField<Type, fvsPatchField, surfaceMesh>& Uf
			)
		{
			return fv::ddtScheme<Type>::New
			(
				U.mesh(),
				U.mesh().ddtScheme("ddt(" + U.name() + ')')
			).ref().fvcDdtUfCorr(rho, U, Uf);
		}


		template<class Type>
		tmp<GeometricField<typename tnbLib::flux<Type>::type, fvsPatchField, surfaceMesh>>
			ddtCorr
			(
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& U,
				const GeometricField
				<
				typename tnbLib::flux<Type>::type,
				fvsPatchField,
				surfaceMesh
				>& phi
			)
		{
			return fv::ddtScheme<Type>::New
			(
				U.mesh(),
				U.mesh().ddtScheme("ddt(" + rho.name() + ',' + U.name() + ')')
			).ref().fvcDdtPhiCorr(rho, U, phi);
		}


		template<class Type>
		tmp<GeometricField<typename tnbLib::flux<Type>::type, fvsPatchField, surfaceMesh>>
			ddtCorr
			(
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& U,
				const GeometricField
				<
				typename tnbLib::flux<Type>::type,
				fvsPatchField,
				surfaceMesh
				>& phi,
				const autoPtr<GeometricField<Type, fvsPatchField, surfaceMesh>>& Uf
			)
		{
			if (U.mesh().dynamic())
			{
				return ddtCorr(rho, U, Uf());
			}
			else
			{
				return ddtCorr(rho, U, phi);
			}
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fvc

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //