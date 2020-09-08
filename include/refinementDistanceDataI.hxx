#pragma once
#include <transform.hxx>
#include <polyMesh.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

// Returns the wanted level
inline tnbLib::label tnbLib::refinementDistanceData::wantedLevel(const point& pt)
const
{
	const scalar distSqr = magSqr(pt - origin_);

	// Get the size at the origin level
	scalar levelSize = level0Size_ / (1 << originLevel_);

	scalar r = 0;

	for (label level = originLevel_; level >= 0; --level)
	{
		// Current range
		r += levelSize;

		// Check if our distance is within influence sphere
		if (sqr(r) > distSqr)
		{
			return level;
		}

		// Lower level will have double the size
		levelSize *= 2;
	}
	return 0;
}


template<class TrackingData>
inline bool tnbLib::refinementDistanceData::update
(
	const point& pos,
	const refinementDistanceData& neighbourInfo,
	const scalar tol,
	TrackingData& td
)
{
	if (!valid(td))
	{
		if (!neighbourInfo.valid(td))
		{
			FatalErrorInFunction
				<< "problem" << abort(FatalError);
		}
		operator=(neighbourInfo);
		return true;
	}

	// Determine wanted level at current position.
	label cellLevel = wantedLevel(pos);

	// Determine wanted level coming through the neighbour
	label nbrLevel = neighbourInfo.wantedLevel(pos);

	if (nbrLevel > cellLevel)
	{
		operator=(neighbourInfo);
		return true;
	}
	else if (nbrLevel == cellLevel)
	{
		scalar myDistSqr = magSqr(pos - origin_);
		scalar nbrDistSqr = magSqr(pos - neighbourInfo.origin());
		scalar diff = myDistSqr - nbrDistSqr;

		if (diff < 0)
		{
			// already nearest
			return false;
		}

		if ((diff < small) || ((myDistSqr > small) && (diff / myDistSqr < tol)))
		{
			// don't propagate small changes
			return false;
		}
		else
		{
			// update with new values
			operator=(neighbourInfo);
			return true;
		}
	}
	else
	{
		return false;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Null constructor
inline tnbLib::refinementDistanceData::refinementDistanceData()
	:
	level0Size_(-1)
{}


// Construct from components
inline tnbLib::refinementDistanceData::refinementDistanceData
(
	const scalar level0Size,
	const point& origin,
	const label originLevel
)
	:
	level0Size_(level0Size),
	origin_(origin),
	originLevel_(originLevel)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class TrackingData>
inline bool tnbLib::refinementDistanceData::valid(TrackingData& td) const
{
	return level0Size_ != -1;
}


// No geometric data so never any problem on cyclics
template<class TrackingData>
inline bool tnbLib::refinementDistanceData::sameGeometry
(
	const polyMesh&,
	const refinementDistanceData&,
	const scalar,
	TrackingData& td
) const
{
	return true;
}


template<class TrackingData>
inline void tnbLib::refinementDistanceData::leaveDomain
(
	const polyMesh&,
	const polyPatch& patch,
	const label patchFacei,
	const point& faceCentre,
	TrackingData& td
)
{
	origin_ -= faceCentre;
}


template<class TrackingData>
inline void tnbLib::refinementDistanceData::transform
(
	const polyMesh&,
	const tensor& rotTensor,
	TrackingData& td
)
{
	origin_ = tnbLib::transform(rotTensor, origin_);
}


// Update absolute geometric quantities.
template<class TrackingData>
inline void tnbLib::refinementDistanceData::enterDomain
(
	const polyMesh&,
	const polyPatch& patch,
	const label patchFacei,
	const point& faceCentre,
	TrackingData& td
)
{
	// back to absolute form
	origin_ += faceCentre;
}


// Update cell with neighbouring face information
template<class TrackingData>
inline bool tnbLib::refinementDistanceData::updateCell
(
	const polyMesh& mesh,
	const label thisCelli,
	const label neighbourFacei,
	const refinementDistanceData& neighbourInfo,
	const scalar tol,
	TrackingData& td
)
{
	const point& pos = mesh.cellCentres()[thisCelli];

	return update(pos, neighbourInfo, tol, td);
}


// Update face with neighbouring cell information
template<class TrackingData>
inline bool tnbLib::refinementDistanceData::updateFace
(
	const polyMesh& mesh,
	const label thisFacei,
	const label neighbourCelli,
	const refinementDistanceData& neighbourInfo,
	const scalar tol,
	TrackingData& td
)
{
	const point& pos = mesh.faceCentres()[thisFacei];

	return update(pos, neighbourInfo, tol, td);
}


// Update face with coupled face information
template<class TrackingData>
inline bool tnbLib::refinementDistanceData::updateFace
(
	const polyMesh& mesh,
	const label thisFacei,
	const refinementDistanceData& neighbourInfo,
	const scalar tol,
	TrackingData& td
)
{
	const point& pos = mesh.faceCentres()[thisFacei];

	return update(pos, neighbourInfo, tol, td);
}


template<class TrackingData>
inline bool tnbLib::refinementDistanceData::equal
(
	const refinementDistanceData& rhs,
	TrackingData& td
) const
{
	if (!valid(td))
	{
		if (!rhs.valid(td))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return operator==(rhs);
	}
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline bool tnbLib::refinementDistanceData::operator==
(
	const tnbLib::refinementDistanceData& rhs
	)
	const
{
	return
		level0Size_ == rhs.level0Size_
		&& origin_ == rhs.origin_
		&& originLevel_ == rhs.originLevel_;
}


inline bool tnbLib::refinementDistanceData::operator!=
(
	const tnbLib::refinementDistanceData& rhs
	)
	const
{
	return !(*this == rhs);
}


// ************************************************************************* //