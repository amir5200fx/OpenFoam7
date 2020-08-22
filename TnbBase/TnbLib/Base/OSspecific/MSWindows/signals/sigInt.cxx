#include <sigInt.hxx>

#include <JobInfo.hxx>
#include <error.hxx>
#include <IOstreams.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

__p_sig_fn_t tnbLib::sigInt::oldAction_ = SIG_DFL;

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::sigInt::sigIntHandler(int)
{
	// Reset old handling
	const __p_sig_fn_t success = ::signal(SIGINT, oldAction_);

	if (SIG_ERR == success)
	{
		FatalErrorIn
		(
			"tnbLib::sigInt::sigIntHandler()"
		) << "Cannot reset SIGINT trapping"
			<< abort(FatalError);
	}

	// Update jobInfo file
	//jobInfo.signalEnd();
	jobInfo_.signalEnd();  // Edited by amir

	// Throw signal (to old handler)
	raise(SIGINT);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::sigInt::sigInt()
{
	oldAction_ = SIG_DFL;
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::sigInt::~sigInt()
{
	// Reset old handling
	const __p_sig_fn_t success = ::signal(SIGINT, oldAction_);
	oldAction_ = SIG_DFL;

	if (SIG_ERR == success)
	{
		FatalErrorIn
		(
			"tnbLib::sigInt::~sigInt()"
		) << "Cannot reset SIGINT trapping"
			<< abort(FatalError);
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::sigInt::set(const bool verbose)
{
	if (SIG_DFL != oldAction_)
	{
		FatalErrorIn
		(
			"tnbLib::sigInt::set()"
		) << "Cannot call sigInt::set() more than once"
			<< abort(FatalError);
	}

	oldAction_ = ::signal(SIGINT, &tnbLib::sigInt::sigIntHandler);

	if (SIG_ERR == oldAction_)
	{
		oldAction_ = SIG_DFL;

		FatalErrorIn
		(
			"tnbLib::sigInt::set()"
		) << "Cannot set SIGINT trapping"
			<< abort(FatalError);
	}
}


// ************************************************************************* //