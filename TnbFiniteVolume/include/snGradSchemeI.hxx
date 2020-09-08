#pragma once
#include <fv.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <HashTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		// * * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * //

		template<class Type>
		tmp<snGradScheme<Type>> snGradScheme<Type>::New
		(
			const fvMesh& mesh,
			Istream& schemeData
		)
		{
			if (fv::debug)
			{
				InfoInFunction << "Constructing snGradScheme<Type>" << endl;
			}

			if (schemeData.eof())
			{
				FatalIOErrorInFunction
				(
					schemeData
				) << "Discretisation scheme not specified"
					<< endl << endl
					<< "Valid schemes are :" << endl
					<< MeshConstructorTablePtr_->sortedToc()
					<< exit(FatalIOError);
			}

			const word schemeName(schemeData);

			typename MeshConstructorTable::iterator constructorIter =
				MeshConstructorTablePtr_->find(schemeName);

			if (constructorIter == MeshConstructorTablePtr_->end())
			{
				FatalIOErrorInFunction
				(
					schemeData
				) << "Unknown discretisation scheme "
					<< schemeName << nl << nl
					<< "Valid schemes are :" << endl
					<< MeshConstructorTablePtr_->sortedToc()
					<< exit(FatalIOError);
			}

			return constructorIter()(mesh, schemeData);
		}


		// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

		template<class Type>
		snGradScheme<Type>::~snGradScheme()
		{}


		// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

		template<class Type>
		tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
			snGradScheme<Type>::snGrad
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf,
				const tmp<surfaceScalarField>& tdeltaCoeffs,
				const word& snGradName
			)
		{
			const fvMesh& mesh = vf.mesh();

			// construct GeometricField<Type, fvsPatchField, surfaceMesh>
			tmp<GeometricField<Type, fvsPatchField, surfaceMesh>> tsf
			(
				new GeometricField<Type, fvsPatchField, surfaceMesh>
				(
					IOobject
					(
						snGradName + "(" + vf.name() + ')',
						vf.instance(),
						vf.mesh(),
						IOobject::NO_READ,
						IOobject::NO_WRITE
					),
					mesh,
					vf.dimensions()*tdeltaCoeffs().dimensions()
					)
			);
			GeometricField<Type, fvsPatchField, surfaceMesh>& ssf = tsf.ref();

			// set reference to difference factors array
			const scalarField& deltaCoeffs = tdeltaCoeffs();

			// owner/neighbour addressing
			const labelUList& owner = mesh.owner();
			const labelUList& neighbour = mesh.neighbour();

			forAll(owner, facei)
			{
				ssf[facei] =
					deltaCoeffs[facei] * (vf[neighbour[facei]] - vf[owner[facei]]);
			}

			typename GeometricField<Type, fvsPatchField, surfaceMesh>::
				Boundary& ssfbf = ssf.boundaryFieldRef();

			forAll(vf.boundaryField(), patchi)
			{
				const fvPatchField<Type>& pvf = vf.boundaryField()[patchi];

				if (pvf.coupled())
				{
					ssfbf[patchi] = pvf.snGrad(tdeltaCoeffs().boundaryField()[patchi]);
				}
				else
				{
					ssfbf[patchi] = pvf.snGrad();
				}
			}

			return tsf;
		}


		template<class Type>
		tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
			snGradScheme<Type>::sndGrad
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf,
				const word& sndGradName
			)
		{
			return snGrad(vf, vf.mesh().nonOrthDeltaCoeffs(), sndGradName);
		}


		template<class Type>
		tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
			snGradScheme<Type>::snGrad
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			) const
		{
			tmp<GeometricField<Type, fvsPatchField, surfaceMesh>> tsf
			(
				snGrad(vf, deltaCoeffs(vf))
			);

			if (corrected())
			{
				tsf.ref() += correction(vf);
			}

			return tsf;
		}


		template<class Type>
		tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
			snGradScheme<Type>::snGrad
			(
				const tmp<GeometricField<Type, fvPatchField, volMesh>>& tvf
			) const
		{
			tmp<GeometricField<Type, fvsPatchField, surfaceMesh>> tsf
			(
				snGrad(tvf())
			);

			tsf.clear();
			return tsf;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //