#include <nonuniformTransformCyclicPolyPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(nonuniformTransformCyclicPolyPatch, 0);

	addToRunTimeSelectionTable
	(
		polyPatch,
		nonuniformTransformCyclicPolyPatch,
		word
	);
	addToRunTimeSelectionTable
	(
		polyPatch,
		nonuniformTransformCyclicPolyPatch,
		dictionary
	);
}


// ************************************************************************* //