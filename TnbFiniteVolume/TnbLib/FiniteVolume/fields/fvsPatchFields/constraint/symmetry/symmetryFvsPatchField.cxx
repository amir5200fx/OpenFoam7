#include <symmetryFvsPatchField.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::symmetryFvsPatchField<Type>::symmetryFvsPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, surfaceMesh>& iF
)
	:
	fvsPatchField<Type>(p, iF)
{}


template<class Type>
tnbLib::symmetryFvsPatchField<Type>::symmetryFvsPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, surfaceMesh>& iF,
	const dictionary& dict
)
	:
	fvsPatchField<Type>(p, iF, dict)
{
	if (!isType<symmetryFvPatch>(p))
	{
		FatalIOErrorInFunction
		(
			dict
		) << "patch " << this->patch().index() << " not symmetry type. "
			<< "Patch type = " << p.type()
			<< exit(FatalIOError);
	}
}


template<class Type>
tnbLib::symmetryFvsPatchField<Type>::symmetryFvsPatchField
(
	const symmetryFvsPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, surfaceMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fvsPatchField<Type>(ptf, p, iF, mapper)
{
	if (!isType<symmetryFvPatch>(this->patch()))
	{
		FatalErrorInFunction
			<< "Field type does not correspond to patch type for patch "
			<< this->patch().index() << "." << endl
			<< "Field type: " << typeName << endl
			<< "Patch type: " << this->patch().type()
			<< exit(FatalError);
	}
}


template<class Type>
tnbLib::symmetryFvsPatchField<Type>::symmetryFvsPatchField
(
	const symmetryFvsPatchField<Type>& ptf
)
	:
	fvsPatchField<Type>(ptf)
{}


template<class Type>
tnbLib::symmetryFvsPatchField<Type>::symmetryFvsPatchField
(
	const symmetryFvsPatchField<Type>& ptf,
	const DimensionedField<Type, surfaceMesh>& iF
)
	:
	fvsPatchField<Type>(ptf, iF)
{}


// ************************************************************************* //