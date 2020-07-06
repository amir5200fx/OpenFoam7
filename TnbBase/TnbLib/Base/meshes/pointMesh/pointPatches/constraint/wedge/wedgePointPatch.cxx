#include <wedgePointPatch.hxx>

#include <pointConstraint.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(wedgePointPatch, 0);

	// Add the patch constructor functions to the hash tables
	addToRunTimeSelectionTable
	(
		facePointPatch,
		wedgePointPatch,
		polyPatch
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::wedgePointPatch::wedgePointPatch
(
	const polyPatch& patch,
	const pointBoundaryMesh& bm
)
	:
	facePointPatch(patch, bm),
	wedgePolyPatch_(refCast<const wedgePolyPatch>(patch))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::wedgePointPatch::applyConstraint
(
	const label pointi,
	pointConstraint& pc
) const
{
	pc.applyConstraint(wedgePolyPatch_.n());
}


// ************************************************************************* //