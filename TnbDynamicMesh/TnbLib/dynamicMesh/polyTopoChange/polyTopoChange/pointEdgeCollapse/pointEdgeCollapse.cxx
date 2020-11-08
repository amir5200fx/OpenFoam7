#include <pointEdgeCollapse.hxx>

// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

FoamDynamicMesh_EXPORT tnbLib::Ostream& tnbLib::operator<<
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

FoamDynamicMesh_EXPORT tnbLib::Istream& tnbLib::operator>>
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