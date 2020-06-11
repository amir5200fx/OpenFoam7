#include <prefixOSstream.hxx>

#include <Pstream.hxx>
#include <token.hxx>

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

inline void tnbLib::prefixOSstream::checkWritePrefix()
{
	if (printPrefix_ && prefix_.size())
	{
		OSstream::write(prefix_.c_str());
		printPrefix_ = false;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::prefixOSstream::prefixOSstream
(
	ostream& os,
	const string& name,
	streamFormat format,
	versionNumber version,
	compressionType compression
)
	:
	OSstream(os, name, format, version, compression),
	printPrefix_(true),
	prefix_("")
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::prefixOSstream::print(Ostream& os) const
{
	os << "prefixOSstream ";
	OSstream::print(os);
}


tnbLib::Ostream& tnbLib::prefixOSstream::write(const token& t)
{
	if (t.type() == token::VERBATIMSTRING)
	{
		write(char(token::HASH));
		write(char(token::BEGIN_BLOCK));
		writeQuoted(t.stringToken(), false);
		write(char(token::HASH));
		write(char(token::END_BLOCK));
	}
	else if (t.type() == token::VARIABLE)
	{
		writeQuoted(t.stringToken(), false);
	}
	return *this;
}


tnbLib::Ostream& tnbLib::prefixOSstream::write(const char c)
{
	checkWritePrefix();
	OSstream::write(c);

	if (c == token::NL)
	{
		printPrefix_ = true;
	}

	return *this;
}


tnbLib::Ostream& tnbLib::prefixOSstream::write(const char* str)
{
	checkWritePrefix();
	OSstream::write(str);

	size_t len = strlen(str);
	if (len && str[len - 1] == token::NL)
	{
		printPrefix_ = true;
	}

	return *this;
}


tnbLib::Ostream& tnbLib::prefixOSstream::write(const word& val)
{
	checkWritePrefix();
	return OSstream::write(val);
}


tnbLib::Ostream& tnbLib::prefixOSstream::write(const string& val)
{
	checkWritePrefix();
	return OSstream::write(val);
}


tnbLib::Ostream& tnbLib::prefixOSstream::writeQuoted
(
	const std::string& val,
	const bool quoted
)
{
	checkWritePrefix();
	return OSstream::writeQuoted(val, quoted);
}


tnbLib::Ostream& tnbLib::prefixOSstream::write(const int32_t val)
{
	checkWritePrefix();
	return OSstream::write(val);
}


tnbLib::Ostream& tnbLib::prefixOSstream::write(const int64_t val)
{
	checkWritePrefix();
	return OSstream::write(val);
}


tnbLib::Ostream& tnbLib::prefixOSstream::write(const floatScalar val)
{
	checkWritePrefix();
	return OSstream::write(val);
}


tnbLib::Ostream& tnbLib::prefixOSstream::write(const doubleScalar val)
{
	checkWritePrefix();
	return OSstream::write(val);
}


tnbLib::Ostream& tnbLib::prefixOSstream::write(const longDoubleScalar val)
{
	checkWritePrefix();
	return OSstream::write(val);
}


tnbLib::Ostream& tnbLib::prefixOSstream::write
(
	const char* buf,
	std::streamsize count
)
{
	checkWritePrefix();
	return OSstream::write(buf, count);
}


void tnbLib::prefixOSstream::indent()
{
	checkWritePrefix();
	OSstream::indent();
}

// ************************************************************************* //