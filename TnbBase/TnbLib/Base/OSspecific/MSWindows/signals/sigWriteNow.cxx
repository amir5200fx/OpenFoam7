#include <sigWriteNow.hxx>

#include <error.hxx>
#include <jobInfo.hxx>
#include <IOstreams.hxx>
#include <Time.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{

	// Signal number to catch
	int sigWriteNow::signal_
	(
		debug::optimisationSwitch("writeNowSignal", -1)
	);

	// Register re-reader
	class addwriteNowSignalToOpt
		:
		public ::tnbLib::simpleRegIOobject
	{

	public:

		addwriteNowSignalToOpt(const char* name)
			:
			::tnbLib::simpleRegIOobject(tnbLib::debug::addOptimisationObject, name)
		{}

		virtual ~addwriteNowSignalToOpt()
		{}

		virtual void readData(tnbLib::Istream& is)
		{
			sigWriteNow::signal_ = readLabel(is);
			sigWriteNow::set(true);
		}

		virtual void writeData(tnbLib::Ostream& os) const
		{
			os << sigWriteNow::signal_;
		}
	};

	addwriteNowSignalToOpt addwriteNowSignalToOpt_("writeNowSignal");

}


tnbLib::Time* tnbLib::sigWriteNow::runTimePtr_ = nullptr;


//struct sigaction tnbLib::sigWriteNow::oldAction_;
__p_sig_fn_t tnbLib::sigWriteNow::oldAction_ = SIG_DFL;

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::sigWriteNow::sigHandler(int)
{
	Info << "sigWriteNow :"
		<< " setting up write at end of the next iteration" << nl << endl;
	runTimePtr_->writeOnce();

	//// Throw signal (to old handler)
	// raise(signal_);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::sigWriteNow::sigWriteNow()
{}


tnbLib::sigWriteNow::sigWriteNow(const bool verbose, Time& runTime)
{
	// Store runTime
	runTimePtr_ = &runTime;

	set(verbose);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::sigWriteNow::~sigWriteNow()
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

void tnbLib::sigWriteNow::set(const bool verbose)
{
	if (signal_ >= 0)
	{
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

		oldAction_ = ::signal(signal_, &tnbLib::sigWriteNow::sigHandler);

		if (SIG_ERR == oldAction_)
		{
			oldAction_ = SIG_DFL;

			FatalErrorInFunction
				<< "Cannot set " << signal_ << " trapping"
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << "sigWriteNow :"
				<< " Enabling writing upon signal " << signal_
				<< endl;
		}
	}
}


bool tnbLib::sigWriteNow::active() const
{
	return signal_ > 0;
}


// ************************************************************************* //