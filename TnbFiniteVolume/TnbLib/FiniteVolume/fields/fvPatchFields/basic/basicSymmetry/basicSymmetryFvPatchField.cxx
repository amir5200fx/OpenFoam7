#include <basicSymmetryFvPatchField.hxx>

#include <symmTransformField.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::basicSymmetryFvPatchField<Type>::basicSymmetryFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	transformFvPatchField<Type>(p, iF)
{}


template<class Type>
tnbLib::basicSymmetryFvPatchField<Type>::basicSymmetryFvPatchField
(
	const basicSymmetryFvPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	transformFvPatchField<Type>(ptf, p, iF, mapper)
{}


template<class Type>
tnbLib::basicSymmetryFvPatchField<Type>::basicSymmetryFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict
)
	:
	transformFvPatchField<Type>(p, iF, dict)
{
	this->evaluate();
}


template<class Type>
tnbLib::basicSymmetryFvPatchField<Type>::basicSymmetryFvPatchField
(
	const basicSymmetryFvPatchField<Type>& ptf
)
	:
	transformFvPatchField<Type>(ptf)
{}


template<class Type>
tnbLib::basicSymmetryFvPatchField<Type>::basicSymmetryFvPatchField
(
	const basicSymmetryFvPatchField<Type>& ptf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	transformFvPatchField<Type>(ptf, iF)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::basicSymmetryFvPatchField<Type>::snGrad() const
{
	tmp<vectorField> nHat = this->patch().nf();

	const Field<Type> iF(this->patchInternalField());

	return
		(transform(I - 2.0*sqr(nHat), iF) - iF)
		*(this->patch().deltaCoeffs() / 2.0);
}


template<class Type>
void tnbLib::basicSymmetryFvPatchField<Type>::evaluate(const Pstream::commsTypes)
{
	if (!this->updated())
	{
		this->updateCoeffs();
	}

	tmp<vectorField> nHat = this->patch().nf();

	const Field<Type> iF(this->patchInternalField());

	Field<Type>::operator=
		(
		(iF + transform(I - 2.0*sqr(nHat), iF)) / 2.0
			);

	transformFvPatchField<Type>::evaluate();
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::basicSymmetryFvPatchField<Type>::snGradTransformDiag() const
{
	const vectorField nHat(this->patch().nf());

	vectorField diag(nHat.size());

	diag.replace(vector::X, mag(nHat.component(vector::X)));
	diag.replace(vector::Y, mag(nHat.component(vector::Y)));
	diag.replace(vector::Z, mag(nHat.component(vector::Z)));

	return transformFieldMask<Type>(pow<vector, pTraits<Type>::rank>(diag));
}


// ************************************************************************* //