#include <jumpCyclicFvPatchField.hxx>

#include <transformField.hxx>  // added by amir
#include <volMesh.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::jumpCyclicFvPatchField<Type>::jumpCyclicFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	cyclicFvPatchField<Type>(p, iF)
{}


template<class Type>
tnbLib::jumpCyclicFvPatchField<Type>::jumpCyclicFvPatchField
(
	const jumpCyclicFvPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	cyclicFvPatchField<Type>(ptf, p, iF, mapper)
{}


template<class Type>
tnbLib::jumpCyclicFvPatchField<Type>::jumpCyclicFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict
)
	:
	cyclicFvPatchField<Type>(p, iF, dict)
{
	// Call this evaluation in derived classes
	// this->evaluate(Pstream::commsTypes::blocking);
}


template<class Type>
tnbLib::jumpCyclicFvPatchField<Type>::jumpCyclicFvPatchField
(
	const jumpCyclicFvPatchField<Type>& ptf
)
	:
	cyclicFvPatchField<Type>(ptf)
{}


template<class Type>
tnbLib::jumpCyclicFvPatchField<Type>::jumpCyclicFvPatchField
(
	const jumpCyclicFvPatchField<Type>& ptf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	cyclicFvPatchField<Type>(ptf, iF)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::jumpCyclicFvPatchField<Type>::patchNeighbourField() const
{
	const Field<Type>& iField = this->primitiveField();
	const labelUList& nbrFaceCells =
		this->cyclicPatch().neighbFvPatch().faceCells();

	tmp<Field<Type>> tpnf(new Field<Type>(this->size()));
	Field<Type>& pnf = tpnf.ref();

	Field<Type> jf(this->jump());
	if (!this->cyclicPatch().owner())
	{
		jf *= -1.0;
	}

	if (this->doTransform())
	{
		forAll(*this, facei)
		{
			pnf[facei] = transform
			(
				this->forwardT()[0], iField[nbrFaceCells[facei]]
			) - jf[facei];
		}
	}
	else
	{
		forAll(*this, facei)
		{
			pnf[facei] = iField[nbrFaceCells[facei]] - jf[facei];
		}
	}

	return tpnf;
}


template<class Type>
void tnbLib::jumpCyclicFvPatchField<Type>::updateInterfaceMatrix
(
	scalarField& result,
	const scalarField& psiInternal,
	const scalarField& coeffs,
	const direction cmpt,
	const Pstream::commsTypes
) const
{
	NotImplemented;
}


template<class Type>
void tnbLib::jumpCyclicFvPatchField<Type>::updateInterfaceMatrix
(
	Field<Type>& result,
	const Field<Type>& psiInternal,
	const scalarField& coeffs,
	const Pstream::commsTypes
) const
{
	Field<Type> pnf(this->size());

	const labelUList& nbrFaceCells =
		this->cyclicPatch().neighbFvPatch().faceCells();

	// only apply jump to original field
	if (&psiInternal == &this->primitiveField())
	{
		Field<Type> jf(this->jump());

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
	this->transformCoupleField(pnf);

	// Multiply the field by coefficients and add into the result
	const labelUList& faceCells = this->cyclicPatch().faceCells();
	forAll(faceCells, elemI)
	{
		result[faceCells[elemI]] -= coeffs[elemI] * pnf[elemI];
	}
}


// ************************************************************************* //