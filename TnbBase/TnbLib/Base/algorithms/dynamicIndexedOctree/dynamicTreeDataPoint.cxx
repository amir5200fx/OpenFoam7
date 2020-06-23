#include <dynamicTreeDataPoint.hxx>

#include <treeBoundBox.hxx>
#include <dynamicIndexedOctree.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(dynamicTreeDataPoint, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::dynamicTreeDataPoint::dynamicTreeDataPoint
(
	const DynamicList<point>& points
)
	:
	points_(points)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::DynamicList<tnbLib::point>&
tnbLib::dynamicTreeDataPoint::shapePoints() const
{
	return points_;
}


tnbLib::volumeType tnbLib::dynamicTreeDataPoint::getVolumeType
(
	const dynamicIndexedOctree<dynamicTreeDataPoint>& oc,
	const point& sample
) const
{
	return volumeType::unknown;
}


bool tnbLib::dynamicTreeDataPoint::overlaps
(
	const label index,
	const treeBoundBox& cubeBb
) const
{
	return cubeBb.contains(points_[index]);
}


bool tnbLib::dynamicTreeDataPoint::overlaps
(
	const label index,
	const point& centre,
	const scalar radiusSqr
) const
{
	const point& p = points_[index];

	const scalar distSqr = magSqr(p - centre);

	if (distSqr <= radiusSqr)
	{
		return true;
	}

	return false;
}


void tnbLib::dynamicTreeDataPoint::findNearest
(
	const labelUList& indices,
	const point& sample,

	scalar& nearestDistSqr,
	label& minIndex,
	point& nearestPoint
) const
{
	forAll(indices, i)
	{
		const label index = indices[i];

		const point& pt = points_[index];

		scalar distSqr = magSqr(pt - sample);

		if (distSqr < nearestDistSqr)
		{
			nearestDistSqr = distSqr;
			minIndex = index;
			nearestPoint = pt;
		}
	}
}


void tnbLib::dynamicTreeDataPoint::findNearest
(
	const labelUList& indices,
	const linePointRef& ln,

	treeBoundBox& tightest,
	label& minIndex,
	point& linePoint,
	point& nearestPoint
) const
{
	// Best so far
	scalar nearestDistSqr = magSqr(linePoint - nearestPoint);

	forAll(indices, i)
	{
		const label index = indices[i];

		const point& shapePt = points_[index];

		if (tightest.contains(shapePt))
		{
			// Nearest point on line
			pointHit pHit = ln.nearestDist(shapePt);
			scalar distSqr = sqr(pHit.distance());

			if (distSqr < nearestDistSqr)
			{
				nearestDistSqr = distSqr;
				minIndex = index;
				linePoint = pHit.rawPoint();
				nearestPoint = shapePt;

				{
					point& minPt = tightest.min();
					minPt = min(ln.start(), ln.end());
					minPt.x() -= pHit.distance();
					minPt.y() -= pHit.distance();
					minPt.z() -= pHit.distance();
				}
				{
					point& maxPt = tightest.max();
					maxPt = max(ln.start(), ln.end());
					maxPt.x() += pHit.distance();
					maxPt.y() += pHit.distance();
					maxPt.z() += pHit.distance();
				}
			}
		}
	}
}


// ************************************************************************* //