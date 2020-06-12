#include <int32.hxx>

#include <IOstreams.hxx>

#include <inttypes.h>
#include <sstream>
#include <cerrno>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::word tnbLib::name(const int32_t val)
{
	std::ostringstream buf;
	buf << val;
	return buf.str();
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

tnbLib::Istream& tnbLib::operator>>(Istream& is, int32_t& i)
{
	token t(is);

	if (!t.good())
	{
		is.setBad();
		return is;
	}

	if (t.isLabel())
	{
		i = int32_t(t.labelToken());
	}
	else
	{
		is.setBad();
		FatalIOErrorInFunction(is)
			<< "wrong token type - expected int32_t, found " << t.info()
			<< exit(FatalIOError);

		return is;
	}

	// Check state of Istream
	is.check("Istream& operator>>(Istream&, int32_t&)");

	return is;
}


int32_t tnbLib::readInt32(Istream& is)
{
	int32_t val;
	is >> val;

	return val;
}


bool tnbLib::read(const char* buf, int32_t& s)
{
	char *endptr = nullptr;
	errno = 0;
	intmax_t l = strtoimax(buf, &endptr, 10);
	s = int32_t(l);
	return
		(*endptr == 0) && (errno == 0)
		&& (l >= INT32_MIN) && (l <= INT32_MAX);
}


tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const int32_t i)
{
	os.write(label(i));
	os.check("Ostream& operator<<(Ostream&, const int32_t)");
	return os;
}


#if WM_ARCH_OPTION == 32
tnbLib::Istream& tnbLib::operator>>(Istream& is, long& i)
{
	return operator>>(is, reinterpret_cast<int32_t&>(i));
}

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const long i)
{
	os << int32_t(i);
	return os;
}
#endif


// ************************************************************************* //