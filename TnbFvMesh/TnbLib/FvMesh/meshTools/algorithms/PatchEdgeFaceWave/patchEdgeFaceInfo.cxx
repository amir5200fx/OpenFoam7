#include <patchEdgeFaceInfo.hxx>

// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<
(
	tnbLib::Ostream& os,
	const tnbLib::patchEdgeFaceInfo& wDist
	)
{
	return os << wDist.origin() << wDist.distSqr();
}


tnbLib::Istream& tnbLib::operator>>
(
	tnbLib::Istream& is,
	tnbLib::patchEdgeFaceInfo& wDist
	)
{
	return is >> wDist.origin_ >> wDist.distSqr_;
}


// ************************************************************************* //