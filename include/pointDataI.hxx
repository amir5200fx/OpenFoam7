#pragma once
#include <polyMesh.hxx>
#include <transform.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::pointData::pointData()
	:
	pointEdgePoint(),
	s_(great),
	v_(point::max)
{}


inline tnbLib::pointData::pointData
(
	const point& origin,
	const scalar distSqr,
	const scalar s,
	const vector& v
)
	:
	pointEdgePoint(origin, distSqr),
	s_(s),
	v_(v)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::scalar tnbLib::pointData::s() const
{
	return s_;
}


inline const tnbLib::vector& tnbLib::pointData::v() const
{
	return v_;
}


template<class TrackingData>
inline void tnbLib::pointData::transform
(
	const tensor& rotTensor,
	TrackingData& td
)
{
	pointEdgePoint::transform(rotTensor, td);
	v_ = tnbLib::transform(rotTensor, v_);
}


// Update this with information from connected edge
template<class TrackingData>
inline bool tnbLib::pointData::updatePoint
(
	const polyMesh& mesh,
	const label pointi,
	const label edgeI,
	const pointData& edgeInfo,
	const scalar tol,
	TrackingData& td
)
{
	if
		(
			pointEdgePoint::updatePoint
			(
				mesh,
				pointi,
				edgeI,
				edgeInfo,
				tol,
				td
			)
			)
	{
		s_ = edgeInfo.s_;
		v_ = edgeInfo.v_;
		return true;
	}
	else
	{
		return false;
	}
}

// Update this with new information on same point
template<class TrackingData>
inline bool tnbLib::pointData::updatePoint
(
	const polyMesh& mesh,
	const label pointi,
	const pointData& newPointInfo,
	const scalar tol,
	TrackingData& td
)
{
	if
		(
			pointEdgePoint::updatePoint
			(
				mesh,
				pointi,
				newPointInfo,
				tol,
				td
			)
			)
	{
		s_ = newPointInfo.s_;
		v_ = newPointInfo.v_;
		return true;
	}
	else
	{
		return false;
	}
}


// Update this with new information on same point. No extra information.
template<class TrackingData>
inline bool tnbLib::pointData::updatePoint
(
	const pointData& newPointInfo,
	const scalar tol,
	TrackingData& td
)
{
	if (pointEdgePoint::updatePoint(newPointInfo, tol, td))
	{
		s_ = newPointInfo.s_;
		v_ = newPointInfo.v_;
		return true;
	}
	else
	{
		return false;
	}
}


// Update this with information from connected point
template<class TrackingData>
inline bool tnbLib::pointData::updateEdge
(
	const polyMesh& mesh,
	const label edgeI,
	const label pointi,
	const pointData& pointInfo,
	const scalar tol,
	TrackingData& td

)
{
	if
		(
			pointEdgePoint::updateEdge
			(
				mesh,
				edgeI,
				pointi,
				pointInfo,
				tol,
				td
			)
			)
	{
		s_ = pointInfo.s_;
		v_ = pointInfo.v_;
		return true;
	}
	else
	{
		return false;
	}
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline bool tnbLib::pointData::operator==(const tnbLib::pointData& rhs)
const
{
	return
		pointEdgePoint::operator==(rhs)
		&& (s() == rhs.s())
		&& (v() == rhs.v());
}


inline bool tnbLib::pointData::operator!=(const tnbLib::pointData& rhs)
const
{
	return !(*this == rhs);
}


// ************************************************************************* //