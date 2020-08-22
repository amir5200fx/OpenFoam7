#include <sigStopAtWriteNow.hxx>

#include <error.hxx>
#include <jobInfo.hxx>
#include <IOstreams.hxx>
#include <Time.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{

	// Signal number to catch
	int sigStopAtWriteNow::signal_
	(
		debug::optimisationSwitch("stopAtWriteNowSignal", -1)
	);

	// Register re-reader
	class addstopAtWriteNowSignalToOpt
		:
		public ::tnbLib::simpleRegIOobject
	{

	public:

		addstopAtWriteNowSignalToOpt(const char* name)
			:
			::tnbLib::simpleRegIOobject(tnbLib::debug::addOptimisationObject, name)
		{}

		virtual ~addstopAtWriteNowSignalToOpt()
		{}

		virtual void readData(tnbLib::Istream& is)
		{
			sigStopAtWriteNow::signal_ = readLabel(is);
			sigStopAtWriteNow::set(true);
		}

		virtual void writeData(tnbLib::Ostream& os) const
		{
			os << sigStopAtWriteNow::signal_;
		}
	};

	addstopAtWriteNowSignalToOpt addstopAtWriteNowSignalToOpt_
	(
		"stopAtWriteNowSignal"
	);

}


tnbLib::Time const* tnbLib::sigStopAtWriteNow::runTimePtr_ = nullptr;


__p_sig_fn_t tnbLib::sigStopAtWriteNow::oldAction_ = SIG_DFL;


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::sigStopAtWriteNow::sigHandler(int)
{
	// Reset old handling
	/*if (sigaction(signal_, &oldAction_, nullptr) < 0)
	{
		FatalErrorInFunction
			<< "Cannot reset " << signal_ << " trapping"
			<< abort(FatalError);
	}*/

	const __p_sig_fn_t success = ::signal(signal_, oldAction_);

	if (SIG_ERR == success)
	{
		FatalErrorInFunction
			<< "Cannot reset " << signal_ << " trapping"
			<< abort(FatalError);
	}

	// Update jobInfo file
	jobInfo_.signalEnd();

	Info << "sigStopAtWriteNow :"
		<< " setting up write and stop at end of the next iteration"
		<< nl << endl;
	runTimePtr_->stopAt(Time::stopAtControl::writeNow);

	//// Throw signal (to old handler)
	// raise(signal_);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::sigStopAtWriteNow::sigStopAtWriteNow() {}


tnbLib::sigStopAtWriteNow::sigStopAtWriteNow
(
	const bool verbose,
	const Time& runTime
)
{
	// Store runTime
	runTimePtr_ = &runTime;

	set(verbose);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::sigStopAtWriteNow::~sigStopAtWriteNow()
{
	// Reset old handling
	if (signal_ > 0)
	{
		/*if (sigaction(signal_, &oldAction_, nullptr) < 0)
		{
			FatalErrorInFunction
				<< "Cannot reset " << signal_ << " trapping"
				<< abort(FatalError);
		}*/

		const __p_sig_fn_t success = ::signal(signal_, oldAction_);

		if (SIG_ERR == success)
		{
			FatalErrorInFunction
				<< "Cannot reset " << signal_ << " trapping"
				<< abort(FatalError);
		}
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::sigStopAtWriteNow::set(const bool verbose)
{
	if (signal_ > 0)
	{
		// Check that the signal is different from the writeNowSignal
		if (sigWriteNow::signal_ == signal_)
		{
			FatalErrorInFunction
				<< "stopAtWriteNowSignal : " << signal_
				<< " cannot be the same as the writeNowSignal."
				<< " Please change this in the etc/controlDict."
				<< exit(FatalError);
		}

		oldAction_ = ::signal(signal_, &tnbLib::sigStopAtWriteNow::sigHandler);

		if (SIG_ERR == oldAction_)
		{
			oldAction_ = SIG_DFL;

			FatalErrorInFunction
				<< "Cannot set " << signal_ << " trapping"
				<< abort(FatalError);
		}

		/*struct sigaction newAction;
		newAction.sa_handler = sigHandler;
		newAction.sa_flags = SA_NODEFER;
		sigemptyset(&newAction.sa_mask);
		if (sigaction(signal_, &newAction, &oldAction_) < 0)
		{
			FatalErrorInFunction
				<< "Cannot set " << signal_ << " trapping"
				<< abort(FatalError);
		}*/

		if (verbose)
		{
			Info << "sigStopAtWriteNow :"
				<< " Enabling writing and stopping upon signal " << signal_
				<< endl;
		}
	}
}


bool tnbLib::sigStopAtWriteNow::active() const
{
	return signal_ > 0;
}


// ************************************************************************* //