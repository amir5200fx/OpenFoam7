#include <cyclicRepeatAMIPointPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(cyclicRepeatAMIPointPatch, 0);
	addToRunTimeSelectionTable
	(
		facePointPatch,
		cyclicRepeatAMIPointPatch,
		polyPatch
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::cyclicRepeatAMIPointPatch::cyclicRepeatAMIPointPatch
(
	const polyPatch& patch,
	const pointBoundaryMesh& bm
)
	:
	cyclicAMIPointPatch(patch, bm)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::cyclicRepeatAMIPointPatch::~cyclicRepeatAMIPointPatch()
{}


// ************************************************************************* //