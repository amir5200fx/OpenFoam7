#include <polyLineEdge.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace blockEdges
	{
		defineTypeNameAndDebug(polyLineEdge, 0);
		addToRunTimeSelectionTable(blockEdge, polyLineEdge, Istream);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::blockEdges::polyLineEdge::polyLineEdge
(
	const pointField& ps,
	const label start,
	const label end,
	const pointField& otherPoints
)
	:
	blockEdge(ps, start, end),
	polyLine(appendEndPoints(ps, start_, end_, otherPoints))
{}


tnbLib::blockEdges::polyLineEdge::polyLineEdge
(
	const dictionary& dict,
	const label index,
	const searchableSurfaces& geometry,
	const pointField& ps,
	Istream& is
)
	:
	blockEdge(dict, index, ps, is),
	polyLine(appendEndPoints(ps, start_, end_, pointField(is)))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::blockEdges::polyLineEdge::~polyLineEdge()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::point tnbLib::blockEdges::polyLineEdge::position(const scalar lambda) const
{
	return polyLine::position(lambda);
}


tnbLib::scalar tnbLib::blockEdges::polyLineEdge::length() const
{
	return polyLine::lineLength_;
}


// ************************************************************************* //