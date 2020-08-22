#include <externalPointEdgePoint.hxx>

// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<
(
	tnbLib::Ostream& os,
	const tnbLib::externalPointEdgePoint& wDist
	)
{
	return os << wDist.origin() << wDist.distSqr();
}


tnbLib::Istream& tnbLib::operator>>
(
	tnbLib::Istream& is,
	tnbLib::externalPointEdgePoint& wDist
	)
{
	return is >> wDist.origin_ >> wDist.distSqr_;
}


// ************************************************************************* //