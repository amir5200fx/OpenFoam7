#include <coupledFacePointPatch.hxx>

#include <pointBoundaryMesh.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(coupledFacePointPatch, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::coupledFacePointPatch::coupledFacePointPatch
(
	const polyPatch& patch,
	const pointBoundaryMesh& bm
)
	:
	facePointPatch(patch, bm),
	coupledPointPatch(bm),
	coupledPolyPatch_(refCast<const coupledPolyPatch>(patch))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::coupledFacePointPatch::~coupledFacePointPatch()
{}


// ************************************************************************* //