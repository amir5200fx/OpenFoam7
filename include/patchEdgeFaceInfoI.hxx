#pragma once
#include <polyMesh.hxx>
#include <transform.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

// Update this with w2 if w2 nearer to pt.
template<class TrackingData>
inline bool tnbLib::patchEdgeFaceInfo::update
(
	const point& pt,
	const patchEdgeFaceInfo& w2,
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


// Update this with w2 (information on same edge)
template<class TrackingData>
inline bool tnbLib::patchEdgeFaceInfo::update
(
	const patchEdgeFaceInfo& w2,
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

inline tnbLib::patchEdgeFaceInfo::patchEdgeFaceInfo()
	:
	origin_(point::max),
	distSqr_(sqr(great))
{}


inline tnbLib::patchEdgeFaceInfo::patchEdgeFaceInfo
(
	const point& origin,
	const scalar distSqr
)
	:
	origin_(origin),
	distSqr_(distSqr)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const tnbLib::point& tnbLib::patchEdgeFaceInfo::origin() const
{
	return origin_;
}


inline tnbLib::scalar tnbLib::patchEdgeFaceInfo::distSqr() const
{
	return distSqr_;
}


template<class TrackingData>
inline bool tnbLib::patchEdgeFaceInfo::valid(TrackingData& td) const
{
	return origin_ != point::max;
}


template<class TrackingData>
inline void tnbLib::patchEdgeFaceInfo::transform
(
	const polyMesh& mesh,
	const primitivePatch& patch,
	const tensor& rotTensor,
	const scalar tol,
	TrackingData& td
)
{
	origin_ = tnbLib::transform(rotTensor, origin_);
}


template<class TrackingData>
inline bool tnbLib::patchEdgeFaceInfo::updateEdge
(
	const polyMesh& mesh,
	const primitivePatch& patch,
	const label edgeI,
	const label facei,
	const patchEdgeFaceInfo& faceInfo,
	const scalar tol,
	TrackingData& td
)
{
	const edge& e = patch.edges()[edgeI];
	point eMid =
		0.5
		* (
			patch.points()[patch.meshPoints()[e[0]]]
			+ patch.points()[patch.meshPoints()[e[1]]]
			);
	return update(eMid, faceInfo, tol, td);
}


template<class TrackingData>
inline bool tnbLib::patchEdgeFaceInfo::updateEdge
(
	const polyMesh& mesh,
	const primitivePatch& patch,
	const patchEdgeFaceInfo& edgeInfo,
	const bool sameOrientation,
	const scalar tol,
	TrackingData& td
)
{
	return update(edgeInfo, tol, td);
}


template<class TrackingData>
inline bool tnbLib::patchEdgeFaceInfo::updateFace
(
	const polyMesh& mesh,
	const primitivePatch& patch,
	const label facei,
	const label edgeI,
	const patchEdgeFaceInfo& edgeInfo,
	const scalar tol,
	TrackingData& td
)
{
	return update(patch.faceCentres()[facei], edgeInfo, tol, td);
}


template<class TrackingData>
inline bool tnbLib::patchEdgeFaceInfo::equal
(
	const patchEdgeFaceInfo& rhs,
	TrackingData& td
) const
{
	return operator==(rhs);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline bool tnbLib::patchEdgeFaceInfo::operator==
(
	const tnbLib::patchEdgeFaceInfo& rhs
	) const
{
	return origin() == rhs.origin();
}


inline bool tnbLib::patchEdgeFaceInfo::operator!=
(
	const tnbLib::patchEdgeFaceInfo& rhs
	) const
{
	return !(*this == rhs);
}


// ************************************************************************* //