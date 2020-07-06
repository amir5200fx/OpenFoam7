#include <pairGAMGAgglomeration.hxx>

#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(pairGAMGAgglomeration, 0);
	bool pairGAMGAgglomeration::forward_(true);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::pairGAMGAgglomeration::pairGAMGAgglomeration
(
	const lduMesh& mesh,
	const dictionary& controlDict
)
	:
	GAMGAgglomeration(mesh, controlDict),
	mergeLevels_(controlDict.lookupOrDefault<label>("mergeLevels", 1))
{}


// ************************************************************************* //