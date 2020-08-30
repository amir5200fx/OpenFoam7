#include <triSurfaceMeshSampledSet.hxx>

#include <meshSearch.hxx>
#include <polyMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <triSurfaceMesh.hxx>
#include <Time.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace sampledSets
	{
		defineTypeNameAndDebug(triSurfaceMeshSampledSet, 0);
		addToRunTimeSelectionTable(sampledSet, triSurfaceMeshSampledSet, word);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::sampledSets::triSurfaceMeshSampledSet::calcSamples
(
	DynamicList<point>& samplingPts,
	DynamicList<label>& samplingCells,
	DynamicList<label>& samplingFaces,
	DynamicList<label>& samplingSegments,
	DynamicList<scalar>& samplingCurveDist
) const
{
	forAll(points_, i)
	{
		const point& pt = points_[i];
		const label celli = searchEngine().findCell(pt);

		if (celli != -1)
		{
			samplingPts.append(pt);
			samplingCells.append(celli);
			samplingFaces.append(-1);
			samplingSegments.append(0);
			samplingCurveDist.append(scalar(i));
		}
	}
}


void tnbLib::sampledSets::triSurfaceMeshSampledSet::genSamples()
{
	// Storage for sample points
	DynamicList<point> samplingPts;
	DynamicList<label> samplingCells;
	DynamicList<label> samplingFaces;
	DynamicList<label> samplingSegments;
	DynamicList<scalar> samplingCurveDist;

	calcSamples
	(
		samplingPts,
		samplingCells,
		samplingFaces,
		samplingSegments,
		samplingCurveDist
	);

	samplingPts.shrink();
	samplingCells.shrink();
	samplingFaces.shrink();
	samplingSegments.shrink();
	samplingCurveDist.shrink();

	setSamples
	(
		samplingPts,
		samplingCells,
		samplingFaces,
		samplingSegments,
		samplingCurveDist
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::sampledSets::triSurfaceMeshSampledSet::triSurfaceMeshSampledSet
(
	const word& name,
	const polyMesh& mesh,
	const meshSearch& searchEngine,
	const dictionary& dict
)
	:
	sampledSet(name, mesh, searchEngine, dict),
	surface_(dict.lookup("surface")),
	points_
	(
		mesh.time().foundObject<triSurfaceMesh>(surface_)
		? mesh.time().lookupObject<triSurfaceMesh>(surface_).points()
		: triSurfaceMesh
		(
			IOobject
			(
				surface_,
				mesh.time().constant(),
				"triSurface",
				mesh.time(),
				IOobject::MUST_READ,
				IOobject::NO_WRITE,
				false
			)
		).points()
	)
{
	genSamples();

	if (debug)
	{
		write(Info);
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::sampledSets::triSurfaceMeshSampledSet::~triSurfaceMeshSampledSet()
{}


// ************************************************************************* //