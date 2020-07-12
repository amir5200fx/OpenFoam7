#include <wallPoint.hxx>

// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(tnbLib::Ostream& os, const tnbLib::wallPoint& wDist)
{
	return os << wDist.origin() << token::SPACE << wDist.distSqr();
}

tnbLib::Istream& tnbLib::operator>>(tnbLib::Istream& is, tnbLib::wallPoint& wDist)
{
	return is >> wDist.origin() >> wDist.distSqr();
}

// ************************************************************************* //