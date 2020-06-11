#include <tnbString.hxx>

#include <IOstreams.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::string::string(Istream& is)
{
	is >> *this;
}


// * * * * * * * * * * * * * * * IOstream Functions  * * * * * * * * * * * * //

void tnbLib::writeEntry(Ostream& os, const char* value)
{
	os << value;
}


void tnbLib::writeEntry(Ostream& os, const string& value)
{
	os << value;
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

tnbLib::Istream& tnbLib::operator>>(Istream& is, string& s)
{
	token t(is);

	if (!t.good())
	{
		is.setBad();
		return is;
	}

	if (t.isString())
	{
		s = t.stringToken();
	}
	else
	{
		is.setBad();
		FatalIOErrorInFunction(is)
			<< "wrong token type - expected string, found " << t.info()
			<< exit(FatalIOError);

		return is;
	}

	// Check state of Istream
	is.check("Istream& operator>>(Istream&, string&)");

	return is;
}


tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const string& s)
{
	os.write(s);
	os.check("Ostream& operator<<(Ostream&, const string&)");
	return os;
}


tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const std::string& s)
{
	os.write(string(s));
	os.check("Ostream& operator<<(Ostream&, const std::string&)");
	return os;
}


// ************************************************************************* //