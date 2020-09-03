#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
const tnbLib::word& tnbLib::pointPatchField<Type>::calculatedType()
{
	return calculatedPointPatchField<Type>::typeName;
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::calculatedPointPatchField<Type>::calculatedPointPatchField
(
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF
)
	:
	pointPatchField<Type>(p, iF)
{}


template<class Type>
tnbLib::calculatedPointPatchField<Type>::calculatedPointPatchField
(
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF,
	const dictionary& dict
)
	:
	pointPatchField<Type>(p, iF, dict)
{}


template<class Type>
tnbLib::calculatedPointPatchField<Type>::calculatedPointPatchField
(
	const calculatedPointPatchField<Type>& ptf,
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF,
	const pointPatchFieldMapper& mapper
)
	:
	pointPatchField<Type>(ptf, p, iF, mapper)
{}


template<class Type>
tnbLib::calculatedPointPatchField<Type>::calculatedPointPatchField
(
	const calculatedPointPatchField<Type>& ptf,
	const DimensionedField<Type, pointMesh>& iF
)
	:
	pointPatchField<Type>(ptf, iF)
{}


template<class Type>
template<class Type2>
tnbLib::autoPtr<tnbLib::pointPatchField<Type>>
tnbLib::pointPatchField<Type>::NewCalculatedType
(
	const pointPatchField<Type2>& pf
)
{
	typename pointPatchConstructorTable::iterator patchTypeCstrIter =
		pointPatchConstructorTablePtr_->find(pf.patch().type());

	if (patchTypeCstrIter != pointPatchConstructorTablePtr_->end())
	{
		return autoPtr<pointPatchField<Type>>
			(
				patchTypeCstrIter()
				(
					pf.patch(),
					Field<Type>::null()
					)
				);
	}
	else
	{
		return autoPtr<pointPatchField<Type>>
			(
				new calculatedPointPatchField<Type>
				(
					pf.patch(),
					Field<Type>::null()
					)
				);
	}
}


// ************************************************************************* //