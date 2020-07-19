#include <nonuniformTransformCyclicFvPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	defineTypeNameAndDebug(nonuniformTransformCyclicFvPatch, 0);
	addToRunTimeSelectionTable
	(
		fvPatch,
		nonuniformTransformCyclicFvPatch,
		polyPatch
	);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //