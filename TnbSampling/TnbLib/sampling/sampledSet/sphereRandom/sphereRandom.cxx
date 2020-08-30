#include <sphereRandom.hxx>

#include <sampledSet.hxx>
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
		defineTypeNameAndDebug(sphereRandom, 0);
		addToRunTimeSelectionTable(sampledSet, sphereRandom, word);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::sampledSets::sphereRandom::calcSamples
(
	DynamicList<point>& samplingPts,
	DynamicList<label>& samplingCells,
	DynamicList<label>& samplingFaces,
	DynamicList<label>& samplingSegments,
	DynamicList<scalar>& samplingCurveDist
) const
{
	Random rndGen(261782);

	for (label i = 0; i < nPoints_; ++i)
	{
		// Request all random numbers simultaneously on all processors so that
		// the generator state stays consistent

		vector dpt(vector::uniform(radius_));
		while (magSqr(dpt) > sqr(radius_))
		{
			dpt = 2 * radius_*(rndGen.sample01<vector>() - vector::uniform(0.5));
		}

		const point pt = centre_ + dpt;
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


void tnbLib::sampledSets::sphereRandom::genSamples()
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

tnbLib::sampledSets::sphereRandom::sphereRandom
(
	const word& name,
	const polyMesh& mesh,
	const meshSearch& searchEngine,
	const dictionary& dict
)
	:
	sampledSet(name, mesh, searchEngine, dict),
	centre_(dict.lookup("centre")),
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

tnbLib::sampledSets::sphereRandom::~sphereRandom()
{}


// ************************************************************************* //