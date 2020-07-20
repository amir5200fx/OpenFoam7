#include <fvmLaplacian.hxx>

#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <fvMatrix.hxx>
#include <laplacianScheme.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fvm
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<class Type>
		tmp<fvMatrix<Type>>
			laplacian
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf,
				const word& name
			)
		{
			surfaceScalarField Gamma
			(
				IOobject
				(
					"1",
					vf.time().constant(),
					vf.mesh(),
					IOobject::NO_READ
				),
				vf.mesh(),
				dimensionedScalar(dimless, 1.0)
			);

			return fvm::laplacian(Gamma, vf, name);
		}


		template<class Type>
		tmp<fvMatrix<Type>>
			laplacian
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			surfaceScalarField Gamma
			(
				IOobject
				(
					"1",
					vf.time().constant(),
					vf.mesh(),
					IOobject::NO_READ
				),
				vf.mesh(),
				dimensionedScalar(dimless, 1.0)
			);

			return fvm::laplacian
			(
				Gamma,
				vf,
				"laplacian(" + vf.name() + ')'
			);
		}


		template<class Type>
		tmp<fvMatrix<Type>>
			laplacian
			(
				const zero&,
				const GeometricField<Type, fvPatchField, volMesh>& vf,
				const word& name
			)
		{
			return tmp<fvMatrix<Type>>
				(
					new fvMatrix<Type>(vf, dimensionSet(0, 0, -2, 0, 0))
					);
		}


		template<class Type>
		tmp<fvMatrix<Type>>
			laplacian
			(
				const zero&,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return tmp<fvMatrix<Type>>
				(
					new fvMatrix<Type>(vf, dimensionSet(0, 0, -2, 0, 0))
					);
		}


		template<class Type>
		tmp<fvMatrix<Type>>
			laplacian
			(
				const one&,
				const GeometricField<Type, fvPatchField, volMesh>& vf,
				const word& name
			)
		{
			return fvm::laplacian(vf, name);
		}


		template<class Type>
		tmp<fvMatrix<Type>>
			laplacian
			(
				const one&,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return fvm::laplacian(vf);
		}


		template<class Type, class GType>
		tmp<fvMatrix<Type>>
			laplacian
			(
				const dimensioned<GType>& gamma,
				const GeometricField<Type, fvPatchField, volMesh>& vf,
				const word& name
			)
		{
			const GeometricField<GType, fvsPatchField, surfaceMesh> Gamma
			(
				IOobject
				(
					gamma.name(),
					vf.instance(),
					vf.mesh(),
					IOobject::NO_READ
				),
				vf.mesh(),
				gamma
			);

			return fvm::laplacian(Gamma, vf, name);
		}


		template<class Type, class GType>
		tmp<fvMatrix<Type>>
			laplacian
			(
				const dimensioned<GType>& gamma,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			const GeometricField<GType, fvsPatchField, surfaceMesh> Gamma
			(
				IOobject
				(
					gamma.name(),
					vf.instance(),
					vf.mesh(),
					IOobject::NO_READ
				),
				vf.mesh(),
				gamma
			);

			return fvm::laplacian(Gamma, vf);
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<class Type, class GType>
		tmp<fvMatrix<Type>>
			laplacian
			(
				const GeometricField<GType, fvPatchField, volMesh>& gamma,
				const GeometricField<Type, fvPatchField, volMesh>& vf,
				const word& name
			)
		{
			return fv::laplacianScheme<Type, GType>::New
			(
				vf.mesh(),
				vf.mesh().laplacianScheme(name)
			).ref().fvmLaplacian(gamma, vf);
		}


		template<class Type, class GType>
		tmp<fvMatrix<Type>>
			laplacian
			(
				const tmp<GeometricField<GType, fvPatchField, volMesh>>& tgamma,
				const GeometricField<Type, fvPatchField, volMesh>& vf,
				const word& name
			)
		{
			tmp<fvMatrix<Type>> Laplacian(fvm::laplacian(tgamma(), vf, name));
			tgamma.clear();
			return Laplacian;
		}


		template<class Type, class GType>
		tmp<fvMatrix<Type>>
			laplacian
			(
				const GeometricField<GType, fvPatchField, volMesh>& gamma,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return fvm::laplacian
			(
				gamma,
				vf,
				"laplacian(" + gamma.name() + ',' + vf.name() + ')'
			);
		}


		template<class Type, class GType>
		tmp<fvMatrix<Type>>
			laplacian
			(
				const tmp<GeometricField<GType, fvPatchField, volMesh>>& tgamma,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			tmp<fvMatrix<Type>> Laplacian(fvm::laplacian(tgamma(), vf));
			tgamma.clear();
			return Laplacian;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<class Type, class GType>
		tmp<fvMatrix<Type>>
			laplacian
			(
				const GeometricField<GType, fvsPatchField, surfaceMesh>& gamma,
				const GeometricField<Type, fvPatchField, volMesh>& vf,
				const word& name
			)
		{
			return fv::laplacianScheme<Type, GType>::New
			(
				vf.mesh(),
				vf.mesh().laplacianScheme(name)
			).ref().fvmLaplacian(gamma, vf);
		}


		template<class Type, class GType>
		tmp<fvMatrix<Type>>
			laplacian
			(
				const tmp<GeometricField<GType, fvsPatchField, surfaceMesh>>& tgamma,
				const GeometricField<Type, fvPatchField, volMesh>& vf,
				const word& name
			)
		{
			tmp<fvMatrix<Type>> tLaplacian = fvm::laplacian(tgamma(), vf, name);
			tgamma.clear();
			return tLaplacian;
		}


		template<class Type, class GType>
		tmp<fvMatrix<Type>>
			laplacian
			(
				const GeometricField<GType, fvsPatchField, surfaceMesh>& gamma,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return fvm::laplacian
			(
				gamma,
				vf,
				"laplacian(" + gamma.name() + ',' + vf.name() + ')'
			);
		}


		template<class Type, class GType>
		tmp<fvMatrix<Type>>
			laplacian
			(
				const tmp<GeometricField<GType, fvsPatchField, surfaceMesh>>& tGamma,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			tmp<fvMatrix<Type>> tfvm(fvm::laplacian(tGamma(), vf));
			tGamma.clear();
			return tfvm;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fvm

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //