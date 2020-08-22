#include <sigFpe.hxx>

#include <JobInfo.hxx>
#include <OSspecific.hxx>
#include <IOstreams.hxx>
#include <error.hxx>

#include <float.h>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

__p_sig_fn_t tnbLib::sigFpe::oldAction_ = SIG_DFL;

static unsigned int fpOld_ = 0;


static void clearFpe()
{
	//_clearfp();
	//_controlfp(fpOld_, 0xFFFFFFFF);
}


void tnbLib::sigFpe::sigFpeHandler(int)
{
	const __p_sig_fn_t success = ::signal(SIGFPE, oldAction_);

	// Reset old handling
	if (SIG_ERR == success)
	{
		FatalErrorIn
		(
			"tnbLib::sigSegv::sigFpeHandler()"
		) << "Cannot reset SIGFPE trapping"
			<< abort(FatalError);
	}

	// Update jobInfo file
	//jobInfo.signalEnd();   
	jobInfo_.signalEnd();  // Edited by amir

	error::printStack(Perr);

	clearFpe();

	// Throw signal (to old handler)
	::raise(SIGFPE);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::sigFpe::sigFpe()
{
	oldAction_ = SIG_DFL;
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::sigFpe::~sigFpe()
{
	if (env("TONB_SIGFPE"))
	{
		clearFpe();

		// Reset signal
		const __p_sig_fn_t success = ::signal(SIGFPE, oldAction_);
		oldAction_ = SIG_DFL;

		if (SIG_ERR == success)
		{
			FatalErrorIn
			(
				"tnbLib::sigFpe::~sigFpe()"
			) << "Cannot reset SIGFPE trapping"
				<< abort(FatalError);
		}
	}

	if (env("TONB_SETNAN"))
	{
		WarningIn("tnbLib::sigFpe::~sigFpe()")
			<< "TONB_SETNAN not supported under MSwindows "
			<< endl;
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::sigFpe::set(const bool verbose)
{
	if (SIG_DFL != oldAction_)
	{
		FatalErrorIn
		(
			"tnbLib::sigFpe::set()"
		) << "Cannot call sigFpe::set() more than once"
			<< abort(FatalError);
	}

	if (env("TONB_SIGFPE"))
	{
		if (verbose)
		{
			Info << "SigFpe : Enabling floating point exception trapping"
				<< " (TONB_SIGFPE)." << endl;
		}
		/*
				fpOld_ = _controlfp(0, 0);
				const unsigned int fpNew =
				  fpOld_ & ~(_EM_ZERODIVIDE | _EM_INVALID | _EM_OVERFLOW);
				_controlfp(fpNew, _MCW_EM);

				oldAction_ = ::signal(SIGFPE, &tnbLib::sigFpe::sigFpeHandler);

				if( SIG_ERR == oldAction_ )
				{
					oldAction_ = SIG_DFL;

					FatalErrorIn
					(
						"tnbLib::sigFpe::set()"
					)   << "Cannot set SIGFPE trapping"
						<< abort(FatalError);
				}
		*/
	}


	if (env("TONB_SETNAN"))
	{
		if (verbose)
		{
			WarningIn("tnbLib::sigFpe::set()")
				<< "TONB_SETNAN not supported under MSwindows "
				<< endl;
		}
	}
}

void tnbLib::sigFpe::fillNan(UList<scalar>& lst)
{
	lst = std::numeric_limits<scalar>::signaling_NaN();
}


// ************************************************************************* //
