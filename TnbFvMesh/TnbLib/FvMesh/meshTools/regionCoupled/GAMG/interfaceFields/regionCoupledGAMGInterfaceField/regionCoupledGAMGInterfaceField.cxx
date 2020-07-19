#include <regionCoupledGAMGInterfaceField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <lduMatrix.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(regionCoupledGAMGInterfaceField, 0);
	addToRunTimeSelectionTable
	(
		GAMGInterfaceField,
		regionCoupledGAMGInterfaceField,
		lduInterface
	);
	addToRunTimeSelectionTable
	(
		GAMGInterfaceField,
		regionCoupledGAMGInterfaceField,
		lduInterfaceField
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::regionCoupledGAMGInterfaceField::regionCoupledGAMGInterfaceField
(
	const GAMGInterface& GAMGCp,
	const lduInterfaceField& fineInterface
)
	:
	GAMGInterfaceField(GAMGCp, fineInterface),
	regionCoupledGAMGInterface_
	(
		refCast<const regionCoupledGAMGInterface>(GAMGCp)
	)
{}


tnbLib::regionCoupledGAMGInterfaceField::regionCoupledGAMGInterfaceField
(
	const GAMGInterface& GAMGCp,
	const bool doTransform,
	const int rank
)
	:
	GAMGInterfaceField(GAMGCp, doTransform, rank),
	regionCoupledGAMGInterface_
	(
		refCast<const regionCoupledGAMGInterface>(GAMGCp)
	)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::regionCoupledGAMGInterfaceField::~regionCoupledGAMGInterfaceField()
{}


// ************************************************************************* //