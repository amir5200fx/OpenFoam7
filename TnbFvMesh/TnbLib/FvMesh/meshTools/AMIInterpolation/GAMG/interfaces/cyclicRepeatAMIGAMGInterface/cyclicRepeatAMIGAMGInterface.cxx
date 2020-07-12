#include <cyclicRepeatAMIGAMGInterface.hxx>

#include <AMIInterpolation.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <Map.hxx>


// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(cyclicRepeatAMIGAMGInterface, 0);
	addToRunTimeSelectionTable
	(
		GAMGInterface,
		cyclicRepeatAMIGAMGInterface,
		lduInterface
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::cyclicRepeatAMIGAMGInterface::cyclicRepeatAMIGAMGInterface
(
	const label index,
	const lduInterfacePtrsList& coarseInterfaces,
	const lduInterface& fineInterface,
	const labelField& localRestrictAddressing,
	const labelField& neighbourRestrictAddressing,
	const label fineLevelIndex,
	const label coarseComm
)
	:
	cyclicAMIGAMGInterface
	(
		index,
		coarseInterfaces,
		fineInterface,
		localRestrictAddressing,
		neighbourRestrictAddressing,
		fineLevelIndex,
		coarseComm
	)
{}


// * * * * * * * * * * * * * * * * Destructor * * * * * * * * * * * * * * * //

tnbLib::cyclicRepeatAMIGAMGInterface::~cyclicRepeatAMIGAMGInterface()
{}


// ************************************************************************* //