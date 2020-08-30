#include <lineUniform.hxx>

#include <meshSearch.hxx>
#include <polyMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace sampledSets
	{
		defineTypeNameAndDebug(lineUniform, 0);
		addToRunTimeSelectionTable(sampledSet, lineUniform, word);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::sampledSets::lineUniform::calcSamples
(
	DynamicList<point>& samplingPts,
	DynamicList<label>& samplingCells,
	DynamicList<label>& samplingFaces,
	DynamicList<label>& samplingSegments,
	DynamicList<scalar>& samplingCurveDist
) const
{
	label sampleSegmentI = 0, sampleI = 0;
	scalar sampleT = 0;

	while (sampleI < nPoints_)
	{
		const point pt = (1 - sampleT)*start_ + sampleT * end_;

		const label sampleCellI = searchEngine().findCell(pt);

		if (sampleCellI == -1)
		{
			if (++sampleI < nPoints_)
			{
				sampleT = scalar(sampleI) / (nPoints_ - 1);
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
				samplingCurveDist.append(sampleT*mag(end_ - start_));

				if (++sampleI < nPoints_)
				{
					sampleT = scalar(sampleI) / (nPoints_ - 1);
					sampleParticle.track((end_ - start_) / (nPoints_ - 1), 0);
				}
			} while (sampleI < nPoints_ && !sampleParticle.onBoundaryFace());

			++sampleSegmentI;
		}
	}
}


void tnbLib::sampledSets::lineUniform::genSamples()
{
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

tnbLib::sampledSets::lineUniform::lineUniform
(
	const word& name,
	const polyMesh& mesh,
	const meshSearch& searchEngine,
	const dictionary& dict
)
	:
	sampledSet(name, mesh, searchEngine, dict),
	start_(dict.lookup("start")),
	end_(dict.lookup("end")),
	nPoints_(readLabel(dict.lookup("nPoints")))
{
	genSamples();

	if (debug)
	{
		write(Pout);
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::sampledSets::lineUniform::~lineUniform()
{}


// ************************************************************************* //