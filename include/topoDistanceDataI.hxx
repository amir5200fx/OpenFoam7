#pragma once
#include <polyMesh.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Null constructor
inline tnbLib::topoDistanceData::topoDistanceData()
	:
	data_(-1),
	distance_(-1)
{}


// Construct from components
inline tnbLib::topoDistanceData::topoDistanceData
(
	const label data,
	const label distance
)
	:
	data_(data),
	distance_(distance)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class TrackingData>
inline bool tnbLib::topoDistanceData::valid(TrackingData& td) const
{
	return distance_ != -1;
}


// No geometric data so never any problem on cyclics
template<class TrackingData>
inline bool tnbLib::topoDistanceData::sameGeometry
(
	const polyMesh&,
	const topoDistanceData&,
	const scalar,
	TrackingData&
) const
{
	return true;
}


// No geometric data.
template<class TrackingData>
inline void tnbLib::topoDistanceData::leaveDomain
(
	const polyMesh&,
	const polyPatch& patch,
	const label patchFacei,
	const point& faceCentre,
	TrackingData&
)
{}


// No geometric data.
template<class TrackingData>
inline void tnbLib::topoDistanceData::transform
(
	const polyMesh&,
	const tensor& rotTensor,
	TrackingData&
)
{}


// No geometric data.
template<class TrackingData>
inline void tnbLib::topoDistanceData::enterDomain
(
	const polyMesh&,
	const polyPatch& patch,
	const label patchFacei,
	const point& faceCentre,
	TrackingData&
)
{}


// Update cell with neighbouring face information
template<class TrackingData>
inline bool tnbLib::topoDistanceData::updateCell
(
	const polyMesh&,
	const label thisCelli,
	const label neighbourFacei,
	const topoDistanceData& neighbourInfo,
	const scalar tol,
	TrackingData&
)
{
	if (distance_ == -1)
	{
		operator=(neighbourInfo);
		return true;
	}
	else
	{
		return false;
	}
}


// Update face with neighbouring cell information
template<class TrackingData>
inline bool tnbLib::topoDistanceData::updateFace
(
	const polyMesh& mesh,
	const label thisFacei,
	const label neighbourCelli,
	const topoDistanceData& neighbourInfo,
	const scalar tol,
	TrackingData&
)
{
	// From cell to its faces.

	if (distance_ == -1)
	{
		data_ = neighbourInfo.data_;
		distance_ = neighbourInfo.distance_ + 1;
		return true;
	}
	else
	{
		return false;
	}
}


// Update face with coupled face information
template<class TrackingData>
inline bool tnbLib::topoDistanceData::updateFace
(
	const polyMesh&,
	const label thisFacei,
	const topoDistanceData& neighbourInfo,
	const scalar tol,
	TrackingData&
)
{
	// From face to face (e.g. coupled faces)
	if (distance_ == -1)
	{
		operator=(neighbourInfo);
		return true;
	}
	else
	{
		return false;
	}
}


template<class TrackingData>
inline bool tnbLib::topoDistanceData::equal
(
	const topoDistanceData& rhs,
	TrackingData& td
) const
{
	return operator==(rhs);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline bool tnbLib::topoDistanceData::operator==
(
	const tnbLib::topoDistanceData& rhs
	) const
{
	return data() == rhs.data() && distance() == rhs.distance();
}


inline bool tnbLib::topoDistanceData::operator!=
(
	const tnbLib::topoDistanceData& rhs
	) const
{
	return !(*this == rhs);
}


// ************************************************************************* //