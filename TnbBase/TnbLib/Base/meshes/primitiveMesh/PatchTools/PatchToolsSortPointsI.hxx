#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class FaceList, class PointField>
tnbLib::labelListList tnbLib::PatchTools::sortedPointEdges
(
	const PrimitivePatch<FaceList, PointField>& p
)
{
	// Now order the edges of each point according to whether they share a
	// face
	const labelListList& pointEdges = p.pointEdges();
	const edgeList& edges = p.edges();
	const labelListList& edgeFaces = p.edgeFaces();
	const labelListList& faceEdges = p.faceEdges();

	// create the lists for the various results. (resized on completion)
	labelListList sortedPointEdges(pointEdges);

	DynamicList<label> newEdgeList;

	forAll(pointEdges, pointi)
	{
		const labelList& pEdges = pointEdges[pointi];

		label nPointEdges = pEdges.size();

		label edgeI = pEdges[0];

		label prevFacei = edgeFaces[edgeI][0];

		newEdgeList.clear();
		newEdgeList.setCapacity(nPointEdges);

		label nVisitedEdges = 0;

		do
		{
			newEdgeList.append(edgeI);

			// Cross edge to next face
			const labelList& eFaces = edgeFaces[edgeI];

			if (eFaces.size() != 2)
			{
				break;
			}

			label facei = eFaces[0];
			if (facei == prevFacei)
			{
				facei = eFaces[1];
			}

			// Cross face to next edge
			const labelList& fEdges = faceEdges[facei];

			forAll(fEdges, feI)
			{
				const label nextEdgeI = fEdges[feI];
				const edge& nextEdge = edges[nextEdgeI];

				if
					(
						nextEdgeI != edgeI
						&& (nextEdge.start() == pointi || nextEdge.end() == pointi)
						)
				{
					edgeI = nextEdgeI;
					break;
				}
			}

			prevFacei = facei;

			nVisitedEdges++;
			if (nVisitedEdges > nPointEdges)
			{
				WarningInFunction
					<< "Unable to order pointEdges as the face connections "
					<< "are not circular" << nl
					<< "    Original pointEdges = " << pEdges << nl
					<< "    New pointEdges = " << newEdgeList
					<< endl;

				newEdgeList = pEdges;

				break;
			}

		} while (edgeI != pEdges[0]);

		if (newEdgeList.size() == nPointEdges)
		{
			forAll(pEdges, eI)
			{
				if (findIndex(newEdgeList, pEdges[eI]) == -1)
				{
					WarningInFunction
						<< "Cannot find all original edges in the new list"
						<< nl
						<< "    Original pointEdges = " << pEdges << nl
						<< "    New pointEdges = " << newEdgeList
						<< endl;

					newEdgeList = pEdges;

					break;
				}
			}

			sortedPointEdges[pointi] = newEdgeList;
		}
	}

	return sortedPointEdges;
}


// ************************************************************************* //