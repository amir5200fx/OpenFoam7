#include <ensightFile.hxx>

#include <sstream>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

bool tnbLib::ensightFile::allowUndef_ = false;

tnbLib::scalar tnbLib::ensightFile::undefValue_ = tnbLib::floatScalarVGreat;

// default is width 8
tnbLib::string tnbLib::ensightFile::mask_ = "********";

tnbLib::string tnbLib::ensightFile::dirFmt_ = "%08d";


// * * * * * * * * * * * * * Static Member Functions * * * * * * * * * * * * //

tnbLib::string tnbLib::ensightFile::mask()
{
	return mask_;
}


tnbLib::string tnbLib::ensightFile::subDir(const label n)
{
	char buf[32];

	sprintf(buf, dirFmt_.c_str(), n);
	return buf;
}


void tnbLib::ensightFile::subDirWidth(const label n)
{
	// enforce max limit to avoid buffer overflow in subDir()
	if (n < 1 || n > 31)
	{
		return;
	}

	// appropriate printf format
	std::ostringstream oss;
	oss << "%0" << n << "d";
	dirFmt_ = oss.str();

	// set mask accordingly
	mask_.resize(n, '*');
}


tnbLib::label tnbLib::ensightFile::subDirWidth()
{
	return (label)mask_.size();
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::ensightFile::ensightFile
(
	const fileName& pathname,
	IOstream::streamFormat format
)
	:
	OFstream(pathname, format)
{
	// ascii formatting specs
	setf
	(
		ios_base::scientific,
		ios_base::floatfield
	);
	precision(5);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::ensightFile::~ensightFile()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::ensightFile::allowUndef()
{
	return allowUndef_;
}


bool tnbLib::ensightFile::allowUndef(bool value)
{
	bool old = allowUndef_;
	allowUndef_ = value;
	return old;
}


tnbLib::scalar tnbLib::ensightFile::undefValue(const scalar value)
{
	// enable its use too
	allowUndef_ = true;

	scalar old = undefValue_;
	undefValue_ = value;
	return old;
}


tnbLib::Ostream& tnbLib::ensightFile::write
(
	const char* buf,
	std::streamsize count
)
{
	stdStream().write(buf, count);
	return *this;
}


tnbLib::Ostream& tnbLib::ensightFile::write(const char* value)
{
	return write(string(value));
}


tnbLib::Ostream& tnbLib::ensightFile::write(const string& value)
{
	char buf[80];

	for (string::size_type i = 0; i < 80; ++i)
	{
		buf[i] = 0;
	}

	string::size_type n = value.size();
	if (n >= 80)
	{
		n = 79;
	}

	for (string::size_type i = 0; i < n; ++i)
	{
		buf[i] = value[i];
	}

	if (format() == IOstream::BINARY)
	{
		write
		(
			reinterpret_cast<char const *>(buf),
			sizeof(buf)
		);
	}
	else
	{
		stdStream() << buf;
	}

	return *this;
}


tnbLib::Ostream& tnbLib::ensightFile::write(const label value)
{
	if (format() == IOstream::BINARY)
	{
		unsigned int ivalue(value);

		write
		(
			reinterpret_cast<char const *>(&ivalue),
			sizeof(ivalue)
		);
	}
	else
	{
		stdStream().width(10);
		stdStream() << value;
	}

	return *this;
}


tnbLib::Ostream& tnbLib::ensightFile::write
(
	const label value,
	const label fieldWidth
)
{
	if (format() == IOstream::BINARY)
	{
		unsigned int ivalue(value);

		write
		(
			reinterpret_cast<char const *>(&ivalue),
			sizeof(ivalue)
		);
	}
	else
	{
		stdStream().width(fieldWidth);
		stdStream() << value;
	}

	return *this;
}


tnbLib::Ostream& tnbLib::ensightFile::write(const scalar value)
{
	float fvalue((float)value);

	if (format() == IOstream::BINARY)
	{
		write
		(
			reinterpret_cast<char const *>(&fvalue),
			sizeof(fvalue)
		);
	}
	else
	{
		stdStream().width(12);
		stdStream() << fvalue;
	}

	return *this;
}


void tnbLib::ensightFile::newline()
{
	if (format() == IOstream::ASCII)
	{
		stdStream() << nl;
	}
}


tnbLib::Ostream& tnbLib::ensightFile::writeUndef()
{
	write(undefValue_);
	return *this;
}


tnbLib::Ostream& tnbLib::ensightFile::writeKeyword(const string& key)
{
	if (allowUndef_)
	{
		write(string(key + " undef"));
		newline();
		write(undefValue_);
		newline();
	}
	else
	{
		write(key);
		newline();
	}
	return *this;
}


tnbLib::Ostream& tnbLib::ensightFile::writeBinaryHeader()
{
	if (format() == IOstream::BINARY)
	{
		write("C Binary");
	}

	return *this;
}


// ************************************************************************* //