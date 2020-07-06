#include <processorPointPatch.hxx>

#include <pointBoundaryMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <pointMesh.hxx>
#include <faceList.hxx>
#include <primitiveFacePatch.hxx>
#include <emptyPolyPatch.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(processorPointPatch, 0);
	addToRunTimeSelectionTable
	(
		facePointPatch,
		processorPointPatch,
		polyPatch
	);
}


// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

void tnbLib::processorPointPatch::initGeometry(PstreamBuffers& pBufs)
{
	// Algorithm:
	// Depending on whether the patch is a master or a slave, get the primitive
	// patch points and filter away the points from the global patch.

	// Create the reversed patch and pick up its points
	// so that the order is correct
	const polyPatch& pp = patch();

	faceList masterFaces(pp.size());

	forAll(pp, facei)
	{
		masterFaces[facei] = pp[facei].reverseFace();
	}

	reverseMeshPoints_ = primitiveFacePatch
	(
		masterFaces,
		pp.points()
	).meshPoints();
}


void tnbLib::processorPointPatch::calcGeometry(PstreamBuffers& pBufs)
{}


void tnbLib::processorPointPatch::initMovePoints
(
	PstreamBuffers&,
	const pointField&
)
{}


void tnbLib::processorPointPatch::movePoints(PstreamBuffers&, const pointField&)
{}


void tnbLib::processorPointPatch::initUpdateMesh(PstreamBuffers& pBufs)
{
	facePointPatch::initUpdateMesh(pBufs);
	processorPointPatch::initGeometry(pBufs);
}


void tnbLib::processorPointPatch::updateMesh(PstreamBuffers& pBufs)
{
	facePointPatch::updateMesh(pBufs);
	processorPointPatch::calcGeometry(pBufs);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::processorPointPatch::processorPointPatch
(
	const polyPatch& patch,
	const pointBoundaryMesh& bm
)
	:
	coupledFacePointPatch(patch, bm),
	procPolyPatch_(refCast<const processorPolyPatch>(patch))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::processorPointPatch::~processorPointPatch()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::labelList& tnbLib::processorPointPatch::reverseMeshPoints() const
{
	return reverseMeshPoints_;
}


// ************************************************************************* //