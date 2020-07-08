#include <treeDataPoint.hxx>

#include <indexedOctree.hxx>
#include <treeBoundBox.hxx>
#include <triangleFuncs.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(treeDataPoint, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::treeDataPoint::treeDataPoint(const pointField& points)
	:
	points_(points),
	useSubset_(false)
{}


tnbLib::treeDataPoint::treeDataPoint
(
	const pointField& points,
	const labelList& pointLabels
)
	:
	points_(points),
	pointLabels_(pointLabels),
	useSubset_(true)
{}


tnbLib::treeDataPoint::findNearestOp::findNearestOp
(
	const indexedOctree<treeDataPoint>& tree
)
	:
	tree_(tree)
{}


tnbLib::treeDataPoint::findIntersectOp::findIntersectOp
(
	const indexedOctree<treeDataPoint>& tree
)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::pointField tnbLib::treeDataPoint::shapePoints() const
{
	if (useSubset_)
	{
		return pointField(points_, pointLabels_);
	}
	else
	{
		return points_;
	}
}


tnbLib::volumeType tnbLib::treeDataPoint::getVolumeType
(
	const indexedOctree<treeDataPoint>& oc,
	const point& sample
) const
{
	return volumeType::unknown;
}


bool tnbLib::treeDataPoint::overlaps
(
	const label index,
	const treeBoundBox& cubeBb
) const
{
	label pointi = (useSubset_ ? pointLabels_[index] : index);
	return cubeBb.contains(points_[pointi]);
}


bool tnbLib::treeDataPoint::overlaps
(
	const label index,
	const point& centre,
	const scalar radiusSqr
) const
{
	label pointi = (useSubset_ ? pointLabels_[index] : index);

	if (magSqr(points_[pointi] - centre) <= radiusSqr)
	{
		return true;
	}

	return false;
}


void tnbLib::treeDataPoint::findNearestOp::operator()
(
	const labelUList& indices,
	const point& sample,

	scalar& nearestDistSqr,
	label& minIndex,
	point& nearestPoint
	) const
{
	const treeDataPoint& shape = tree_.shapes();

	forAll(indices, i)
	{
		const label index = indices[i];
		label pointi =
			(
				shape.useSubset()
				? shape.pointLabels()[index]
				: index
				);

		const point& pt = shape.points()[pointi];

		scalar distSqr = magSqr(pt - sample);

		if (distSqr < nearestDistSqr)
		{
			nearestDistSqr = distSqr;
			minIndex = index;
			nearestPoint = pt;
		}
	}
}


void tnbLib::treeDataPoint::findNearestOp::operator()
(
	const labelUList& indices,
	const linePointRef& ln,

	treeBoundBox& tightest,
	label& minIndex,
	point& linePoint,
	point& nearestPoint
	) const
{
	const treeDataPoint& shape = tree_.shapes();

	// Best so far
	scalar nearestDistSqr = great;
	if (minIndex >= 0)
	{
		nearestDistSqr = magSqr(linePoint - nearestPoint);
	}

	forAll(indices, i)
	{
		const label index = indices[i];
		label pointi =
			(
				shape.useSubset()
				? shape.pointLabels()[index]
				: index
				);

		const point& shapePt = shape.points()[pointi];

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


bool tnbLib::treeDataPoint::findIntersectOp::operator()
(
	const label index,
	const point& start,
	const point& end,
	point& result
	) const
{
	NotImplemented;
	return false;
}


// ************************************************************************* //