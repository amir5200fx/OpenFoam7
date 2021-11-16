#pragma once
#include <meshSearch.hxx> //- Added by Amir

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Triangulation>
bool tnbLib::conformalVoronoiMesh::distributeBackground(const Triangulation& mesh)
{
	if (!Pstream::parRun())
	{
		return false;
	}

	Info << nl << "Redistributing points" << endl;

	timeCheck("Before distribute");

	label iteration = 0;

	scalar previousLoadUnbalance = 0;

	while (true)
	{
		scalar maxLoadUnbalance = mesh.calculateLoadUnbalance();

		if
			(
				maxLoadUnbalance <= foamyHexMeshControls().maxLoadUnbalance()
				|| maxLoadUnbalance <= previousLoadUnbalance
				)
		{
			// If this is the first iteration, return false, if it was a
			// subsequent one, return true;
			return iteration != 0;
		}

		previousLoadUnbalance = maxLoadUnbalance;

		Info << "    Total number of vertices before redistribution "
			<< returnReduce(label(mesh.number_of_vertices()), sumOp<label>())
			<< endl;

		const fvMesh& bMesh = decomposition_().mesh();

		volScalarField cellWeights
		(
			IOobject
			(
				"cellWeights",
				bMesh.time().timeName(),
				bMesh,
				IOobject::NO_READ,
				IOobject::NO_WRITE
			),
			bMesh,
			dimensionedScalar(dimless, 1e-2),
			zeroGradientFvPatchScalarField::typeName
		);

		meshSearch cellSearch(bMesh, polyMesh::FACE_PLANES);

		labelList cellVertices(bMesh.nCells(), label(0));

		for
			(
				typename Triangulation::Finite_vertices_iterator vit
				= mesh.finite_vertices_begin();
				vit != mesh.finite_vertices_end();
				++vit
				)
		{
			// Only store real vertices that are not feature vertices
			if (vit->real() && !vit->featurePoint())
			{
				pointFromPoint v = topoint(vit->point());

				label celli = cellSearch.findCell(v);

				if (celli == -1)
				{
					//                     Pout<< "findCell conformalVoronoiMesh::distribute "
					//                         << "findCell "
					//                         << vit->type() << " "
					//                         << vit->index() << " "
					//                         << v << " "
					//                         << celli
					//                         << " find nearest celli ";

					celli = cellSearch.findNearestCell(v);
				}

				cellVertices[celli]++;
			}
		}

		scalarField& cwi = cellWeights.primitiveFieldRef();

		forAll(cellVertices, cI)
		{
			// Give a small but finite weight for empty cells.  Some
			// decomposition methods have difficulty with integer overflows in
			// the sum of the normalised weight field.
			cwi[cI] = max(cellVertices[cI], 1e-2);
		}

		autoPtr<mapDistributePolyMesh> mapDist = decomposition_().distribute
		(
			cellWeights
		);

		cellShapeControl_.shapeControlMesh().distribute(decomposition_);

		distribute();

		timeCheck("After distribute");

		iteration++;
	}

	return true;
}


// ************************************************************************* //