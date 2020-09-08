#pragma once
#include <wedgeFvPatch.hxx>
#include <transformField.hxx>
#include <symmTransform.hxx>
#include <diagTensor.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::wedgeFvPatchField<Type>::wedgeFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	transformFvPatchField<Type>(p, iF)
{}


template<class Type>
tnbLib::wedgeFvPatchField<Type>::wedgeFvPatchField
(
	const wedgeFvPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	transformFvPatchField<Type>(ptf, p, iF, mapper)
{
	if (!isType<wedgeFvPatch>(this->patch()))
	{
		FatalErrorInFunction
			<< "' not constraint type '" << typeName << "'"
			<< "\n    for patch " << p.name()
			<< " of field " << this->internalField().name()
			<< " in file " << this->internalField().objectPath()
			<< exit(FatalIOError);
	}
}


template<class Type>
tnbLib::wedgeFvPatchField<Type>::wedgeFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict
)
	:
	transformFvPatchField<Type>(p, iF, dict)
{
	if (!isType<wedgeFvPatch>(p))
	{
		FatalIOErrorInFunction
		(
			dict
		) << "\n    patch type '" << p.type()
			<< "' not constraint type '" << typeName << "'"
			<< "\n    for patch " << p.name()
			<< " of field " << this->internalField().name()
			<< " in file " << this->internalField().objectPath()
			<< exit(FatalIOError);
	}

	evaluate();
}


template<class Type>
tnbLib::wedgeFvPatchField<Type>::wedgeFvPatchField
(
	const wedgeFvPatchField<Type>& ptf
)
	:
	transformFvPatchField<Type>(ptf)
{}


template<class Type>
tnbLib::wedgeFvPatchField<Type>::wedgeFvPatchField
(
	const wedgeFvPatchField<Type>& ptf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	transformFvPatchField<Type>(ptf, iF)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::Field<Type>> tnbLib::wedgeFvPatchField<Type>::snGrad() const
{
	const Field<Type> pif(this->patchInternalField());

	return
		(
			transform(refCast<const wedgeFvPatch>(this->patch()).cellT(), pif) - pif
			)*(0.5*this->patch().deltaCoeffs());
}


template<class Type>
void tnbLib::wedgeFvPatchField<Type>::evaluate(const Pstream::commsTypes)
{
	if (!this->updated())
	{
		this->updateCoeffs();
	}

	fvPatchField<Type>::operator==
		(
			transform
			(
				refCast<const wedgeFvPatch>(this->patch()).faceT(),
				this->patchInternalField()
			)
			);
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::wedgeFvPatchField<Type>::snGradTransformDiag() const
{
	const diagTensor diagT =
		0.5*diag(I - refCast<const wedgeFvPatch>(this->patch()).cellT());

	const vector diagV(diagT.xx(), diagT.yy(), diagT.zz());

	return tmp<Field<Type>>
		(
			new Field<Type>
			(
				this->size(),
				transformMask<Type>
				(
					pow
					(
						diagV,
						pTraits<typename powProduct<vector, pTraits<Type>::rank>
						::type>::zero
					)
					)
				)
			);
}


// ************************************************************************* //