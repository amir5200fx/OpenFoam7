#include <boxUniform.hxx>

#include <meshSearch.hxx>
#include <polyMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <word.hxx>
#include <transform.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace sampledSets
	{
		defineTypeNameAndDebug(boxUniform, 0);
		addToRunTimeSelectionTable(sampledSet, boxUniform, word);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::sampledSets::boxUniform::calcSamples
(
	DynamicList<point>& samplingPts,
	DynamicList<label>& samplingCells,
	DynamicList<label>& samplingFaces,
	DynamicList<label>& samplingSegments,
	DynamicList<scalar>& samplingCurveDist
) const
{
	for (label k = 0; k < nPoints_.z(); ++k)
	{
		for (label j = 0; j < nPoints_.y(); ++j)
		{
			for (label i = 0; i < nPoints_.x(); ++i)
			{
				const vector t =
					cmptDivide(vector(i, j, k), vector(nPoints_) - vector::one);

				const point pt =
					cmptMultiply(vector::one - t, box_.min())
					+ cmptMultiply(t, box_.max());

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
	}
}


void tnbLib::sampledSets::boxUniform::genSamples()
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

tnbLib::sampledSets::boxUniform::boxUniform
(
	const word& name,
	const polyMesh& mesh,
	const meshSearch& searchEngine,
	const dictionary& dict
)
	:
	sampledSet(name, mesh, searchEngine, dict),
	box_(dict.lookup("box")),
	nPoints_(dict.lookup("nPoints"))
{
	genSamples();

	if (debug)
	{
		write(Info);
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::sampledSets::boxUniform::~boxUniform()
{}


// ************************************************************************* //