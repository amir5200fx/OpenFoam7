#include <IOstream.hxx>

#include <error.hxx>
#include <Switch.hxx>

#include <sstream>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

tnbLib::fileName tnbLib::IOstream::name_("IOstream");


// * * * * * * * * * * * * Static Member Functions * * * * * * * * * * * * * //

tnbLib::IOstream::streamFormat
tnbLib::IOstream::formatEnum(const word& format)
{
	if (format == "ascii")
	{
		return IOstream::ASCII;
	}
	else if (format == "binary")
	{
		return IOstream::BINARY;
	}
	else
	{
		WarningInFunction
			<< "bad format specifier '" << format << "', using 'ascii'"
			<< endl;

		return IOstream::ASCII;
	}
}


tnbLib::IOstream::compressionType
tnbLib::IOstream::compressionEnum(const word& compression)
{
	// get Switch (bool) value, but allow it to fail
	Switch sw(compression, true);

	if (sw.valid())
	{
		return sw ? IOstream::COMPRESSED : IOstream::UNCOMPRESSED;
	}
	else if (compression == "uncompressed")
	{
		return IOstream::UNCOMPRESSED;
	}
	else if (compression == "compressed")
	{
		return IOstream::COMPRESSED;
	}
	else
	{
		WarningInFunction
			<< "bad compression specifier '" << compression
			<< "', using 'uncompressed'"
			<< endl;

		return IOstream::UNCOMPRESSED;
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::IOstream::check(const char* operation) const
{
	if (bad())
	{
		FatalIOErrorInFunction(*this)
			<< "error in IOstream " << name() << " for operation " << operation
			<< exit(FatalIOError);
	}

	return !bad();
}


void tnbLib::IOstream::fatalCheck(const char* operation) const
{
	if (bad())
	{
		FatalIOErrorInFunction(*this)
			<< "error in IOstream " << name() << " for operation " << operation
			<< exit(FatalIOError);
	}
}


tnbLib::string tnbLib::IOstream::versionNumber::str() const
{
	std::ostringstream os;
	os.precision(1);
	os.setf(ios_base::fixed, ios_base::floatfield);
	os << versionNumber_;
	return os.str();
}


void tnbLib::IOstream::print(Ostream& os) const
{
	os << "IOstream: " << "Version " << version_ << ", format ";

	switch (format_)
	{
	case ASCII:
		os << "ASCII";
		break;

	case BINARY:
		os << "BINARY";
		break;
	}

	os << ", line " << lineNumber();

	if (opened())
	{
		os << ", OPENED";
	}

	if (closed())
	{
		os << ", CLOSED";
	}

	if (good())
	{
		os << ", GOOD";
	}

	if (eof())
	{
		os << ", EOF";
	}

	if (fail())
	{
		os << ", FAIL";
	}

	if (bad())
	{
		os << ", BAD";
	}

	os << endl;
}


void tnbLib::IOstream::print(Ostream& os, const int streamState) const
{
	if (streamState == ios_base::goodbit)
	{
		os << "ios_base::goodbit set : the last operation on stream succeeded"
			<< endl;
	}
	else if (streamState & ios_base::badbit)
	{
		os << "ios_base::badbit set : characters possibly lost"
			<< endl;
	}
	else if (streamState & ios_base::failbit)
	{
		os << "ios_base::failbit set : some type of formatting error"
			<< endl;
	}
	else if (streamState & ios_base::eofbit)
	{
		os << "ios_base::eofbit set : at end of stream"
			<< endl;
	}
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const IOstream::streamFormat& sf)
{
	if (sf == IOstream::ASCII)
	{
		os << "ascii";
	}
	else
	{
		os << "binary";
	}

	return os;
}


tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const IOstream::versionNumber& vn)
{
	os << vn.str().c_str();
	return os;
}


template<>
tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const InfoProxy<IOstream>& ip)
{
	ip.t_.print(os);
	return os;
}


// ************************************************************************* //