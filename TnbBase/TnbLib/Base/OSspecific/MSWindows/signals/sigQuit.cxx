//#include <sigQuit.hxx>
//
//#include <JobInfo.hxx>
//#include <IOstreams.hxx>
//#include <error.hxx>
//
//// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //
//
//__p_sig_fn_t tnbLib::sigQuit::oldAction_ = SIG_DFL;
//
//// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //
//
//void tnbLib::sigQuit::sigQuitHandler(int)
//{
//	// Reset old handling
//	const __p_sig_fn_t success = ::signal(SIGBREAK, oldAction_);
//
//	if (SIG_ERR == success)
//	{
//		FatalErrorIn
//		(
//			"tnbLib::sigQuit::sigQuitHandler()"
//		) << "Cannot reset SIGQUIT trapping"
//			<< abort(FatalError);
//	}
//
//	// Update jobInfo file
//	jobInfo.signalEnd();
//
//	error::printStack(Perr);
//
//	// Throw signal (to old handler)
//	::raise(SIGBREAK);
//}
//
//
//// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //
//
//tnbLib::sigQuit::sigQuit()
//{
//	oldAction_ = SIG_DFL;
//}
//
//
//// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //
//
//tnbLib::sigQuit::~sigQuit()
//{
//	// Reset old handling
//	if (SIG_DFL != oldAction_)
//	{
//		const __p_sig_fn_t success = ::signal(SIGBREAK, oldAction_);
//		oldAction_ = SIG_DFL;
//
//		if (SIG_ERR == success)
//		{
//			FatalErrorIn("tnbLib::sigQuit::~sigQuit()")
//				<< "Cannot reset SIGBREAK trapping"
//				<< abort(FatalError);
//		}
//	}
//}
//
//
//// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //
//
//void tnbLib::sigQuit::set(const bool verbose)
//{
//	if (SIG_DFL != oldAction_)
//	{
//		FatalErrorIn
//		(
//			"tnbLib::sigQuit::set()"
//		) << "Cannot call sigQuit::set() more than once"
//			<< abort(FatalError);
//	}
//
//	oldAction_ = ::signal(SIGBREAK, &tnbLib::sigQuit::sigQuitHandler);
//
//	if (SIG_ERR == oldAction_)
//	{
//		oldAction_ = SIG_DFL;
//
//		FatalErrorIn
//		(
//			"tnbLib::sigQuit::set()"
//		) << "Cannot set SIGQUIT trapping"
//			<< abort(FatalError);
//	}
//}
//
//
//// ************************************************************************* //