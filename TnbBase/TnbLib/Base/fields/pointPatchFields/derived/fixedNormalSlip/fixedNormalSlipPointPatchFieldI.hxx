#pragma once
#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::fixedNormalSlipPointPatchField<Type>::fixedNormalSlipPointPatchField
(
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF
)
	:
	slipPointPatchField<Type>(p, iF),
	n_(vector::max)
{}


template<class Type>
tnbLib::fixedNormalSlipPointPatchField<Type>::fixedNormalSlipPointPatchField
(
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF,
	const dictionary& dict
)
	:
	slipPointPatchField<Type>(p, iF, dict),
	n_(dict.lookup("n"))
{}


template<class Type>
tnbLib::fixedNormalSlipPointPatchField<Type>::fixedNormalSlipPointPatchField
(
	const fixedNormalSlipPointPatchField<Type>& ptf,
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF,
	const pointPatchFieldMapper& mapper
)
	:
	slipPointPatchField<Type>(ptf, p, iF, mapper),
	n_(ptf.n_)
{}


template<class Type>
tnbLib::fixedNormalSlipPointPatchField<Type>::fixedNormalSlipPointPatchField
(
	const fixedNormalSlipPointPatchField<Type>& ptf,
	const DimensionedField<Type, pointMesh>& iF
)
	:
	slipPointPatchField<Type>(ptf, iF),
	n_(ptf.n_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::fixedNormalSlipPointPatchField<Type>::evaluate
(
	const Pstream::commsTypes
)
{
	tmp<Field<Type>> tvalues =
		transform(I - n_ * n_, this->patchInternalField());

	// Get internal field to insert values into
	Field<Type>& iF = const_cast<Field<Type>&>(this->primitiveField());

	this->setInInternalField(iF, tvalues());
}


template<class Type>
void tnbLib::fixedNormalSlipPointPatchField<Type>::write(Ostream& os) const
{
	slipPointPatchField<Type>::write(os);
	os.writeKeyword("n")
		<< n_ << token::END_STATEMENT << nl;
}


// ************************************************************************* //