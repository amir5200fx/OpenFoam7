#include <pointEdgeStructuredWalk.hxx>

// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<
(
	tnbLib::Ostream& os,
	const tnbLib::pointEdgeStructuredWalk& wDist
	)
{
	return os
		<< wDist.point0_ << wDist.previousPoint_
		<< wDist.dist_ << wDist.data_;
}

tnbLib::Istream& tnbLib::operator>>
(
	tnbLib::Istream& is,
	tnbLib::pointEdgeStructuredWalk& wDist
	)
{
	return is
		>> wDist.point0_ >> wDist.previousPoint_
		>> wDist.dist_ >> wDist.data_;
}


// ************************************************************************* //