#include <cyclicPointPatch.hxx>

#include <pointBoundaryMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <pointMesh.hxx>
#include <edgeList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(cyclicPointPatch, 0);
	addToRunTimeSelectionTable
	(
		facePointPatch,
		cyclicPointPatch,
		polyPatch
	);
}

// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

void tnbLib::cyclicPointPatch::initGeometry(PstreamBuffers&)
{}


void tnbLib::cyclicPointPatch::calcGeometry(PstreamBuffers&)
{}


void tnbLib::cyclicPointPatch::initMovePoints(PstreamBuffers&, const pointField&)
{}


void tnbLib::cyclicPointPatch::movePoints(PstreamBuffers&, const pointField&)
{}


void tnbLib::cyclicPointPatch::initUpdateMesh(PstreamBuffers& pBufs)
{
	facePointPatch::initUpdateMesh(pBufs);
	cyclicPointPatch::initGeometry(pBufs);
}


void tnbLib::cyclicPointPatch::updateMesh(PstreamBuffers& pBufs)
{
	facePointPatch::updateMesh(pBufs);
	cyclicPointPatch::calcGeometry(pBufs);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::cyclicPointPatch::cyclicPointPatch
(
	const polyPatch& patch,
	const pointBoundaryMesh& bm
)
	:
	coupledFacePointPatch(patch, bm),
	cyclicPolyPatch_(refCast<const cyclicPolyPatch>(patch))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::cyclicPointPatch::~cyclicPointPatch()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::edgeList& tnbLib::cyclicPointPatch::transformPairs() const
{
	return cyclicPolyPatch_.coupledPoints();
}


// ************************************************************************* //