#include <jumpCyclicAMIFvPatchFields.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <volFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	makePatchFieldTypeNames(jumpCyclicAMI);

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<>
	void tnbLib::jumpCyclicAMIFvPatchField<scalar>::updateInterfaceMatrix
	(
		scalarField& result,
		const scalarField& psiInternal,
		const scalarField& coeffs,
		const direction cmpt,
		const Pstream::commsTypes
	) const
	{
		const labelUList& nbrFaceCells =
			this->cyclicAMIPatch().cyclicAMIPatch().neighbPatch().faceCells();

		scalarField pnf(psiInternal, nbrFaceCells);

		pnf = this->cyclicAMIPatch().interpolate(pnf);

		// only apply jump to original field
		if (&psiInternal == &this->primitiveField())
		{
			Field<scalar> jf(this->jump());

			if (!this->cyclicAMIPatch().owner())
			{
				jf *= -1.0;
			}

			pnf -= jf;
		}

		// Transform according to the transformation tensors
		this->transformCoupleField(pnf, cmpt);

		// Multiply the field by coefficients and add into the result
		const labelUList& faceCells = this->cyclicAMIPatch().faceCells();
		forAll(faceCells, elemI)
		{
			result[faceCells[elemI]] -= coeffs[elemI] * pnf[elemI];
		}
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //