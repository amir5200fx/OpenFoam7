#include <jumpCyclicFvPatchFields.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <volFields.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchFieldTypeNames(jumpCyclic);
}

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<>
void tnbLib::jumpCyclicFvPatchField<tnbLib::scalar>::updateInterfaceMatrix
(
	scalarField& result,
	const scalarField& psiInternal,
	const scalarField& coeffs,
	const direction cmpt,
	const Pstream::commsTypes
) const
{
	scalarField pnf(this->size());

	const labelUList& nbrFaceCells =
		this->cyclicPatch().neighbFvPatch().faceCells();

	// only apply jump to original field
	if (&psiInternal == &this->primitiveField())
	{
		Field<scalar> jf(this->jump());

		if (!this->cyclicPatch().owner())
		{
			jf *= -1.0;
		}

		forAll(*this, facei)
		{
			pnf[facei] = psiInternal[nbrFaceCells[facei]] - jf[facei];
		}
	}
	else
	{
		forAll(*this, facei)
		{
			pnf[facei] = psiInternal[nbrFaceCells[facei]];
		}
	}

	// Transform according to the transformation tensors
	this->transformCoupleField(pnf, cmpt);

	// Multiply the field by coefficients and add into the result
	const labelUList& faceCells = this->cyclicPatch().faceCells();
	forAll(faceCells, elemI)
	{
		result[faceCells[elemI]] -= coeffs[elemI] * pnf[elemI];
	}
}


// ************************************************************************* //