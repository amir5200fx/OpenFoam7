#pragma once
#include <cellClassification.hxx>
#include <polyMesh.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

// Update this with w2 information
template<class TrackingData>
inline bool tnbLib::cellInfo::update
(
	const cellInfo& w2,
	const label thisFacei,
	const label thisCelli,
	const label neighbourFacei,
	const label neighbourCelli,
	TrackingData& td
)
{
	if
		(
		(w2.type() == cellClassification::NOTSET)
			|| (w2.type() == cellClassification::CUT)
			)
	{
		FatalErrorInFunction
			<< "Problem: trying to propagate NOTSET or CUT type:" << w2.type()
			<< " into cell/face with type:" << type() << endl
			<< "thisFacei:" << thisFacei
			<< "  thisCelli:" << thisCelli
			<< "  neighbourFacei:" << neighbourFacei
			<< "  neighbourCelli:" << neighbourCelli
			<< abort(FatalError);
		return false;
	}

	if (type() == cellClassification::NOTSET)
	{
		type_ = w2.type();

		return true;
	}

	if (type() == cellClassification::CUT)
	{
		// Reached boundary. Stop.
		return false;
	}

	if (type() == w2.type())
	{
		// Should never happen; already checked in meshWave
		return false;
	}

	// Two conflicting types
	FatalErrorInFunction
		<< "Problem: trying to propagate conflicting types:" << w2.type()
		<< " into cell/face with type:" << type() << endl
		<< "thisFacei:" << thisFacei
		<< "  thisCelli:" << thisCelli
		<< "  neighbourFacei:" << neighbourFacei
		<< "  neighbourCelli:" << neighbourCelli
		<< abort(FatalError);

	return false;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::cellInfo::cellInfo()
	:
	type_(cellClassification::NOTSET)
{}


inline tnbLib::cellInfo::cellInfo(const label type)
	:
	type_(type)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class TrackingData>
inline bool tnbLib::cellInfo::valid(TrackingData& td) const
{
	return type_ != cellClassification::NOTSET;
}


template<class TrackingData>
inline bool tnbLib::cellInfo::sameGeometry
(
	const polyMesh&,
	const cellInfo& w2,
	const scalar tol,
	TrackingData& td
)
const
{
	return true;
}


template<class TrackingData>
inline void tnbLib::cellInfo::leaveDomain
(
	const polyMesh&,
	const polyPatch& patch,
	const label patchFacei,
	const point& faceCentre,
	TrackingData& td
)
{}


template<class TrackingData>
inline void tnbLib::cellInfo::transform
(
	const polyMesh&,
	const tensor& rotTensor,
	TrackingData& td
)
{}


template<class TrackingData>
inline void tnbLib::cellInfo::enterDomain
(
	const polyMesh&,
	const polyPatch& patch,
	const label patchFacei,
	const point& faceCentre,
	TrackingData& td
)
{}


template<class TrackingData>
inline bool tnbLib::cellInfo::updateCell
(
	const polyMesh&,
	const label thisCelli,
	const label neighbourFacei,
	const cellInfo& neighbourInfo,
	const scalar tol,
	TrackingData& td
)
{
	return update
	(
		neighbourInfo,
		-1,
		thisCelli,
		neighbourFacei,
		-1,
		td
	);
}


template<class TrackingData>
inline bool tnbLib::cellInfo::updateFace
(
	const polyMesh&,
	const label thisFacei,
	const label neighbourCelli,
	const cellInfo& neighbourInfo,
	const scalar tol,
	TrackingData& td
)
{
	return update
	(
		neighbourInfo,
		thisFacei,
		-1,
		-1,
		neighbourCelli,
		td
	);
}


template<class TrackingData>
inline bool tnbLib::cellInfo::updateFace
(
	const polyMesh&,
	const label thisFacei,
	const cellInfo& neighbourInfo,
	const scalar tol,
	TrackingData& td
)
{
	return update
	(
		neighbourInfo,
		thisFacei,
		-1,
		-1,
		-1,
		td
	);
}


template<class TrackingData>
inline bool tnbLib::cellInfo::equal
(
	const cellInfo& rhs,
	TrackingData& td
) const
{
	return operator==(rhs);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline bool tnbLib::cellInfo::operator==(const tnbLib::cellInfo& rhs) const
{
	return type() == rhs.type();
}


inline bool tnbLib::cellInfo::operator!=(const tnbLib::cellInfo& rhs) const
{
	return !(*this == rhs);
}


// ************************************************************************* //