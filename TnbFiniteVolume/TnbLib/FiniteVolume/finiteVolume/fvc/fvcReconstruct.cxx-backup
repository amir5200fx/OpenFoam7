#include <fvcReconstruct.hxx>

#include <fvMesh.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <fvcSurfaceIntegrate.hxx>
#include <extrapolatedCalculatedFvPatchFields.hxx>

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
			reconstruct
			(
				const GeometricField<Type, fvsPatchField, surfaceMesh>& ssf
			)
		{
			typedef typename outerProduct<vector, Type>::type GradType;

			const fvMesh& mesh = ssf.mesh();

			surfaceVectorField SfHat(mesh.Sf() / mesh.magSf());

			tmp<GeometricField<GradType, fvPatchField, volMesh>> treconField
			(
				new GeometricField<GradType, fvPatchField, volMesh>
				(
					IOobject
					(
						"volIntegrate(" + ssf.name() + ')',
						ssf.instance(),
						mesh,
						IOobject::NO_READ,
						IOobject::NO_WRITE
					),
					mesh,
					dimensioned<GradType>("0", ssf.dimensions() / dimArea, Zero),
					extrapolatedCalculatedFvPatchField<GradType>::typeName
					)
			);

			if (!mesh.nGeometricD())
			{
				return treconField;
			}

			treconField.ref() = inv(surfaceSum(SfHat*mesh.Sf()))&surfaceSum(SfHat*ssf),

				treconField.ref().correctBoundaryConditions();

			return treconField;
		}


		template<class Type>
		tmp
			<
			GeometricField
			<
			typename outerProduct<vector, Type>::type, fvPatchField, volMesh
			>
			>
			reconstruct
			(
				const tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>& tssf
			)
		{
			typedef typename outerProduct<vector, Type>::type GradType;
			tmp<GeometricField<GradType, fvPatchField, volMesh>> tvf
			(
				fvc::reconstruct(tssf())
			);
			tssf.clear();
			return tvf;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fvc

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //