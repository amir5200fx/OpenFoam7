#include <cyclicRepeatAMIGAMGInterfaceField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <lduMatrix.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(cyclicRepeatAMIGAMGInterfaceField, 0);
	addToRunTimeSelectionTable
	(
		GAMGInterfaceField,
		cyclicRepeatAMIGAMGInterfaceField,
		lduInterface
	);
	addToRunTimeSelectionTable
	(
		GAMGInterfaceField,
		cyclicRepeatAMIGAMGInterfaceField,
		lduInterfaceField
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::cyclicRepeatAMIGAMGInterfaceField::cyclicRepeatAMIGAMGInterfaceField
(
	const GAMGInterface& GAMGCp,
	const lduInterfaceField& fineInterface
)
	:
	cyclicAMIGAMGInterfaceField(GAMGCp, fineInterface)
{}


tnbLib::cyclicRepeatAMIGAMGInterfaceField::cyclicRepeatAMIGAMGInterfaceField
(
	const GAMGInterface& GAMGCp,
	const bool doTransform,
	const int rank
)
	:
	cyclicAMIGAMGInterfaceField(GAMGCp, doTransform, rank)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::cyclicRepeatAMIGAMGInterfaceField::~cyclicRepeatAMIGAMGInterfaceField()
{}


// ************************************************************************* //