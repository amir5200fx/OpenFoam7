#include <lineEdge.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace blockEdges
	{
		defineTypeNameAndDebug(lineEdge, 0);
		addToRunTimeSelectionTable(blockEdge, lineEdge, Istream);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::blockEdges::lineEdge::lineEdge
(
	const pointField& points,
	const label start,
	const label end
)
	:
	blockEdge(points, start, end)
{}


tnbLib::blockEdges::lineEdge::lineEdge
(
	const dictionary& dict,
	const label index,
	const searchableSurfaces& geometry,
	const pointField& points,
	Istream& is
)
	:
	blockEdge(dict, index, points, is)
{}


// * * * * * * * * * * * * * * * * Destructor * * * * * * * * * * * * * * * * //

tnbLib::blockEdges::lineEdge::~lineEdge()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::point tnbLib::blockEdges::lineEdge::position(const scalar lambda) const
{
	if (lambda < -small || lambda > 1 + small)
	{
		FatalErrorInFunction
			<< "Parameter out of range, lambda = " << lambda
			<< abort(FatalError);
	}

	return points_[start_] + lambda * (points_[end_] - points_[start_]);
}


tnbLib::scalar tnbLib::blockEdges::lineEdge::length() const
{
	return mag(points_[end_] - points_[start_]);
}


// ************************************************************************* //