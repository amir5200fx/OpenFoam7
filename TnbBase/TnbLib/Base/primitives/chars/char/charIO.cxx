#include <char.hxx>

#include <IOstreams.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

char tnbLib::readChar(Istream& is)
{
	char c;
	is.read(c);
	return c;
}


FoamBase_EXPORT tnbLib::Istream& tnbLib::operator>>(Istream& is, char& c)
{
	is.read(c);
	is.check("Istream& operator>>(Istream&, char&)");
	return is;
}


FoamBase_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const char c)
{
	os.write(c);
	os.check("Ostream& operator<<(Ostream&, const char)");
	return os;
}


FoamBase_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const char* s)
{
	os.write(s);
	os.check("Ostream& operator<<(Ostream&, const char*)");
	return os;
}


// ************************************************************************* //