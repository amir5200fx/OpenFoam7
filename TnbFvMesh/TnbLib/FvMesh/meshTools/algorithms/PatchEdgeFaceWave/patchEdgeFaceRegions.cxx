#include <patchEdgeFaceRegions.hxx>

// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

FoamFvMesh_EXPORT tnbLib::Ostream& tnbLib::operator<<
(
	tnbLib::Ostream& os,
	const tnbLib::patchEdgeFaceRegions& wDist
	)
{
	return os << wDist.regions_;
}


FoamFvMesh_EXPORT tnbLib::Istream& tnbLib::operator>>
(
	tnbLib::Istream& is,
	tnbLib::patchEdgeFaceRegions& wDist
	)
{
	return is >> wDist.regions_;
}


// ************************************************************************* //