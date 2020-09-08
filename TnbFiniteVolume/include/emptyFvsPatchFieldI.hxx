#pragma once
#include <fvPatchFieldMapper.hxx>
#include <surfaceMesh.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::emptyFvsPatchField<Type>::emptyFvsPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, surfaceMesh>& iF
)
	:
	fvsPatchField<Type>(p, iF, Field<Type>(0))
{}


template<class Type>
tnbLib::emptyFvsPatchField<Type>::emptyFvsPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, surfaceMesh>& iF,
	const dictionary& dict
)
	:
	fvsPatchField<Type>(p, iF, Field<Type>(0))
{
	if (!isType<emptyFvPatch>(p))
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
tnbLib::emptyFvsPatchField<Type>::emptyFvsPatchField
(
	const emptyFvsPatchField<Type>&,
	const fvPatch& p,
	const DimensionedField<Type, surfaceMesh>& iF,
	const fvPatchFieldMapper&
)
	:
	fvsPatchField<Type>(p, iF, Field<Type>(0))
{
	if (!isType<emptyFvPatch>(this->patch()))
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
tnbLib::emptyFvsPatchField<Type>::emptyFvsPatchField
(
	const emptyFvsPatchField<Type>& ptf
)
	:
	fvsPatchField<Type>
	(
		ptf.patch(),
		ptf.internalField(),
		Field<Type>(0)
		)
{}


template<class Type>
tnbLib::emptyFvsPatchField<Type>::emptyFvsPatchField
(
	const emptyFvsPatchField<Type>& ptf,
	const DimensionedField<Type, surfaceMesh>& iF
)
	:
	fvsPatchField<Type>(ptf.patch(), iF, Field<Type>(0))
{}


// ************************************************************************* //