#pragma once
#include <transform.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class TrackingData>
inline bool tnbLib::sweepData::update
(
	const sweepData& svf,
	const point& position,
	const scalar tol,
	TrackingData& td
)
{
	if (!valid(td))
	{
		operator=(svf);
		return true;
	}

	scalar myDist2 = magSqr(position - origin());

	if (myDist2 < small)
	{
		if (svf.value() > value())
		{
			operator=(svf);
			return true;
		}
		else
		{
			return false;
		}
	}

	scalar dist2 = magSqr(position - svf.origin());

	if (dist2 < myDist2)
	{
		operator=(svf);
		return true;
	}

	return false;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::sweepData::sweepData()
	:
	value_(-great),
	origin_(vector::max)
{}


inline tnbLib::sweepData::sweepData(const scalar value, const point& origin)
	:
	value_(value),
	origin_(origin)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class TrackingData>
inline bool tnbLib::sweepData::valid(TrackingData& td) const
{
	return value_ > -small;
}


template<class TrackingData>
inline bool tnbLib::sweepData::sameGeometry
(
	const polyMesh&,
	const sweepData&,
	const scalar,
	TrackingData& td
) const
{
	return true;
}


template<class TrackingData>
inline void tnbLib::sweepData::leaveDomain
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
inline void tnbLib::sweepData::transform
(
	const polyMesh&,
	const tensor& rotTensor,
	TrackingData& td
)
{
	origin_ = tnbLib::transform(rotTensor, origin_);
}


template<class TrackingData>
inline void tnbLib::sweepData::enterDomain
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


template<class TrackingData>
inline bool tnbLib::sweepData::updateCell
(
	const polyMesh& mesh,
	const label thisCelli,
	const label,
	const sweepData& svf,
	const scalar tol,
	TrackingData& td
)
{
	return update(svf, mesh.cellCentres()[thisCelli], tol, td);
}


template<class TrackingData>
inline bool tnbLib::sweepData::updateFace
(
	const polyMesh& mesh,
	const label thisFacei,
	const label,
	const sweepData& svf,
	const scalar tol,
	TrackingData& td
)
{
	return update(svf, mesh.faceCentres()[thisFacei], tol, td);
}


// Update this (face) with coupled face information.
template<class TrackingData>
inline bool tnbLib::sweepData::updateFace
(
	const polyMesh& mesh,
	const label thisFacei,
	const sweepData& svf,
	const scalar tol,
	TrackingData& td
)
{
	return update(svf, mesh.faceCentres()[thisFacei], tol, td);
}


template<class TrackingData>
inline bool tnbLib::sweepData::equal
(
	const sweepData& rhs,
	TrackingData& td
) const
{
	return operator==(rhs);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline void tnbLib::sweepData::operator=
(
	const scalar value
	)
{
	value_ = value;
}


inline bool tnbLib::sweepData::operator==
(
	const sweepData& rhs
	) const
{
	return origin() == rhs.origin();
}


inline bool tnbLib::sweepData::operator!=
(
	const sweepData& rhs
	) const
{
	return !(*this == rhs);
}


// ************************************************************************* //