#include <uint32.hxx>

#include <IOstreams.hxx>

#include <sstream>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::word tnbLib::name(const uint32_t val)
{
	std::ostringstream buf;
	buf << val;
	return buf.str();
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

FoamBase_EXPORT tnbLib::Istream& tnbLib::operator>>(Istream& is, uint32_t& i)
{
	token t(is);

	if (!t.good())
	{
		is.setBad();
		return is;
	}

	if (t.isLabel())
	{
		i = uint32_t(t.labelToken());
	}
	else
	{
		is.setBad();
		FatalIOErrorInFunction(is)
			<< "wrong token type - expected uint32_t, found " << t.info()
			<< exit(FatalIOError);

		return is;
	}

	// Check state of Istream
	is.check("Istream& operator>>(Istream&, uint32_t&)");

	return is;
}


uint32_t tnbLib::readUint32(Istream& is)
{
	uint32_t val;
	is >> val;

	return val;
}


bool tnbLib::read(const char* buf, uint32_t& s)
{
	char *endptr = nullptr;
	long l = strtol(buf, &endptr, 10);
	s = uint32_t(l);
	return (*endptr == 0);
}


FoamBase_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const uint32_t i)
{
	os.write(label(i));
	os.check("Ostream& operator<<(Ostream&, const uint32_t)");
	return os;
}


// ************************************************************************* //