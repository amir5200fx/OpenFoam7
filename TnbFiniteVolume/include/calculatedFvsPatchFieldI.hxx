#pragma once
#include <fvPatchFieldMapper.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
const tnbLib::word& tnbLib::fvsPatchField<Type>::calculatedType()
{
	return calculatedFvsPatchField<Type>::typeName;
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::calculatedFvsPatchField<Type>::calculatedFvsPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, surfaceMesh>& iF
)
	:
	fvsPatchField<Type>(p, iF)
{}


template<class Type>
tnbLib::calculatedFvsPatchField<Type>::calculatedFvsPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, surfaceMesh>& iF,
	const dictionary& dict
)
	:
	fvsPatchField<Type>(p, iF, Field<Type>("value", dict, p.size()))
{}


template<class Type>
tnbLib::calculatedFvsPatchField<Type>::calculatedFvsPatchField
(
	const calculatedFvsPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, surfaceMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fvsPatchField<Type>(ptf, p, iF, mapper)
{}


template<class Type>
tnbLib::calculatedFvsPatchField<Type>::calculatedFvsPatchField
(
	const calculatedFvsPatchField<Type>& ptf
)
	:
	fvsPatchField<Type>(ptf)
{}


template<class Type>
tnbLib::calculatedFvsPatchField<Type>::calculatedFvsPatchField
(
	const calculatedFvsPatchField<Type>& ptf,
	const DimensionedField<Type, surfaceMesh>& iF
)
	:
	fvsPatchField<Type>(ptf, iF)
{}


template<class Type>
tnbLib::tmp<tnbLib::fvsPatchField<Type>>
tnbLib::fvsPatchField<Type>::NewCalculatedType
(
	const fvPatch& p
)
{
	typename patchConstructorTable::iterator patchTypeCstrIter =
		patchConstructorTablePtr_->find(p.type());

	if (patchTypeCstrIter != patchConstructorTablePtr_->end())
	{
		return patchTypeCstrIter()
			(
				p,
				DimensionedField<Type, surfaceMesh>::null()
				);
	}
	else
	{
		return tmp<fvsPatchField<Type>>
			(
				new calculatedFvsPatchField<Type>
				(
					p,
					DimensionedField<Type, surfaceMesh>::null()
					)
				);
	}
}


template<class Type>
template<class Type2>
tnbLib::tmp<tnbLib::fvsPatchField<Type>>
tnbLib::fvsPatchField<Type>::NewCalculatedType
(
	const fvsPatchField<Type2>& pf
)
{
	return NewCalculatedType(pf.patch());
}


// ************************************************************************* //