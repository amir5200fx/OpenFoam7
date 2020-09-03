#pragma once
#include <processorPolyPatch.hxx>

// * * * * * * * * * * * * * * * * Constructors * * * * * * * * * * * * * * //

template<class Type>
tnbLib::processorPointPatchField<Type>::processorPointPatchField
(
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF
)
	:
	coupledPointPatchField<Type>(p, iF),
	procPatch_(refCast<const processorPointPatch>(p))
{}


template<class Type>
tnbLib::processorPointPatchField<Type>::processorPointPatchField
(
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF,
	const dictionary& dict
)
	:
	coupledPointPatchField<Type>(p, iF, dict),
	procPatch_(refCast<const processorPointPatch>(p))
{}


template<class Type>
tnbLib::processorPointPatchField<Type>::processorPointPatchField
(
	const processorPointPatchField<Type>& ptf,
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF,
	const pointPatchFieldMapper& mapper
)
	:
	coupledPointPatchField<Type>(ptf, p, iF, mapper),
	procPatch_(refCast<const processorPointPatch>(ptf.patch()))
{}


template<class Type>
tnbLib::processorPointPatchField<Type>::processorPointPatchField
(
	const processorPointPatchField<Type>& ptf,
	const DimensionedField<Type, pointMesh>& iF
)
	:
	coupledPointPatchField<Type>(ptf, iF),
	procPatch_(refCast<const processorPointPatch>(ptf.patch()))
{}


// * * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::processorPointPatchField<Type>::~processorPointPatchField()
{}


// ************************************************************************* //