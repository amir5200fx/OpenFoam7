#include <patchEdgeFaceRegion.hxx>

// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

FoamFvMesh_EXPORT tnbLib::Ostream& tnbLib::operator<<
(
	tnbLib::Ostream& os,
	const tnbLib::patchEdgeFaceRegion& wDist
	)
{
	return os << wDist.region_;
}


FoamFvMesh_EXPORT tnbLib::Istream& tnbLib::operator>>
(
	tnbLib::Istream& is,
	tnbLib::patchEdgeFaceRegion& wDist
	)
{
	return is >> wDist.region_;
}


// ************************************************************************* //