#include <timer.hxx>


#include <MSwindows.hxx>

#include <error.hxx>
#include <IOstreams.hxx>
#include <timer.hxx>

#define WINVER 0x0500 // To access CreateTimerQueueTimer
#undef DebugInfo
#include <windows.h>

#define SIGALRM 14

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

//defineTypeNameAndDebug(tnbLib::timer, 0);  // Edited by amir
namespace tnbLib
{
	defineTypeNameAndDebug(timer, 0);
}

jmp_buf tnbLib::timer::envAlarm;

__p_sig_fn_t tnbLib::timer::oldAction_ = SIG_DFL;

static HANDLE hTimer_ = NULL;

// * * * * * * * * * * * * * Static Member Functions * * * * * * * * * * * * //

void tnbLib::timer::signalHandler(int)
{
	if (debug)
	{
		Info << "tnbLib::timer::signalHandler(int sig) : "
			<< " timed out. Jumping."
			<< endl;
	}
	longjmp(envAlarm, 1);
}


static VOID CALLBACK timerExpired(PVOID lpParam, BOOLEAN TimerOrWaitFired)
{
	::raise(SIGALRM);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //


// Construct from components
tnbLib::timer::timer(const unsigned int newTimeOut)
	:
	newTimeOut_(newTimeOut)
{

	if (newTimeOut > 0)
	{
		// Is singleton since handler is static function
		if (NULL != hTimer_)
		{
			FatalErrorIn
			(
				"tnbLib::timer::timer(const unsigned int)"
			) << "timer already used."
				<< abort(FatalError);
		}

		// Install alarm signal handler:
		oldAction_ = ::signal(SIGALRM, &tnbLib::timer::signalHandler);

		if (SIG_ERR == oldAction_)
		{
			oldAction_ = SIG_DFL;

			FatalErrorIn
			(
				"tnbLib::timer::timer(const unsigned int)"
			) << "sigaction(SIGALRM) error"
				<< abort(FatalError);
		}

		if (debug)
		{
			Info << "tnbLib::timer::timer(const unsigned int) : "
				<< " installing timeout " << int(newTimeOut_)
				<< " seconds." << endl;
		}

		const bool success =
			::CreateTimerQueueTimer(&hTimer_,
				NULL,
				(WAITORTIMERCALLBACK)timerExpired,
				NULL,
				newTimeOut * 1000,
				0, 0);

		if (!success)
		{
			hTimer_ = NULL;
			FatalErrorIn
			(
				"tnbLib::timer::timer(const unsigned int)"
			) << "CreateTimerQueueTimer, "
				<< MSwindows::getLastError()
				<< abort(FatalError);
		}
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::timer::~timer()
{
	if (newTimeOut_ > 0)
	{
		// Reset timer
		const bool timerSuccess =
			::DeleteTimerQueueTimer(NULL, hTimer_, NULL);
		hTimer_ = NULL;

		if (!timerSuccess)
		{
			FatalErrorIn
			(
				"tnbLib::timer::~timer() "
			) << "DeleteTimerQueueTimer, "
				<< MSwindows::getLastError()
				<< abort(FatalError);
		}

		if (debug)
		{
			Info << "tnbLib::timer::~timer() timeOut="
				<< int(newTimeOut_) << endl;
		}

		const __p_sig_fn_t signalSuccess = signal(SIGALRM, oldAction_);
		oldAction_ = SIG_DFL;

		// Restore signal handler
		if (SIG_ERR == signalSuccess)
		{
			FatalErrorIn
			(
				"tnbLib::timer::~timer()"
			) << "sigaction(SIGALRM) error"
				<< abort(FatalError);
		}
	}
}

// ************************************************************************* //