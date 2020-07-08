#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //


inline tnbLib::scalar tnbLib::TimeState::timeOutputValue() const
{
	return timeToUserTime(value());
}


inline tnbLib::label tnbLib::TimeState::timeIndex() const
{
	return timeIndex_;
}


inline tnbLib::scalar tnbLib::TimeState::deltaTValue() const
{
	return deltaT_;
}


inline tnbLib::scalar tnbLib::TimeState::deltaT0Value() const
{
	return deltaT0_;
}


inline tnbLib::dimensionedScalar tnbLib::TimeState::deltaT() const
{
	return dimensionedScalar("deltaT", dimTime, deltaT_);
}


inline tnbLib::dimensionedScalar tnbLib::TimeState::deltaT0() const
{
	return dimensionedScalar("deltaT0", dimTime, deltaT0_);
}


inline bool tnbLib::TimeState::writeTime() const
{
	return writeTime_;
}


inline bool tnbLib::TimeState::outputTime() const
{
	return writeTime_;
}


// ************************************************************************* //