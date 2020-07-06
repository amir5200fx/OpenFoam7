#include <emptyPointPatch.hxx>

#include <pointConstraint.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(emptyPointPatch, 0);
	addToRunTimeSelectionTable
	(
		facePointPatch,
		emptyPointPatch,
		polyPatch
	);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::emptyPointPatch::applyConstraint
(
	const label pointi,
	pointConstraint& pc
) const
{
	pc.applyConstraint(pointNormals()[pointi]);
}


// ************************************************************************* //