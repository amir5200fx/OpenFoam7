#include <processorCyclicGAMGInterface.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <Map.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(processorCyclicGAMGInterface, 0);
	addToRunTimeSelectionTable
	(
		GAMGInterface,
		processorCyclicGAMGInterface,
		lduInterface
	);
	addToRunTimeSelectionTable
	(
		GAMGInterface,
		processorCyclicGAMGInterface,
		Istream
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::processorCyclicGAMGInterface::processorCyclicGAMGInterface
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
	processorGAMGInterface
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


tnbLib::processorCyclicGAMGInterface::processorCyclicGAMGInterface
(
	const label index,
	const lduInterfacePtrsList& coarseInterfaces,
	Istream& is
)
	:
	processorGAMGInterface(index, coarseInterfaces, is)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::processorCyclicGAMGInterface::~processorCyclicGAMGInterface()
{}


// ************************************************************************* //