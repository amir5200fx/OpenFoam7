#include <symmTransformField.hxx>

#include <transformField.hxx>

#define TEMPLATE
#include <FieldFunctionsM.cxx>

template<>
tnbLib::tmp<tnbLib::Field<tnbLib::sphericalTensor>> tnbLib::transformFieldMask<tnbLib::sphericalTensor>
(
	const symmTensorField& stf
	)
{
	return sph(stf);
}

template<>
tnbLib::tmp<tnbLib::Field<tnbLib::sphericalTensor>> tnbLib::transformFieldMask<tnbLib::sphericalTensor>
(
	const tmp<symmTensorField>& tstf
	)
{
	tmp<Field<sphericalTensor>> ret =
		transformFieldMask<sphericalTensor>(tstf());
	tstf.clear();
	return ret;
}

template<>
tnbLib::tmp<tnbLib::Field<tnbLib::symmTensor>> tnbLib::transformFieldMask<tnbLib::symmTensor>
(
	const symmTensorField& stf
	)
{
	return stf;
}

template<>
tnbLib::tmp<tnbLib::Field<tnbLib::symmTensor>> tnbLib::transformFieldMask<tnbLib::symmTensor>
(
	const tmp<symmTensorField>& tstf
	)
{
	return tstf;
}

template<>
tnbLib::tmp<tnbLib::Field<tnbLib::tensor>> tnbLib::transformFieldMask<tnbLib::tensor>
(
	const symmTensorField& stf
	)
{
	tmp<tensorField> tRes(new tensorField(stf.size()));
	tensorField& res = tRes.ref();
	TFOR_ALL_F_OP_F(tensor, res, =, symmTensor, stf)
		return tRes;
}

template<>
tnbLib::tmp<tnbLib::Field<tnbLib::tensor>> tnbLib::transformFieldMask<tnbLib::tensor>
(
	const tmp<symmTensorField>& tstf
	)
{
	tmp<Field<tensor>> ret = transformFieldMask<tensor>(tstf());
	tstf.clear();
	return ret;
}
