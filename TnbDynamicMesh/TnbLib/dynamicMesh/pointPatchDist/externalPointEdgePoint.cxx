#include <externalPointEdgePoint.hxx>

// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

FoamDynamicMesh_EXPORT tnbLib::Ostream& tnbLib::operator<<
(
	tnbLib::Ostream& os,
	const tnbLib::externalPointEdgePoint& wDist
	)
{
	return os << wDist.origin() << wDist.distSqr();
}


FoamDynamicMesh_EXPORT tnbLib::Istream& tnbLib::operator>>
(
	tnbLib::Istream& is,
	tnbLib::externalPointEdgePoint& wDist
	)
{
	return is >> wDist.origin_ >> wDist.distSqr_;
}


// ************************************************************************* //