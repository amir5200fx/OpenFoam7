#include <regionCoupledPointPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	defineTypeNameAndDebug(regionCoupledPointPatch, 0);
	addToRunTimeSelectionTable
	(
		facePointPatch,
		regionCoupledPointPatch,
		polyPatch
	);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib


// ************************************************************************* //