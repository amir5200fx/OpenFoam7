#include <slicedFvsPatchField.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::slicedFvsPatchField<Type>::slicedFvsPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, surfaceMesh>& iF,
	const Field<Type>& completeField
)
	:
	fvsPatchField<Type>(p, iF, Field<Type>())
{
	// Set the fvsPatchField to a slice of the given complete field
	UList<Type>::shallowCopy(p.patchSlice(completeField));
}


template<class Type>
tnbLib::slicedFvsPatchField<Type>::slicedFvsPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, surfaceMesh>& iF
)
	:
	fvsPatchField<Type>(p, iF)
{}


template<class Type>
tnbLib::slicedFvsPatchField<Type>::slicedFvsPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, surfaceMesh>& iF,
	const dictionary& dict
)
	:
	fvsPatchField<Type>(p, iF, Field<Type>("value", dict, p.size()))
{
	NotImplemented;
}


template<class Type>
tnbLib::slicedFvsPatchField<Type>::slicedFvsPatchField
(
	const slicedFvsPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, surfaceMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fvsPatchField<Type>(ptf, p, iF, mapper)
{
	NotImplemented;
}


template<class Type>
tnbLib::slicedFvsPatchField<Type>::slicedFvsPatchField
(
	const slicedFvsPatchField<Type>& ptf,
	const DimensionedField<Type, surfaceMesh>& iF
)
	:
	fvsPatchField<Type>(ptf.patch(), iF, Field<Type>())
{
	// Transfer the slice from the argument
	UList<Type>::shallowCopy(ptf);
}


template<class Type>
tnbLib::tmp<tnbLib::fvsPatchField<Type>>
tnbLib::slicedFvsPatchField<Type>::clone() const
{
	return tmp<fvsPatchField<Type>>
		(
			new slicedFvsPatchField<Type>(*this)
			);
}


template<class Type>
tnbLib::slicedFvsPatchField<Type>::slicedFvsPatchField
(
	const slicedFvsPatchField<Type>& ptf
)
	:
	fvsPatchField<Type>
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
tnbLib::tmp<tnbLib::fvsPatchField<Type>>
tnbLib::slicedFvsPatchField<Type>::clone
(
	const DimensionedField<Type, surfaceMesh>& iF
) const
{
	return tmp<fvsPatchField<Type>>
		(
			new slicedFvsPatchField<Type>(*this, iF)
			);
}


template<class Type>
tnbLib::slicedFvsPatchField<Type>::~slicedFvsPatchField()
{
	// Set the fvsPatchField storage pointer to nullptr before its destruction
	// to protect the field it a slice of.
	UList<Type>::shallowCopy(UList<Type>(nullptr, 0));
}


// ************************************************************************* //