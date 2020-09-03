#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::emptyPointPatchField<Type>::emptyPointPatchField
(
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF
)
	:
	pointPatchField<Type>(p, iF)
{}


template<class Type>
tnbLib::emptyPointPatchField<Type>::emptyPointPatchField
(
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF,
	const dictionary& dict
)
	:
	pointPatchField<Type>(p, iF, dict)
{
	if (!isType<emptyPointPatch>(p))
	{
		FatalIOErrorInFunction
		(
			dict
		) << "patch " << this->patch().index() << " not empty type. "
			<< "Patch type = " << p.type()
			<< exit(FatalIOError);
	}
}


template<class Type>
tnbLib::emptyPointPatchField<Type>::emptyPointPatchField
(
	const emptyPointPatchField<Type>& ptf,
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF,
	const pointPatchFieldMapper& mapper
)
	:
	pointPatchField<Type>(ptf, p, iF, mapper)
{
	if (!isType<emptyPointPatch>(this->patch()))
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
tnbLib::emptyPointPatchField<Type>::emptyPointPatchField
(
	const emptyPointPatchField<Type>& ptf,
	const DimensionedField<Type, pointMesh>& iF
)
	:
	pointPatchField<Type>(ptf, iF)
{}


// ************************************************************************* //