#include <pointIndexHitList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::scalar tnbLib::minDist(const List<pointIndexHit>& hitList)
{
	scalar minDist = GREAT;

	for (label hi1 = 0; hi1 < hitList.size() - 1; ++hi1)
	{
		const pointIndexHit& pHit1 = hitList[hi1];

		if (pHit1.hit())
		{
			for (label hi2 = hi1 + 1; hi2 < hitList.size(); ++hi2)
			{
				const pointIndexHit& pHit2 = hitList[hi2];

				if (pHit2.hit())
				{
					minDist =
						min(mag(pHit1.hitPoint() - pHit2.hitPoint()), minDist);
				}
			}
		}
	}

	return minDist;
}


// ************************************************************************* //