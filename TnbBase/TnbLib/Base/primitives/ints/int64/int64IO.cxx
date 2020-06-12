#include <int64.hxx>

#include <IOstreams.hxx>

#include <inttypes.h>
#include <sstream>
#include <cerrno>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::word tnbLib::name(const int64_t val)
{
	std::ostringstream buf;
	buf << val;
	return buf.str();
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

tnbLib::Istream& tnbLib::operator>>(Istream& is, int64_t& i)
{
	token t(is);

	if (!t.good())
	{
		is.setBad();
		return is;
	}

	if (t.isLabel())
	{
		i = int64_t(t.labelToken());
	}
	else
	{
		is.setBad();
		FatalIOErrorInFunction(is)
			<< "wrong token type - expected int64_t, found " << t.info()
			<< exit(FatalIOError);

		return is;
	}

	// Check state of Istream
	is.check("Istream& operator>>(Istream&, int64_t&)");

	return is;
}


int64_t tnbLib::readInt64(Istream& is)
{
	int64_t val;
	is >> val;

	return val;
}


bool tnbLib::read(const char* buf, int64_t& s)
{
	char *endptr = nullptr;
	errno = 0;
	intmax_t l = strtoimax(buf, &endptr, 10);
	s = int64_t(l);
	return (*endptr == 0) && (errno == 0);
}


tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const int64_t i)
{
	os.write(label(i));
	os.check("Ostream& operator<<(Ostream&, const int64_t)");
	return os;
}


// ************************************************************************* //