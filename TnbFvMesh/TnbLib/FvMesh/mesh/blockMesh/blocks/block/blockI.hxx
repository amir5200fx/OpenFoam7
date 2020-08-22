#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const tnbLib::pointField& tnbLib::block::points() const
{
	return points_;
}


inline const tnbLib::FixedList<tnbLib::List<tnbLib::FixedList<tnbLib::label, 4>>, 6>&
tnbLib::block::boundaryPatches() const
{
	return boundaryPatches_;
}


// ************************************************************************* //