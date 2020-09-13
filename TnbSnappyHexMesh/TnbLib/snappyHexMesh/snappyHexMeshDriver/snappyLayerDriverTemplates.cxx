#include <snappyLayerDriver.hxx>

#include <syncTools.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Type>
void tnbLib::snappyLayerDriver::averageNeighbours
(
	const polyMesh& mesh,
	const PackedBoolList& isMasterEdge,
	const labelList& meshEdges,
	const labelList& meshPoints,
	const edgeList& edges,
	const scalarField& invSumWeight,
	const Field<Type>& data,
	Field<Type>& average
)
{
	const pointField& pts = mesh.points();

	average = Zero;

	forAll(edges, edgeI)
	{
		if (isMasterEdge.get(meshEdges[edgeI]) == 1)
		{
			const edge& e = edges[edgeI];
			// scalar eWeight = edgeWeights[edgeI];
			// scalar eWeight =  1.0;
			scalar eMag = max
			(
				vSmall,
				mag
				(
					pts[meshPoints[e[1]]]
					- pts[meshPoints[e[0]]]
				)
			);
			scalar eWeight = 1.0 / eMag;

			label v0 = e[0];
			label v1 = e[1];

			average[v0] += eWeight * data[v1];
			average[v1] += eWeight * data[v0];
		}
	}

	syncTools::syncPointList
	(
		mesh,
		meshPoints,
		average,
		plusEqOp<Type>(),
		Zero     // null value
	);

	average *= invSumWeight;
}


// ************************************************************************* //