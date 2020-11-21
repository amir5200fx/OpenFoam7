#include <cellInfo.hxx>

// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

FoamFvMesh_EXPORT tnbLib::Ostream& tnbLib::operator<<(tnbLib::Ostream& os, const tnbLib::cellInfo& wDist)
{
	return os << wDist.type_;
}

FoamFvMesh_EXPORT tnbLib::Istream& tnbLib::operator>>(tnbLib::Istream& is, tnbLib::cellInfo& wDist)
{
	return is >> wDist.type_;
}

// ************************************************************************* //