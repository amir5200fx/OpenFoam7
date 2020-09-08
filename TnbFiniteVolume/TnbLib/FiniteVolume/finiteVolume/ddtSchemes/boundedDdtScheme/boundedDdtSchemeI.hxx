#pragma once
#include <fvcDiv.hxx>
#include <fvcDdt.hxx>
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
		tmp<GeometricField<Type, fvPatchField, volMesh>>
			boundedDdtScheme<Type>::fvcDdt
			(
				const dimensioned<Type>& dt
			)
		{
			return scheme_.ref().fvcDdt(dt);
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>>
			boundedDdtScheme<Type>::fvcDdt
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return scheme_.ref().fvcDdt(vf);
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>>
			boundedDdtScheme<Type>::fvcDdt
			(
				const dimensionedScalar& rho,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return scheme_.ref().fvcDdt(rho, vf);
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>>
			boundedDdtScheme<Type>::fvcDdt
			(
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return scheme_.ref().fvcDdt(rho, vf) - fvc::ddt(rho)*vf;
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>>
			boundedDdtScheme<Type>::fvcDdt
			(
				const volScalarField& alpha,
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return scheme_.ref().fvcDdt(alpha, rho, vf) - fvc::ddt(alpha, rho)*vf;
		}


		template<class Type>
		tmp<fvMatrix<Type>>
			boundedDdtScheme<Type>::fvmDdt
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return scheme_.ref().fvmDdt(vf);
		}


		template<class Type>
		tmp<fvMatrix<Type>>
			boundedDdtScheme<Type>::fvmDdt
			(
				const dimensionedScalar& rho,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return scheme_.ref().fvmDdt(rho, vf);
		}


		template<class Type>
		tmp<fvMatrix<Type>>
			boundedDdtScheme<Type>::fvmDdt
			(
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return scheme_.ref().fvmDdt(rho, vf) - fvm::Sp(fvc::ddt(rho), vf);
		}


		template<class Type>
		tmp<fvMatrix<Type>>
			boundedDdtScheme<Type>::fvmDdt
			(
				const volScalarField& alpha,
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return
				scheme_.ref().fvmDdt(alpha, rho, vf)
				- fvm::Sp(fvc::ddt(alpha, rho), vf);
		}


		template<class Type>
		tmp<typename boundedDdtScheme<Type>::fluxFieldType>
			boundedDdtScheme<Type>::fvcDdtUfCorr
			(
				const GeometricField<Type, fvPatchField, volMesh>& U,
				const GeometricField<Type, fvsPatchField, surfaceMesh>& Uf
			)
		{
			return scheme_.ref().fvcDdtUfCorr(U, Uf);
		}


		template<class Type>
		tmp<typename boundedDdtScheme<Type>::fluxFieldType>
			boundedDdtScheme<Type>::fvcDdtPhiCorr
			(
				const GeometricField<Type, fvPatchField, volMesh>& U,
				const fluxFieldType& phi
			)
		{
			return scheme_.ref().fvcDdtPhiCorr(U, phi);
		}


		template<class Type>
		tmp<typename boundedDdtScheme<Type>::fluxFieldType>
			boundedDdtScheme<Type>::fvcDdtUfCorr
			(
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& U,
				const GeometricField<Type, fvsPatchField, surfaceMesh>& Uf
			)
		{
			return scheme_.ref().fvcDdtUfCorr(rho, U, Uf);
		}


		template<class Type>
		tmp<typename boundedDdtScheme<Type>::fluxFieldType>
			boundedDdtScheme<Type>::fvcDdtPhiCorr
			(
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& U,
				const fluxFieldType& phi
			)
		{
			return scheme_.ref().fvcDdtPhiCorr(rho, U, phi);
		}


		template<class Type>
		tmp<surfaceScalarField> boundedDdtScheme<Type>::meshPhi
		(
			const GeometricField<Type, fvPatchField, volMesh>& vf
		)
		{
			return scheme_.ref().meshPhi(vf);
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //