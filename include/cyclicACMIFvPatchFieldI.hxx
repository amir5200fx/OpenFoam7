#pragma once
#include <transformField.hxx>
#include <GeometricField.hxx>  // added by amir

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
const tnbLib::fvPatchField<Type>&
tnbLib::cyclicACMIFvPatchField<Type>::nonOverlapPatchField() const
{
	const GeometricField<Type, fvPatchField, volMesh>& fld =
		static_cast<const GeometricField<Type, fvPatchField, volMesh>&>
		(
			this->primitiveField()
			);

	return fld.boundaryField()
		[
			cyclicACMIPatch().cyclicACMIPatch().nonOverlapPatchID()
		];
}


template<class Type>
void tnbLib::cyclicACMIFvPatchField<Type>::manipulateMatrix
(
	fvMatrix<Type>& matrix
)
{
	const scalarField& mask = cyclicACMIPatch().cyclicACMIPatch().mask();

	// nothing to be done by the AMI, but re-direct to non-overlap patch
	// with non-overlap patch weights
	const fvPatchField<Type>& npf = nonOverlapPatchField();

	const_cast<fvPatchField<Type>&>(npf).manipulateMatrix(matrix, 1.0 - mask);
}


template<class Type>
void tnbLib::cyclicACMIFvPatchField<Type>::updateCoeffs()
{
	// Update non-overlap patch - some will implement updateCoeffs, and
	// others will implement evaluate

	// Pass in (1 - mask) to give non-overlap patch the chance to do
	// manipulation of non-face based data

	const scalarField& mask = cyclicACMIPatch().cyclicACMIPatch().mask();
	const fvPatchField<Type>& npf = nonOverlapPatchField();
	const_cast<fvPatchField<Type>&>(npf).updateWeightedCoeffs(1.0 - mask);
}


// ************************************************************************* //