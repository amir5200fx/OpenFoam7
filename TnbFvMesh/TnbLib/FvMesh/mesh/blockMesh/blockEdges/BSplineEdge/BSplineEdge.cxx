#include <BSplineEdge.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace blockEdges
	{
		defineTypeNameAndDebug(BSplineEdge, 0);

		addToRunTimeSelectionTable
		(
			blockEdge,
			BSplineEdge,
			Istream
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::blockEdges::BSplineEdge::BSplineEdge
(
	const pointField& points,
	const label start,
	const label end,
	const pointField& internalPoints
)
	:
	blockEdge(points, start, end),
	BSpline(appendEndPoints(points, start, end, internalPoints))
{}


tnbLib::blockEdges::BSplineEdge::BSplineEdge
(
	const dictionary& dict,
	const label index,
	const searchableSurfaces& geometry,
	const pointField& points,
	Istream& is
)
	:
	blockEdge(dict, index, points, is),
	BSpline(appendEndPoints(points, start_, end_, pointField(is)))
{
	token t(is);
	is.putBack(t);

	// discard unused start/end tangents
	if (t == token::BEGIN_LIST)
	{
		vector tangent0Ignored(is);
		vector tangent1Ignored(is);
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::blockEdges::BSplineEdge::~BSplineEdge()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::point tnbLib::blockEdges::BSplineEdge::position(const scalar mu) const
{
	return BSpline::position(mu);
}


tnbLib::scalar tnbLib::blockEdges::BSplineEdge::length() const
{
	return BSpline::length();
}


// ************************************************************************* //