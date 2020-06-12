#include <TimeState.hxx>

#include <Time.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::TimeState::TimeState()
	:
	dimensionedScalar(Time::timeName(0), dimTime, 0),
	timeIndex_(0),
	deltaT_(0),
	deltaTSave_(0),
	deltaT0_(0),
	deltaTchanged_(false),
	writeTimeIndex_(0),
	writeTime_(false)
{}


// * * * * * * * * * * * * * * * * Destructor * * * * * * * * * * * * * * * * //

tnbLib::TimeState::~TimeState()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::scalar tnbLib::TimeState::userTimeToTime(const scalar theta) const
{
	return theta;
}


tnbLib::scalar tnbLib::TimeState::timeToUserTime(const scalar t) const
{
	return t;
}


// ************************************************************************* //