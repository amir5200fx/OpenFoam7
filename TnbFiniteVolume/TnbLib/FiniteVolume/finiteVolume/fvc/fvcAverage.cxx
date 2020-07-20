#include <fvcAverage.hxx>

#include <fvcSurfaceIntegrate.hxx>
#include <fvMesh.hxx>
#include <linear.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fvc
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>>
			average
			(
				const GeometricField<Type, fvsPatchField, surfaceMesh>& ssf
			)
		{
			const fvMesh& mesh = ssf.mesh();

			tmp<GeometricField<Type, fvPatchField, volMesh>> taverage
			(
				new GeometricField<Type, fvPatchField, volMesh>
				(
					IOobject
					(
						"average(" + ssf.name() + ')',
						ssf.instance(),
						mesh,
						IOobject::NO_READ,
						IOobject::NO_WRITE
					),
					mesh,
					dimensioned<Type>("0", ssf.dimensions(), Zero)
					)
			);

			if (!mesh.nGeometricD())
			{
				return taverage;
			}

			GeometricField<Type, fvPatchField, volMesh>& av = taverage.ref();

			av.primitiveFieldRef() =
				(
					surfaceSum(mesh.magSf()*ssf)().primitiveField()
					/ surfaceSum(mesh.magSf())().primitiveField()
					);

			typename GeometricField<Type, fvPatchField, volMesh>::
				Boundary& bav = av.boundaryFieldRef();

			forAll(bav, patchi)
			{
				bav[patchi] = ssf.boundaryField()[patchi];
			}

			av.correctBoundaryConditions();

			return taverage;
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>>
			average
			(
				const tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>& tssf
			)
		{
			tmp<GeometricField<Type, fvPatchField, volMesh>> taverage
			(
				fvc::average(tssf())
			);
			tssf.clear();
			return taverage;
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>>
			average
			(
				const GeometricField<Type, fvPatchField, volMesh>& vtf
			)
		{
			return fvc::average(linearInterpolate(vtf));
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>>
			average
			(
				const tmp<GeometricField<Type, fvPatchField, volMesh>>& tvtf
			)
		{
			tmp<GeometricField<Type, fvPatchField, volMesh>> taverage
			(
				fvc::average(tvtf())
			);
			tvtf.clear();
			return taverage;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fvc

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //