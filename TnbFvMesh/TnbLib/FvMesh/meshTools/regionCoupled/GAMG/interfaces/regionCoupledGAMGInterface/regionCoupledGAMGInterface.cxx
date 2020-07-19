#include <regionCoupledGAMGInterface.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(regionCoupledGAMGInterface, 0);
	addToRunTimeSelectionTable
	(
		GAMGInterface,
		regionCoupledGAMGInterface,
		lduInterface
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::regionCoupledGAMGInterface::regionCoupledGAMGInterface
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
	regionCoupledBaseGAMGInterface
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

tnbLib::regionCoupledGAMGInterface::~regionCoupledGAMGInterface()
{}


// ************************************************************************* //