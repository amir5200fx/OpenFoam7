#include <regionCoupledWallGAMGInterface.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(regionCoupledWallGAMGInterface, 0);
	addToRunTimeSelectionTable
	(
		GAMGInterface,
		regionCoupledWallGAMGInterface,
		lduInterface
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::regionCoupledWallGAMGInterface::regionCoupledWallGAMGInterface
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

tnbLib::regionCoupledWallGAMGInterface::~regionCoupledWallGAMGInterface()
{}


// ************************************************************************* //