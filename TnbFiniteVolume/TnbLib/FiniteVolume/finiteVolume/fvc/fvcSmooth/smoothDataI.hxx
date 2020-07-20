#pragma once
// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class TrackingData>
inline bool tnbLib::smoothData::update
(
	const smoothData& svf,
	const scalar scale,
	const scalar tol,
	TrackingData& td
)
{
	if (!valid(td) || (value_ < vSmall))
	{
		// My value not set - take over neighbour
		value_ = svf.value() / scale;

		// Something changed - let caller know
		return true;
	}
	else if (svf.value() > (1 + tol)*scale*value_)
	{
		// Neighbour is too big for me - Up my value
		value_ = svf.value() / scale;

		// Something changed - let caller know
		return true;
	}
	else
	{
		// Neighbour is not too big for me or change is too small
		// Nothing changed
		return false;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::smoothData::smoothData()
	:
	value_(-great)
{}


inline tnbLib::smoothData::smoothData(const scalar value)
	:
	value_(value)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class TrackingData>
inline bool tnbLib::smoothData::valid(TrackingData& td) const
{
	return value_ > -small;
}


template<class TrackingData>
inline bool tnbLib::smoothData::sameGeometry
(
	const polyMesh&,
	const smoothData&,
	const scalar,
	TrackingData& td
) const
{
	return true;
}


template<class TrackingData>
inline void tnbLib::smoothData::leaveDomain
(
	const polyMesh&,
	const polyPatch&,
	const label,
	const point&,
	TrackingData& td
)
{}


template<class TrackingData>
inline void tnbLib::smoothData::transform
(
	const polyMesh&,
	const tensor&,
	TrackingData& td
)
{}


template<class TrackingData>
inline void tnbLib::smoothData::enterDomain
(
	const polyMesh&,
	const polyPatch&,
	const label,
	const point&,
	TrackingData& td
)
{}


template<class TrackingData>
inline bool tnbLib::smoothData::updateCell
(
	const polyMesh&,
	const label,
	const label,
	const smoothData& svf,
	const scalar tol,
	TrackingData& td
)
{
	// Take over info from face if more than deltaRatio larger
	return update(svf, td.maxRatio, tol, td);
}


template<class TrackingData>
inline bool tnbLib::smoothData::updateFace
(
	const polyMesh&,
	const label,
	const label,
	const smoothData& svf,
	const scalar tol,
	TrackingData& td
)
{
	// Take over information from cell without any scaling (scale = 1.0)
	return update(svf, 1.0, tol, td);
}


// Update this (face) with coupled face information.
template<class TrackingData>
inline bool tnbLib::smoothData::updateFace
(
	const polyMesh&,
	const label,
	const smoothData& svf,
	const scalar tol,
	TrackingData& td
)
{
	// Take over information from coupled face without any scaling (scale = 1.0)
	return update(svf, 1.0, tol, td);
}


template<class TrackingData>
inline bool tnbLib::smoothData::equal
(
	const smoothData& rhs,
	TrackingData& td
) const
{
	return operator==(rhs);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline void tnbLib::smoothData::operator=
(
	const scalar value
	)
{
	value_ = value;
}


inline bool tnbLib::smoothData::operator==
(
	const smoothData& rhs
	) const
{
	return value_ == rhs.value();
}


inline bool tnbLib::smoothData::operator!=
(
	const smoothData& rhs
	) const
{
	return !(*this == rhs);
}


// ************************************************************************* //