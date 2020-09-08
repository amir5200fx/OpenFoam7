#include <processorFvsPatchField.hxx>

// * * * * * * * * * * * * * * * * Constructors * * * * * * * * * * * * * * //

template<class Type>
tnbLib::processorFvsPatchField<Type>::processorFvsPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, surfaceMesh>& iF
)
	:
	coupledFvsPatchField<Type>(p, iF),
	procPatch_(refCast<const processorFvPatch>(p))
{}


template<class Type>
tnbLib::processorFvsPatchField<Type>::processorFvsPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, surfaceMesh>& iF,
	const Field<Type>& f
)
	:
	coupledFvsPatchField<Type>(p, iF, f),
	procPatch_(refCast<const processorFvPatch>(p))
{}


template<class Type>
tnbLib::processorFvsPatchField<Type>::processorFvsPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, surfaceMesh>& iF,
	const dictionary& dict
)
	:
	coupledFvsPatchField<Type>(p, iF, dict),
	procPatch_(refCast<const processorFvPatch>(p))
{
	if (!isType<processorFvPatch>(p))
	{
		FatalIOErrorInFunction
		(
			dict
		) << "patch " << this->patch().index() << " not processor type. "
			<< "Patch type = " << p.type()
			<< exit(FatalIOError);
	}
}


template<class Type>
tnbLib::processorFvsPatchField<Type>::processorFvsPatchField
(
	const processorFvsPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, surfaceMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	coupledFvsPatchField<Type>(ptf, p, iF, mapper),
	procPatch_(refCast<const processorFvPatch>(p))
{
	if (!isType<processorFvPatch>(this->patch()))
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
tnbLib::processorFvsPatchField<Type>::processorFvsPatchField
(
	const processorFvsPatchField<Type>& ptf
)
	:
	coupledFvsPatchField<Type>(ptf),
	procPatch_(refCast<const processorFvPatch>(ptf.patch()))
{}


template<class Type>
tnbLib::processorFvsPatchField<Type>::processorFvsPatchField
(
	const processorFvsPatchField<Type>& ptf,
	const DimensionedField<Type, surfaceMesh>& iF
)
	:
	coupledFvsPatchField<Type>(ptf, iF),
	procPatch_(refCast<const processorFvPatch>(ptf.patch()))
{}


// * * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::processorFvsPatchField<Type>::~processorFvsPatchField()
{}


// ************************************************************************* //