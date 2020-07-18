#include <genericFvPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(genericFvPatch, 0);
	addToRunTimeSelectionTable(fvPatch, genericFvPatch, polyPatch);
}

// ************************************************************************* //