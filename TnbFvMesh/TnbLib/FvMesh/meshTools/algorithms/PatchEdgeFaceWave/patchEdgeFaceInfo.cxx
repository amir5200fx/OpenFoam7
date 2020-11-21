#include <patchEdgeFaceInfo.hxx>

// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

FoamFvMesh_EXPORT tnbLib::Ostream& tnbLib::operator<<
(
	tnbLib::Ostream& os,
	const tnbLib::patchEdgeFaceInfo& wDist
	)
{
	return os << wDist.origin() << wDist.distSqr();
}


FoamFvMesh_EXPORT tnbLib::Istream& tnbLib::operator>>
(
	tnbLib::Istream& is,
	tnbLib::patchEdgeFaceInfo& wDist
	)
{
	return is >> wDist.origin_ >> wDist.distSqr_;
}


// ************************************************************************* //