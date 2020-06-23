#include <primitiveMeshTools.hxx>

#include <primitiveMesh.hxx>
#include <SortableList.hxx>
#include <PstreamReduceOps.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

bool tnbLib::primitiveMesh::checkPointNearness
(
	const bool report,
	const scalar reportDistSqr,
	labelHashSet* setPtr
) const
{
	const pointField& points = this->points();

	// Sort points
	SortableList<scalar> sortedMag(magSqr(points));

	label nClose = 0;

	for (label i = 1; i < sortedMag.size(); i++)
	{
		label pti = sortedMag.indices()[i];

		// Compare pti to any previous points with similar sortedMag
		for
			(
				label j = i - 1;
				j >= 0 && (sortedMag[j] > sortedMag[i] - reportDistSqr);
				--j
				)
		{
			label prevPtI = sortedMag.indices()[j];

			if (magSqr(points[pti] - points[prevPtI]) < reportDistSqr)
			{
				//// Check if unconnected.
				// const labelList& pEdges = pointEdges()[pti];
				//
				// bool connected = false;
				//
				// forAll(pEdges, pEdgei)
				//{
				//    if (edges()[pEdges[pEdgei]].otherVertex(prevPtI) != -1)
				//    {
				//        connected = true;
				//        break;
				//    }
				//}
				//
				// if (!connected)
				{
					nClose++;

					if (setPtr)
					{
						setPtr->insert(pti);
						setPtr->insert(prevPtI);
					}
				}
			}
		}
	}

	reduce(nClose, sumOp<label>());

	if (nClose > 0)
	{
		if (report)
		{
			Info << "  <<Points closer than " << tnbLib::sqrt(reportDistSqr)
				<< " together found, number: " << nClose
				<< endl;
		}

		return true;
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //