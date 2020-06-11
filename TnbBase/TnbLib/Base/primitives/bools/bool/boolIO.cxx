#include <bool.hxx>

#include <Switch.hxx>
#include <error.hxx>
#include <IOstreams.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::Istream& tnbLib::operator>>(Istream& is, bool& b)
{
	if (is.good())
	{
		b = Switch(is);
	}

	return is;
}


tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const bool b)
{
	// we could also write as text string without any difficulty
	// os  << (b ? "true" : "false");
	os.write(label(b));
	os.check("Ostream& operator<<(Ostream&, const bool)");
	return os;
}


bool tnbLib::readBool(Istream& is)
{
	bool b;
	is >> b;

	return b;
}


// ************************************************************************* //