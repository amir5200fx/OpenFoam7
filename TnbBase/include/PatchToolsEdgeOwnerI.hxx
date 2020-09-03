#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class FaceList, class PointField>
tnbLib::labelList tnbLib::PatchTools::edgeOwner
(
	const PrimitivePatch<FaceList, PointField>& p
)
{
	typedef typename PrimitivePatch<FaceList, PointField>::FaceType FaceType;

	const edgeList& edges = p.edges();
	const labelListList& edgeFaces = p.edgeFaces();
	const List<FaceType>& localFaces = p.localFaces();

	// create the owner list
	labelList edgeOwner(edges.size(), -1);

	forAll(edges, edgeI)
	{
		const labelList& nbrFaces = edgeFaces[edgeI];

		if (nbrFaces.size() == 1)
		{
			edgeOwner[edgeI] = nbrFaces[0];
		}
		else
		{
			// Find the first face whose vertices are aligned with the edge.
			// with multiply connected edges, this is the best we can do
			forAll(nbrFaces, i)
			{
				const FaceType& f = localFaces[nbrFaces[i]];

				if (f.edgeDirection(edges[edgeI]) > 0)
				{
					edgeOwner[edgeI] = nbrFaces[i];
					break;
				}
			}

			if (edgeOwner[edgeI] == -1)
			{
				FatalErrorInFunction
					<< "Edge " << edgeI << " vertices:" << edges[edgeI]
					<< " is used by faces " << nbrFaces
					<< " vertices:"
					<< UIndirectList<FaceType>(localFaces, nbrFaces)()
					<< " none of which use the edge vertices in the same order"
					<< nl << "I give up" << abort(FatalError);
			}
		}
	}

	return edgeOwner;
}


// ************************************************************************* //