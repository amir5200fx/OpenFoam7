#pragma once
#include <fvcSurfaceIntegrate.hxx>
#include <fvMatrices.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<class Type>
		tmp
			<
			GeometricField
			<typename innerProduct<vector, Type>::type, fvPatchField, volMesh>
			>
			gaussDivScheme<Type>::fvcDiv
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			tmp
				<
				GeometricField
				<typename innerProduct<vector, Type>::type, fvPatchField, volMesh>
				> tDiv
				(
					fvc::surfaceIntegrate
					(
						this->tinterpScheme_().dotInterpolate(this->mesh_.Sf(), vf)
					)
				);

			tDiv.ref().rename("div(" + vf.name() + ')');

			return tDiv;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //