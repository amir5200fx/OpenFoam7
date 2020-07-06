#include <symmetryPlanePointPatch.hxx>

#include <pointConstraint.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(symmetryPlanePointPatch, 0);

	// Add the patch constructor functions to the hash tables
	addToRunTimeSelectionTable
	(
		facePointPatch,
		symmetryPlanePointPatch,
		polyPatch
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::symmetryPlanePointPatch::symmetryPlanePointPatch
(
	const polyPatch& patch,
	const pointBoundaryMesh& bm
)
	:
	facePointPatch(patch, bm),
	symmetryPlanePolyPatch_(refCast<const symmetryPlanePolyPatch>(patch))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::symmetryPlanePointPatch::applyConstraint
(
	const label,
	pointConstraint& pc
) const
{
	pc.applyConstraint(symmetryPlanePolyPatch_.n());
}


// ************************************************************************* //