#pragma once
#include <polyMesh.hxx>
#include <transform.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

// Update this with w2 if w2 nearer to pt.
template<class TrackingData>
inline bool tnbLib::patchEdgeFaceRegion::update
(
	const patchEdgeFaceRegion& w2,
	const scalar tol,
	TrackingData& td
)
{
	if (!w2.valid(td))
	{
		FatalErrorInFunction
			<< "problem." << abort(FatalError);
	}

	if (w2.region_ == -2 || region_ == -2)
	{
		// Blocked edge/face
		return false;
	}

	if (!valid(td))
	{
		// current not yet set so use any value
		operator=(w2);
		return true;
	}
	else
	{
		if (w2.region_ < region_)
		{
			operator=(w2);
			return true;
		}
		else
		{
			return false;
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Null constructor
inline tnbLib::patchEdgeFaceRegion::patchEdgeFaceRegion()
	:
	region_(-1)
{}


// Construct from origin, distance
inline tnbLib::patchEdgeFaceRegion::patchEdgeFaceRegion
(
	const label region
)
	:
	region_(region)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::label tnbLib::patchEdgeFaceRegion::region() const
{
	return region_;
}


template<class TrackingData>
inline bool tnbLib::patchEdgeFaceRegion::valid(TrackingData& td) const
{
	return region_ != -1;
}


template<class TrackingData>
inline void tnbLib::patchEdgeFaceRegion::transform
(
	const polyMesh& mesh,
	const indirectPrimitivePatch& patch,
	const tensor& rotTensor,
	const scalar tol,
	TrackingData& td
)
{}


template<class TrackingData>
inline bool tnbLib::patchEdgeFaceRegion::updateEdge
(
	const polyMesh& mesh,
	const indirectPrimitivePatch& patch,
	const label edgeI,
	const label facei,
	const patchEdgeFaceRegion& faceInfo,
	const scalar tol,
	TrackingData& td
)
{
	return update(faceInfo, tol, td);
}


template<class TrackingData>
inline bool tnbLib::patchEdgeFaceRegion::updateEdge
(
	const polyMesh& mesh,
	const indirectPrimitivePatch& patch,
	const patchEdgeFaceRegion& edgeInfo,
	const bool sameOrientation,
	const scalar tol,
	TrackingData& td
)
{
	return update(edgeInfo, tol, td);
}


template<class TrackingData>
inline bool tnbLib::patchEdgeFaceRegion::updateFace
(
	const polyMesh& mesh,
	const indirectPrimitivePatch& patch,
	const label facei,
	const label edgeI,
	const patchEdgeFaceRegion& edgeInfo,
	const scalar tol,
	TrackingData& td
)
{
	return update(edgeInfo, tol, td);
}


template<class TrackingData>
inline bool tnbLib::patchEdgeFaceRegion::equal
(
	const patchEdgeFaceRegion& rhs,
	TrackingData& td
) const
{
	return operator==(rhs);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline bool tnbLib::patchEdgeFaceRegion::operator==
(
	const tnbLib::patchEdgeFaceRegion& rhs
	) const
{
	return region() == rhs.region();
}


inline bool tnbLib::patchEdgeFaceRegion::operator!=
(
	const tnbLib::patchEdgeFaceRegion& rhs
	) const
{
	return !(*this == rhs);
}


// ************************************************************************* //
