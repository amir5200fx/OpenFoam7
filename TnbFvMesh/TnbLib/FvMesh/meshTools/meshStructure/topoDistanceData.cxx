#include <topoDistanceData.hxx>

#include <token.hxx>  // added by amir

// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

FoamFvMesh_EXPORT tnbLib::Ostream& tnbLib::operator<<
(
	tnbLib::Ostream& os,
	const tnbLib::topoDistanceData& wDist
	)
{
	return os << wDist.data_ << token::SPACE << wDist.distance_;
}


FoamFvMesh_EXPORT tnbLib::Istream& tnbLib::operator>>
(
	tnbLib::Istream& is,
	tnbLib::topoDistanceData& wDist
	)
{
	return is >> wDist.data_ >> wDist.distance_;
}


// ************************************************************************* //