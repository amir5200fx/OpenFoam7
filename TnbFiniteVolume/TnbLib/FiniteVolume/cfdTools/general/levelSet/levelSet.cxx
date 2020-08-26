#include <levelSet.hxx>

#include <cut.hxx>
#include <polyMeshTetDecomposition.hxx>
#include <tetIndices.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::scalarField> tnbLib::levelSetFraction
(
	const fvMesh& mesh,
	const scalarField& levelC,
	const scalarField& levelP,
	const bool above
)
{
	tmp<scalarField> tResult(new scalarField(mesh.nCells(), Zero));
	scalarField& result = tResult.ref();

	forAll(result, cI)
	{
		const List<tetIndices> cellTetIs =
			polyMeshTetDecomposition::cellTetIndices(mesh, cI);

		scalar v = 0, r = 0;

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

			v += cut::volumeOp()(tet);

			if (above)
			{
				r += tetCut(tet, level, cut::volumeOp(), cut::noOp());
			}
			else
			{
				r += tetCut(tet, level, cut::noOp(), cut::volumeOp());
			}
		}

		result[cI] = r / v;
	}

	return tResult;
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::levelSetFraction
(
	const fvPatch& patch,
	const scalarField& levelF,
	const scalarField& levelP,
	const bool above
)
{
	tmp<scalarField> tResult(new scalarField(patch.size(), 0));
	scalarField& result = tResult.ref();

	forAll(result, fI)
	{
		const face& f = patch.patch().localFaces()[fI];

		scalar a = 0, r = 0;

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

			a += cut::areaMagOp()(tri);

			if (above)
			{
				r += triCut(tri, level, cut::areaMagOp(), cut::noOp());
			}
			else
			{
				r += triCut(tri, level, cut::noOp(), cut::areaMagOp());
			}
		}

		result[fI] = r / a;
	}

	return tResult;
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::levelSetFraction
(
	const volScalarField& levelC,
	const pointScalarField& levelP,
	const bool above
)
{
	const fvMesh& mesh = levelC.mesh();

	tmp<volScalarField> tResult
	(
		volScalarField::New
		(
			"levelSetFraction",
			mesh,
			dimensionedScalar(dimless, 0)
		)
	);
	volScalarField& result = tResult.ref();

	result.primitiveFieldRef() =
		levelSetFraction
		(
			mesh,
			levelC.primitiveField(),
			levelP.primitiveField(),
			above
		);

	forAll(mesh.boundary(), patchi)
	{
		result.boundaryFieldRef()[patchi] =
			levelSetFraction
			(
				mesh.boundary()[patchi],
				levelC.boundaryField()[patchi],
				levelP.boundaryField()[patchi].patchInternalField()(),
				above
			);
	}

	return tResult;
}


// ************************************************************************* //