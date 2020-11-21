#include <pointTopoDistanceData.hxx>

#include <token.hxx>  // added by amir

// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

FoamFvMesh_EXPORT tnbLib::Ostream& tnbLib::operator<<
(
	tnbLib::Ostream& os,
	const tnbLib::pointTopoDistanceData& wDist
	)
{
	return os << wDist.data_ << token::SPACE << wDist.distance_;
}


FoamFvMesh_EXPORT tnbLib::Istream& tnbLib::operator>>
(
	tnbLib::Istream& is,
	tnbLib::pointTopoDistanceData& wDist
	)
{
	return is >> wDist.data_ >> wDist.distance_;
}


// ************************************************************************* //