#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::cyclicAMIFvsPatchField<Type>::cyclicAMIFvsPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, surfaceMesh>& iF
)
	:
	coupledFvsPatchField<Type>(p, iF),
	cyclicAMIPatch_(refCast<const cyclicAMIFvPatch>(p))
{}


template<class Type>
tnbLib::cyclicAMIFvsPatchField<Type>::cyclicAMIFvsPatchField
(
	const cyclicAMIFvsPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, surfaceMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	coupledFvsPatchField<Type>(ptf, p, iF, mapper),
	cyclicAMIPatch_(refCast<const cyclicAMIFvPatch>(p))
{
	if (!isA<cyclicAMIFvPatch>(this->patch()))
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
tnbLib::cyclicAMIFvsPatchField<Type>::cyclicAMIFvsPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, surfaceMesh>& iF,
	const dictionary& dict
)
	:
	coupledFvsPatchField<Type>(p, iF, dict),
	cyclicAMIPatch_(refCast<const cyclicAMIFvPatch>(p))
{
	if (!isA<cyclicAMIFvPatch>(p))
	{
		FatalIOErrorInFunction
		(
			dict
		) << "patch " << this->patch().index() << " not cyclicAMI type. "
			<< "Patch type = " << p.type()
			<< exit(FatalIOError);
	}
}


template<class Type>
tnbLib::cyclicAMIFvsPatchField<Type>::cyclicAMIFvsPatchField
(
	const cyclicAMIFvsPatchField<Type>& ptf
)
	:
	coupledFvsPatchField<Type>(ptf),
	cyclicAMIPatch_(ptf.cyclicAMIPatch_)
{}


template<class Type>
tnbLib::cyclicAMIFvsPatchField<Type>::cyclicAMIFvsPatchField
(
	const cyclicAMIFvsPatchField<Type>& ptf,
	const DimensionedField<Type, surfaceMesh>& iF
)
	:
	coupledFvsPatchField<Type>(ptf, iF),
	cyclicAMIPatch_(ptf.cyclicAMIPatch_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
bool tnbLib::cyclicAMIFvsPatchField<Type>::coupled() const
{
	return cyclicAMIPatch_.coupled();
}


// ************************************************************************* //