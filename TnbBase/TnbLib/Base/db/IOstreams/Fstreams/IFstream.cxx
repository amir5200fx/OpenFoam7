#include <IFstream.hxx>

#include <OSspecific.hxx>
#include <gzstream.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(IFstream, 0);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::IFstreamAllocator::IFstreamAllocator(const fileName& pathname)
	:
	ifPtr_(nullptr),
	compression_(IOstream::UNCOMPRESSED)
{
	if (pathname.empty())
	{
		if (IFstream::debug)
		{
			InfoInFunction << "Cannot open null file " << endl;
		}
	}

	ifPtr_ = new ifstream(pathname.c_str());

	// If the file is compressed, decompress it before reading.
	if (!ifPtr_->good())
	{
		if (isFile(pathname + ".gz", false, false))
		{
			delete ifPtr_;

			if (IFstream::debug)
			{
				InfoInFunction << "Decompressing " << pathname + ".gz" << endl;
			}

			ifPtr_ = new igzstream((pathname + ".gz").c_str());

			if (ifPtr_->good())
			{
				compression_ = IOstream::COMPRESSED;
			}
		}
		else if (isFile(pathname + ".orig", false, false))
		{
			delete ifPtr_;

			ifPtr_ = new ifstream((pathname + ".orig").c_str());
		}
	}
}


tnbLib::IFstreamAllocator::~IFstreamAllocator()
{
	delete ifPtr_;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::IFstream::IFstream
(
	const fileName& pathname,
	streamFormat format,
	versionNumber version
)
	:
	IFstreamAllocator(pathname),
	ISstream
	(
		*ifPtr_,
		"IFstream.sourceFile_",
		format,
		version,
		IFstreamAllocator::compression_
	),
	pathname_(pathname)
{
	setClosed();

	setState(ifPtr_->rdstate());

	if (!good())
	{
		if (debug)
		{
			InfoInFunction
				<< "Could not open file for input" << endl << info() << endl;
		}

		setBad();
	}
	else
	{
		setOpened();
	}

	lineNumber_ = 1;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::IFstream::~IFstream()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

std::istream& tnbLib::IFstream::stdStream()
{
	if (!ifPtr_)
	{
		FatalErrorInFunction
			<< "No stream allocated" << abort(FatalError);
	}
	return *ifPtr_;
}


const std::istream& tnbLib::IFstream::stdStream() const
{
	if (!ifPtr_)
	{
		FatalErrorInFunction
			<< "No stream allocated" << abort(FatalError);
	}
	return *ifPtr_;
}


void tnbLib::IFstream::print(Ostream& os) const
{
	// Print File data
	os << "IFstream: ";
	ISstream::print(os);
}


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

tnbLib::IFstream& tnbLib::IFstream::operator()() const
{
	if (!good())
	{
		// also checks variants
		if (isFile(pathname_, true, true))
		{
			check("IFstream::operator()");
			FatalIOError.exit();
		}
		else
		{
			FatalIOErrorInFunction(*this)
				<< "file " << pathname_ << " does not exist"
				<< exit(FatalIOError);
		}
	}

	return const_cast<IFstream&>(*this);
}


// ************************************************************************* //