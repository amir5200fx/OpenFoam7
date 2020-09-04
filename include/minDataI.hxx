#pragma once
#include <polyMesh.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::minData::minData()
	:
	data_(labelMax)
{}


inline tnbLib::minData::minData(const label data)
	:
	data_(data)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class TrackingData>
inline bool tnbLib::minData::valid(TrackingData& td) const
{
	return data_ != labelMax;
}


template<class TrackingData>
inline bool tnbLib::minData::sameGeometry
(
	const polyMesh&,
	const minData&,
	const scalar,
	TrackingData&
) const
{
	return true;
}


template<class TrackingData>
inline void tnbLib::minData::leaveDomain
(
	const polyMesh&,
	const polyPatch& patch,
	const label patchFacei,
	const point& faceCentre,
	TrackingData&
)
{}


template<class TrackingData>
inline void tnbLib::minData::transform
(
	const polyMesh&,
	const tensor& rotTensor,
	TrackingData&
)
{}


template<class TrackingData>
inline void tnbLib::minData::enterDomain
(
	const polyMesh&,
	const polyPatch& patch,
	const label patchFacei,
	const point& faceCentre,
	TrackingData&
)
{}


template<class TrackingData>
inline bool tnbLib::minData::updateCell
(
	const polyMesh&,
	const label thisCelli,
	const label neighbourFacei,
	const minData& neighbourInfo,
	const scalar tol,
	TrackingData&
)
{
	if (neighbourInfo.data_ < data_)
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
inline bool tnbLib::minData::updateFace
(
	const polyMesh& mesh,
	const label thisFacei,
	const label neighbourCelli,
	const minData& neighbourInfo,
	const scalar tol,
	TrackingData&
)
{
	// From cell to its faces.

	if (neighbourInfo.data_ < data_)
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
inline bool tnbLib::minData::updateFace
(
	const polyMesh&,
	const label thisFacei,
	const minData& neighbourInfo,
	const scalar tol,
	TrackingData&
)
{
	// From face to face (e.g. coupled faces)
	if (neighbourInfo.data_ < data_)
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
inline bool tnbLib::minData::equal
(
	const minData& rhs,
	TrackingData& td
) const
{
	return operator==(rhs);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline bool tnbLib::minData::operator==
(
	const tnbLib::minData& rhs
	) const
{
	return data() == rhs.data();
}


inline bool tnbLib::minData::operator!=
(
	const tnbLib::minData& rhs
	) const
{
	return !(*this == rhs);
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<
(
	tnbLib::Ostream& os,
	const tnbLib::minData& wDist
	)
{
	return os << wDist.data_;
}


tnbLib::Istream& tnbLib::operator>>
(
	tnbLib::Istream& is,
	tnbLib::minData& wDist
	)
{
	return is >> wDist.data_;
}


// ************************************************************************* //