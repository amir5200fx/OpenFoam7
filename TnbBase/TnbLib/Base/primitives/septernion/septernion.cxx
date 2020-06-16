#include <septernion.hxx>

#include <UList.hxx> // added by amir
#include <IOstreams.hxx>
#include <OStringStream.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const char* const tnbLib::septernion::typeName = "septernion";
const tnbLib::septernion tnbLib::septernion::zero
(
	vector(0, 0, 0),
	quaternion(0, vector(0, 0, 0))
);
const tnbLib::septernion tnbLib::septernion::I
(
	vector(0, 0, 0),
	quaternion(1, vector(0, 0, 0))
);

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::septernion::septernion(Istream& is)
{
	is >> *this;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::word tnbLib::name(const septernion& s)
{
	OStringStream buf;
	buf << '(' << s.t() << ',' << s.r() << ')';
	return buf.str();
}


tnbLib::septernion tnbLib::slerp
(
	const septernion& sa,
	const septernion& sb,
	const scalar t
)
{
	return septernion((1 - t)*sa.t() + t * sb.t(), slerp(sa.r(), sb.r(), t));
}


tnbLib::septernion tnbLib::average
(
	const UList<septernion>& ss,
	const UList<scalar> w
)
{
	septernion sa(w[0] * ss[0]);

	for (label i = 1; i < ss.size(); i++)
	{
		sa.t() += w[i] * ss[i].t();

		// Invert quaternion if it has the opposite sign to the average
		if ((sa.r() & ss[i].r()) > 0)
		{
			sa.r() += w[i] * ss[i].r();
		}
		else
		{
			sa.r() -= w[i] * ss[i].r();
		}
	}

	sa.r().normalize();

	return sa;
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

tnbLib::Istream& tnbLib::operator>>(Istream& is, septernion& s)
{
	// Read beginning of septernion
	is.readBegin("septernion");

	is >> s.t() >> s.r();

	// Read end of septernion
	is.readEnd("septernion");

	// Check state of Istream
	is.check("operator>>(Istream&, septernion&)");

	return is;
}


tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const septernion& s)
{
	os << token::BEGIN_LIST
		<< s.t() << token::SPACE << s.r()
		<< token::END_LIST;

	return os;
}


// ************************************************************************* //