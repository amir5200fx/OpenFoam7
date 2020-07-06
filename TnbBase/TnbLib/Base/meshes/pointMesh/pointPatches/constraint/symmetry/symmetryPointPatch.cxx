#include <symmetryPointPatch.hxx>

#include <pointConstraint.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(symmetryPointPatch, 0);

	// Add the patch constructor functions to the hash tables
	addToRunTimeSelectionTable
	(
		facePointPatch,
		symmetryPointPatch,
		polyPatch
	);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::symmetryPointPatch::applyConstraint
(
	const label pointi,
	pointConstraint& pc
) const
{
	pc.applyConstraint(pointNormals()[pointi]);
}


// ************************************************************************* //