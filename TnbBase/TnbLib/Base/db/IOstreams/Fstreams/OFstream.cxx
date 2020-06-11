#include <OFstream.hxx>

#include <OSspecific.hxx>
#include <gzstream.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(OFstream, 0);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::OFstreamAllocator::OFstreamAllocator
(
	const fileName& pathname,
	IOstream::compressionType compression,
	const bool append
)
	:
	ofPtr_(nullptr)
{
	if (pathname.empty())
	{
		if (OFstream::debug)
		{
			InfoInFunction << "Cannot open null file " << endl;
		}
	}
	ofstream::openmode mode(ofstream::out);
	if (append)
	{
		mode |= ofstream::app;
	}

	if (compression == IOstream::COMPRESSED)
	{
		// Get identically named uncompressed version out of the way
		fileType pathType = tnbLib::type(pathname, false, false);
		if (pathType == fileType::file || pathType == fileType::link)
		{
			rm(pathname);
		}
		fileName gzPathName(pathname + ".gz");

		if (!append && tnbLib::type(gzPathName) == fileType::link)
		{
			// Disallow writing into softlink to avoid any problems with
			// e.g. softlinked initial fields
			rm(gzPathName);
		}

		ofPtr_ = new ogzstream(gzPathName.c_str(), mode);
	}
	else
	{
		// get identically named compressed version out of the way
		fileName gzPathName(pathname + ".gz");
		fileType gzType = tnbLib::type(gzPathName, false, false);
		if (gzType == fileType::file || gzType == fileType::link)
		{
			rm(gzPathName);
		}
		if
			(
				!append
				&& tnbLib::type(pathname, false, false) == fileType::link
				)
		{
			// Disallow writing into softlink to avoid any problems with
			// e.g. softlinked initial fields
			rm(pathname);
		}

		ofPtr_ = new ofstream(pathname.c_str(), mode);
	}
}


tnbLib::OFstreamAllocator::~OFstreamAllocator()
{
	delete ofPtr_;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::OFstream::OFstream
(
	const fileName& pathname,
	streamFormat format,
	versionNumber version,
	compressionType compression,
	const bool append
)
	:
	OFstreamAllocator(pathname, compression, append),
	OSstream(*ofPtr_, "OFstream.sinkFile_", format, version, compression),
	pathname_(pathname)
{
	setClosed();
	setState(ofPtr_->rdstate());

	if (!good())
	{
		if (debug)
		{
			InfoInFunction
				<< "Could not open file " << pathname
				<< "for input\n"
				"in stream " << info() << tnbLib::endl;
		}

		setBad();
	}
	else
	{
		setOpened();
	}

	lineNumber_ = 1;
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::OFstream::~OFstream()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

std::ostream& tnbLib::OFstream::stdStream()
{
	if (!ofPtr_)
	{
		FatalErrorInFunction
			<< "No stream allocated." << abort(FatalError);
	}
	return *ofPtr_;
}


const std::ostream& tnbLib::OFstream::stdStream() const
{
	if (!ofPtr_)
	{
		FatalErrorInFunction
			<< "No stream allocated." << abort(FatalError);
	}
	return *ofPtr_;
}


void tnbLib::OFstream::print(Ostream& os) const
{
	os << "    OFstream: ";
	OSstream::print(os);
}


// ************************************************************************* //