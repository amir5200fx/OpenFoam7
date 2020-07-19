#pragma once
#include <polyMesh.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Null constructor
inline tnbLib::pointTopoDistanceData::pointTopoDistanceData()
	:
	data_(-1),
	distance_(-1)
{}


// Construct from components
inline tnbLib::pointTopoDistanceData::pointTopoDistanceData
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
inline bool tnbLib::pointTopoDistanceData::valid(TrackingData& td) const
{
	return distance_ != -1;
}


// No geometric data so never any problem on cyclics
template<class TrackingData>
inline bool tnbLib::pointTopoDistanceData::sameGeometry
(
	const pointTopoDistanceData&,
	const scalar tol,
	TrackingData& td
) const
{
	return true;
}


// No geometric data.
template<class TrackingData>
inline void tnbLib::pointTopoDistanceData::leaveDomain
(
	const polyPatch& patch,
	const label patchPointi,
	const point& coord,
	TrackingData& td
)
{}


// No geometric data.
template<class TrackingData>
inline void tnbLib::pointTopoDistanceData::transform
(
	const tensor& rotTensor,
	TrackingData& td
)
{}


// No geometric data.
template<class TrackingData>
inline void tnbLib::pointTopoDistanceData::enterDomain
(
	const polyPatch& patch,
	const label patchPointi,
	const point& coord,
	TrackingData& td
)
{}


// Update this with information from connected edge
template<class TrackingData>
inline bool tnbLib::pointTopoDistanceData::updatePoint
(
	const polyMesh& mesh,
	const label pointi,
	const label edgeI,
	const pointTopoDistanceData& edgeInfo,
	const scalar tol,
	TrackingData& td
)
{
	if (distance_ == -1)
	{
		data_ = edgeInfo.data_;
		distance_ = edgeInfo.distance_ + 1;
		return true;
	}
	else
	{
		return false;
	}
}


// Update this with new information on same point
template<class TrackingData>
inline bool tnbLib::pointTopoDistanceData::updatePoint
(
	const polyMesh& mesh,
	const label pointi,
	const pointTopoDistanceData& newPointInfo,
	const scalar tol,
	TrackingData& td
)
{
	if (distance_ == -1)
	{
		operator=(newPointInfo);
		return true;
	}
	else
	{
		return false;
	}
}


// Update this with new information on same point. No extra information.
template<class TrackingData>
inline bool tnbLib::pointTopoDistanceData::updatePoint
(
	const pointTopoDistanceData& newPointInfo,
	const scalar tol,
	TrackingData& td
)
{
	if (distance_ == -1)
	{
		operator=(newPointInfo);
		return true;
	}
	else
	{
		return false;
	}
}


// Update this with information from connected point
template<class TrackingData>
inline bool tnbLib::pointTopoDistanceData::updateEdge
(
	const polyMesh& mesh,
	const label edgeI,
	const label pointi,
	const pointTopoDistanceData& pointInfo,
	const scalar tol,
	TrackingData& td
)
{
	if (distance_ == -1)
	{
		operator=(pointInfo);
		return true;
	}
	else
	{
		return false;
	}
}


template<class TrackingData>
inline bool tnbLib::pointTopoDistanceData::equal
(
	const pointTopoDistanceData& rhs,
	TrackingData& td
) const
{
	return operator==(rhs);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline bool tnbLib::pointTopoDistanceData::operator==
(
	const tnbLib::pointTopoDistanceData& rhs
	) const
{
	return data() == rhs.data() && distance() == rhs.distance();
}


inline bool tnbLib::pointTopoDistanceData::operator!=
(
	const tnbLib::pointTopoDistanceData& rhs
	) const
{
	return !(*this == rhs);
}


// ************************************************************************* //