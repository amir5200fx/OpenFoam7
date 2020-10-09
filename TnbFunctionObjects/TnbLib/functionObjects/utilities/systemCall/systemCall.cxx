#include <systemCall.hxx>

#include <Time.hxx>
#include <dynamicCode.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(systemCall, 0);

		addToRunTimeSelectionTable
		(
			functionObject,
			systemCall,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::systemCall::systemCall
(
	const word& name,
	const Time&,
	const dictionary& dict
)
	:
	functionObject(name),
	executeCalls_(),
	endCalls_(),
	writeCalls_()
{
	read(dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::systemCall::~systemCall()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::systemCall::read(const dictionary& dict)
{
	dict.readIfPresent("executeCalls", executeCalls_);
	dict.readIfPresent("endCalls", endCalls_);
	dict.readIfPresent("writeCalls", writeCalls_);

	if (executeCalls_.empty() && endCalls_.empty() && writeCalls_.empty())
	{
		WarningInFunction
			<< "no executeCalls, endCalls or writeCalls defined."
			<< endl;
	}
	else if (!dynamicCode::allowSystemOperations)
	{
		FatalErrorInFunction
			<< "Executing user-supplied system calls is not enabled by "
			<< "default because of " << nl
			<< "security issues.  If you trust the case you can enable this "
			<< "facility by " << nl
			<< "adding to the InfoSwitches setting in the system controlDict:"
			<< nl << nl
			<< "    allowSystemOperations 1" << nl << nl
			<< "The system controlDict is either" << nl << nl
			<< "    ~/.OpenFOAM/$WM_PROJECT_VERSION/controlDict" << nl << nl
			<< "or" << nl << nl
			<< "    $WM_PROJECT_DIR/etc/controlDict" << nl << nl
			<< exit(FatalError);
	}

	return true;
}


bool tnbLib::functionObjects::systemCall::execute()
{
	forAll(executeCalls_, callI)
	{
		tnbLib::system(executeCalls_[callI]);
	}

	return true;
}


bool tnbLib::functionObjects::systemCall::end()
{
	forAll(endCalls_, callI)
	{
		tnbLib::system(endCalls_[callI]);
	}

	return true;
}


bool tnbLib::functionObjects::systemCall::write()
{
	forAll(writeCalls_, callI)
	{
		tnbLib::system(writeCalls_[callI]);
	}

	return true;
}


// ************************************************************************* //