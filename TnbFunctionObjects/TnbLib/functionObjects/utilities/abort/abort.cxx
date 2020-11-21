#define FoamNamedEnum_EXPORT_DEFINE

#include <abort.hxx>

#include <dictionary.hxx>
#include <error.hxx>
#include <Time.hxx>
#include <OSspecific.hxx>
#include <PstreamReduceOps.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(abort, 0);

		addToRunTimeSelectionTable
		(
			functionObject,
			abort,
			dictionary
		);
	}
}

template<>
const char* tnbLib::NamedEnum
<
	tnbLib::functionObjects::abort::actionType,
	3
>::names[] =
{
	"noWriteNow",
	"writeNow",
	"nextWrite"
};

const tnbLib::NamedEnum
<
	tnbLib::functionObjects::abort::actionType,
	3
> tnbLib::functionObjects::abort::actionTypeNames_;


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::functionObjects::abort::removeFile() const
{
	bool hasAbort = isFile(abortFile_);
	reduce(hasAbort, orOp<bool>());

	if (hasAbort && Pstream::master())
	{
		// Cleanup ABORT file (on master only)
		rm(abortFile_);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::abort::abort
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	functionObject(name),
	time_(runTime),
	abortFile_("$FOAM_CASE/" + name),
	action_(actionType::nextWrite)
{
	abortFile_.expand();
	read(dict);

	// Remove any old files from previous runs
	removeFile();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::abort::~abort()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::abort::read(const dictionary& dict)
{
	if (dict.found("action"))
	{
		action_ = actionTypeNames_.read(dict.lookup("action"));
	}
	else
	{
		action_ = actionType::nextWrite;
	}

	if (dict.readIfPresent("file", abortFile_))
	{
		abortFile_.expand();
	}

	return true;
}


bool tnbLib::functionObjects::abort::execute()
{
	bool hasAbort = isFile(abortFile_);
	reduce(hasAbort, orOp<bool>());

	if (hasAbort)
	{
		switch (action_)
		{
		case actionType::noWriteNow:
		{
			if (time_.stopAt(Time::stopAtControl::noWriteNow))
			{
				Info << "USER REQUESTED ABORT (timeIndex="
					<< time_.timeIndex()
					<< "): stop without writing data"
					<< endl;
			}
			break;
		}

		case actionType::writeNow:
		{
			if (time_.stopAt(Time::stopAtControl::writeNow))
			{
				Info << "USER REQUESTED ABORT (timeIndex="
					<< time_.timeIndex()
					<< "): stop+write data"
					<< endl;
			}
			break;
		}

		case actionType::nextWrite:
		{
			if (time_.stopAt(Time::stopAtControl::nextWrite))
			{
				Info << "USER REQUESTED ABORT (timeIndex="
					<< time_.timeIndex()
					<< "): stop after next data write"
					<< endl;
			}
			break;
		}
		}
	}

	return true;
}


bool tnbLib::functionObjects::abort::write()
{
	return true;
}


bool tnbLib::functionObjects::abort::end()
{
	removeFile();
	return true;
}


// ************************************************************************* //