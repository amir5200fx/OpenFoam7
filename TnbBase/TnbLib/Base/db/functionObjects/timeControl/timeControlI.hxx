#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const tnbLib::Time& tnbLib::timeControl::time() const
{
	return time_;
}


inline tnbLib::timeControl::timeControls tnbLib::timeControl::control() const
{
	return timeControl_;
}


inline tnbLib::scalar tnbLib::timeControl::interval() const
{
	return interval_;
}


inline tnbLib::label tnbLib::timeControl::executionIndex() const
{
	return executionIndex_;
}


// ************************************************************************* //