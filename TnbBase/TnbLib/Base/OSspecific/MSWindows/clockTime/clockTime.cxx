#include <clockTime.hxx>

#include <scalar.hxx>

#include <time.h>
#include <windows.h> 

#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
#define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
#define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::clockTime::getTime(timeType& t)
{
	//gettimeofday(&t, 0);
	//http://stackoverflow.com/questions/2494356/how-to-use-gettimeofday-or-something-equivalent-with-visual-studio-c-2008
	FILETIME ft;
	unsigned __int64 tmpres = 0;
	if (NULL != &t)
	{
		GetSystemTimeAsFileTime(&ft);

		tmpres |= ft.dwHighDateTime;
		tmpres <<= 32;
		tmpres |= ft.dwLowDateTime;

		/*converting file time to unix epoch*/
		tmpres -= DELTA_EPOCH_IN_MICROSECS;
		tmpres /= 10;  /*convert into microseconds*/
		t.tv_sec = (long)(tmpres / 1000000UL);
		t.tv_usec = (long)(tmpres % 1000000UL);
	}
}


double tnbLib::clockTime::timeDifference(const timeType& beg, const timeType& end)
{
	return end.tv_sec - beg.tv_sec + 1e-6*(end.tv_usec - beg.tv_usec);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::clockTime::clockTime()
{
	getTime(startTime_);
	lastTime_ = startTime_;
	newTime_ = startTime_;
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

double tnbLib::clockTime::elapsedTime() const
{
	getTime(newTime_);
	return timeDifference(startTime_, newTime_);
}


double tnbLib::clockTime::timeIncrement() const
{
	lastTime_ = newTime_;
	getTime(newTime_);
	return timeDifference(lastTime_, newTime_);
}


// ************************************************************************* //