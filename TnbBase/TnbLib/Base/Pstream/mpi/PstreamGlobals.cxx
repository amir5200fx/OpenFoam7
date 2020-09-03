#include <PstreamGlobals.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	MPI_Comm PstreamGlobals::MPI_COMM_FOAM;

	// Outstanding non-blocking operations.
	//! \cond fileScope
	DynamicList<MPI_Request> PstreamGlobals::outstandingRequests_;
	//! \endcond

	//// Max outstanding non-blocking operations.
	////! \cond fileScope
	//int PstreamGlobals::nRequests_ = 0;
	////! \endcond

	// Free'd non-blocking operations.
	//! \cond fileScope
	//DynamicList<label> PstreamGlobals::freedRequests_;
	//! \endcond

	// Max outstanding message tag operations.
	//! \cond fileScope
	int PstreamGlobals::nTags_ = 0;
	//! \endcond

	// Free'd message tags
	//! \cond fileScope
	DynamicList<int> PstreamGlobals::freedTags_;
	//! \endcond


	// Allocated communicators.
	//! \cond fileScope
	DynamicList<MPI_Comm> PstreamGlobals::MPICommunicators_;
	DynamicList<MPI_Group> PstreamGlobals::MPIGroups_;
	//! \endcond

	void PstreamGlobals::checkCommunicator
	(
		const label comm,
		const label otherProcNo
	)
	{
		if
			(
				comm < 0
				|| comm >= PstreamGlobals::MPICommunicators_.size()
				)
		{
			FatalErrorInFunction
				<< "otherProcNo:" << otherProcNo << " : illegal communicator "
				<< comm << endl
				<< "Communicator should be within range 0.."
				<< PstreamGlobals::MPICommunicators_.size() - 1 << abort(FatalError);
		}
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
