#include <arcUniform.hxx>

#include <meshSearch.hxx>
#include <polyMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <word.hxx>
#include <unitConversion.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace sampledSets
	{
		defineTypeNameAndDebug(arcUniform, 0);
		addToRunTimeSelectionTable(sampledSet, arcUniform, word);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::sampledSets::arcUniform::calcSamples
(
	DynamicList<point>& samplingPts,
	DynamicList<label>& samplingCells,
	DynamicList<label>& samplingFaces,
	DynamicList<label>& samplingSegments,
	DynamicList<scalar>& samplingCurveDist
) const
{
	const vector axis1 = radial_ - (radial_ & normal_)*normal_;
	const vector axis2 = normal_ ^ axis1;
	const scalar radius = mag(axis1);

	for (label i = 0; i < nPoints_; ++i)
	{
		const scalar t = scalar(i) / (nPoints_ - 1);
		const scalar theta = (1 - t)*startAngle_ + t * endAngle_;
		const scalar c = cos(theta), s = sin(theta);

		const point pt = centre_ + c * axis1 + s * axis2;
		const label celli = searchEngine().findCell(pt);

		if (celli != -1)
		{
			samplingPts.append(pt);
			samplingCells.append(celli);
			samplingFaces.append(-1);
			samplingSegments.append(samplingSegments.size());
			samplingCurveDist.append(radius*theta);
		}
	}
}


void tnbLib::sampledSets::arcUniform::genSamples()
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

tnbLib::sampledSets::arcUniform::arcUniform
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
	radial_(dict.lookupType<vector>("radial")),
	startAngle_(readScalar(dict.lookup("startAngle"))),
	endAngle_(readScalar(dict.lookup("endAngle"))),
	nPoints_(dict.lookupType<scalar>("nPoints"))
{
	genSamples();

	if (debug)
	{
		write(Info);
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::sampledSets::arcUniform::~arcUniform()
{}


// ************************************************************************* //