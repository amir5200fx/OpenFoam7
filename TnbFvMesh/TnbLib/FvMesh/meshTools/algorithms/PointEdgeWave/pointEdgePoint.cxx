#include <pointEdgePoint.hxx>

// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<
(
	tnbLib::Ostream& os,
	const tnbLib::pointEdgePoint& wDist
	)
{
	return os << wDist.origin() << wDist.distSqr();
}


tnbLib::Istream& tnbLib::operator>>(tnbLib::Istream& is, tnbLib::pointEdgePoint& wDist)
{
	return is >> wDist.origin_ >> wDist.distSqr_;
}


// ************************************************************************* //