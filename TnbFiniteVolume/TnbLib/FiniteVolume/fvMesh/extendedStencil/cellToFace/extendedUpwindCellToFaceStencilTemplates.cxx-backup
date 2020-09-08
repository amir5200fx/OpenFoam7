#include <extendedUpwindCellToFaceStencil.hxx>  // added by amir

#include <extendedCellToFaceStencil.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::GeometricField<Type, tnbLib::fvsPatchField, tnbLib::surfaceMesh>>
tnbLib::extendedUpwindCellToFaceStencil::weightedSum
(
	const surfaceScalarField& phi,
	const GeometricField<Type, fvPatchField, volMesh>& fld,
	const List<List<scalar>>& ownWeights,
	const List<List<scalar>>& neiWeights
) const
{
	const fvMesh& mesh = fld.mesh();

	// Collect internal and boundary values
	List<List<Type>> ownFld;
	collectData(ownMap(), ownStencil(), fld, ownFld);
	List<List<Type>> neiFld;
	collectData(neiMap(), neiStencil(), fld, neiFld);

	tmp<GeometricField<Type, fvsPatchField, surfaceMesh>> tsfCorr
	(
		new GeometricField<Type, fvsPatchField, surfaceMesh>
		(
			IOobject
			(
				fld.name(),
				mesh.time().timeName(),
				mesh,
				IOobject::NO_READ,
				IOobject::NO_WRITE,
				false
			),
			mesh,
			dimensioned<Type>
			(
				fld.name(),
				fld.dimensions(),
				Zero
				)
			)
	);
	GeometricField<Type, fvsPatchField, surfaceMesh>& sf = tsfCorr.ref();

	// Internal faces
	for (label facei = 0; facei < mesh.nInternalFaces(); facei++)
	{
		if (phi[facei] > 0)
		{
			// Flux out of owner. Use upwind (= owner side) stencil.
			const List<Type>& stField = ownFld[facei];
			const List<scalar>& stWeight = ownWeights[facei];

			forAll(stField, i)
			{
				sf[facei] += stField[i] * stWeight[i];
			}
		}
		else
		{
			const List<Type>& stField = neiFld[facei];
			const List<scalar>& stWeight = neiWeights[facei];

			forAll(stField, i)
			{
				sf[facei] += stField[i] * stWeight[i];
			}
		}
	}

	// Boundaries. Either constrained or calculated so assign value
	// directly (instead of nicely using operator==)
	typename GeometricField<Type, fvsPatchField, surfaceMesh>::
		Boundary& bSfCorr = sf.boundaryFieldRef();

	forAll(bSfCorr, patchi)
	{
		fvsPatchField<Type>& pSfCorr = bSfCorr[patchi];

		if (pSfCorr.coupled())
		{
			label facei = pSfCorr.patch().start();

			forAll(pSfCorr, i)
			{
				if (phi.boundaryField()[patchi][i] > 0)
				{
					// Flux out of owner. Use upwind (= owner side) stencil.
					const List<Type>& stField = ownFld[facei];
					const List<scalar>& stWeight = ownWeights[facei];

					forAll(stField, j)
					{
						pSfCorr[i] += stField[j] * stWeight[j];
					}
				}
				else
				{
					const List<Type>& stField = neiFld[facei];
					const List<scalar>& stWeight = neiWeights[facei];

					forAll(stField, j)
					{
						pSfCorr[i] += stField[j] * stWeight[j];
					}
				}
				facei++;
			}
		}
	}

	return tsfCorr;
}


// ************************************************************************* //