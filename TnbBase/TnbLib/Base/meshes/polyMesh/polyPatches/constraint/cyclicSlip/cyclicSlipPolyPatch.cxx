#include <cyclicSlipPolyPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(cyclicSlipPolyPatch, 0);

	addToRunTimeSelectionTable(polyPatch, cyclicSlipPolyPatch, word);
	addToRunTimeSelectionTable(polyPatch, cyclicSlipPolyPatch, dictionary);
}


// ************************************************************************* //