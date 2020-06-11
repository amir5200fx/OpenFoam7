#include <OPstream.hxx>

// * * * * * * * * * * * * * * * * Constructor * * * * * * * * * * * * * * * //

tnbLib::OPstream::OPstream
(
	const commsTypes commsType,
	const int toProcNo,
	const label bufSize,
	const int tag,
	const label comm,
	streamFormat format,
	versionNumber version
)
	:
	Pstream(commsType, bufSize),
	UOPstream(commsType, toProcNo, buf_, tag, comm, true, format, version)
{}


// ************************************************************************* //