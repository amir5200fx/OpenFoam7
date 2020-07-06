#include <genericPointPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(genericPointPatch, 0);

	// Add the patch constructor functions to the hash tables
	addToRunTimeSelectionTable
	(
		facePointPatch,
		genericPointPatch,
		polyPatch
	);
}


// ************************************************************************* //