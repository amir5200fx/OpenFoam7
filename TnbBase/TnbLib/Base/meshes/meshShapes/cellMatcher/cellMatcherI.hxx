#pragma once
#include <primitiveMesh.hxx>
#include <cellModeller.hxx>
#include <cellModel.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const tnbLib::Map<tnbLib::label>& tnbLib::cellMatcher::localPoint() const
{
	return localPoint_;
}


inline const tnbLib::faceList& tnbLib::cellMatcher::localFaces() const
{
	return localFaces_;
}


inline const tnbLib::labelList& tnbLib::cellMatcher::faceSize() const
{
	return faceSize_;
}


inline const tnbLib::labelList& tnbLib::cellMatcher::pointMap() const
{
	return pointMap_;
}


inline const tnbLib::labelList& tnbLib::cellMatcher::faceMap() const
{
	return faceMap_;
}


inline const tnbLib::labelList& tnbLib::cellMatcher::edgeFaces() const
{
	return edgeFaces_;
}


inline const tnbLib::labelListList& tnbLib::cellMatcher::pointFaceIndex() const
{
	return pointFaceIndex_;
}


inline const tnbLib::labelList& tnbLib::cellMatcher::vertLabels() const
{
	return vertLabels_;
}


inline const tnbLib::labelList& tnbLib::cellMatcher::faceLabels() const
{
	return faceLabels_;
}


inline const tnbLib::cellModel& tnbLib::cellMatcher::model() const
{
	if (cellModelPtr_ == nullptr)
	{
		cellModelPtr_ = cellModeller::lookup(cellModelName_);
	}
	return *cellModelPtr_;
}



// Key into edgeFaces_. key and key+1 are the entries for edge going from
// v0 to v1
inline tnbLib::label tnbLib::cellMatcher::edgeKey
(
	const label numVert,
	const label v0,
	const label v1
)
{
	return 2 * (v0*numVert + v1);
}


// Walk along face consistent with face orientation
inline tnbLib::label tnbLib::cellMatcher::nextVert
(
	const label localVertI,
	const label size,
	const bool rightHand
)
{
	if (rightHand)
	{
		// face oriented acc. to righthand rule
		return (localVertI + 1) % size;
	}
	else
	{
		// face oriented acc. to lefthand rule
		return (size + localVertI - 1) % size;
	}
}


// ************************************************************************* //