#include <pointPatchDist.hxx>

#include <externalPointEdgePoint.hxx>
#include <pointMesh.hxx>
#include <PointEdgeWave.hxx>

#include <Time.hxx>  // added by amir
#include <globalMeshData.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::pointPatchDist::pointPatchDist
(
	const pointMesh& pMesh,
	const labelHashSet& patchIDs,
	const pointField& points
)
	:
	pointScalarField
	(
		IOobject
		(
			"pointDistance",
			pMesh.db().time().timeName(),
			pMesh.db()
		),
		pMesh,
		dimensionedScalar(dimLength, great)
	),
	points_(points),
	patchIDs_(patchIDs),
	nUnset_(0)
{
	correct();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::pointPatchDist::~pointPatchDist()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::pointPatchDist::correct()
{
	const pointBoundaryMesh& pbm = mesh().boundary();

	label nPoints = 0;

	forAllConstIter(labelHashSet, patchIDs_, iter)
	{
		label patchi = iter.key();
		nPoints += pbm[patchi].meshPoints().size();
	}

	externalPointEdgePoint::trackingData td(points_);

	// Set initial changed points to all the patch points(if patch present)
	List<externalPointEdgePoint> wallInfo(nPoints);
	labelList wallPoints(nPoints);
	nPoints = 0;

	forAllConstIter(labelHashSet, patchIDs_, iter)
	{
		label patchi = iter.key();
		// Retrieve the patch now we have its index in patches.

		const labelList& mp = pbm[patchi].meshPoints();

		forAll(mp, ppI)
		{
			label meshPointi = mp[ppI];
			wallPoints[nPoints] = meshPointi;
			wallInfo[nPoints] = externalPointEdgePoint
			(
				td.points_[meshPointi],
				0.0
			);
			nPoints++;
		}
	}

	// Current info on points
	List<externalPointEdgePoint> allPointInfo(mesh()().nPoints());

	// Current info on edges
	List<externalPointEdgePoint> allEdgeInfo(mesh()().nEdges());

	PointEdgeWave
		<
		externalPointEdgePoint,
		externalPointEdgePoint::trackingData
		> wallCalc
		(
			mesh()(),
			wallPoints,
			wallInfo,

			allPointInfo,
			allEdgeInfo,
			mesh().globalData().nTotalPoints(), // max iterations
			td
		);

	pointScalarField& psf = *this;


	forAll(allPointInfo, pointi)
	{
		if (allPointInfo[pointi].valid(td))
		{
			psf[pointi] = tnbLib::sqrt(allPointInfo[pointi].distSqr());
		}
		else
		{
			nUnset_++;
		}
	}
}


// ************************************************************************* //
