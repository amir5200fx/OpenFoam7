#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::scalar tnbLib::fv::cellSetOption::timeStart() const
{
	return timeStart_;
}


inline tnbLib::scalar tnbLib::fv::cellSetOption::duration() const
{
	return duration_;
}


inline bool tnbLib::fv::cellSetOption::inTimeLimits(const scalar time) const
{
	return
		(
		(timeStart_ < 0)
			||
			(
			(mesh_.time().value() >= timeStart_)
				&& (mesh_.time().value() <= (timeStart_ + duration_))
				)
			);
}


inline const tnbLib::fv::cellSetOption::selectionModeType&
tnbLib::fv::cellSetOption::selectionMode() const
{
	return selectionMode_;
}


inline const tnbLib::word& tnbLib::fv::cellSetOption::cellSetName() const
{
	return cellSetName_;
}


inline tnbLib::scalar tnbLib::fv::cellSetOption::V() const
{
	return V_;
}


inline const tnbLib::labelList& tnbLib::fv::cellSetOption::cells() const
{
	return cells_;
}


inline tnbLib::scalar& tnbLib::fv::cellSetOption::timeStart()
{
	return timeStart_;
}


inline tnbLib::scalar& tnbLib::fv::cellSetOption::duration()
{
	return duration_;
}


// ************************************************************************* //