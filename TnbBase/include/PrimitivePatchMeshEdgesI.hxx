#pragma once
// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class FaceList, class PointField>
tnbLib::labelList tnbLib::PrimitivePatch<FaceList, PointField>::meshEdges
(
	const edgeList& allEdges,
	const labelListList& cellEdges,
	const labelList& faceCells
) const
{
	if (debug)
	{
		InfoInFunction
			<< "Calculating labels of patch edges in mesh edge list" << endl;
	}

	// get reference to the list of edges on the patch
	const edgeList& PatchEdges = edges();

	const labelListList& EdgeFaces = edgeFaces();

	// create the storage
	labelList meshEdges(PatchEdges.size());

	bool found = false;

	// get reference to the points on the patch
	const labelList& pp = meshPoints();

	// WARNING: Remember that local edges address into local point list;
	// local-to-global point label translation is necessary
	forAll(PatchEdges, edgeI)
	{
		const edge curEdge
		(pp[PatchEdges[edgeI].start()], pp[PatchEdges[edgeI].end()]);

		found = false;

		// get the patch faces sharing the edge
		const labelList& curFaces = EdgeFaces[edgeI];

		forAll(curFaces, facei)
		{
			// get the cell next to the face
			label curCell = faceCells[curFaces[facei]];

			// get reference to edges on the cell
			const labelList& ce = cellEdges[curCell];

			forAll(ce, cellEdgeI)
			{
				if (allEdges[ce[cellEdgeI]] == curEdge)
				{
					found = true;

					meshEdges[edgeI] = ce[cellEdgeI];

					break;
				}
			}

			if (found) break;
		}
	}

	return meshEdges;
}


template<class FaceList, class PointField>
tnbLib::labelList tnbLib::PrimitivePatch<FaceList, PointField>::meshEdges
(
	const edgeList& allEdges,
	const labelListList& pointEdges
) const
{
	if (debug)
	{
		InfoInFunction
			<< "Calculating labels of patch edges in mesh edge list" << endl;
	}

	// get reference to the list of edges on the patch
	const edgeList& PatchEdges = edges();

	// create the storage
	labelList meshEdges(PatchEdges.size());

	// get reference to the points on the patch
	const labelList& pp = meshPoints();

	// WARNING: Remember that local edges address into local point list;
	// local-to-global point label translation is necessary
	forAll(PatchEdges, edgeI)
	{
		const label globalPointi = pp[PatchEdges[edgeI].start()];
		const edge curEdge(globalPointi, pp[PatchEdges[edgeI].end()]);

		const labelList& pe = pointEdges[globalPointi];

		forAll(pe, i)
		{
			if (allEdges[pe[i]] == curEdge)
			{
				meshEdges[edgeI] = pe[i];
				break;
			}
		}
	}

	return meshEdges;
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class FaceList, class PointField>
tnbLib::label tnbLib::PrimitivePatch<FaceList, PointField>::whichEdge
(
	const edge& e
) const
{
	// Get pointEdges from the starting point and search all the candidates
	const edgeList& Edges = edges();

	if (e.start() > -1 && e.start() < nPoints())
	{
		const labelList& pe = pointEdges()[e.start()];

		forAll(pe, peI)
		{
			if (e == Edges[pe[peI]])
			{
				return pe[peI];
			}
		}
	}

	// Edge not found.  Return -1
	return -1;
}


// ************************************************************************* //