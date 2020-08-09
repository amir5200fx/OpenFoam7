#include <fixedInternalValueFvPatchField.hxx>

#include <fvPatchFieldMapper.hxx>
#include <fvMatrix.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::fixedInternalValueFvPatchField<Type>::fixedInternalValueFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	zeroGradientFvPatchField<Type>(p, iF)
{}


template<class Type>
tnbLib::fixedInternalValueFvPatchField<Type>::fixedInternalValueFvPatchField
(
	const fixedInternalValueFvPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	zeroGradientFvPatchField<Type>(ptf, p, iF, mapper)
{}


template<class Type>
tnbLib::fixedInternalValueFvPatchField<Type>::fixedInternalValueFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict
)
	:
	zeroGradientFvPatchField<Type>(p, iF, dict)
{}


template<class Type>
tnbLib::fixedInternalValueFvPatchField<Type>::fixedInternalValueFvPatchField
(
	const fixedInternalValueFvPatchField& fivpf
)
	:
	zeroGradientFvPatchField<Type>(fivpf)
{}


template<class Type>
tnbLib::fixedInternalValueFvPatchField<Type>::fixedInternalValueFvPatchField
(
	const fixedInternalValueFvPatchField& fivpf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	zeroGradientFvPatchField<Type>(fivpf, iF)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::fixedInternalValueFvPatchField<Type>::manipulateMatrix
(
	fvMatrix<Type>& matrix
)
{
	// Apply the patch internal field as a constraint in the matrix
	matrix.setValues(this->patch().faceCells(), this->patchInternalField());
}


// ************************************************************************* //