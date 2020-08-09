#include <threadedCollatedOFstream.hxx>

#include <decomposedBlockData.hxx>
#include <OFstreamCollator.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::threadedCollatedOFstream::threadedCollatedOFstream
(
	OFstreamCollator& writer,
	const fileName& pathName,
	streamFormat format,
	versionNumber version,
	compressionType compression,
	const bool useThread
)
	:
	OStringStream(format, version),
	writer_(writer),
	pathName_(pathName),
	compression_(compression),
	useThread_(useThread)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::threadedCollatedOFstream::~threadedCollatedOFstream()
{
	writer_.write
	(
		decomposedBlockData::typeName,
		pathName_,
		str(),
		IOstream::BINARY,
		version(),
		compression_,
		false,                  // append
		useThread_
	);
}


// ************************************************************************* //