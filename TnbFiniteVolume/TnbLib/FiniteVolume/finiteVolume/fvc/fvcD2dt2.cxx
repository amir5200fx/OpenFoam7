#include <fvcD2dt2.hxx>

#include <fvMesh.hxx>
#include <d2dt2Scheme.hxx>

#include <volMesh.hxx>  // added by amir
#include <GeometricFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fvc
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>>
			d2dt2
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return fv::d2dt2Scheme<Type>::New
			(
				vf.mesh(),
				vf.mesh().ddtScheme("d2dt2(" + vf.name() + ')')
			).ref().fvcD2dt2(vf);
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>>
			d2dt2
			(
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return fv::d2dt2Scheme<Type>::New
			(
				vf.mesh(),
				vf.mesh().ddtScheme("d2dt2(" + rho.name() + ',' + vf.name() + ')')
			).ref().fvcD2dt2(rho, vf);
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fvc

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //