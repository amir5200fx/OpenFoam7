#include <cyclicACMIGAMGInterface.hxx>

#include <cyclicACMIGAMGInterface.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <Map.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(cyclicACMIGAMGInterface, 0);
	addToRunTimeSelectionTable
	(
		GAMGInterface,
		cyclicACMIGAMGInterface,
		lduInterface
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::cyclicACMIGAMGInterface::cyclicACMIGAMGInterface
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


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::cyclicACMIGAMGInterface::~cyclicACMIGAMGInterface()
{}


// ************************************************************************* //