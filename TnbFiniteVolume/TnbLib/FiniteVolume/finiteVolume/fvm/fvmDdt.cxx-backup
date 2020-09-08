#include <fvmDdt.hxx>

#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <fvMatrix.hxx>
#include <ddtScheme.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fvm
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<class Type>
		tmp<fvMatrix<Type>>
			ddt
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return fv::ddtScheme<Type>::New
			(
				vf.mesh(),
				vf.mesh().ddtScheme("ddt(" + vf.name() + ')')
			).ref().fvmDdt(vf);
		}


		template<class Type>
		tmp<fvMatrix<Type>>
			ddt
			(
				const one&,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return ddt(vf);
		}


		template<class Type>
		tmp<fvMatrix<Type>>
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
			).ref().fvmDdt(rho, vf);
		}


		template<class Type>
		tmp<fvMatrix<Type>>
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
			).ref().fvmDdt(rho, vf);
		}


		template<class Type>
		tmp<fvMatrix<Type>>
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
			).ref().fvmDdt(alpha, rho, vf);
		}


		template<class Type>
		tmp<fvMatrix<Type>>
			ddt
			(
				const one&,
				const one&,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return ddt(vf);
		}


		template<class Type>
		tmp<fvMatrix<Type>>
			ddt
			(
				const one&,
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return ddt(rho, vf);
		}


		template<class Type>
		tmp<fvMatrix<Type>>
			ddt
			(
				const volScalarField& alpha,
				const one&,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return ddt(alpha, vf);
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fvm

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //