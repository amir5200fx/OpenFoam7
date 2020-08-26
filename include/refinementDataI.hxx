#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Null constructor
inline tnbLib::refinementData::refinementData()
	:
	refinementCount_(-1),
	count_(-1)
{}


// Construct from components
inline tnbLib::refinementData::refinementData
(
	const label refinementCount,
	const label count
)
	:
	refinementCount_(refinementCount),
	count_(count)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class TrackingData>
inline bool tnbLib::refinementData::valid(TrackingData& td) const
{
	return count_ != -1;
}


// No geometric data so never any problem on cyclics
template<class TrackingData>
inline bool tnbLib::refinementData::sameGeometry
(
	const polyMesh&,
	const refinementData&,
	const scalar,
	TrackingData& td
) const
{
	return true;
}


// No geometric data.
template<class TrackingData>
inline void tnbLib::refinementData::leaveDomain
(
	const polyMesh&,
	const polyPatch& patch,
	const label patchFacei,
	const point& faceCentre,
	TrackingData& td
)
{}


// No geometric data.
template<class TrackingData>
inline void tnbLib::refinementData::transform
(
	const polyMesh&,
	const tensor& rotTensor,
	TrackingData& td
)
{}


// No geometric data.
template<class TrackingData>
inline void tnbLib::refinementData::enterDomain
(
	const polyMesh&,
	const polyPatch& patch,
	const label patchFacei,
	const point& faceCentre,
	TrackingData& td
)
{}


// Update cell with neighbouring face information
template<class TrackingData>
inline bool tnbLib::refinementData::updateCell
(
	const polyMesh&,
	const label thisCelli,
	const label neighbourFacei,
	const refinementData& neighbourInfo,
	const scalar tol,
	TrackingData& td
)
{
	if (!valid(td))
	{
		FatalErrorInFunction
			<< abort(FatalError);
		return false;
	}


	// Check if more than 2:1 ratio. This is when I am not refined but neighbour
	// is and neighbour already had higher cell level.
	if
		(
			neighbourInfo.isRefined()
			&& !isRefined()
			&& neighbourInfo.refinementCount() > refinementCount()
			)
	{
		count_ = refinementCount();
		return true;
	}



	// Count from neighbour face by the time it reaches the current cell.
	label transportedFaceCount;

	if (neighbourInfo.isRefined())
	{
		// refined so passes through two cells.
		transportedFaceCount = max(0, neighbourInfo.count() - 2);
	}
	else
	{
		// unrefined.
		transportedFaceCount = max(0, neighbourInfo.count() - 1);
	}

	if (count_ >= transportedFaceCount)
	{
		return false;
	}
	else
	{
		count_ = transportedFaceCount;

		return true;
	}
}


// Update face with neighbouring cell information
template<class TrackingData>
inline bool tnbLib::refinementData::updateFace
(
	const polyMesh&,
	const label thisFacei,
	const label neighbourCelli,
	const refinementData& neighbourInfo,
	const scalar tol,
	TrackingData& td
)
{
	// From cell to its faces.
	if (!valid(td))
	{
		refinementCount_ = neighbourInfo.refinementCount();
		count_ = neighbourInfo.count();

		return true;
	}

	if (count_ >= neighbourInfo.count())
	{
		return false;
	}
	else
	{
		refinementCount_ = neighbourInfo.refinementCount();
		count_ = neighbourInfo.count();

		return true;
	}
}


// Update face with coupled face information
template<class TrackingData>
inline bool tnbLib::refinementData::updateFace
(
	const polyMesh&,
	const label thisFacei,
	const refinementData& neighbourInfo,
	const scalar tol,
	TrackingData& td
)
{
	// From face to face (e.g. coupled faces)
	if (!valid(td))
	{
		refinementCount_ = neighbourInfo.refinementCount();
		count_ = neighbourInfo.count();

		return true;
	}

	if (count_ >= neighbourInfo.count())
	{
		return false;
	}
	else
	{
		refinementCount_ = neighbourInfo.refinementCount();
		count_ = neighbourInfo.count();

		return true;
	}
}


template<class TrackingData>
inline bool tnbLib::refinementData::equal
(
	const refinementData& rhs,
	TrackingData& td
) const
{
	return operator==(rhs);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline bool tnbLib::refinementData::operator==(const tnbLib::refinementData& rhs)
const
{
	return count() == rhs.count() && refinementCount() == rhs.refinementCount();
}


inline bool tnbLib::refinementData::operator!=(const tnbLib::refinementData& rhs)
const
{
	return !(*this == rhs);
}


// ************************************************************************* //