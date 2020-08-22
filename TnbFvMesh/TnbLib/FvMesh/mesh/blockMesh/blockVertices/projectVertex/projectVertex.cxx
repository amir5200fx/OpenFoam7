#include <projectVertex.hxx>

#include <unitConversion.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <searchableSurfacesQueries.hxx>
#include <pointConstraint.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace blockVertices
	{
		defineTypeNameAndDebug(projectVertex, 0);
		addToRunTimeSelectionTable(blockVertex, projectVertex, Istream);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::blockVertices::projectVertex::projectVertex
(
	const dictionary& dict,
	const label index,
	const searchableSurfaces& geometry,
	Istream& is
)
	:
	pointVertex(dict, index, geometry, is),
	geometry_(geometry)
{
	wordList names(is);
	surfaces_.setSize(names.size());
	forAll(names, i)
	{
		surfaces_[i] = geometry_.findSurfaceID(names[i]);

		if (surfaces_[i] == -1)
		{
			FatalIOErrorInFunction(is)
				<< "Cannot find surface " << names[i] << " in geometry"
				<< exit(FatalIOError);
		}
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::blockVertices::projectVertex::operator tnbLib::point() const
{
	pointField start(1, pointVertex::operator point());

	pointField boundaryNear(start);
	List<pointConstraint> boundaryConstraint;


	// Note: how far do we need to search? Probably not further than
	//       span of surfaces themselves. Make sure to limit in case
	//       of e.g. searchablePlane which has infinite bb.
	boundBox bb(searchableSurfacesQueries::bounds(geometry_, surfaces_));
	bb.min() = max(bb.min(), point(-great, -great, -great));
	bb.max() = min(bb.max(), point(great, great, great));

	searchableSurfacesQueries::findNearest
	(
		geometry_,
		surfaces_,
		start,
		scalarField(start.size(), magSqr(bb.span())),
		boundaryNear,
		boundaryConstraint
	);

	return boundaryNear[0];
}


// ************************************************************************* //