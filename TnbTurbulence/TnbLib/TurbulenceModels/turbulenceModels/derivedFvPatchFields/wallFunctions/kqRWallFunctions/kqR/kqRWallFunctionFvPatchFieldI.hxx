#pragma once
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::kqRWallFunctionFvPatchField<Type>::kqRWallFunctionFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	zeroGradientFvPatchField<Type>(p, iF)
{}


template<class Type>
tnbLib::kqRWallFunctionFvPatchField<Type>::kqRWallFunctionFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict
)
	:
	zeroGradientFvPatchField<Type>(p, iF, dict)
{}


template<class Type>
tnbLib::kqRWallFunctionFvPatchField<Type>::kqRWallFunctionFvPatchField
(
	const kqRWallFunctionFvPatchField& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	zeroGradientFvPatchField<Type>(ptf, p, iF, mapper)
{}


template<class Type>
tnbLib::kqRWallFunctionFvPatchField<Type>::kqRWallFunctionFvPatchField
(
	const kqRWallFunctionFvPatchField& tkqrwfpf
)
	:
	zeroGradientFvPatchField<Type>(tkqrwfpf)
{}


template<class Type>
tnbLib::kqRWallFunctionFvPatchField<Type>::kqRWallFunctionFvPatchField
(
	const kqRWallFunctionFvPatchField& tkqrwfpf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	zeroGradientFvPatchField<Type>(tkqrwfpf, iF)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::kqRWallFunctionFvPatchField<Type>::evaluate
(
	const Pstream::commsTypes commsType
)
{
	zeroGradientFvPatchField<Type>::evaluate(commsType);
}


template<class Type>
void tnbLib::kqRWallFunctionFvPatchField<Type>::write(Ostream& os) const
{
	zeroGradientFvPatchField<Type>::write(os);
	writeEntry(os, "value", *this);
}


// ************************************************************************* //