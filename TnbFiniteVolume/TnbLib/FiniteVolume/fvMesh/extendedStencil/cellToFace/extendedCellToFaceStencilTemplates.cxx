#include <extendedCellToFaceStencil.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::extendedCellToFaceStencil::collectData
(
	const mapDistribute& map,
	const labelListList& stencil,
	const GeometricField<Type, fvPatchField, volMesh>& fld,
	List<List<Type>>& stencilFld
)
{
	// 1. Construct cell data in compact addressing
	List<Type> flatFld(map.constructSize(), Zero);

	// Insert my internal values
	forAll(fld, celli)
	{
		flatFld[celli] = fld[celli];
	}
	// Insert my boundary values
	forAll(fld.boundaryField(), patchi)
	{
		const fvPatchField<Type>& pfld = fld.boundaryField()[patchi];

		label nCompact =
			pfld.patch().start()
			- fld.mesh().nInternalFaces()
			+ fld.mesh().nCells();

		forAll(pfld, i)
		{
			flatFld[nCompact++] = pfld[i];
		}
	}

	// Do all swapping
	map.distribute(flatFld);

	// 2. Pull to stencil
	stencilFld.setSize(stencil.size());

	forAll(stencil, facei)
	{
		const labelList& compactCells = stencil[facei];

		stencilFld[facei].setSize(compactCells.size());

		forAll(compactCells, i)
		{
			stencilFld[facei][i] = flatFld[compactCells[i]];
		}
	}
}


template<class Type>
tnbLib::tmp<tnbLib::GeometricField<Type, tnbLib::fvsPatchField, tnbLib::surfaceMesh>>
tnbLib::extendedCellToFaceStencil::weightedSum
(
	const mapDistribute& map,
	const labelListList& stencil,
	const GeometricField<Type, fvPatchField, volMesh>& fld,
	const List<List<scalar>>& stencilWeights
)
{
	const fvMesh& mesh = fld.mesh();

	// Collect internal and boundary values
	List<List<Type>> stencilFld;
	collectData(map, stencil, fld, stencilFld);

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
		const List<Type>& stField = stencilFld[facei];
		const List<scalar>& stWeight = stencilWeights[facei];

		forAll(stField, i)
		{
			sf[facei] += stField[i] * stWeight[i];
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
				const List<Type>& stField = stencilFld[facei];
				const List<scalar>& stWeight = stencilWeights[facei];

				forAll(stField, j)
				{
					pSfCorr[i] += stField[j] * stWeight[j];
				}

				facei++;
			}
		}
	}

	return tsfCorr;
}


// ************************************************************************* //