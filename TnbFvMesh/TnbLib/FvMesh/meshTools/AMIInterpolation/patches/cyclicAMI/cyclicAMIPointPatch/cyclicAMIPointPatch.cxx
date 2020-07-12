#include <cyclicAMIPointPatch.hxx>

#include <pointMesh.hxx>
#include <Time.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(cyclicAMIPointPatch, 0);
	addToRunTimeSelectionTable
	(
		facePointPatch,
		cyclicAMIPointPatch,
		polyPatch
	);
}


// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

void tnbLib::cyclicAMIPointPatch::initGeometry(PstreamBuffers&)
{}


void tnbLib::cyclicAMIPointPatch::calcGeometry(PstreamBuffers&)
{}


void tnbLib::cyclicAMIPointPatch::initMovePoints
(
	PstreamBuffers&,
	const pointField&
)
{}


void tnbLib::cyclicAMIPointPatch::movePoints(PstreamBuffers&, const pointField&)
{}


void tnbLib::cyclicAMIPointPatch::initUpdateMesh(PstreamBuffers& pBufs)
{
	facePointPatch::initUpdateMesh(pBufs);
	//    cyclicAMIPointPatch::initGeometry(pBufs);
}


void tnbLib::cyclicAMIPointPatch::updateMesh(PstreamBuffers& pBufs)
{
	facePointPatch::updateMesh(pBufs);
	//    cyclicAMIPointPatch::calcGeometry(pBufs);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::cyclicAMIPointPatch::cyclicAMIPointPatch
(
	const polyPatch& patch,
	const pointBoundaryMesh& bm
)
	:
	coupledFacePointPatch(patch, bm),
	cyclicAMIPolyPatch_(refCast<const cyclicAMIPolyPatch>(patch))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::cyclicAMIPointPatch::~cyclicAMIPointPatch()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::cyclicAMIPointPatch::coupled() const
{
	return
		Pstream::parRun()
		|| !this->boundaryMesh().mesh().mesh().time().processorCase();
}


// ************************************************************************* //