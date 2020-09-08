#include <fvcMagSqrGradGrad.hxx>

#include <fvcGrad.hxx>
#include <fvMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fvc
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<class Type>
		tmp<volScalarField> magSqrGradGrad
		(
			const GeometricField<Type, fvPatchField, volMesh>& vf
		)
		{
			tmp<volScalarField> tMagSqrGradGrad
			(
				magSqr(fvc::grad(fvc::grad(vf.component(0))))
			);

			// Loop over other vector field components
			for (direction cmpt = 1; cmpt < pTraits<Type>::nComponents; cmpt++)
			{
				tMagSqrGradGrad.ref() +=
					magSqr(fvc::grad(fvc::grad(vf.component(cmpt))))();
			}

			return tMagSqrGradGrad;
		}


		template<class Type>
		tmp<volScalarField>
			magSqrGradGrad
			(
				const tmp<GeometricField<Type, fvPatchField, volMesh>>& tvf
			)
		{
			tmp<volScalarField> tMagSqrGradGrad(fvc::magSqrGradGrad(tvf()));
			tvf.clear();
			return tMagSqrGradGrad;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fvc

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //