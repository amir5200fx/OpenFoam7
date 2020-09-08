#pragma once
#include <IOstreams.hxx>
#include <transformField.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::transformFvPatchField<Type>::transformFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	fvPatchField<Type>(p, iF)
{}


template<class Type>
tnbLib::transformFvPatchField<Type>::transformFvPatchField
(
	const transformFvPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fvPatchField<Type>(ptf, p, iF, mapper)
{}


template<class Type>
tnbLib::transformFvPatchField<Type>::transformFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict
)
	:
	fvPatchField<Type>(p, iF, dict, false)
{}


template<class Type>
tnbLib::transformFvPatchField<Type>::transformFvPatchField
(
	const transformFvPatchField<Type>& ptf
)
	:
	fvPatchField<Type>(ptf)
{}


template<class Type>
tnbLib::transformFvPatchField<Type>::transformFvPatchField
(
	const transformFvPatchField<Type>& ptf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	fvPatchField<Type>(ptf, iF)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::transformFvPatchField<Type>::valueInternalCoeffs
(
	const tmp<scalarField>&
) const
{
	return pTraits<Type>::one - snGradTransformDiag();
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::transformFvPatchField<Type>::valueBoundaryCoeffs
(
	const tmp<scalarField>&
) const
{
	return
		*this
		- cmptMultiply
		(
			valueInternalCoeffs(this->patch().weights()),
			this->patchInternalField()
		);
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::transformFvPatchField<Type>::gradientInternalCoeffs() const
{
	return -this->patch().deltaCoeffs()*snGradTransformDiag();
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::transformFvPatchField<Type>::gradientBoundaryCoeffs() const
{
	return
		snGrad()
		- cmptMultiply(gradientInternalCoeffs(), this->patchInternalField());
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::transformFvPatchField<Type>::operator=
(
	const fvPatchField<Type>& ptf
	)
{
	this->evaluate();
}


// ************************************************************************* //