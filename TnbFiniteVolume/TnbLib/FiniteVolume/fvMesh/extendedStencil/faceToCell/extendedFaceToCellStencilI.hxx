#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::extendedFaceToCellStencil::collectData
(
	const mapDistribute& map,
	const labelListList& stencil,
	const GeometricField<Type, fvsPatchField, surfaceMesh>& fld,
	List<List<Type>>& stencilFld
)
{
	// 1. Construct face data in compact addressing
	List<Type> flatFld(map.constructSize(), Zero);

	// Insert my internal values
	forAll(fld, celli)
	{
		flatFld[celli] = fld[celli];
	}
	// Insert my boundary values
	forAll(fld.boundaryField(), patchi)
	{
		const fvsPatchField<Type>& pfld = fld.boundaryField()[patchi];

		label nCompact = pfld.patch().start();

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
tnbLib::tmp<tnbLib::GeometricField<Type, tnbLib::fvPatchField, tnbLib::volMesh>>
tnbLib::extendedFaceToCellStencil::weightedSum
(
	const mapDistribute& map,
	const labelListList& stencil,
	const GeometricField<Type, fvsPatchField, surfaceMesh>& fld,
	const List<List<scalar>>& stencilWeights
)
{
	const fvMesh& mesh = fld.mesh();

	// Collect internal and boundary values
	List<List<Type>> stencilFld;
	collectData(map, stencil, fld, stencilFld);

	tmp<GeometricField<Type, fvPatchField, volMesh>> tsfCorr
	(
		new GeometricField<Type, fvPatchField, volMesh>
		(
			IOobject
			(
				fld.name(),
				mesh.time().timeName(),
				mesh
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
	GeometricField<Type, fvPatchField, volMesh>& sf = tsfCorr.ref();

	// cells
	forAll(sf, celli)
	{
		const List<Type>& stField = stencilFld[celli];
		const List<scalar>& stWeight = stencilWeights[celli];

		forAll(stField, i)
		{
			sf[celli] += stField[i] * stWeight[i];
		}
	}

	// Boundaries values?

	return tsfCorr;
}


// ************************************************************************* //