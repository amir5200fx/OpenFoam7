#include <subCycleTime.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::subCycleTime::subCycleTime(Time& t, const label nSubCycles)
	:
	time_(t),
	nSubCycles_(nSubCycles),
	subCycleIndex_(0)
{
	time_.subCycle(nSubCycles_);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::subCycleTime::~subCycleTime()
{
	endSubCycle();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::subCycleTime::end() const
{
	return subCycleIndex_ > nSubCycles_;
}


void tnbLib::subCycleTime::endSubCycle()
{
	time_.endSubCycle();
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

tnbLib::subCycleTime& tnbLib::subCycleTime::operator++()
{
	time_++;
	subCycleIndex_++;
	return *this;
}


tnbLib::subCycleTime& tnbLib::subCycleTime::operator++(int)
{
	return operator++();
}


// ************************************************************************* //