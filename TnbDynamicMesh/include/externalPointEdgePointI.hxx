#pragma once
#include <polyMesh.hxx>
#include <transform.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class TrackingData>
inline bool tnbLib::externalPointEdgePoint::update
(
	const point& pt,
	const externalPointEdgePoint& w2,
	const scalar tol,
	TrackingData& td
)
{
	scalar dist2 = magSqr(pt - w2.origin());

	if (!valid(td))
	{
		// current not yet set so use any value
		distSqr_ = dist2;
		origin_ = w2.origin();

		return true;
	}

	scalar diff = distSqr_ - dist2;

	if (diff < 0)
	{
		// already nearer to pt
		return false;
	}

	if ((diff < small) || ((distSqr_ > small) && (diff / distSqr_ < tol)))
	{
		// don't propagate small changes
		return false;
	}
	else
	{
		// update with new values
		distSqr_ = dist2;
		origin_ = w2.origin();

		return true;
	}
}


template<class TrackingData>
inline bool tnbLib::externalPointEdgePoint::update
(
	const externalPointEdgePoint& w2,
	const scalar tol,
	TrackingData& td
)
{
	if (!valid(td))
	{
		// current not yet set so use any value
		distSqr_ = w2.distSqr();
		origin_ = w2.origin();

		return true;
	}

	scalar diff = distSqr_ - w2.distSqr();

	if (diff < 0)
	{
		// already nearer to pt
		return false;
	}

	if ((diff < small) || ((distSqr_ > small) && (diff / distSqr_ < tol)))
	{
		// don't propagate small changes
		return false;
	}
	else
	{
		// update with new values
		distSqr_ = w2.distSqr();
		origin_ = w2.origin();

		return true;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::externalPointEdgePoint::externalPointEdgePoint()
	:
	origin_(point::max),
	distSqr_(great)
{}


inline tnbLib::externalPointEdgePoint::externalPointEdgePoint
(
	const point& origin,
	const scalar distSqr
)
	:
	origin_(origin),
	distSqr_(distSqr)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const tnbLib::point& tnbLib::externalPointEdgePoint::origin() const
{
	return origin_;
}


inline tnbLib::scalar tnbLib::externalPointEdgePoint::distSqr() const
{
	return distSqr_;
}


template<class TrackingData>
inline bool tnbLib::externalPointEdgePoint::valid(TrackingData& td) const
{
	return origin_ != point::max;
}


// Checks for cyclic points
template<class TrackingData>
inline bool tnbLib::externalPointEdgePoint::sameGeometry
(
	const externalPointEdgePoint& w2,
	const scalar tol,
	TrackingData& td
) const
{
	scalar diff = tnbLib::mag(distSqr() - w2.distSqr());

	if (diff < small)
	{
		return true;
	}
	else
	{
		if ((distSqr() > small) && ((diff / distSqr()) < tol))
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
inline void tnbLib::externalPointEdgePoint::leaveDomain
(
	const polyPatch& patch,
	const label patchPointi,
	const point& coord,
	TrackingData& td
)
{
	origin_ -= coord;
}


template<class TrackingData>
inline void tnbLib::externalPointEdgePoint::transform
(
	const tensor& rotTensor,
	TrackingData& td
)
{
	origin_ = tnbLib::transform(rotTensor, origin_);
}


template<class TrackingData>
inline void tnbLib::externalPointEdgePoint::enterDomain
(
	const polyPatch& patch,
	const label patchPointi,
	const point& coord,
	TrackingData& td
)
{
	// back to absolute form
	origin_ += coord;
}


template<class TrackingData>
inline bool tnbLib::externalPointEdgePoint::updatePoint
(
	const polyMesh& mesh,
	const label pointi,
	const label edgeI,
	const externalPointEdgePoint& edgeInfo,
	const scalar tol,
	TrackingData& td
)
{
	return update(td.points_[pointi], edgeInfo, tol, td);
}


template<class TrackingData>
inline bool tnbLib::externalPointEdgePoint::updatePoint
(
	const polyMesh& mesh,
	const label pointi,
	const externalPointEdgePoint& newPointInfo,
	const scalar tol,
	TrackingData& td
)
{
	return update(td.points_[pointi], newPointInfo, tol, td);
}


template<class TrackingData>
inline bool tnbLib::externalPointEdgePoint::updatePoint
(
	const externalPointEdgePoint& newPointInfo,
	const scalar tol,
	TrackingData& td
)
{
	return update(newPointInfo, tol, td);
}


template<class TrackingData>
inline bool tnbLib::externalPointEdgePoint::updateEdge
(
	const polyMesh& mesh,
	const label edgeI,
	const label pointi,
	const externalPointEdgePoint& pointInfo,
	const scalar tol,
	TrackingData& td
)
{
	const edge& e = mesh.edges()[edgeI];
	return update(e.centre(td.points_), pointInfo, tol, td);
}


template<class TrackingData>
inline bool tnbLib::externalPointEdgePoint::equal
(
	const externalPointEdgePoint& rhs,
	TrackingData& td
) const
{
	return operator==(rhs);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline bool tnbLib::externalPointEdgePoint::operator==
(
	const tnbLib::externalPointEdgePoint& rhs
	)
	const
{
	return (origin() == rhs.origin()) && (distSqr() == rhs.distSqr());
}


inline bool tnbLib::externalPointEdgePoint::operator!=
(
	const tnbLib::externalPointEdgePoint& rhs
	)
	const
{
	return !(*this == rhs);
}


// ************************************************************************* //