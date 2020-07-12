#include <cyclicAMIGAMGInterfaceField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <lduMatrix.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(cyclicAMIGAMGInterfaceField, 0);
	addToRunTimeSelectionTable
	(
		GAMGInterfaceField,
		cyclicAMIGAMGInterfaceField,
		lduInterface
	);
	addToRunTimeSelectionTable
	(
		GAMGInterfaceField,
		cyclicAMIGAMGInterfaceField,
		lduInterfaceField
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::cyclicAMIGAMGInterfaceField::cyclicAMIGAMGInterfaceField
(
	const GAMGInterface& GAMGCp,
	const lduInterfaceField& fineInterface
)
	:
	GAMGInterfaceField(GAMGCp, fineInterface),
	cyclicAMIInterface_(refCast<const cyclicAMIGAMGInterface>(GAMGCp)),
	doTransform_(false),
	rank_(0)
{
	const cyclicAMILduInterfaceField& p =
		refCast<const cyclicAMILduInterfaceField>(fineInterface);

	doTransform_ = p.doTransform();
	rank_ = p.rank();
}


tnbLib::cyclicAMIGAMGInterfaceField::cyclicAMIGAMGInterfaceField
(
	const GAMGInterface& GAMGCp,
	const bool doTransform,
	const int rank
)
	:
	GAMGInterfaceField(GAMGCp, doTransform, rank),
	cyclicAMIInterface_(refCast<const cyclicAMIGAMGInterface>(GAMGCp)),
	doTransform_(doTransform),
	rank_(rank)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::cyclicAMIGAMGInterfaceField::~cyclicAMIGAMGInterfaceField()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::cyclicAMIGAMGInterfaceField::updateInterfaceMatrix
(
	scalarField& result,
	const scalarField& psiInternal,
	const scalarField& coeffs,
	const direction cmpt,
	const Pstream::commsTypes
) const
{
	const cyclicAMIGAMGInterface& thisInterface = cyclicAMIInterface_;
	const cyclicAMIGAMGInterface& neiInterface = thisInterface.neighbPatch();

	// Get neighbouring field
	scalarField pnf(neiInterface.interfaceInternalField(psiInternal));

	// Transform according to the transformation tensors
	transformCoupleField(pnf, cmpt);

	// Transform and interpolate
	scalarField pf(size(), Zero);
	if (thisInterface.owner())
	{
		forAll(thisInterface.AMIs(), i)
		{
			const scalar r =
				pow
				(
					inv(thisInterface.AMITransforms()[i]).R()(cmpt, cmpt),
					rank()
				);

			pf += thisInterface.AMIs()[i].interpolateToSource(r*pnf);
		}
	}
	else
	{
		forAll(neiInterface.AMIs(), i)
		{
			const scalar r =
				pow
				(
					neiInterface.AMITransforms()[i].R()(cmpt, cmpt),
					rank()
				);

			pf += neiInterface.AMIs()[i].interpolateToTarget(r*pnf);
		}
	}

	// Multiply the field by coefficients and add into the result
	const labelUList& faceCells = cyclicAMIInterface_.faceCells();
	forAll(faceCells, elemI)
	{
		result[faceCells[elemI]] -= coeffs[elemI] * pf[elemI];
	}
}


// ************************************************************************* //