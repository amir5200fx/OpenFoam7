#include <fvcReconstruct.hxx>

#include <fvMesh.hxx>
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

			const labelUList& owner = mesh.owner();
			const labelUList& neighbour = mesh.neighbour();

			const volVectorField& C = mesh.C();
			const surfaceVectorField& Cf = mesh.Cf();

			tmp<GeometricField<GradType, fvPatchField, volMesh>> treconField
			(
				new GeometricField<GradType, fvPatchField, volMesh>
				(
					IOobject
					(
						"reconstruct(" + ssf.name() + ')',
						ssf.instance(),
						mesh,
						IOobject::NO_READ,
						IOobject::NO_WRITE
					),
					mesh,
					dimensioned<GradType>
					(
						"0",
						ssf.dimensions() / dimArea,
						Zero
						),
					extrapolatedCalculatedFvPatchField<GradType>::typeName
					)
			);

			Field<GradType>& rf = treconField();

			forAll(owner, facei)
			{
				label own = owner[facei];
				label nei = neighbour[facei];

				rf[own] += (Cf[facei] - C[own])*ssf[facei];
				rf[nei] -= (Cf[facei] - C[nei])*ssf[facei];
			}

			const typename GeometricField<Type, fvsPatchField, surfaceMesh>::
				Boundary& bsf = ssf.boundaryField();

			forAll(bsf, patchi)
			{
				const fvsPatchField<Type>& psf = bsf[patchi];

				const labelUList& pOwner = mesh.boundary()[patchi].faceCells();
				const vectorField& pCf = Cf.boundaryField()[patchi];

				forAll(pOwner, pFacei)
				{
					label own = pOwner[pFacei];
					rf[own] += (pCf[pFacei] - C[own])*psf[pFacei];
				}
			}

			rf /= mesh.V();

			treconField().correctBoundaryConditions();

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