#include <IPstream.hxx>

// * * * * * * * * * * * * * * * * Constructor * * * * * * * * * * * * * * * //

tnbLib::IPstream::IPstream
(
	const commsTypes commsType,
	const int fromProcNo,
	const label bufSize,
	const int tag,
	const label comm,
	streamFormat format,
	versionNumber version
)
	:
	Pstream(commsType, bufSize),
	UIPstream
	(
		commsType,
		fromProcNo,
		buf_,
		externalBufPosition_,
		tag,                        // tag
		comm,
		false,                      // do not clear buf_ if at end
		format,
		version
	),
	externalBufPosition_(0)
{}


// ************************************************************************* //