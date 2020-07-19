#include <regionCoupledWallGAMGInterfaceField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <lduMatrix.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(regionCoupledWallGAMGInterfaceField, 0);
	addToRunTimeSelectionTable
	(
		GAMGInterfaceField,
		regionCoupledWallGAMGInterfaceField,
		lduInterface
	);
	addToRunTimeSelectionTable
	(
		GAMGInterfaceField,
		regionCoupledWallGAMGInterfaceField,
		lduInterfaceField
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::regionCoupledWallGAMGInterfaceField::regionCoupledWallGAMGInterfaceField
(
	const GAMGInterface& GAMGCp,
	const lduInterfaceField& fineInterface
)
	:
	GAMGInterfaceField(GAMGCp, fineInterface),
	regionCoupledGAMGInterface_
	(
		refCast<const regionCoupledWallGAMGInterface>(GAMGCp)
	)
{}


tnbLib::regionCoupledWallGAMGInterfaceField::regionCoupledWallGAMGInterfaceField
(
	const GAMGInterface& GAMGCp,
	const bool doTransform,
	const int rank
)
	:
	GAMGInterfaceField(GAMGCp, doTransform, rank),
	regionCoupledGAMGInterface_
	(
		refCast<const regionCoupledWallGAMGInterface>(GAMGCp)
	)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::regionCoupledWallGAMGInterfaceField::~regionCoupledWallGAMGInterfaceField
()
{}


// ************************************************************************* //