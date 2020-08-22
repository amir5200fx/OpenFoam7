#pragma once
#include <polyMesh.hxx>
#include <transform.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

// Update this with w2.
template<class TrackingData>
inline bool tnbLib::pointEdgeStructuredWalk::update
(
	const pointEdgeStructuredWalk& w2,
	const scalar tol,
	TrackingData& td
)
{
	if (!valid(td))
	{
		// current not yet set. Walked from w2 to here (=point0)
		dist_ = w2.dist_ + mag(point0_ - w2.previousPoint_);
		previousPoint_ = point0_;
		data_ = w2.data_;

		return true;
	}
	else
	{
		return false;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Null constructor
inline tnbLib::pointEdgeStructuredWalk::pointEdgeStructuredWalk()
	:
	point0_(vector::max),
	previousPoint_(vector::max),
	dist_(0),
	data_(Zero)
{}


// Construct from origin, distance
inline tnbLib::pointEdgeStructuredWalk::pointEdgeStructuredWalk
(
	const point& point0,
	const point& previousPoint,
	const scalar dist,
	const vector& data
)
	:
	point0_(point0),
	previousPoint_(previousPoint),
	dist_(dist),
	data_(data)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline bool tnbLib::pointEdgeStructuredWalk::inZone() const
{
	return point0_ != vector::max;
}


//inline const tnbLib::point& tnbLib::pointEdgeStructuredWalk::previousPoint() const
//{
//    return previousPoint_;
//}


inline tnbLib::scalar tnbLib::pointEdgeStructuredWalk::dist() const
{
	return dist_;
}


inline const tnbLib::vector& tnbLib::pointEdgeStructuredWalk::data() const
{
	return data_;
}


template<class TrackingData>
inline bool tnbLib::pointEdgeStructuredWalk::valid(TrackingData& td) const
{
	return previousPoint_ != vector::max;
}


// Checks for cyclic points
template<class TrackingData>
inline bool tnbLib::pointEdgeStructuredWalk::sameGeometry
(
	const pointEdgeStructuredWalk& w2,
	const scalar tol,
	TrackingData& td
) const
{
	scalar diff = tnbLib::mag(dist() - w2.dist());

	if (diff < small)
	{
		return true;
	}
	else
	{
		if ((dist() > small) && ((diff / dist()) < tol))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}


template<class TrackingData>
inline void tnbLib::pointEdgeStructuredWalk::leaveDomain
(
	const polyPatch& patch,
	const label patchPointi,
	const point& coord,
	TrackingData& td
)
{
	previousPoint_ -= coord;
}


template<class TrackingData>
inline void tnbLib::pointEdgeStructuredWalk::transform
(
	const tensor& rotTensor,
	TrackingData& td
)
{
	previousPoint_ = tnbLib::transform(rotTensor, previousPoint_);
}


// Update absolute geometric quantities. Note that distance (dist_)
// is not affected by leaving/entering domain.
template<class TrackingData>
inline void tnbLib::pointEdgeStructuredWalk::enterDomain
(
	const polyPatch& patch,
	const label patchPointi,
	const point& coord,
	TrackingData& td
)
{
	// back to absolute form
	previousPoint_ += coord;
}


// Update this with information from connected edge
template<class TrackingData>
inline bool tnbLib::pointEdgeStructuredWalk::updatePoint
(
	const polyMesh& mesh,
	const label pointi,
	const label edgeI,
	const pointEdgeStructuredWalk& edgeInfo,
	const scalar tol,
	TrackingData& td
)
{
	if (inZone())
	{
		return update(edgeInfo, tol, td);
	}
	else
	{
		return false;
	}
}


// Update this with new information on same point
template<class TrackingData>
inline bool tnbLib::pointEdgeStructuredWalk::updatePoint
(
	const polyMesh& mesh,
	const label pointi,
	const pointEdgeStructuredWalk& newPointInfo,
	const scalar tol,
	TrackingData& td
)
{
	if (inZone())
	{
		return update(newPointInfo, tol, td);
	}
	else
	{
		return false;
	}
}


// Update this with new information on same point. No extra information.
template<class TrackingData>
inline bool tnbLib::pointEdgeStructuredWalk::updatePoint
(
	const pointEdgeStructuredWalk& newPointInfo,
	const scalar tol,
	TrackingData& td
)
{
	return update(newPointInfo, tol, td);
}


// Update this with information from connected point
template<class TrackingData>
inline bool tnbLib::pointEdgeStructuredWalk::updateEdge
(
	const polyMesh& mesh,
	const label edgeI,
	const label pointi,
	const pointEdgeStructuredWalk& pointInfo,
	const scalar tol,
	TrackingData& td
)
{
	if (inZone())
	{
		return update(pointInfo, tol, td);
	}
	else
	{
		return false;
	}
}


template<class TrackingData>
inline bool tnbLib::pointEdgeStructuredWalk::equal
(
	const pointEdgeStructuredWalk& rhs,
	TrackingData& td
) const
{
	return operator==(rhs);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline bool tnbLib::pointEdgeStructuredWalk::operator==
(
	const tnbLib::pointEdgeStructuredWalk& rhs
	) const
{
	return previousPoint_ == rhs.previousPoint_;
}


inline bool tnbLib::pointEdgeStructuredWalk::operator!=
(
	const tnbLib::pointEdgeStructuredWalk& rhs
	) const
{
	return !(*this == rhs);
}


// ************************************************************************* //