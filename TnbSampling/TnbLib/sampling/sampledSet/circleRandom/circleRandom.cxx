#include <circleRandom.hxx>

#include <meshSearch.hxx>
#include <polyMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <word.hxx>
#include <mathematicalConstants.hxx>
#include <Random.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace sampledSets
	{
		defineTypeNameAndDebug(circleRandom, 0);
		addToRunTimeSelectionTable(sampledSet, circleRandom, word);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::sampledSets::circleRandom::calcSamples
(
	DynamicList<point>& samplingPts,
	DynamicList<label>& samplingCells,
	DynamicList<label>& samplingFaces,
	DynamicList<label>& samplingSegments,
	DynamicList<scalar>& samplingCurveDist
) const
{
	Random rndGen(261782);

	const vector radial1 = normalised(perpendicular(normal_));
	const vector radial2 = normalised(normal_ ^ radial1);

	for (label i = 0; i < nPoints_; ++i)
	{
		// Request all random numbers simultaneously on all processors so that
		// the generator state stays consistent

		const scalar r = radius_ * rndGen.scalar01();
		const scalar theta = 2 * constant::mathematical::pi*rndGen.scalar01();
		const scalar c = cos(theta), s = sin(theta);

		const point pt = centre_ + r * (c*radial1 + s * radial2);
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


void tnbLib::sampledSets::circleRandom::genSamples()
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

tnbLib::sampledSets::circleRandom::circleRandom
(
	const word& name,
	const polyMesh& mesh,
	const meshSearch& searchEngine,
	const dictionary& dict
)
	:
	sampledSet(name, mesh, searchEngine, dict),
	centre_(dict.lookup("centre")),
	normal_(normalised(dict.lookupType<vector>("normal"))),
	radius_(readScalar(dict.lookup("radius"))),
	nPoints_(readLabel(dict.lookup("nPoints")))
{
	genSamples();

	if (debug)
	{
		write(Info);
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::sampledSets::circleRandom::~circleRandom()
{}


// ************************************************************************* //