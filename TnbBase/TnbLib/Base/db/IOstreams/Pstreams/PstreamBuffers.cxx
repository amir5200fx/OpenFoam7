#include <PstreamBuffers.hxx>

#include <Pstream.hxx> // added by amir!

/* * * * * * * * * * * * * * * Static Member Data  * * * * * * * * * * * * * */

namespace tnbLib
{

	DynamicList<char> PstreamBuffers::nullBuf(0);
}


// * * * * * * * * * * * * * * * * Constructor * * * * * * * * * * * * * * * //

tnbLib::PstreamBuffers::PstreamBuffers
(
	const UPstream::commsTypes commsType,
	const int tag,
	const label comm,
	IOstream::streamFormat format,
	IOstream::versionNumber version
)
	:
	commsType_(commsType),
	tag_(tag),
	comm_(comm),
	format_(format),
	version_(version),
	sendBuf_(UPstream::nProcs(comm)),
	recvBuf_(UPstream::nProcs(comm)),
	recvBufPos_(UPstream::nProcs(comm), 0),
	finishedSendsCalled_(false)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::PstreamBuffers::~PstreamBuffers()
{
	// Check that all data has been consumed.
	forAll(recvBufPos_, proci)
	{
		if (recvBufPos_[proci] < recvBuf_[proci].size())
		{
			FatalErrorInFunction
				<< "Message from processor " << proci
				<< " not fully consumed. messageSize:" << recvBuf_[proci].size()
				<< " bytes of which only " << recvBufPos_[proci]
				<< " consumed."
				<< tnbLib::abort(FatalError);
		}
	}
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::PstreamBuffers::finishedSends(const bool block)
{
	finishedSendsCalled_ = true;

	if (commsType_ == UPstream::commsTypes::nonBlocking)
	{
		Pstream::exchange<DynamicList<char>, char>
			(
				sendBuf_,
				recvBuf_,
				tag_,
				comm_,
				block
				);
	}
}


void tnbLib::PstreamBuffers::finishedSends(labelList& recvSizes, const bool block)
{
	finishedSendsCalled_ = true;

	if (commsType_ == UPstream::commsTypes::nonBlocking)
	{
		Pstream::exchangeSizes(sendBuf_, recvSizes, comm_);

		Pstream::exchange<DynamicList<char>, char>
			(
				sendBuf_,
				recvSizes,
				recvBuf_,
				tag_,
				comm_,
				block
				);
	}
	else
	{
		FatalErrorInFunction
			<< "Obtaining sizes not supported in "
			<< UPstream::commsTypeNames[commsType_] << endl
			<< " since transfers already in progress. Use non-blocking instead."
			<< exit(FatalError);

		// Note: maybe possible only if using different tag from write started
		// by ~UOPstream. Needs some work.
	}
}


void tnbLib::PstreamBuffers::clear()
{
	forAll(sendBuf_, i)
	{
		sendBuf_[i].clear();
	}
	forAll(recvBuf_, i)
	{
		recvBuf_[i].clear();
	}
	recvBufPos_ = 0;
	finishedSendsCalled_ = false;
}


// ************************************************************************* //