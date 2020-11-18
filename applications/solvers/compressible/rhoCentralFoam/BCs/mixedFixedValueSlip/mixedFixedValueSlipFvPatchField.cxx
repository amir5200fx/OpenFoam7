#include <mixedFixedValueSlipFvPatchField.hxx>

//#include <symmTransformField.hxx>
//
//// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //
//
//template<class Type>
//tnbLib::mixedFixedValueSlipFvPatchField<Type>::mixedFixedValueSlipFvPatchField
//(
//	const fvPatch& p,
//	const DimensionedField<Type, volMesh>& iF
//)
//	:
//	transformFvPatchField<Type>(p, iF),
//	refValue_(p.size()),
//	valueFraction_(p.size(), 1.0)
//{}
//
//
//template<class Type>
//tnbLib::mixedFixedValueSlipFvPatchField<Type>::mixedFixedValueSlipFvPatchField
//(
//	const fvPatch& p,
//	const DimensionedField<Type, volMesh>& iF,
//	const dictionary& dict
//)
//	:
//	transformFvPatchField<Type>(p, iF),
//	refValue_("refValue", dict, p.size()),
//	valueFraction_("valueFraction", dict, p.size())
//{}
//
//
//template<class Type>
//tnbLib::mixedFixedValueSlipFvPatchField<Type>::mixedFixedValueSlipFvPatchField
//(
//	const mixedFixedValueSlipFvPatchField<Type>& ptf,
//	const fvPatch& p,
//	const DimensionedField<Type, volMesh>& iF,
//	const fvPatchFieldMapper& mapper
//)
//	:
//	transformFvPatchField<Type>(ptf, p, iF, mapper),
//	refValue_(mapper(ptf.refValue_)),
//	valueFraction_(mapper(ptf.valueFraction_))
//{}
//
//
//template<class Type>
//tnbLib::mixedFixedValueSlipFvPatchField<Type>::mixedFixedValueSlipFvPatchField
//(
//	const mixedFixedValueSlipFvPatchField<Type>& ptf
//)
//	:
//	transformFvPatchField<Type>(ptf),
//	refValue_(ptf.refValue_),
//	valueFraction_(ptf.valueFraction_)
//{}
//
//
//template<class Type>
//tnbLib::mixedFixedValueSlipFvPatchField<Type>::mixedFixedValueSlipFvPatchField
//(
//	const mixedFixedValueSlipFvPatchField<Type>& ptf,
//	const DimensionedField<Type, volMesh>& iF
//)
//	:
//	transformFvPatchField<Type>(ptf, iF),
//	refValue_(ptf.refValue_),
//	valueFraction_(ptf.valueFraction_)
//{}
//
//
//// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //
//
//template<class Type>
//void tnbLib::mixedFixedValueSlipFvPatchField<Type>::autoMap
//(
//	const fvPatchFieldMapper& m
//)
//{
//	m(*this, *this);
//	m(refValue_, refValue_);
//	m(valueFraction_, valueFraction_);
//}
//
//
//template<class Type>
//void tnbLib::mixedFixedValueSlipFvPatchField<Type>::rmap
//(
//	const fvPatchField<Type>& ptf,
//	const labelList& addr
//)
//{
//	transformFvPatchField<Type>::rmap(ptf, addr);
//
//	const mixedFixedValueSlipFvPatchField<Type>& dmptf =
//		refCast<const mixedFixedValueSlipFvPatchField<Type>>(ptf);
//
//	refValue_.rmap(dmptf.refValue_, addr);
//	valueFraction_.rmap(dmptf.valueFraction_, addr);
//}
//
//
//template<class Type>
//tnbLib::tmp<tnbLib::Field<Type>>
//tnbLib::mixedFixedValueSlipFvPatchField<Type>::snGrad() const
//{
//	tmp<vectorField> nHat = this->patch().nf();
//	Field<Type> pif(this->patchInternalField());
//
//	return
//		(
//			valueFraction_*refValue_
//			+ (1.0 - valueFraction_)*transform(I - sqr(nHat), pif) - pif
//			)*this->patch().deltaCoeffs();
//}
//
//
//template<class Type>
//void tnbLib::mixedFixedValueSlipFvPatchField<Type>::evaluate
//(
//	const Pstream::commsTypes
//)
//{
//	if (!this->updated())
//	{
//		this->updateCoeffs();
//	}
//
//	vectorField nHat(this->patch().nf());
//
//	Field<Type>::operator=
//		(
//			valueFraction_*refValue_
//			+
//			(1.0 - valueFraction_)
//			*transform(I - nHat * nHat, this->patchInternalField())
//			);
//
//	transformFvPatchField<Type>::evaluate();
//}
//
//
//template<class Type>
//tnbLib::tmp<tnbLib::Field<Type>>
//tnbLib::mixedFixedValueSlipFvPatchField<Type>::snGradTransformDiag() const
//{
//	vectorField nHat(this->patch().nf());
//	vectorField diag(nHat.size());
//
//	diag.replace(vector::X, mag(nHat.component(vector::X)));
//	diag.replace(vector::Y, mag(nHat.component(vector::Y)));
//	diag.replace(vector::Z, mag(nHat.component(vector::Z)));
//
//	return
//		valueFraction_ * Type(pTraits<Type>::one)
//		+ (1.0 - valueFraction_)
//		*transformFieldMask<Type>(pow<vector, pTraits<Type>::rank>(diag));
//}
//
//
//template<class Type>
//void tnbLib::mixedFixedValueSlipFvPatchField<Type>::write(Ostream& os) const
//{
//	transformFvPatchField<Type>::write(os);
//	writeEntry(os, "refValue", refValue_);
//	writeEntry(os, "valueFraction", valueFraction_);
//}
//
//
//// ************************************************************************* //