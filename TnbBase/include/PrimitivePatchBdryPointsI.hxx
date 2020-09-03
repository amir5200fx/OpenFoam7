#pragma once
#include <HashSet.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class FaceList, class PointField>
void tnbLib::PrimitivePatch<FaceList, PointField>::calcBdryPoints() const
{
	if (debug)
	{
		InfoInFunction << "Calculating boundary points" << endl;
	}

	if (boundaryPointsPtr_)
	{
		// it is considered an error to attempt to recalculate
		// if already allocated
		FatalErrorInFunction
			<< "edge types already calculated"
			<< abort(FatalError);
	}

	const edgeList& e = edges();

	labelHashSet bp(2 * e.size());

	for (label edgeI = nInternalEdges_; edgeI < e.size(); edgeI++)
	{
		const edge& curEdge = e[edgeI];

		bp.insert(curEdge.start());
		bp.insert(curEdge.end());
	}

	boundaryPointsPtr_ = new labelList(bp.toc());
	sort(*boundaryPointsPtr_);

	if (debug)
	{
		Info << "    Finished." << endl;
	}
}


// ************************************************************************* //