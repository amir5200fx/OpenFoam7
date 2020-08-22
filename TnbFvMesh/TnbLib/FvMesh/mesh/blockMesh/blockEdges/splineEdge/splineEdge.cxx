#include <splineEdge.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace blockEdges
	{
		defineTypeNameAndDebug(splineEdge, 0);

		addToRunTimeSelectionTable
		(
			blockEdge,
			splineEdge,
			Istream
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::blockEdges::splineEdge::splineEdge
(
	const pointField& points,
	const label start,
	const label end,
	const pointField& internalPoints
)
	:
	blockEdge(points, start, end),
	CatmullRomSpline(appendEndPoints(points, start, end, internalPoints))
{}


tnbLib::blockEdges::splineEdge::splineEdge
(
	const dictionary& dict,
	const label index,
	const searchableSurfaces& geometry,
	const pointField& points,
	Istream& is
)
	:
	blockEdge(dict, index, points, is),
	CatmullRomSpline(appendEndPoints(points, start_, end_, pointField(is)))
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

tnbLib::blockEdges::splineEdge::~splineEdge()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::point tnbLib::blockEdges::splineEdge::position(const scalar mu) const
{
	return CatmullRomSpline::position(mu);
}


tnbLib::scalar tnbLib::blockEdges::splineEdge::length() const
{
	return CatmullRomSpline::length();
}


// ************************************************************************* //