#include <points.hxx>

#include <meshSearch.hxx>
#include <polyMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace sampledSets
	{
		defineTypeNameAndDebug(points, 0);
		addToRunTimeSelectionTable(sampledSet, points, word);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::sampledSets::points::calcSamplesUnordered
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
			samplingSegments.append(samplingSegments.size());
			samplingCurveDist.append(scalar(i));
		}
	}
}

void tnbLib::sampledSets::points::calcSamplesOrdered
(
	DynamicList<point>& samplingPts,
	DynamicList<label>& samplingCells,
	DynamicList<label>& samplingFaces,
	DynamicList<label>& samplingSegments,
	DynamicList<scalar>& samplingCurveDist
) const
{
	const label n = points_.size();

	label sampleSegmentI = 0;
	label sampleI = 0;
	scalar sampleDist = 0;

	while (sampleI < n)
	{
		const point pt = points_[sampleI];

		const label sampleCellI = searchEngine().findCell(pt);

		if (sampleCellI == -1)
		{
			if (++sampleI < n)
			{
				sampleDist += mag(points_[sampleI] - points_[sampleI - 1]);
			}
		}
		else
		{
			passiveParticle sampleParticle(mesh(), pt, sampleCellI);

			do
			{
				samplingPts.append(sampleParticle.position());
				samplingCells.append(sampleParticle.cell());
				samplingFaces.append(-1);
				samplingSegments.append(sampleSegmentI);
				samplingCurveDist.append(sampleDist);

				if (++sampleI < n)
				{
					const vector s = points_[sampleI] - points_[sampleI - 1];
					sampleDist += mag(s);
					sampleParticle.track(s, 0);
				}
			} while (sampleI < n && !sampleParticle.onBoundaryFace());

			++sampleSegmentI;
		}
	}
}


void tnbLib::sampledSets::points::genSamples()
{
	DynamicList<point> samplingPts;
	DynamicList<label> samplingCells;
	DynamicList<label> samplingFaces;
	DynamicList<label> samplingSegments;
	DynamicList<scalar> samplingCurveDist;

	if (!ordered_)
	{
		calcSamplesUnordered
		(
			samplingPts,
			samplingCells,
			samplingFaces,
			samplingSegments,
			samplingCurveDist
		);
	}
	else
	{
		calcSamplesOrdered
		(
			samplingPts,
			samplingCells,
			samplingFaces,
			samplingSegments,
			samplingCurveDist
		);
	}

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

tnbLib::sampledSets::points::points
(
	const word& name,
	const polyMesh& mesh,
	const meshSearch& searchEngine,
	const dictionary& dict
)
	:
	sampledSet(name, mesh, searchEngine, dict),
	points_(dict.lookup("points")),
	ordered_(dict.lookup("ordered"))
{
	genSamples();

	if (debug)
	{
		write(Info);
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::sampledSets::points::~points()
{}


// ************************************************************************* //