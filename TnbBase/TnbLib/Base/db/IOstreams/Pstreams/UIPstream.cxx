#include <UIPstream.hxx>

#include <int.hxx>
#include <token.hxx>
#include <error.hxx>

#include <cctype>

#include <IOstreams.hxx> // added by amir

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

inline void tnbLib::UIPstream::checkEof()
{
	if (externalBufPosition_ == messageSize_)
	{
		setEof();
	}
}


template<class T>
inline void tnbLib::UIPstream::readFromBuffer(T& t)
{
	const size_t align = sizeof(T);
	externalBufPosition_ = align + ((externalBufPosition_ - 1) & ~(align - 1));

	t = reinterpret_cast<T&>(externalBuf_[externalBufPosition_]);
	externalBufPosition_ += sizeof(T);
	checkEof();
}


inline void tnbLib::UIPstream::readFromBuffer
(
	void* data,
	size_t count,
	size_t align
)
{
	if (align > 1)
	{
		externalBufPosition_ =
			align
			+ ((externalBufPosition_ - 1) & ~(align - 1));
	}

	const char* bufPtr = &externalBuf_[externalBufPosition_];
	char* dataPtr = reinterpret_cast<char*>(data);
	size_t i = count;
	while (i--) *dataPtr++ = *bufPtr++;
	externalBufPosition_ += (label)count;  //- modified by amir
	checkEof();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::UIPstream::~UIPstream()
{
	if (clearAtEnd_ && eof())
	{
		if (debug)
		{
			Pout << "UIPstream::~UIPstream() : tag:" << tag_
				<< " fromProcNo:" << fromProcNo_
				<< " clearing externalBuf_ of size "
				<< externalBuf_.size()
				<< " messageSize_:" << messageSize_ << endl;
		}
		externalBuf_.clearStorage();
	}
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::Istream& tnbLib::UIPstream::read(token& t)
{
	// Return the put back token if it exists
	if (Istream::getBack(t))
	{
		return *this;
	}

	char c;

	// return on error
	if (!read(c))
	{
		t.setBad();
		return *this;
	}

	// Set the line number of this token to the current stream line number
	t.lineNumber() = lineNumber();

	// Analyse input starting with this character.
	switch (c)
	{
		// Punctuation
	case token::END_STATEMENT:
	case token::BEGIN_LIST:
	case token::END_LIST:
	case token::BEGIN_SQR:
	case token::END_SQR:
	case token::BEGIN_BLOCK:
	case token::END_BLOCK:
	case token::COLON:
	case token::COMMA:
	case token::ASSIGN:
	case token::ADD:
	case token::SUBTRACT:
	case token::MULTIPLY:
	case token::DIVIDE:
	{
		t = token::punctuationToken(c);
		return *this;
	}

	// Word
	case token::WORD:
	{
		word* pval = new word;
		if (read(*pval))
		{
			if (token::compound::isCompound(*pval))
			{
				t = token::compound::New(*pval, *this).ptr();
				delete pval;
			}
			else
			{
				t = pval;
			}
		}
		else
		{
			delete pval;
			t.setBad();
		}
		return *this;
	}

	// String
	case token::VERBATIMSTRING:
	{
		// Recurse to read actual string
		read(t);
		t.type() = token::VERBATIMSTRING;
		return *this;
	}
	case token::VARIABLE:
	{
		// Recurse to read actual string
		read(t);
		t.type() = token::VARIABLE;
		return *this;
	}
	case token::STRING:
	{
		string* pval = new string;
		if (read(*pval))
		{
			t = pval;
			if (c == token::VERBATIMSTRING)
			{
				t.type() = token::VERBATIMSTRING;
			}
		}
		else
		{
			delete pval;
			t.setBad();
		}
		return *this;
	}

	// Label
	case token::LABEL:
	{
		label val;
		if (read(val))
		{
			t = val;
		}
		else
		{
			t.setBad();
		}
		return *this;
	}

	// floatScalar
	case token::FLOAT_SCALAR:
	{
		floatScalar val;
		if (read(val))
		{
			t = val;
		}
		else
		{
			t.setBad();
		}
		return *this;
	}

	// doubleScalar
	case token::DOUBLE_SCALAR:
	{
		doubleScalar val;
		if (read(val))
		{
			t = val;
		}
		else
		{
			t.setBad();
		}
		return *this;
	}

	// longDoubleScalar
	case token::LONG_DOUBLE_SCALAR:
	{
		longDoubleScalar val;
		if (read(val))
		{
			t = val;
		}
		else
		{
			t.setBad();
		}
		return *this;
	}

	// Character (returned as a single character word) or error
	default:
	{
		if (isalpha(c))
		{
			t = word(c);
			return *this;
		}

		setBad();
		t.setBad();

		return *this;
	}
	}
}


tnbLib::Istream& tnbLib::UIPstream::read(char& c)
{
	c = externalBuf_[externalBufPosition_];
	externalBufPosition_++;
	checkEof();
	return *this;
}


tnbLib::Istream& tnbLib::UIPstream::read(word& str)
{
	size_t len;
	readFromBuffer(len);
	str = &externalBuf_[externalBufPosition_];
	externalBufPosition_ += (label)len + 1;  //- modified by amir
	checkEof();
	return *this;
}


tnbLib::Istream& tnbLib::UIPstream::read(string& str)
{
	size_t len;
	readFromBuffer(len);
	str = &externalBuf_[externalBufPosition_];
	externalBufPosition_ += (label)len + 1;	//- modified by amir
	checkEof();
	return *this;
}


tnbLib::Istream& tnbLib::UIPstream::read(label& val)
{
	readFromBuffer(val);
	return *this;
}


tnbLib::Istream& tnbLib::UIPstream::read(floatScalar& val)
{
	readFromBuffer(val);
	return *this;
}


tnbLib::Istream& tnbLib::UIPstream::read(doubleScalar& val)
{
	readFromBuffer(val);
	return *this;
}


tnbLib::Istream& tnbLib::UIPstream::read(longDoubleScalar& val)
{
	readFromBuffer(val);
	return *this;
}


tnbLib::Istream& tnbLib::UIPstream::read(char* data, std::streamsize count)
{
	if (format() != BINARY)
	{
		FatalErrorInFunction
			<< "stream format not binary"
			<< tnbLib::abort(FatalError);
	}

	readFromBuffer(data, count, 8);
	return *this;
}


tnbLib::Istream& tnbLib::UIPstream::rewind()
{
	externalBufPosition_ = 0;
	return *this;
}


void tnbLib::UIPstream::print(Ostream& os) const
{
	os << "Reading from processor " << fromProcNo_
		<< " using communicator " << comm_
		<< " and tag " << tag_
		<< tnbLib::endl;
}


// ************************************************************************* //