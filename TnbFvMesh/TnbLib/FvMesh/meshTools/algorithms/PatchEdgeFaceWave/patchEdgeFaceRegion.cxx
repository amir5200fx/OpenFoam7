#include <patchEdgeFaceRegion.hxx>

// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<
(
	tnbLib::Ostream& os,
	const tnbLib::patchEdgeFaceRegion& wDist
	)
{
	return os << wDist.region_;
}


tnbLib::Istream& tnbLib::operator>>
(
	tnbLib::Istream& is,
	tnbLib::patchEdgeFaceRegion& wDist
	)
{
	return is >> wDist.region_;
}


// ************************************************************************* //