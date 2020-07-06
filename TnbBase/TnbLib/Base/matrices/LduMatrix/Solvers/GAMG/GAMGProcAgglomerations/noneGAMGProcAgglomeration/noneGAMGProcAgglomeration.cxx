#include <noneGAMGProcAgglomeration.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <GAMGAgglomeration.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(noneGAMGProcAgglomeration, 0);

	addNamedToRunTimeSelectionTable
	(
		GAMGProcAgglomeration,
		noneGAMGProcAgglomeration,
		GAMGAgglomeration,
		none
	);
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::noneGAMGProcAgglomeration::noneGAMGProcAgglomeration
(
	GAMGAgglomeration& agglom,
	const dictionary& controlDict
)
	:
	GAMGProcAgglomeration(agglom, controlDict)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::noneGAMGProcAgglomeration::~noneGAMGProcAgglomeration()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //


// ************************************************************************* //