#include <uint64.hxx>

#include <IOstreams.hxx>

#include <sstream>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::word tnbLib::name(const uint64_t val)
{
	std::ostringstream buf;
	buf << val;
	return buf.str();
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

tnbLib::Istream& tnbLib::operator>>(Istream& is, uint64_t& i)
{
	token t(is);

	if (!t.good())
	{
		is.setBad();
		return is;
	}

	if (t.isLabel())
	{
		i = uint64_t(t.labelToken());
	}
	else
	{
		is.setBad();
		FatalIOErrorInFunction(is)
			<< "wrong token type - expected uint64_t, found " << t.info()
			<< exit(FatalIOError);

		return is;
	}

	// Check state of Istream
	is.check("Istream& operator>>(Istream&, uint64_t&)");

	return is;
}


uint64_t tnbLib::readUint64(Istream& is)
{
	uint64_t val;
	is >> val;

	return val;
}


bool tnbLib::read(const char* buf, uint64_t& s)
{
	char *endptr = nullptr;
	long l = strtol(buf, &endptr, 10);
	s = uint64_t(l);
	return (*endptr == 0);
}


tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const uint64_t i)
{
	os.write(label(i));
	os.check("Ostream& operator<<(Ostream&, const uint64_t)");
	return os;
}


// ************************************************************************* //