#pragma once
#include <transformField.hxx>
#include <symmTransformField.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::basicSymmetryPointPatchField<Type>::basicSymmetryPointPatchField
(
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF
)
	:
	pointPatchField<Type>(p, iF)
{}


template<class Type>
tnbLib::basicSymmetryPointPatchField<Type>::basicSymmetryPointPatchField
(
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF,
	const dictionary& dict
)
	:
	pointPatchField<Type>(p, iF, dict)
{}


template<class Type>
tnbLib::basicSymmetryPointPatchField<Type>::basicSymmetryPointPatchField
(
	const basicSymmetryPointPatchField<Type>& ptf,
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF,
	const pointPatchFieldMapper& mapper
)
	:
	pointPatchField<Type>(ptf, p, iF, mapper)
{}


template<class Type>
tnbLib::basicSymmetryPointPatchField<Type>::basicSymmetryPointPatchField
(
	const basicSymmetryPointPatchField<Type>& ptf,
	const DimensionedField<Type, pointMesh>& iF
)
	:
	pointPatchField<Type>(ptf, iF)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::basicSymmetryPointPatchField<Type>::evaluate
(
	const Pstream::commsTypes
)
{
	const vectorField& nHat = this->patch().pointNormals();

	tmp<Field<Type>> tvalues =
		(
		(
			this->patchInternalField()
			+ transform(I - 2.0*sqr(nHat), this->patchInternalField())
			) / 2.0
			);

	// Get internal field to insert values into
	Field<Type>& iF = const_cast<Field<Type>&>(this->primitiveField());

	this->setInInternalField(iF, tvalues());
}


// ************************************************************************* //