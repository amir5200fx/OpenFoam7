#pragma once
#include <pointConversion.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class PointType>
tnbLib::autoPtr<tnbLib::mapDistribute>
tnbLib::backgroundMeshDecomposition::distributePoints
(
	List<PointType>& points
) const
{
	labelList toProc(processorPosition(points));

	autoPtr<mapDistribute> map(buildMap(toProc));

	map().distribute(points);

	return map;
}


template<class PointType>
tnbLib::labelList tnbLib::backgroundMeshDecomposition::processorPosition
(
	const List<PointType>& pts
) const
{
	DynamicList<label> toCandidateProc;
	DynamicList<point> testPoints;
	labelList ptBlockStart(pts.size(), -1);
	labelList ptBlockSize(pts.size(), -1);

	label nTotalCandidates = 0;

	forAll(pts, pI)
	{
		pointFromPoint pt = topoint(pts[pI]);

		label nCandidates = 0;

		forAll(allBackgroundMeshBounds_, proci)
		{
			if (allBackgroundMeshBounds_[proci].contains(pt))
			{
				toCandidateProc.append(proci);
				testPoints.append(pt);

				nCandidates++;
			}
		}

		ptBlockStart[pI] = nTotalCandidates;
		ptBlockSize[pI] = nCandidates;

		nTotalCandidates += nCandidates;
	}

	// Needed for reverseDistribute
	label preDistributionToCandidateProcSize = toCandidateProc.size();

	autoPtr<mapDistribute> map(buildMap(toCandidateProc));

	map().distribute(testPoints);

	List<bool> pointOnCandidate(testPoints.size(), false);

	// Test candidate points on candidate processors
	forAll(testPoints, tPI)
	{
		pointOnCandidate[tPI] = positionOnThisProcessor(testPoints[tPI]);
	}

	map().reverseDistribute
	(
		preDistributionToCandidateProcSize,
		pointOnCandidate
	);

	labelList ptProc(pts.size(), -1);

	DynamicList<label> failedPointIndices;
	DynamicList<point> failedPoints;

	forAll(pts, pI)
	{
		// Extract the sub list of results for this point

		SubList<bool> ptProcResults
		(
			pointOnCandidate,
			ptBlockSize[pI],
			ptBlockStart[pI]
		);

		forAll(ptProcResults, pPRI)
		{
			if (ptProcResults[pPRI])
			{
				ptProc[pI] = toCandidateProc[ptBlockStart[pI] + pPRI];

				break;
			}
		}

		if (ptProc[pI] < 0)
		{
			pointFromPoint pt = topoint(pts[pI]);

			if (!globalBackgroundBounds_.contains(pt))
			{
				FatalErrorInFunction
					<< "The position " << pt
					<< " is not in any part of the background mesh "
					<< globalBackgroundBounds_ << endl
					<< "A background mesh with a wider margin around "
					<< "the geometry may help."
					<< exit(FatalError);
			}

			if (debug)
			{
				WarningInFunction
					<< "The position " << pt
					<< " was not found in the background mesh "
					<< globalBackgroundBounds_ << ", finding nearest."
					<< endl;
			}

			failedPointIndices.append(pI);
			failedPoints.append(pt);
		}
	}

	labelList ptNearestProc(processorNearestPosition(failedPoints));

	forAll(failedPoints, fPI)
	{
		label pI = failedPointIndices[fPI];

		ptProc[pI] = ptNearestProc[fPI];
	}

	return ptProc;
}


// ************************************************************************* //