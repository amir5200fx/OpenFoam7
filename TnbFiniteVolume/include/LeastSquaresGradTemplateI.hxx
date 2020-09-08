#pragma once
#include <leastSquaresVectors.hxx>
#include <gaussGrad.hxx>
#include <fvMesh.hxx>
#include <volMesh.hxx>
#include <extrapolatedCalculatedFvPatchField.hxx>
#include <LeastSquaresVectorsTemplate.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type, class Stencil>
tnbLib::tmp
<
	tnbLib::GeometricField
	<
	typename tnbLib::outerProduct<tnbLib::vector, Type>::type,
	tnbLib::fvPatchField,
	tnbLib::volMesh
	>
>
tnbLib::fv::LeastSquaresGrad<Type, Stencil>::calcGrad
(
	const GeometricField<Type, fvPatchField, volMesh>& vtf,
	const word& name
) const
{
	typedef typename outerProduct<vector, Type>::type GradType;

	const fvMesh& mesh = vtf.mesh();

	// Get reference to least square vectors
	const LeastSquaresVectors<Stencil>& lsv = LeastSquaresVectors<Stencil>::New
	(
		mesh
	);

	tmp<GeometricField<GradType, fvPatchField, volMesh>> tlsGrad
	(
		new GeometricField<GradType, fvPatchField, volMesh>
		(
			IOobject
			(
				name,
				vtf.instance(),
				mesh,
				IOobject::NO_READ,
				IOobject::NO_WRITE
			),
			mesh,
			dimensioned<GradType>
			(
				"zero",
				vtf.dimensions() / dimLength,
				Zero
				),
			extrapolatedCalculatedFvPatchField<GradType>::typeName
			)
	);
	GeometricField<GradType, fvPatchField, volMesh>& lsGrad = tlsGrad.ref();
	Field<GradType>& lsGradIf = lsGrad;

	const extendedCentredCellToCellStencil& stencil = lsv.stencil();
	const List<List<label>>& stencilAddr = stencil.stencil();
	const List<List<vector>>& lsvs = lsv.vectors();

	// Construct flat version of vtf
	// including all values referred to by the stencil
	List<Type> flatVtf(stencil.map().constructSize(), Zero);

	// Insert internal values
	forAll(vtf, celli)
	{
		flatVtf[celli] = vtf[celli];
	}

	// Insert boundary values
	forAll(vtf.boundaryField(), patchi)
	{
		const fvPatchField<Type>& ptf = vtf.boundaryField()[patchi];

		label nCompact =
			ptf.patch().start()
			- mesh.nInternalFaces()
			+ mesh.nCells();

		forAll(ptf, i)
		{
			flatVtf[nCompact++] = ptf[i];
		}
	}

	// Do all swapping to complete flatVtf
	stencil.map().distribute(flatVtf);

	// Accumulate the cell-centred gradient from the
	// weighted least-squares vectors and the flattened field values
	forAll(stencilAddr, celli)
	{
		const labelList& compactCells = stencilAddr[celli];
		const List<vector>& lsvc = lsvs[celli];

		forAll(compactCells, i)
		{
			lsGradIf[celli] += lsvc[i] * flatVtf[compactCells[i]];
		}
	}

	// Correct the boundary conditions
	lsGrad.correctBoundaryConditions();
	gaussGrad<Type>::correctBoundaryConditions(vtf, lsGrad);

	return tlsGrad;
}


// ************************************************************************* //