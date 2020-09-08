#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::nonuniformTransformCyclicFvPatchField<Type>::
nonuniformTransformCyclicFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	cyclicFvPatchField<Type>(p, iF)
{}


template<class Type>
tnbLib::nonuniformTransformCyclicFvPatchField<Type>::
nonuniformTransformCyclicFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict
)
	:
	cyclicFvPatchField<Type>(p, iF, dict)
{}


template<class Type>
tnbLib::nonuniformTransformCyclicFvPatchField<Type>::
nonuniformTransformCyclicFvPatchField
(
	const nonuniformTransformCyclicFvPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	cyclicFvPatchField<Type>(ptf, p, iF, mapper)
{}


template<class Type>
tnbLib::nonuniformTransformCyclicFvPatchField<Type>::
nonuniformTransformCyclicFvPatchField
(
	const nonuniformTransformCyclicFvPatchField<Type>& ptf
)
	:
	cyclicFvPatchField<Type>(ptf)
{}


template<class Type>
tnbLib::nonuniformTransformCyclicFvPatchField<Type>::
nonuniformTransformCyclicFvPatchField
(
	const nonuniformTransformCyclicFvPatchField<Type>& ptf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	cyclicFvPatchField<Type>(ptf, iF)
{}


// ************************************************************************* //