#include <fvcSnGrad.hxx>

#include <fvMesh.hxx>
#include <snGradScheme.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fvc
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<class Type>
		tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
			snGrad
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf,
				const word& name
			)
		{
			return fv::snGradScheme<Type>::New
			(
				vf.mesh(),
				vf.mesh().snGradScheme(name)
			)().snGrad(vf);
		}


		template<class Type>
		tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
			snGrad
			(
				const tmp<GeometricField<Type, fvPatchField, volMesh>>& tvf,
				const word& name
			)
		{
			tmp<GeometricField<Type, fvsPatchField, surfaceMesh>> SnGrad
			(
				fvc::snGrad(tvf(), name)
			);
			tvf.clear();
			return SnGrad;
		}


		template<class Type>
		tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
			snGrad
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return fvc::snGrad(vf, "snGrad(" + vf.name() + ')');
		}


		template<class Type>
		tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
			snGrad
			(
				const tmp<GeometricField<Type, fvPatchField, volMesh>>& tvf
			)
		{
			tmp<GeometricField<Type, fvsPatchField, surfaceMesh>> SnGrad
			(
				fvc::snGrad(tvf())
			);
			tvf.clear();
			return SnGrad;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fvc

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //