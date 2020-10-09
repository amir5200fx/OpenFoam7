#include <timeFunctionObject.hxx>

#include <Time.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(time, 0);

		addToRunTimeSelectionTable
		(
			functionObject,
			time,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::time::time
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	regionFunctionObject(name, runTime, dict),
	logFiles(obr_, name),
	perTimeStep_(false),
	cpuTime0_(time_.elapsedCpuTime()),
	clockTime0_(time_.elapsedClockTime())
{
	read(dict);
	resetName(typeName);
	write();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::time::~time()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::time::read(const dictionary& dict)
{
	functionObject::read(dict);

	dict.readIfPresent("perTimeStep", perTimeStep_);

	return true;
}


void tnbLib::functionObjects::time::writeFileHeader(const label i)
{
	if (Pstream::master())
	{
		writeHeader(file(), "time");
		writeCommented(file(), "Time");
		writeTabbed(file(), "cpu");
		writeTabbed(file(), "clock");

		if (perTimeStep_)
		{
			writeTabbed(file(), "cpu/step");
			writeTabbed(file(), "clock/step");
		}

		file() << endl;
	}
}


bool tnbLib::functionObjects::time::execute()
{
	return true;
}


bool tnbLib::functionObjects::time::write()
{
	logFiles::write();

	if (Pstream::master())
	{
		writeTime(file());

		const scalar cpuTime(time_.elapsedCpuTime());
		const scalar clockTime(time_.elapsedClockTime());

		file() << tab << time_.elapsedCpuTime();
		file() << tab << time_.elapsedClockTime();

		if (perTimeStep_)
		{
			file() << tab << time_.elapsedCpuTime() - cpuTime0_;
			file() << tab << time_.elapsedClockTime() - clockTime0_;
		}

		file() << endl;

		cpuTime0_ = cpuTime;
		clockTime0_ = clockTime;
	}

	return true;
}


// ************************************************************************* //