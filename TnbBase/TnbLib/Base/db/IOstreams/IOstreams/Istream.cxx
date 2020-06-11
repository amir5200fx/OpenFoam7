#include <Istream.hxx>

#include <token.hxx>
#include <error.hxx>

tnbLib::Istream::Istream
(
	streamFormat format,
	versionNumber version,
	compressionType compression
)
	: IOstream(format, version, compression)
	, putBack_(false)
	, putBackToken_(NULL)
{
	putBackToken_ = new token;
}

tnbLib::Istream::~Istream()
{
	delete putBackToken_;
}

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::Istream::putBack(const token& t)
{
	if (bad())
	{
		FatalIOErrorInFunction(*this)
			<< "Attempt to put back onto bad stream"
			<< exit(FatalIOError);
	}
	else if (putBack_)
	{
		FatalIOErrorInFunction(*this)
			<< "Attempt to put back another token"
			<< exit(FatalIOError);
	}
	else
	{
		*putBackToken_ = t;
		putBack_ = true;
	}
}


bool tnbLib::Istream::getBack(token& t)
{
	if (bad())
	{
		FatalIOErrorInFunction(*this)
			<< "Attempt to get back from bad stream"
			<< exit(FatalIOError);
	}
	else if (putBack_)
	{
		t = *putBackToken_;
		putBack_ = false;
		return true;
	}

	return false;
}


bool tnbLib::Istream::peekBack(token& t)
{
	if (putBack_)
	{
		t = *putBackToken_;
	}
	else
	{
		t = token::undefinedToken;
	}

	return putBack_;
}


tnbLib::Istream& tnbLib::Istream::readBegin(const char* funcName)
{
	token delimiter(*this);
	if (delimiter != token::BEGIN_LIST)
	{
		setBad();
		FatalIOErrorInFunction(*this)
			<< "Expected a '" << token::BEGIN_LIST
			<< "' while reading " << funcName
			<< ", found " << delimiter.info()
			<< exit(FatalIOError);
	}

	return *this;
}


tnbLib::Istream& tnbLib::Istream::readEnd(const char* funcName)
{
	token delimiter(*this);
	if (delimiter != token::END_LIST)
	{
		setBad();
		FatalIOErrorInFunction(*this)
			<< "Expected a '" << token::END_LIST
			<< "' while reading " << funcName
			<< ", found " << delimiter.info()
			<< exit(FatalIOError);
	}

	return *this;
}


tnbLib::Istream& tnbLib::Istream::readEndBegin(const char* funcName)
{
	readEnd(funcName);
	return readBegin(funcName);
}


char tnbLib::Istream::readBeginList(const char* funcName)
{
	token delimiter(*this);

	if (delimiter != token::BEGIN_LIST && delimiter != token::BEGIN_BLOCK)
	{
		setBad();
		FatalIOErrorInFunction(*this)
			<< "Expected a '" << token::BEGIN_LIST
			<< "' or a '" << token::BEGIN_BLOCK
			<< "' while reading " << funcName
			<< ", found " << delimiter.info()
			<< exit(FatalIOError);

		return '\0';
	}

	return delimiter.pToken();
}


char tnbLib::Istream::readEndList(const char* funcName)
{
	token delimiter(*this);

	if (delimiter != token::END_LIST && delimiter != token::END_BLOCK)
	{
		setBad();
		FatalIOErrorInFunction(*this)
			<< "Expected a '" << token::END_LIST
			<< "' or a '" << token::END_BLOCK
			<< "' while reading " << funcName
			<< ", found " << delimiter.info()
			<< exit(FatalIOError);

		return '\0';
	}

	return delimiter.pToken();
}


tnbLib::Istream& tnbLib::Istream::operator()() const
{
	if (!good())
	{
		check("Istream::operator()");
		FatalIOError.exit();
	}

	return const_cast<Istream&>(*this);
}


// ************************************************************************* //