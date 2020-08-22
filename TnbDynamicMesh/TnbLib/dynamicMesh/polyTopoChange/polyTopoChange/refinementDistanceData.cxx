#include <refinementDistanceData.hxx>

// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<
(
	tnbLib::Ostream& os,
	const tnbLib::refinementDistanceData& wDist
	)
{
	return os
		<< wDist.level0Size_ << token::SPACE << wDist.origin_
		<< token::SPACE << wDist.originLevel_;
}


tnbLib::Istream& tnbLib::operator>>
(
	tnbLib::Istream& is,
	tnbLib::refinementDistanceData& wDist
	)
{
	return is >> wDist.level0Size_ >> wDist.origin_ >> wDist.originLevel_;
}


// ************************************************************************* //