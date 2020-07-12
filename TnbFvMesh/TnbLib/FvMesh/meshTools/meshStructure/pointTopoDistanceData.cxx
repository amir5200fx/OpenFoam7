#include <pointTopoDistanceData.hxx>

#include <token.hxx>  // added by amir

// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<
(
	tnbLib::Ostream& os,
	const tnbLib::pointTopoDistanceData& wDist
	)
{
	return os << wDist.data_ << token::SPACE << wDist.distance_;
}


tnbLib::Istream& tnbLib::operator>>
(
	tnbLib::Istream& is,
	tnbLib::pointTopoDistanceData& wDist
	)
{
	return is >> wDist.data_ >> wDist.distance_;
}


// ************************************************************************* //