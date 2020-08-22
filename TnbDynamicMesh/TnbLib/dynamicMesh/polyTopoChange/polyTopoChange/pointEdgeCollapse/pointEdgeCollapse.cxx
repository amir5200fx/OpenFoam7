#include <pointEdgeCollapse.hxx>

// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<
(
	tnbLib::Ostream& os,
	const tnbLib::pointEdgeCollapse& wDist
	)
{
	return os
		<< wDist.collapsePoint_
		<< wDist.collapseIndex_
		<< wDist.collapsePriority_;
}

tnbLib::Istream& tnbLib::operator>>
(
	tnbLib::Istream& is,
	tnbLib::pointEdgeCollapse& wDist
	)
{
	return is
		>> wDist.collapsePoint_
		>> wDist.collapseIndex_
		>> wDist.collapsePriority_;
}


// ************************************************************************* //