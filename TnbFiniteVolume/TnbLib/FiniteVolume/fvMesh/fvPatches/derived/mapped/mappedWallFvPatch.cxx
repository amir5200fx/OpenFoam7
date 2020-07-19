#include <mappedWallFvPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(mappedWallFvPatch, 0);
	addToRunTimeSelectionTable(fvPatch, mappedWallFvPatch, polyPatch);
}

// ************************************************************************* //