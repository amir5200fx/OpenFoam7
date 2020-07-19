#include <processorCyclicFvsPatchField.hxx>

// * * * * * * * * * * * * * * * * Constructors * * * * * * * * * * * * * * //

template<class Type>
tnbLib::processorCyclicFvsPatchField<Type>::processorCyclicFvsPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, surfaceMesh>& iF
)
	:
	coupledFvsPatchField<Type>(p, iF),
	procPatch_(refCast<const processorCyclicFvPatch>(p))
{}


template<class Type>
tnbLib::processorCyclicFvsPatchField<Type>::processorCyclicFvsPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, surfaceMesh>& iF,
	const Field<Type>& f
)
	:
	coupledFvsPatchField<Type>(p, iF, f),
	procPatch_(refCast<const processorCyclicFvPatch>(p))
{}


template<class Type>
tnbLib::processorCyclicFvsPatchField<Type>::processorCyclicFvsPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, surfaceMesh>& iF,
	const dictionary& dict
)
	:
	coupledFvsPatchField<Type>(p, iF, dict),
	procPatch_(refCast<const processorCyclicFvPatch>(p))
{
	if (!isType<processorCyclicFvPatch>(p))
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
tnbLib::processorCyclicFvsPatchField<Type>::processorCyclicFvsPatchField
(
	const processorCyclicFvsPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, surfaceMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	coupledFvsPatchField<Type>(ptf, p, iF, mapper),
	procPatch_(refCast<const processorCyclicFvPatch>(p))
{
	if (!isType<processorCyclicFvPatch>(this->patch()))
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
tnbLib::processorCyclicFvsPatchField<Type>::processorCyclicFvsPatchField
(
	const processorCyclicFvsPatchField<Type>& ptf
)
	:
	coupledFvsPatchField<Type>(ptf),
	procPatch_(refCast<const processorCyclicFvPatch>(ptf.patch()))
{}


template<class Type>
tnbLib::processorCyclicFvsPatchField<Type>::processorCyclicFvsPatchField
(
	const processorCyclicFvsPatchField<Type>& ptf,
	const DimensionedField<Type, surfaceMesh>& iF
)
	:
	coupledFvsPatchField<Type>(ptf, iF),
	procPatch_(refCast<const processorCyclicFvPatch>(ptf.patch()))
{}


// * * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::processorCyclicFvsPatchField<Type>::~processorCyclicFvsPatchField()
{}


// ************************************************************************* //