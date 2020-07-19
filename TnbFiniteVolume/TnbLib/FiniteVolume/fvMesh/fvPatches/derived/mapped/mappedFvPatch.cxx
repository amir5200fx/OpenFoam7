#include <mappedFvPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(mappedFvPatch, 0);
	addToRunTimeSelectionTable(fvPatch, mappedFvPatch, polyPatch);
}

// ************************************************************************* //