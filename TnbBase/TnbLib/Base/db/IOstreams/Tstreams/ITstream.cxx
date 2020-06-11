#include <ITstream.hxx>

#include <error.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

void tnbLib::ITstream::print(Ostream& os) const
{
	os << "ITstream : " << name_.c_str();

	if (size())
	{
		if (begin()->lineNumber() == rbegin()->lineNumber())
		{
			os << ", line " << begin()->lineNumber() << ", ";
		}
		else
		{
			os << ", lines " << begin()->lineNumber()
				<< '-' << rbegin()->lineNumber() << ", ";
		}
	}
	else
	{
		os << ", line " << lineNumber() << ", ";
	}

	IOstream::print(os);
}


tnbLib::Istream& tnbLib::ITstream::read(token& t)
{
	// Return the put back token if it exists
	if (Istream::getBack(t))
	{
		lineNumber_ = t.lineNumber();
		return *this;
	}

	if (tokenIndex_ < size())
	{
		t = operator[](tokenIndex_++);
		lineNumber_ = t.lineNumber();

		if (tokenIndex_ == size())
		{
			setEof();
		}
	}
	else
	{
		if (eof())
		{
			FatalIOErrorInFunction
			(
				*this
			) << "attempt to read beyond EOF"
				<< exit(FatalIOError);

			setBad();
		}
		else
		{
			setEof();
		}

		t = token::undefinedToken;

		if (size())
		{
			t.lineNumber() = tokenList::last().lineNumber();
		}
		else
		{
			t.lineNumber() = lineNumber();
		}
	}

	return *this;
}


tnbLib::Istream& tnbLib::ITstream::read(char&)
{
	NotImplemented;
	return *this;
}


tnbLib::Istream& tnbLib::ITstream::read(word&)
{
	NotImplemented;
	return *this;
}


tnbLib::Istream& tnbLib::ITstream::read(string&)
{
	NotImplemented;
	return *this;
}


tnbLib::Istream& tnbLib::ITstream::read(label&)
{
	NotImplemented;
	return *this;
}


tnbLib::Istream& tnbLib::ITstream::read(floatScalar&)
{
	NotImplemented;
	return *this;
}


tnbLib::Istream& tnbLib::ITstream::read(doubleScalar&)
{
	NotImplemented;
	return *this;
}


tnbLib::Istream& tnbLib::ITstream::read(longDoubleScalar&)
{
	NotImplemented;
	return *this;
}


tnbLib::Istream& tnbLib::ITstream::read(char*, std::streamsize)
{
	NotImplemented;
	return *this;
}


tnbLib::Istream& tnbLib::ITstream::rewind()
{
	tokenIndex_ = 0;

	if (size())
	{
		lineNumber_ = tokenList::first().lineNumber();
	}

	setGood();

	return *this;
}


// ************************************************************************* //