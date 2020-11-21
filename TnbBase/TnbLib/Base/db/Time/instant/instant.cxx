#include <instantList.hxx>

#include <Time.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const char* const tnbLib::instant::typeName = "instant";

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::instant::instant()
{}

tnbLib::instant::instant(const scalar val, const word& tname)
	:
	value_(val),
	name_(tname)
{}

tnbLib::instant::instant(const scalar val)
	:
	value_(val),
	name_(Time::timeName(val))
{}

tnbLib::instant::instant(const word& tname)
	:
	value_(atof(tname.c_str())),
	name_(tname)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::instant::equal(const scalar b) const
{
	return (value_ < b + small && value_ > b - small);
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

FoamBase_EXPORT bool tnbLib::operator==(const instant& a, const instant& b)
{
	return a.equal(b.value_);
}


FoamBase_EXPORT bool tnbLib::operator!=(const instant& a, const instant& b)
{
	return !operator==(a, b);
}


FoamBase_EXPORT bool tnbLib::operator<(const instant& a, const instant& b)
{
	return a.value_ < b.value_;
}


FoamBase_EXPORT bool tnbLib::operator>(const instant& a, const instant& b)
{
	return a.value_ > b.value_;
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

FoamBase_EXPORT tnbLib::Istream& tnbLib::operator>>(Istream& is, instant& I)
{
	is >> I.value_ >> I.name_;

	return is;
}


FoamBase_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const instant& I)
{
	os << I.value_ << tab << I.name_;

	return os;
}


// ************************************************************************* //