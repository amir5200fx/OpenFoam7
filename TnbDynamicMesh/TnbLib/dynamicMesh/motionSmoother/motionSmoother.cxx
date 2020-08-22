#include <motionSmoother.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(motionSmoother, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::motionSmoother::motionSmoother
(
	polyMesh& mesh,
	pointMesh& pMesh,
	indirectPrimitivePatch& pp,
	const labelList& adaptPatchIDs,
	const dictionary& paramDict
)
	:
	motionSmootherData(pMesh),
	motionSmootherAlgo
	(
		mesh,
		pMesh,
		pp,
		motionSmootherData::displacement_,
		motionSmootherData::scale_,
		motionSmootherData::oldPoints_,
		adaptPatchIDs,
		paramDict
	)
{}


tnbLib::motionSmoother::motionSmoother
(
	polyMesh& mesh,
	indirectPrimitivePatch& pp,
	const labelList& adaptPatchIDs,
	const pointVectorField& displacement,
	const dictionary& paramDict
)
	:
	motionSmootherData(displacement),
	motionSmootherAlgo
	(
		mesh,
		const_cast<pointMesh&>(displacement.mesh()),
		pp,
		motionSmootherData::displacement_,
		motionSmootherData::scale_,
		motionSmootherData::oldPoints_,
		adaptPatchIDs,
		paramDict
	)
{}


// ************************************************************************* //