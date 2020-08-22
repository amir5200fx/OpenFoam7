#include <blockDescriptor.hxx>

#include <lineEdge.hxx>
#include <lineDivide.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

tnbLib::label tnbLib::blockDescriptor::edgePointsWeights
(
	pointField(&edgePoints)[12],
	scalarList(&edgeWeights)[12],
	const label edgei,
	const label start,
	const label end,
	const label nDiv
) const
{
	// Set reference to the list of labels defining the block
	const labelList& blockLabels = blockShape_;

	// Get list of points for this block
	const pointField blockPoints = blockShape_.points(vertices_);

	// Set the edge points/weights
	// The edge is a straight-line if it is not in the list of blockEdges

	forAll(edges_, cedgei)
	{
		const blockEdge& cedge = edges_[cedgei];

		const int cmp = cedge.compare(blockLabels[start], blockLabels[end]);

		if (cmp)
		{
			if (cmp > 0)
			{
				// Curve has the same orientation

				// Divide the line
				const lineDivide divEdge(cedge, nDiv, expand_[edgei]);

				edgePoints[edgei] = divEdge.points();
				edgeWeights[edgei] = divEdge.lambdaDivisions();
			}
			else
			{
				// Curve has the opposite orientation

				// Divide the line
				const lineDivide divEdge(cedge, nDiv, expand_[edgei].inv());

				const pointField& p = divEdge.points();
				const scalarList& d = divEdge.lambdaDivisions();

				edgePoints[edgei].setSize(p.size());
				edgeWeights[edgei].setSize(d.size());

				label pn = p.size() - 1;
				forAll(p, pi)
				{
					edgePoints[edgei][pi] = p[pn - pi];
					edgeWeights[edgei][pi] = 1 - d[pn - pi];
				}
			}

			// Found curved-edge: done
			return 1;
		}
	}


	// Not curved-edge: divide the edge as a straight line
	lineDivide divEdge
	(
		blockEdges::lineEdge(blockPoints, start, end),
		nDiv,
		expand_[edgei]
	);

	edgePoints[edgei] = divEdge.points();
	edgeWeights[edgei] = divEdge.lambdaDivisions();

	return 0;
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::label tnbLib::blockDescriptor::edgesPointsWeights
(
	pointField(&edgePoints)[12],
	scalarList(&edgeWeights)[12]
) const
{
	label nCurvedEdges = 0;

	// X-direction
	const label ni = density_.x();
	nCurvedEdges += edgePointsWeights(edgePoints, edgeWeights, 0, 0, 1, ni);
	nCurvedEdges += edgePointsWeights(edgePoints, edgeWeights, 1, 3, 2, ni);
	nCurvedEdges += edgePointsWeights(edgePoints, edgeWeights, 2, 7, 6, ni);
	nCurvedEdges += edgePointsWeights(edgePoints, edgeWeights, 3, 4, 5, ni);

	// Y-direction
	const label nj = density_.y();
	nCurvedEdges += edgePointsWeights(edgePoints, edgeWeights, 4, 0, 3, nj);
	nCurvedEdges += edgePointsWeights(edgePoints, edgeWeights, 5, 1, 2, nj);
	nCurvedEdges += edgePointsWeights(edgePoints, edgeWeights, 6, 5, 6, nj);
	nCurvedEdges += edgePointsWeights(edgePoints, edgeWeights, 7, 4, 7, nj);

	// Z-direction
	const label nk = density_.z();
	nCurvedEdges += edgePointsWeights(edgePoints, edgeWeights, 8, 0, 4, nk);
	nCurvedEdges += edgePointsWeights(edgePoints, edgeWeights, 9, 1, 5, nk);
	nCurvedEdges += edgePointsWeights(edgePoints, edgeWeights, 10, 2, 6, nk);
	nCurvedEdges += edgePointsWeights(edgePoints, edgeWeights, 11, 3, 7, nk);

	return nCurvedEdges;
}


// ************************************************************************* //