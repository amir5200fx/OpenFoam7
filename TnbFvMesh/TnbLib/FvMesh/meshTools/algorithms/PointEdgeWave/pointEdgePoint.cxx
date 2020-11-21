#include <pointEdgePoint.hxx>

// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

FoamFvMesh_EXPORT tnbLib::Ostream& tnbLib::operator<<
(
	tnbLib::Ostream& os,
	const tnbLib::pointEdgePoint& wDist
	)
{
	return os << wDist.origin() << wDist.distSqr();
}


FoamFvMesh_EXPORT tnbLib::Istream& tnbLib::operator>>(tnbLib::Istream& is, tnbLib::pointEdgePoint& wDist)
{
	return is >> wDist.origin_ >> wDist.distSqr_;
}


// ************************************************************************* //