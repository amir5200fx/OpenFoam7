#include <cellInfo.hxx>

// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(tnbLib::Ostream& os, const tnbLib::cellInfo& wDist)
{
	return os << wDist.type_;
}

tnbLib::Istream& tnbLib::operator>>(tnbLib::Istream& is, tnbLib::cellInfo& wDist)
{
	return is >> wDist.type_;
}

// ************************************************************************* //