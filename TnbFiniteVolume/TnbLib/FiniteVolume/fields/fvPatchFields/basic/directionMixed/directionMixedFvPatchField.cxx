#include <directionMixedFvPatchField.hxx>

#include <symmTransformField.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::directionMixedFvPatchField<Type>::directionMixedFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	transformFvPatchField<Type>(p, iF),
	refValue_(p.size()),
	refGrad_(p.size()),
	valueFraction_(p.size())
{}


template<class Type>
tnbLib::directionMixedFvPatchField<Type>::directionMixedFvPatchField
(
	const directionMixedFvPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	transformFvPatchField<Type>(ptf, p, iF, mapper),
	refValue_(mapper(ptf.refValue_)),
	refGrad_(mapper(ptf.refGrad_)),
	valueFraction_(mapper(ptf.valueFraction_))
{
	if (notNull(iF) && mapper.hasUnmapped())
	{
		WarningInFunction
			<< "On field " << iF.name() << " patch " << p.name()
			<< " patchField " << this->type()
			<< " : mapper does not map all values." << nl
			<< "    To avoid this warning fully specify the mapping in derived"
			<< " patch fields." << endl;
	}
}


template<class Type>
tnbLib::directionMixedFvPatchField<Type>::directionMixedFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict
)
	:
	transformFvPatchField<Type>(p, iF, dict),
	refValue_("refValue", dict, p.size()),
	refGrad_("refGradient", dict, p.size()),
	valueFraction_("valueFraction", dict, p.size())
{
	evaluate();
}


template<class Type>
tnbLib::directionMixedFvPatchField<Type>::directionMixedFvPatchField
(
	const directionMixedFvPatchField<Type>& ptf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	transformFvPatchField<Type>(ptf, iF),
	refValue_(ptf.refValue_),
	refGrad_(ptf.refGrad_),
	valueFraction_(ptf.valueFraction_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::directionMixedFvPatchField<Type>::autoMap
(
	const fvPatchFieldMapper& m
)
{
	transformFvPatchField<Type>::autoMap(m);
	m(refValue_, refValue_);
	m(refGrad_, refGrad_);
	m(valueFraction_, valueFraction_);
}


template<class Type>
void tnbLib::directionMixedFvPatchField<Type>::rmap
(
	const fvPatchField<Type>& ptf,
	const labelList& addr
)
{
	transformFvPatchField<Type>::rmap(ptf, addr);

	const directionMixedFvPatchField<Type>& dmptf =
		refCast<const directionMixedFvPatchField<Type>>(ptf);

	refValue_.rmap(dmptf.refValue_, addr);
	refGrad_.rmap(dmptf.refGrad_, addr);
	valueFraction_.rmap(dmptf.valueFraction_, addr);
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::directionMixedFvPatchField<Type>::snGrad() const
{
	const Field<Type> pif(this->patchInternalField());

	tmp<Field<Type>> normalValue = transform(valueFraction_, refValue_);

	tmp<Field<Type>> gradValue = pif + refGrad_ / this->patch().deltaCoeffs();

	tmp<Field<Type>> transformGradValue =
		transform(I - valueFraction_, gradValue);

	return
		(normalValue + transformGradValue - pif)*
		this->patch().deltaCoeffs();
}


template<class Type>
void tnbLib::directionMixedFvPatchField<Type>::evaluate(const Pstream::commsTypes)
{
	if (!this->updated())
	{
		this->updateCoeffs();
	}

	tmp<Field<Type>> normalValue = transform(valueFraction_, refValue_);

	tmp<Field<Type>> gradValue =
		this->patchInternalField() + refGrad_ / this->patch().deltaCoeffs();

	tmp<Field<Type>> transformGradValue =
		transform(I - valueFraction_, gradValue);

	Field<Type>::operator=(normalValue + transformGradValue);

	transformFvPatchField<Type>::evaluate();
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::directionMixedFvPatchField<Type>::snGradTransformDiag() const
{
	vectorField diag(valueFraction_.size());

	diag.replace
	(
		vector::X,
		sqrt(mag(valueFraction_.component(symmTensor::XX)))
	);
	diag.replace
	(
		vector::Y,
		sqrt(mag(valueFraction_.component(symmTensor::YY)))
	);
	diag.replace
	(
		vector::Z,
		sqrt(mag(valueFraction_.component(symmTensor::ZZ)))
	);

	return transformFieldMask<Type>(pow<vector, pTraits<Type>::rank>(diag));
}


template<class Type>
void tnbLib::directionMixedFvPatchField<Type>::write(Ostream& os) const
{
	transformFvPatchField<Type>::write(os);
	writeEntry(os, "refValue", refValue_);
	writeEntry(os, "refGradient", refGrad_);
	writeEntry(os, "valueFraction", valueFraction_);
	writeEntry(os, "value", *this);
}


// ************************************************************************* //