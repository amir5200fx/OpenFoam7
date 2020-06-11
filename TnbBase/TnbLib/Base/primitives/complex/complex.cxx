#include <complex.hxx>

#include <IOstreams.hxx>

#include <sstream>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const char* const tnbLib::complex::typeName = "complex";
const tnbLib::complex tnbLib::complex::zero(0, 0);
const tnbLib::complex tnbLib::complex::one(1, 1);

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::complex::complex(Istream& is)
{
	is >> *this;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::word tnbLib::name(const complex& c)
{
	std::ostringstream buf;
	buf << '(' << c.Re() << ',' << c.Im() << ')';
	return buf.str();
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

tnbLib::Istream& tnbLib::operator>>(Istream& is, complex& c)
{
	// Read beginning of complex
	is.readBegin("complex");

	is >> c.re >> c.im;

	// Read end of complex
	is.readEnd("complex");

	// Check state of Istream
	is.check("operator>>(Istream&, complex&)");

	return is;
}


tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const complex& c)
{
	os << token::BEGIN_LIST
		<< c.re << token::SPACE << c.im
		<< token::END_LIST;

	return os;
}


// ************************************************************************* //