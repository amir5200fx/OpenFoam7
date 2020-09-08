#pragma once
#include <cut.hxx>
#include <polyMeshTetDecomposition.hxx>
#include <tetIndices.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::Field<Type>> tnbLib::levelSetAverage
(
	const fvMesh& mesh,
	const scalarField& levelC,
	const scalarField& levelP,
	const Field<Type>& positiveC,
	const Field<Type>& positiveP,
	const Field<Type>& negativeC,
	const Field<Type>& negativeP
)
{
	tmp<Field<Type>> tResult(new Field<Type>(mesh.nCells(), Zero));
	Field<Type>& result = tResult.ref();

	forAll(result, cI)
	{
		const List<tetIndices> cellTetIs =
			polyMeshTetDecomposition::cellTetIndices(mesh, cI);

		scalar v = 0;
		Type r = Zero;

		forAll(cellTetIs, cellTetI)
		{
			const triFace triIs = cellTetIs[cellTetI].faceTriIs(mesh);

			const FixedList<point, 4>
				tet =
			{
				mesh.cellCentres()[cI],
				mesh.points()[triIs[0]],
				mesh.points()[triIs[1]],
				mesh.points()[triIs[2]]
			};
			const FixedList<scalar, 4>
				level =
			{
				levelC[cI],
				levelP[triIs[0]],
				levelP[triIs[1]],
				levelP[triIs[2]]
			};
			const cut::volumeIntegrateOp<Type>
				positive = FixedList<Type, 4>
				({
					positiveC[cI],
					positiveP[triIs[0]],
					positiveP[triIs[1]],
					positiveP[triIs[2]]
					});
			const cut::volumeIntegrateOp<Type>
				negative = FixedList<Type, 4>
				({
					negativeC[cI],
					negativeP[triIs[0]],
					negativeP[triIs[1]],
					negativeP[triIs[2]]
					});

			v += cut::volumeOp()(tet);

			r += tetCut(tet, level, positive, negative);
		}

		result[cI] = r / v;
	}

	return tResult;
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>> tnbLib::levelSetAverage
(
	const fvPatch& patch,
	const scalarField& levelF,
	const scalarField& levelP,
	const Field<Type>& positiveF,
	const Field<Type>& positiveP,
	const Field<Type>& negativeF,
	const Field<Type>& negativeP
)
{
	tmp<Field<Type>> tResult(new Field<Type>(patch.size(), Zero));
	Field<Type>& result = tResult.ref();

	forAll(result, fI)
	{
		const face& f = patch.patch().localFaces()[fI];

		scalar a = 0;
		Type r = Zero;

		for (label eI = 0; eI < f.size(); ++eI)
		{
			const edge e = f.faceEdge(eI);

			const FixedList<point, 3>
				tri =
			{
				patch.patch().faceCentres()[fI],
				patch.patch().localPoints()[e[0]],
				patch.patch().localPoints()[e[1]]
			};
			const FixedList<scalar, 3>
				level =
			{
				levelF[fI],
				levelP[e[0]],
				levelP[e[1]]
			};
			const cut::areaMagIntegrateOp<Type>
				positive = FixedList<Type, 3>
				({
					positiveF[fI],
					positiveP[e[0]],
					positiveP[e[1]]
					});
			const cut::areaMagIntegrateOp<Type>
				negative = FixedList<Type, 3>
				({
					negativeF[fI],
					negativeP[e[0]],
					negativeP[e[1]]
					});

			a += cut::areaMagOp()(tri);

			r += triCut(tri, level, positive, negative);
		}

		result[fI] = r / a;
	}

	return tResult;
}


template<class Type>
tnbLib::tmp<tnbLib::GeometricField<Type, tnbLib::fvPatchField, tnbLib::volMesh>>
tnbLib::levelSetAverage
(
	const volScalarField& levelC,
	const pointScalarField& levelP,
	const GeometricField<Type, fvPatchField, volMesh>& positiveC,
	const GeometricField<Type, pointPatchField, pointMesh>& positiveP,
	const GeometricField<Type, fvPatchField, volMesh>& negativeC,
	const GeometricField<Type, pointPatchField, pointMesh>& negativeP
)
{
	const fvMesh& mesh = levelC.mesh();

	tmp<GeometricField<Type, fvPatchField, volMesh>> tResult
	(
		new GeometricField<Type, fvPatchField, volMesh>
		(
			IOobject
			(
				positiveC.name() + ":levelSetAverage",
				mesh.time().timeName(),
				mesh
			),
			mesh,
			dimensioned<Type>("0", positiveC.dimensions(), Zero)
			)
	);
	GeometricField<Type, fvPatchField, volMesh>& result = tResult.ref();

	result.primitiveFieldRef() =
		levelSetAverage
		(
			mesh,
			levelC.primitiveField(),
			levelP.primitiveField(),
			positiveC.primitiveField(),
			positiveP.primitiveField(),
			negativeC.primitiveField(),
			negativeP.primitiveField()
		);

	forAll(mesh.boundary(), patchi)
	{
		result.boundaryFieldRef()[patchi] =
			levelSetAverage
			(
				mesh.boundary()[patchi],
				levelC.boundaryField()[patchi],
				levelP.boundaryField()[patchi].patchInternalField()(),
				positiveC.boundaryField()[patchi],
				positiveP.boundaryField()[patchi].patchInternalField()(),
				negativeC.boundaryField()[patchi],
				negativeP.boundaryField()[patchi].patchInternalField()()
			);
	}

	return tResult;
}


// ************************************************************************* //