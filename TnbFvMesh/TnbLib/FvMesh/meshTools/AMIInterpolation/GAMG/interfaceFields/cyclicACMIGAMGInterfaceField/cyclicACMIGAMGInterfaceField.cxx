#include <cyclicACMIGAMGInterfaceField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <lduMatrix.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(cyclicACMIGAMGInterfaceField, 0);
	addToRunTimeSelectionTable
	(
		GAMGInterfaceField,
		cyclicACMIGAMGInterfaceField,
		lduInterface
	);
	addToRunTimeSelectionTable
	(
		GAMGInterfaceField,
		cyclicACMIGAMGInterfaceField,
		lduInterfaceField
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::cyclicACMIGAMGInterfaceField::cyclicACMIGAMGInterfaceField
(
	const GAMGInterface& GAMGCp,
	const lduInterfaceField& fineInterface
)
	:
	cyclicAMIGAMGInterfaceField(GAMGCp, fineInterface)
{}


tnbLib::cyclicACMIGAMGInterfaceField::cyclicACMIGAMGInterfaceField
(
	const GAMGInterface& GAMGCp,
	const bool doTransform,
	const int rank
)
	:
	cyclicAMIGAMGInterfaceField(GAMGCp, doTransform, rank)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::cyclicACMIGAMGInterfaceField::~cyclicACMIGAMGInterfaceField()
{}


// ************************************************************************* //