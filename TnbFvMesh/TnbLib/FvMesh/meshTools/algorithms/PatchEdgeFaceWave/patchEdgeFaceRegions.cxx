#include <patchEdgeFaceRegions.hxx>

// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<
(
	tnbLib::Ostream& os,
	const tnbLib::patchEdgeFaceRegions& wDist
	)
{
	return os << wDist.regions_;
}


tnbLib::Istream& tnbLib::operator>>
(
	tnbLib::Istream& is,
	tnbLib::patchEdgeFaceRegions& wDist
	)
{
	return is >> wDist.regions_;
}


// ************************************************************************* //