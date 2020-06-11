#include <clock.hxx>

#include <tnbString.hxx>

#include <sstream>
#include <iomanip>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const char *tnbLib::clock::monthNames[] =
{
	"Jan", "Feb", "Mar", "Apr", "May", "Jun",
	"Jul", "Aug", "Sep", "Oct", "Nov", "Dec",
};


// * * * * * * * * * * * * * Static Member Functions * * * * * * * * * * * * //

time_t tnbLib::clock::getTime()
{
	return ::time(reinterpret_cast<time_t*>(0));
}


const struct tm tnbLib::clock::rawDate()
{
	time_t t = getTime();
	struct tm *timeStruct = localtime(&t);
	return *timeStruct;
}


tnbLib::string tnbLib::clock::dateTime()
{
	std::ostringstream osBuffer;

	time_t t = getTime();
	struct tm *timeStruct = localtime(&t);

	osBuffer
		<< std::setfill('0')
		<< std::setw(4) << timeStruct->tm_year + 1900
		<< '-' << std::setw(2) << timeStruct->tm_mon + 1
		<< '-' << std::setw(2) << timeStruct->tm_mday
		<< 'T'
		<< std::setw(2) << timeStruct->tm_hour
		<< ':' << std::setw(2) << timeStruct->tm_min
		<< ':' << std::setw(2) << timeStruct->tm_sec;

	return osBuffer.str();
}

tnbLib::string tnbLib::clock::date()
{
	std::ostringstream osBuffer;

	time_t t = getTime();
	struct tm *timeStruct = localtime(&t);

	osBuffer
		<< monthNames[timeStruct->tm_mon]
		<< ' ' << std::setw(2) << std::setfill('0') << timeStruct->tm_mday
		<< ' ' << std::setw(4) << timeStruct->tm_year + 1900;

	return osBuffer.str();
}


tnbLib::string tnbLib::clock::clockTime()
{
	std::ostringstream osBuffer;

	time_t t = getTime();
	struct tm *timeStruct = localtime(&t);

	osBuffer
		<< std::setfill('0')
		<< std::setw(2) << timeStruct->tm_hour
		<< ':' << std::setw(2) << timeStruct->tm_min
		<< ':' << std::setw(2) << timeStruct->tm_sec;

	return osBuffer.str();
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::clock::clock()
	:
	startTime_(getTime()),
	lastTime_(startTime_),
	newTime_(startTime_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

time_t tnbLib::clock::elapsedClockTime() const
{
	newTime_ = getTime();
	return newTime_ - startTime_;
}


time_t tnbLib::clock::clockTimeIncrement() const
{
	lastTime_ = newTime_;
	newTime_ = getTime();
	return newTime_ - lastTime_;
}


// ************************************************************************* //