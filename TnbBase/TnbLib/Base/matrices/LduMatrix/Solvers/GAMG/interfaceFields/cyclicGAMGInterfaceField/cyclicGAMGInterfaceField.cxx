#include <cyclicGAMGInterfaceField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <lduMatrix.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(cyclicGAMGInterfaceField, 0);
	addToRunTimeSelectionTable
	(
		GAMGInterfaceField,
		cyclicGAMGInterfaceField,
		lduInterface
	);
	addToRunTimeSelectionTable
	(
		GAMGInterfaceField,
		cyclicGAMGInterfaceField,
		lduInterfaceField
	);

	// Add under name cyclicSlip
	addNamedToRunTimeSelectionTable
	(
		GAMGInterfaceField,
		cyclicGAMGInterfaceField,
		lduInterface,
		cyclicSlip
	);
	addNamedToRunTimeSelectionTable
	(
		GAMGInterfaceField,
		cyclicGAMGInterfaceField,
		lduInterfaceField,
		cyclicSlip
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::cyclicGAMGInterfaceField::cyclicGAMGInterfaceField
(
	const GAMGInterface& GAMGCp,
	const lduInterfaceField& fineInterface
)
	:
	GAMGInterfaceField(GAMGCp, fineInterface),
	cyclicInterface_(refCast<const cyclicGAMGInterface>(GAMGCp)),
	doTransform_(false),
	rank_(0)
{
	const cyclicLduInterfaceField& p =
		refCast<const cyclicLduInterfaceField>(fineInterface);

	doTransform_ = p.doTransform();
	rank_ = p.rank();
}


tnbLib::cyclicGAMGInterfaceField::cyclicGAMGInterfaceField
(
	const GAMGInterface& GAMGCp,
	const bool doTransform,
	const int rank
)
	:
	GAMGInterfaceField(GAMGCp, doTransform, rank),
	cyclicInterface_(refCast<const cyclicGAMGInterface>(GAMGCp)),
	doTransform_(doTransform),
	rank_(rank)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::cyclicGAMGInterfaceField::~cyclicGAMGInterfaceField()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::cyclicGAMGInterfaceField::updateInterfaceMatrix
(
	scalarField& result,
	const scalarField& psiInternal,
	const scalarField& coeffs,
	const direction cmpt,
	const Pstream::commsTypes
) const
{
	// Get neighbouring field
	scalarField pnf
	(
		cyclicInterface_.neighbPatch().interfaceInternalField(psiInternal)
	);

	transformCoupleField(pnf, cmpt);

	const labelUList& faceCells = cyclicInterface_.faceCells();

	forAll(faceCells, elemI)
	{
		result[faceCells[elemI]] -= coeffs[elemI] * pnf[elemI];
	}
}


// ************************************************************************* //