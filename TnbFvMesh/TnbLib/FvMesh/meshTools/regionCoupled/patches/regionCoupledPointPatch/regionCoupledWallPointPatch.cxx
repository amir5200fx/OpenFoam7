#include <regionCoupledWallPointPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	defineTypeNameAndDebug(regionCoupledWallPointPatch, 0);
	addToRunTimeSelectionTable
	(
		facePointPatch,
		regionCoupledWallPointPatch,
		polyPatch
	);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib


// ************************************************************************* //