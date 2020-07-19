#include <processorCyclicFvPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <transformField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	defineTypeNameAndDebug(processorCyclicFvPatch, 0);
	addToRunTimeSelectionTable(fvPatch, processorCyclicFvPatch, polyPatch);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //