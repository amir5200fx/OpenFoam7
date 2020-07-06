#include <processorCyclicGAMGInterfaceField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <lduMatrix.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(processorCyclicGAMGInterfaceField, 0);
	addToRunTimeSelectionTable
	(
		GAMGInterfaceField,
		processorCyclicGAMGInterfaceField,
		lduInterface
	);
	addToRunTimeSelectionTable
	(
		GAMGInterfaceField,
		processorCyclicGAMGInterfaceField,
		lduInterfaceField
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::processorCyclicGAMGInterfaceField::processorCyclicGAMGInterfaceField
(
	const GAMGInterface& GAMGCp,
	const lduInterfaceField& fineInterface
)
	:
	processorGAMGInterfaceField(GAMGCp, fineInterface)
{}


tnbLib::processorCyclicGAMGInterfaceField::processorCyclicGAMGInterfaceField
(
	const GAMGInterface& GAMGCp,
	const bool doTransform,
	const int rank
)
	:
	processorGAMGInterfaceField(GAMGCp, doTransform, rank)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::processorCyclicGAMGInterfaceField::~processorCyclicGAMGInterfaceField()
{}


// ************************************************************************* //