#include <slicedFvPatchField.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::slicedFvPatchField<Type>::slicedFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const Field<Type>& completeField
)
	:
	fvPatchField<Type>(p, iF, Field<Type>())
{
	// Set the fvPatchField to a slice of the given complete field
	UList<Type>::shallowCopy(p.patchSlice(completeField));
}


template<class Type>
tnbLib::slicedFvPatchField<Type>::slicedFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	fvPatchField<Type>(p, iF, Field<Type>())
{}


template<class Type>
tnbLib::slicedFvPatchField<Type>::slicedFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict
)
	:
	fvPatchField<Type>(p, iF, dict, false)
{
	NotImplemented;
}


template<class Type>
tnbLib::slicedFvPatchField<Type>::slicedFvPatchField
(
	const slicedFvPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fvPatchField<Type>(ptf, p, iF, mapper)
{
	NotImplemented;
}


template<class Type>
tnbLib::slicedFvPatchField<Type>::slicedFvPatchField
(
	const slicedFvPatchField<Type>& ptf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	fvPatchField<Type>(ptf.patch(), iF, Field<Type>())
{
	// Transfer the slice from the argument
	UList<Type>::shallowCopy(ptf);
}


template<class Type>
tnbLib::tmp<tnbLib::fvPatchField<Type>>
tnbLib::slicedFvPatchField<Type>::clone() const
{
	return tmp<fvPatchField<Type>>
		(
			new slicedFvPatchField<Type>(*this)
			);
}


template<class Type>
tnbLib::slicedFvPatchField<Type>::slicedFvPatchField
(
	const slicedFvPatchField<Type>& ptf
)
	:
	fvPatchField<Type>
	(
		ptf.patch(),
		ptf.internalField(),
		Field<Type>()
		)
{
	// Transfer the slice from the argument
	UList<Type>::shallowCopy(ptf);
}


template<class Type>
tnbLib::tmp<tnbLib::fvPatchField<Type>>
tnbLib::slicedFvPatchField<Type>::clone
(
	const DimensionedField<Type, volMesh>& iF
) const
{
	return tmp<fvPatchField<Type>>
		(
			new slicedFvPatchField<Type>(*this, iF)
			);
}


template<class Type>
tnbLib::slicedFvPatchField<Type>::~slicedFvPatchField()
{
	// Set the fvPatchField storage pointer to nullptr before its destruction
	// to protect the field it a slice of.
	UList<Type>::shallowCopy(UList<Type>(nullptr, 0));
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::Field<Type>> tnbLib::slicedFvPatchField<Type>::snGrad() const
{
	NotImplemented;

	return Field<Type>::null();
}


template<class Type>
void tnbLib::slicedFvPatchField<Type>::updateCoeffs()
{
	NotImplemented;
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::slicedFvPatchField<Type>::patchInternalField() const
{
	NotImplemented;

	return Field<Type>::null();
}


template<class Type>
void tnbLib::slicedFvPatchField<Type>::patchInternalField(Field<Type>&) const
{
	NotImplemented;
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::slicedFvPatchField<Type>::patchNeighbourField
(
	const Field<Type>& iField
) const
{
	NotImplemented;

	return Field<Type>::null();
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::slicedFvPatchField<Type>::patchNeighbourField() const
{
	NotImplemented;

	return Field<Type>::null();
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::slicedFvPatchField<Type>::valueInternalCoeffs
(
	const tmp<scalarField>&
) const
{
	NotImplemented;

	return Field<Type>::null();
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::slicedFvPatchField<Type>::valueBoundaryCoeffs
(
	const tmp<scalarField>&
) const
{
	NotImplemented;

	return Field<Type>::null();
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::slicedFvPatchField<Type>::gradientInternalCoeffs() const
{
	NotImplemented;

	return Field<Type>::null();
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::slicedFvPatchField<Type>::gradientBoundaryCoeffs() const
{
	NotImplemented;

	return Field<Type>::null();
}


template<class Type>
void tnbLib::slicedFvPatchField<Type>::write(Ostream& os) const
{
	fvPatchField<Type>::write(os);
	writeEntry(os, "value", *this);
}


// ************************************************************************* //