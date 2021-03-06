#pragma once
#include <polyMesh.hxx>
#include <transform.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

// Update this with w2 if w2 nearer to pt.
template<class TrackingData>
inline bool tnbLib::wallPoint::update
(
	const point& pt,
	const wallPoint& w2,
	const scalar tol,
	TrackingData& td
)
{
	// Already done in calling algorithm
	// if (w2.origin() == origin_)
	//{
	//    // Shortcut. Same input so same distance.
	//    return false;
	//}

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


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::wallPoint::wallPoint()
	:
	origin_(point::max),
	distSqr_(-great)
{}


inline tnbLib::wallPoint::wallPoint(const point& origin, const scalar distSqr)
	:
	origin_(origin),
	distSqr_(distSqr)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const tnbLib::point& tnbLib::wallPoint::origin() const
{
	return origin_;
}


inline tnbLib::point& tnbLib::wallPoint::origin()
{
	return origin_;
}


inline tnbLib::scalar tnbLib::wallPoint::distSqr() const
{
	return distSqr_;
}


inline tnbLib::scalar& tnbLib::wallPoint::distSqr()
{
	return distSqr_;
}


template<class TrackingData>
inline bool tnbLib::wallPoint::valid(TrackingData& td) const
{
	return distSqr_ > -small;
}


// Checks for cyclic faces
template<class TrackingData>
inline bool tnbLib::wallPoint::sameGeometry
(
	const polyMesh&,
	const wallPoint& w2,
	const scalar tol,
	TrackingData& td
) const
{
	scalar diff = mag(distSqr() - w2.distSqr());

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
inline void tnbLib::wallPoint::leaveDomain
(
	const polyMesh&,
	const polyPatch&,
	const label,
	const point& faceCentre,
	TrackingData& td
)
{
	origin_ -= faceCentre;
}


template<class TrackingData>
inline void tnbLib::wallPoint::transform
(
	const polyMesh&,
	const tensor& rotTensor,
	TrackingData& td
)
{
	origin_ = tnbLib::transform(rotTensor, origin_);
}


// Update absolute geometric quantities. Note that distance (distSqr_)
// is not affected by leaving/entering domain.
template<class TrackingData>
inline void tnbLib::wallPoint::enterDomain
(
	const polyMesh&,
	const polyPatch&,
	const label,
	const point& faceCentre,
	TrackingData& td
)
{
	// back to absolute form
	origin_ += faceCentre;
}


// Update this with w2 if w2 nearer to pt.
template<class TrackingData>
inline bool tnbLib::wallPoint::updateCell
(
	const polyMesh& mesh,
	const label thisCelli,
	const label neighbourFacei,
	const wallPoint& neighbourWallInfo,
	const scalar tol,
	TrackingData& td
)
{
	return
		update
		(
			mesh.cellCentres()[thisCelli],
			neighbourWallInfo,
			tol,
			td
		);
}


// Update this with w2 if w2 nearer to pt.
template<class TrackingData>
inline bool tnbLib::wallPoint::updateFace
(
	const polyMesh& mesh,
	const label thisFacei,
	const label neighbourCelli,
	const wallPoint& neighbourWallInfo,
	const scalar tol,
	TrackingData& td
)
{
	return
		update
		(
			mesh.faceCentres()[thisFacei],
			neighbourWallInfo,
			tol,
			td
		);
}

// Update this with w2 if w2 nearer to pt.
template<class TrackingData>
inline bool tnbLib::wallPoint::updateFace
(
	const polyMesh& mesh,
	const label thisFacei,
	const wallPoint& neighbourWallInfo,
	const scalar tol,
	TrackingData& td
)
{
	return
		update
		(
			mesh.faceCentres()[thisFacei],
			neighbourWallInfo,
			tol,
			td
		);
}


template<class TrackingData>
inline bool tnbLib::wallPoint::equal
(
	const wallPoint& rhs,
	TrackingData& td
) const
{
	return operator==(rhs);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline bool tnbLib::wallPoint::operator==(const tnbLib::wallPoint& rhs) const
{
	return origin() == rhs.origin();
}


inline bool tnbLib::wallPoint::operator!=(const tnbLib::wallPoint& rhs) const
{
	return !(*this == rhs);
}


// ************************************************************************* //