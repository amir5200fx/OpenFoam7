#include <transformField.hxx>

#include <FieldM.hxx>
#include <diagTensor.hxx>

#include <FieldReuseFunctions.hxx>  // added by amir

// * * * * * * * * * * * * * * * global functions  * * * * * * * * * * * * * //

void tnbLib::transform
(
	vectorField& rtf,
	const quaternion& q,
	const vectorField& tf
)
{
	tensor t = q.R();
	TFOR_ALL_F_OP_FUNC_S_F(vector, rtf, =, transform, tensor, t, vector, tf)
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::transform
(
	const quaternion& q,
	const vectorField& tf
)
{
	tmp<vectorField > tranf(new vectorField(tf.size()));
	transform(tranf.ref(), q, tf);
	return tranf;
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::transform
(
	const quaternion& q,
	const tmp<vectorField>& ttf
)
{
	tmp<vectorField > tranf = New(ttf);
	transform(tranf.ref(), q, ttf());
	ttf.clear();
	return tranf;
}


void tnbLib::transformPoints
(
	vectorField& rtf,
	const septernion& tr,
	const vectorField& tf
)
{
	vector T = tr.t();

	// Check if any translation
	if (mag(T) > vSmall)
	{
		TFOR_ALL_F_OP_F_OP_S(vector, rtf, =, vector, tf, -, vector, T);
	}
	else
	{
		rtf = tf;
	}

	// Check if any rotation
	if (mag(tr.r().R() - I) > small)
	{
		transform(rtf, tr.r(), rtf);
	}
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::transformPoints
(
	const septernion& tr,
	const vectorField& tf
)
{
	tmp<vectorField > tranf(new vectorField(tf.size()));
	transformPoints(tranf.ref(), tr, tf);
	return tranf;
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::transformPoints
(
	const septernion& tr,
	const tmp<vectorField>& ttf
)
{
	tmp<vectorField > tranf = New(ttf);
	transformPoints(tranf.ref(), tr, ttf());
	ttf.clear();
	return tranf;
}

#include <transformField.hxx>
#include <tensorField.hxx> 

namespace tnbLib
{
	template<>
	tmp<Field<symmTensor>> transformFieldMask<symmTensor>
		(
			const tensorField& tf
			)
	{
		return symm(tf);
	}

	template<>
	tmp<Field<symmTensor>> transformFieldMask<symmTensor>
		(
			const tmp<tensorField>& ttf
			)
	{
		tmp<Field<symmTensor>> ret = transformFieldMask<symmTensor>(ttf());
		ttf.clear();
		return ret;
	}

	template<>
	tmp<Field<sphericalTensor>> transformFieldMask<sphericalTensor>
		(
			const tensorField& tf
			)
	{
		return sph(tf);
	}

	template<>
	tmp<Field<sphericalTensor>> transformFieldMask<sphericalTensor>
		(
			const tmp<tensorField>& ttf
			)
	{
		tmp<Field<sphericalTensor>> ret =
			transformFieldMask<sphericalTensor>(ttf());
		ttf.clear();
		return ret;
	}
}

// ************************************************************************* //