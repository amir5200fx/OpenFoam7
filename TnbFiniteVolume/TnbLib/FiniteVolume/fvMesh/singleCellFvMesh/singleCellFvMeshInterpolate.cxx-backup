#include <singleCellFvMesh.hxx>

#include <calculatedFvPatchFields.hxx>
#include <directFvPatchFieldMapper.hxx>
#include <Time.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class Type>
	tmp<GeometricField<Type, fvPatchField, volMesh>> singleCellFvMesh::interpolate
	(
		const GeometricField<Type, fvPatchField, volMesh>& vf
	) const
	{
		// 1. Create the complete field with dummy patch fields
		PtrList<fvPatchField<Type>> patchFields(vf.boundaryField().size());

		forAll(patchFields, patchi)
		{
			patchFields.set
			(
				patchi,
				fvPatchField<Type>::New
				(
					calculatedFvPatchField<Type>::typeName,
					boundary()[patchi],
					DimensionedField<Type, volMesh>::null()
				)
			);
		}

		// Create the complete field from the pieces
		tmp<GeometricField<Type, fvPatchField, volMesh>> tresF
		(
			new GeometricField<Type, fvPatchField, volMesh>
			(
				IOobject
				(
					vf.name(),
					time().timeName(),
					*this,
					IOobject::NO_READ,
					IOobject::NO_WRITE
				),
				*this,
				vf.dimensions(),
				Field<Type>(1, gAverage(vf)),
				patchFields
				)
		);
		GeometricField<Type, fvPatchField, volMesh>& resF = tresF.ref();


		// 2. Change the fvPatchFields to the correct type using a mapper
		//  constructor (with reference to the now correct internal field)

		typename GeometricField<Type, fvPatchField, volMesh>::
			Boundary& bf = resF.boundaryFieldRef();

		if (agglomerate())
		{
			forAll(vf.boundaryField(), patchi)
			{
				const labelList& agglom = patchFaceAgglomeration_[patchi];
				label nAgglom = max(agglom) + 1;

				// Use inverse of agglomeration. This is from agglomeration to
				// original (fine) mesh patch face.
				labelListList coarseToFine(invertOneToMany(nAgglom, agglom));
				inplaceReorder(patchFaceMap_[patchi], coarseToFine);
				scalarListList coarseWeights(nAgglom);
				forAll(coarseToFine, coarseI)
				{
					const labelList& fineFaces = coarseToFine[coarseI];
					coarseWeights[coarseI] = scalarList
					(
						fineFaces.size(),
						1.0 / fineFaces.size()
					);
				}

				bf.set
				(
					patchi,
					fvPatchField<Type>::New
					(
						vf.boundaryField()[patchi],
						boundary()[patchi],
						resF(),
						agglomPatchFieldMapper(coarseToFine, coarseWeights)
					)
				);
			}
		}
		else
		{
			forAll(vf.boundaryField(), patchi)
			{
				labelList map(identity(vf.boundaryField()[patchi].size()));

				bf.set
				(
					patchi,
					fvPatchField<Type>::New
					(
						vf.boundaryField()[patchi],
						boundary()[patchi],
						resF(),
						directFvPatchFieldMapper(map)
					)
				);
			}
		}

		return tresF;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //