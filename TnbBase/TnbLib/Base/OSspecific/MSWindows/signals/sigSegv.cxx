//#include <sigSegv.hxx>
//
//#include <JobInfo.hxx>
//#include <IOstreams.hxx>
//#include <error.hxx>
//
//// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //
//
//__p_sig_fn_t tnbLib::sigSegv::oldAction_ = SIG_DFL;
//
//// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //
//
//void tnbLib::sigSegv::sigSegvHandler(int)
//{
//	// Reset old handling
//	const __p_sig_fn_t success = ::signal(SIGSEGV, oldAction_);
//
//	if (SIG_ERR == success)
//	{
//		FatalErrorIn
//		(
//			"tnbLib::sigSegv::sigSegvHandler()"
//		) << "Cannot reset SIGSEGV trapping"
//			<< abort(FatalError);
//	}
//
//	// Update jobInfo file
//	jobInfo.signalEnd();
//
//	error::printStack(Perr);
//
//	// Throw signal (to old handler)
//	::raise(SIGSEGV);
//}
//
//
//// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //
//
//tnbLib::sigSegv::sigSegv()
//{
//	oldAction_ = SIG_DFL;
//}
//
//
//// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //
//
//tnbLib::sigSegv::~sigSegv()
//{
//	// Reset old handling
//	const __p_sig_fn_t success = ::signal(SIGSEGV, oldAction_);
//	oldAction_ = SIG_DFL;
//
//	if (SIG_ERR == success)
//	{
//		FatalErrorIn
//		(
//			"tnbLib::sigSegv::~sigSegv()"
//		) << "Cannot reset SIGSEGV trapping"
//			<< abort(FatalError);
//	}
//}
//
//
//// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //
//
//void tnbLib::sigSegv::set(const bool verbose)
//{
//	if (SIG_DFL != oldAction_)
//	{
//		FatalErrorIn
//		(
//			"tnbLib::sigSegv::set()"
//		) << "Cannot call sigSegv::set() more than once"
//			<< abort(FatalError);
//	}
//
//	oldAction_ = ::signal(SIGSEGV, &tnbLib::sigSegv::sigSegvHandler);
//
//	if (SIG_ERR == oldAction_)
//	{
//		oldAction_ = SIG_DFL;
//
//		FatalErrorIn
//		(
//			"tnbLib::sigSegv::set()"
//		) << "Cannot set SIGSEGV trapping"
//			<< abort(FatalError);
//	}
//}
//
//
//// ************************************************************************* //
