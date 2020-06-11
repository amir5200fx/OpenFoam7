#include <UOPstream.hxx>

#include <int.hxx>
#include <token.hxx>

#include <cctype>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class T>
inline void tnbLib::UOPstream::writeToBuffer(const T& t)
{
	writeToBuffer(&t, sizeof(T), sizeof(T));
}


inline void tnbLib::UOPstream::writeToBuffer(const char& c)
{
	if (!sendBuf_.capacity())
	{
		sendBuf_.setCapacity(1000);
	}
	sendBuf_.append(c);
}


inline void tnbLib::UOPstream::writeToBuffer
(
	const void* data,
	size_t count,
	size_t align
)
{
	if (!sendBuf_.capacity())
	{
		sendBuf_.setCapacity(1000);
	}

	label alignedPos = sendBuf_.size();

	if (align > 1)
	{
		// Align bufPosition. Pads sendBuf_.size() - oldPos characters.
		alignedPos = align + ((sendBuf_.size() - 1) & ~(align - 1));
	}

	// Extend if necessary
	sendBuf_.setSize(alignedPos + count);

	const char* dataPtr = reinterpret_cast<const char*>(data);
	size_t i = count;
	while (i--) sendBuf_[alignedPos++] = *dataPtr++;
}



// * * * * * * * * * * * * * * * * Constructor * * * * * * * * * * * * * * * //

tnbLib::UOPstream::UOPstream
(
	const commsTypes commsType,
	const int toProcNo,
	DynamicList<char>& sendBuf,
	const int tag,
	const label comm,
	const bool sendAtDestruct,
	streamFormat format,
	versionNumber version
)
	:
	UPstream(commsType),
	Ostream(format, version),
	toProcNo_(toProcNo),
	sendBuf_(sendBuf),
	tag_(tag),
	comm_(comm),
	sendAtDestruct_(sendAtDestruct)
{
	setOpened();
	setGood();
}


tnbLib::UOPstream::UOPstream(const int toProcNo, PstreamBuffers& buffers)
	:
	UPstream(buffers.commsType_),
	Ostream(buffers.format_, buffers.version_),
	toProcNo_(toProcNo),
	sendBuf_(buffers.sendBuf_[toProcNo]),
	tag_(buffers.tag_),
	comm_(buffers.comm_),
	sendAtDestruct_(buffers.commsType_ != UPstream::commsTypes::nonBlocking)
{
	setOpened();
	setGood();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::UOPstream::~UOPstream()
{
	if (sendAtDestruct_)
	{
		if
			(
				!UOPstream::write
				(
					commsType_,
					toProcNo_,
					sendBuf_.begin(),
					sendBuf_.size(),
					tag_,
					comm_
				)
				)
		{
			FatalErrorInFunction
				<< "Failed sending outgoing message of size " << sendBuf_.size()
				<< " to processor " << toProcNo_
				<< tnbLib::abort(FatalError);
		}
	}
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::UOPstream::write(const token& t)
{
	// Raw token output only supported for verbatim strings for now
	if (t.type() == token::VERBATIMSTRING)
	{
		writeToBuffer(char(token::VERBATIMSTRING));
		write(t.stringToken());
	}
	else if (t.type() == token::VARIABLE)
	{
		writeToBuffer(char(token::VARIABLE));
		write(t.stringToken());
	}
	else
	{
		NotImplemented;
		setBad();
	}
	return *this;
}


tnbLib::Ostream& tnbLib::UOPstream::write(const char c)
{
	if (!isspace(c))
	{
		writeToBuffer(c);
	}

	return *this;
}


tnbLib::Ostream& tnbLib::UOPstream::write(const char* str)
{
	word nonWhiteChars(string::validate<word>(str));

	if (nonWhiteChars.size() == 1)
	{
		return write(nonWhiteChars[0]);
	}
	else if (nonWhiteChars.size())
	{
		return write(nonWhiteChars);
	}
	else
	{
		return *this;
	}
}


tnbLib::Ostream& tnbLib::UOPstream::write(const word& str)
{
	writeToBuffer(char(token::WORD));

	size_t len = str.size();
	writeToBuffer(len);
	writeToBuffer(str.c_str(), len + 1, 1);

	return *this;
}


tnbLib::Ostream& tnbLib::UOPstream::write(const string& str)
{
	writeToBuffer(char(token::STRING));

	size_t len = str.size();
	writeToBuffer(len);
	writeToBuffer(str.c_str(), len + 1, 1);

	return *this;
}


tnbLib::Ostream& tnbLib::UOPstream::writeQuoted
(
	const std::string& str,
	const bool quoted
)
{
	if (quoted)
	{
		writeToBuffer(char(token::STRING));
	}
	else
	{
		writeToBuffer(char(token::WORD));
	}

	size_t len = str.size();
	writeToBuffer(len);
	writeToBuffer(str.c_str(), len + 1, 1);

	return *this;
}


tnbLib::Ostream& tnbLib::UOPstream::write(const int32_t val)
{
	writeToBuffer(char(token::LABEL));
	writeToBuffer(val);
	return *this;
}


tnbLib::Ostream& tnbLib::UOPstream::write(const int64_t val)
{
	writeToBuffer(char(token::LABEL));
	writeToBuffer(val);
	return *this;
}


tnbLib::Ostream& tnbLib::UOPstream::write(const floatScalar val)
{
	writeToBuffer(char(token::FLOAT_SCALAR));
	writeToBuffer(val);
	return *this;
}


tnbLib::Ostream& tnbLib::UOPstream::write(const doubleScalar val)
{
	writeToBuffer(char(token::DOUBLE_SCALAR));
	writeToBuffer(val);
	return *this;
}


tnbLib::Ostream& tnbLib::UOPstream::write(const longDoubleScalar val)
{
	writeToBuffer(char(token::LONG_DOUBLE_SCALAR));
	writeToBuffer(val);
	return *this;
}


tnbLib::Ostream& tnbLib::UOPstream::write(const char* data, std::streamsize count)
{
	if (format() != BINARY)
	{
		FatalErrorInFunction
			<< "stream format not binary"
			<< tnbLib::abort(FatalError);
	}

	writeToBuffer(data, count, 8);

	return *this;
}


void tnbLib::UOPstream::print(Ostream& os) const
{
	os << "Writing from processor " << toProcNo_
		<< " to processor " << myProcNo() << " in communicator " << comm_
		<< " and tag " << tag_ << tnbLib::endl;
}


// ************************************************************************* //