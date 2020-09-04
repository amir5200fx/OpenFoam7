#pragma once
#include <token.hxx>  // added by amir
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::STLtriangle::STLtriangle()
{}


inline tnbLib::STLtriangle::STLtriangle
(
	const STLpoint& normal,
	const STLpoint& a,
	const STLpoint& b,
	const STLpoint& c,
	unsigned short attrib
)
	:
	normal_(normal),
	a_(a),
	b_(b),
	c_(c),
	attrib_(attrib)
{}


inline tnbLib::STLtriangle::STLtriangle(istream& is)
{
	read(is);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const tnbLib::STLpoint& tnbLib::STLtriangle::normal() const
{
	return normal_;
}


inline const tnbLib::STLpoint& tnbLib::STLtriangle::a() const
{
	return a_;
}


inline const tnbLib::STLpoint& tnbLib::STLtriangle::b() const
{
	return b_;
}


inline const tnbLib::STLpoint& tnbLib::STLtriangle::c() const
{
	return c_;
}


inline unsigned short tnbLib::STLtriangle::attrib() const
{
	return attrib_;
}


inline void tnbLib::STLtriangle::read(istream& is)
{
	is.read(reinterpret_cast<char*>(this), 4 * sizeof(STLpoint));
	is.read(reinterpret_cast<char*>(&attrib_), sizeof(STLattrib));
}


inline void tnbLib::STLtriangle::write(ostream& os)
{
	os.write(reinterpret_cast<char*>(this), 4 * sizeof(STLpoint));
	os.write(reinterpret_cast<char*>(&attrib_), sizeof(STLattrib));
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

inline tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const STLtriangle& t)
{
	os << t.normal_ << token::SPACE
		<< t.a_ << token::SPACE
		<< t.b_ << token::SPACE
		<< t.c_ << token::SPACE
		<< t.attrib_;

	return os;
}


// ************************************************************************* //