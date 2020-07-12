#include <cyclicACMIPointPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(cyclicACMIPointPatch, 0);
	addToRunTimeSelectionTable
	(
		facePointPatch,
		cyclicACMIPointPatch,
		polyPatch
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::cyclicACMIPointPatch::cyclicACMIPointPatch
(
	const polyPatch& patch,
	const pointBoundaryMesh& bm
)
	:
	cyclicAMIPointPatch(patch, bm)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::cyclicACMIPointPatch::~cyclicACMIPointPatch()
{}


// ************************************************************************* //