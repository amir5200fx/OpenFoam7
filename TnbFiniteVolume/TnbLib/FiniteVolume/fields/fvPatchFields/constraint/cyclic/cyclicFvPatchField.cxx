#include <cyclicFvPatchField.hxx>

#include <transformField.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::cyclicFvPatchField<Type>::cyclicFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	coupledFvPatchField<Type>(p, iF),
	cyclicPatch_(refCast<const cyclicFvPatch>(p))
{}


template<class Type>
tnbLib::cyclicFvPatchField<Type>::cyclicFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict
)
	:
	coupledFvPatchField<Type>(p, iF, dict, false),
	cyclicPatch_(refCast<const cyclicFvPatch>(p))
{
	if (!isA<cyclicFvPatch>(p))
	{
		FatalIOErrorInFunction
		(
			dict
		) << "    patch type '" << p.type()
			<< "' not constraint type '" << typeName << "'"
			<< "\n    for patch " << p.name()
			<< " of field " << this->internalField().name()
			<< " in file " << this->internalField().objectPath()
			<< exit(FatalIOError);
	}

	this->evaluate(Pstream::commsTypes::blocking);
}


template<class Type>
tnbLib::cyclicFvPatchField<Type>::cyclicFvPatchField
(
	const cyclicFvPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	coupledFvPatchField<Type>(ptf, p, iF, mapper),
	cyclicLduInterfaceField(),
	cyclicPatch_(refCast<const cyclicFvPatch>(p))
{
	if (!isA<cyclicFvPatch>(this->patch()))
	{
		FatalErrorInFunction
			<< "' not constraint type '" << typeName << "'"
			<< "\n    for patch " << p.name()
			<< " of field " << this->internalField().name()
			<< " in file " << this->internalField().objectPath()
			<< exit(FatalIOError);
	}
}


template<class Type>
tnbLib::cyclicFvPatchField<Type>::cyclicFvPatchField
(
	const cyclicFvPatchField<Type>& ptf
)
	:
	coupledFvPatchField<Type>(ptf),
	cyclicLduInterfaceField(),
	cyclicPatch_(ptf.cyclicPatch_)
{}


template<class Type>
tnbLib::cyclicFvPatchField<Type>::cyclicFvPatchField
(
	const cyclicFvPatchField<Type>& ptf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	coupledFvPatchField<Type>(ptf, iF),
	cyclicLduInterfaceField(),
	cyclicPatch_(ptf.cyclicPatch_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::cyclicFvPatchField<Type>::patchNeighbourField() const
{
	const Field<Type>& iField = this->primitiveField();
	const labelUList& nbrFaceCells =
		cyclicPatch().cyclicPatch().neighbPatch().faceCells();

	tmp<Field<Type>> tpnf(new Field<Type>(this->size()));
	Field<Type>& pnf = tpnf.ref();


	if (doTransform())
	{
		forAll(pnf, facei)
		{
			pnf[facei] = transform
			(
				forwardT()[0], iField[nbrFaceCells[facei]]
			);
		}
	}
	else
	{
		forAll(pnf, facei)
		{
			pnf[facei] = iField[nbrFaceCells[facei]];
		}
	}

	return tpnf;
}


template<class Type>
const tnbLib::cyclicFvPatchField<Type>&
tnbLib::cyclicFvPatchField<Type>::neighbourPatchField() const
{
	const GeometricField<Type, fvPatchField, volMesh>& fld =
		static_cast<const GeometricField<Type, fvPatchField, volMesh>&>
		(
			this->primitiveField()
			);

	return refCast<const cyclicFvPatchField<Type>>
		(
			fld.boundaryField()[this->cyclicPatch().neighbPatchID()]
			);
}


template<class Type>
void tnbLib::cyclicFvPatchField<Type>::updateInterfaceMatrix
(
	scalarField& result,
	const scalarField& psiInternal,
	const scalarField& coeffs,
	const direction cmpt,
	const Pstream::commsTypes
) const
{
	const labelUList& nbrFaceCells =
		cyclicPatch().cyclicPatch().neighbPatch().faceCells();

	scalarField pnf(psiInternal, nbrFaceCells);

	// Transform according to the transformation tensors
	transformCoupleField(pnf, cmpt);

	// Multiply the field by coefficients and add into the result
	const labelUList& faceCells = cyclicPatch_.faceCells();

	forAll(faceCells, elemI)
	{
		result[faceCells[elemI]] -= coeffs[elemI] * pnf[elemI];
	}
}


template<class Type>
void tnbLib::cyclicFvPatchField<Type>::updateInterfaceMatrix
(
	Field<Type>& result,
	const Field<Type>& psiInternal,
	const scalarField& coeffs,
	const Pstream::commsTypes
) const
{
	const labelUList& nbrFaceCells =
		cyclicPatch().cyclicPatch().neighbPatch().faceCells();

	Field<Type> pnf(psiInternal, nbrFaceCells);

	// Transform according to the transformation tensors
	transformCoupleField(pnf);

	// Multiply the field by coefficients and add into the result
	const labelUList& faceCells = cyclicPatch_.faceCells();

	forAll(faceCells, elemI)
	{
		result[faceCells[elemI]] -= coeffs[elemI] * pnf[elemI];
	}
}


template<class Type>
void tnbLib::cyclicFvPatchField<Type>::write(Ostream& os) const
{
	fvPatchField<Type>::write(os);
}


// ************************************************************************* //