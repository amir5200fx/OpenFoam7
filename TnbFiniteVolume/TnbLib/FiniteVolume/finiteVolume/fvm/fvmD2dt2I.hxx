#pragma once
#include <surfaceFields.hxx>
#include <fvMatrix.hxx>
#include <d2dt2Scheme.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fvm
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<class Type>
		tmp<fvMatrix<Type>>
			d2dt2
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return fv::d2dt2Scheme<Type>::New
			(
				vf.mesh(),
				vf.mesh().d2dt2Scheme("d2dt2(" + vf.name() + ')')
			).ref().fvmD2dt2(vf);
		}


		template<class Type>
		tmp<fvMatrix<Type>>
			d2dt2
			(
				const dimensionedScalar& rho,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return fv::d2dt2Scheme<Type>::New
			(
				vf.mesh(),
				vf.mesh().d2dt2Scheme("d2dt2(" + rho.name() + ',' + vf.name() + ')')
			).ref().fvmD2dt2(rho, vf);
		}


		template<class Type>
		tmp<fvMatrix<Type>>
			d2dt2
			(
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return fv::d2dt2Scheme<Type>::New
			(
				vf.mesh(),
				vf.mesh().d2dt2Scheme("d2dt2(" + rho.name() + ',' + vf.name() + ')')
			).ref().fvmD2dt2(rho, vf);
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fvm

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //