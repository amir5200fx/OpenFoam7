#include <laplacianScheme.hxx>

#include <fv.hxx>
#include <HashTable.hxx>
#include <fvMatrix.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		// * * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * //

		template<class Type, class GType>
		tmp<laplacianScheme<Type, GType>> laplacianScheme<Type, GType>::New
		(
			const fvMesh& mesh,
			Istream& schemeData
		)
		{
			if (fv::debug)
			{
				InfoInFunction << "Constructing laplacianScheme<Type, GType>" << endl;
			}

			if (schemeData.eof())
			{
				FatalIOErrorInFunction
				(
					schemeData
				) << "Laplacian scheme not specified" << endl << endl
					<< "Valid laplacian schemes are :" << endl
					<< IstreamConstructorTablePtr_->sortedToc()
					<< exit(FatalIOError);
			}

			const word schemeName(schemeData);

			typename IstreamConstructorTable::iterator cstrIter =
				IstreamConstructorTablePtr_->find(schemeName);

			if (cstrIter == IstreamConstructorTablePtr_->end())
			{
				FatalIOErrorInFunction
				(
					schemeData
				) << "Unknown laplacian scheme " << schemeName << nl << nl
					<< "Valid laplacian schemes are :" << endl
					<< IstreamConstructorTablePtr_->sortedToc()
					<< exit(FatalIOError);
			}

			return cstrIter()(mesh, schemeData);
		}


		// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

		template<class Type, class GType>
		laplacianScheme<Type, GType>::~laplacianScheme()
		{}


		// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

		template<class Type, class GType>
		tmp<fvMatrix<Type>>
			laplacianScheme<Type, GType>::fvmLaplacian
			(
				const GeometricField<GType, fvPatchField, volMesh>& gamma,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return fvmLaplacian(tinterpGammaScheme_().interpolate(gamma)(), vf);
		}


		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh>>
			laplacianScheme<Type, GType>::fvcLaplacian
			(
				const GeometricField<GType, fvPatchField, volMesh>& gamma,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return fvcLaplacian(tinterpGammaScheme_().interpolate(gamma)(), vf);
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //