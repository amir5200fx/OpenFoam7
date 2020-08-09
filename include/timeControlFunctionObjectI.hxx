#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const tnbLib::Time& tnbLib::functionObjects::timeControl::time() const
{
	return time_;
}


inline const tnbLib::dictionary& tnbLib::functionObjects::timeControl::dict() const
{
	return dict_;
}


inline const tnbLib::timeControl&
tnbLib::functionObjects::timeControl::executeControl() const
{
	return executeControl_;
}


inline const tnbLib::timeControl&
tnbLib::functionObjects::timeControl::writeControl() const
{
	return writeControl_;
}


inline const tnbLib::functionObject&
tnbLib::functionObjects::timeControl::filter() const
{
	return foPtr_();
}


// ************************************************************************* //