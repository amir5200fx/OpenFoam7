#include <sphericalTensorField.hxx>

#include <transformField.hxx>
#include <tensorField.hxx> // added by amir!

#define TEMPLATE
#include <FieldFunctionsM.cxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * global functions  * * * * * * * * * * * * * //

	TEMPLATE void tr(Field<scalar>& res, const UList<sphericalTensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::tr, sphericalTensor, f)
	}

	TEMPLATE tmp<Field<scalar>> tr(const UList<sphericalTensor>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		tr(tRes.ref(), f);
		return tRes;
	}

	TEMPLATE tmp<Field<scalar>> tr(const tmp<Field<sphericalTensor>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, sphericalTensor>::New(tf);
		tr(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	TEMPLATE void sph(Field<sphericalTensor>& res, const UList<sphericalTensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(sphericalTensor, res, =, ::tnbLib::sph, sphericalTensor, f)
	}

	TEMPLATE tmp<Field<sphericalTensor>> sph(const UList<sphericalTensor>& f)
	{
		tmp<Field<sphericalTensor>> tRes(new Field<sphericalTensor>(f.size()));
		sph(tRes.ref(), f);
		return tRes;
	}

	TEMPLATE tmp<Field<sphericalTensor>> sph(const tmp<Field<sphericalTensor>>& tf)
	{
		tmp<Field<sphericalTensor>> tRes = reuseTmp<sphericalTensor, sphericalTensor>::New(tf);
		sph(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	TEMPLATE void det(Field<scalar>& res, const UList<sphericalTensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::det, sphericalTensor, f)
	}

	TEMPLATE tmp<Field<scalar>> det(const UList<sphericalTensor>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		det(tRes.ref(), f);
		return tRes;
	}

	TEMPLATE tmp<Field<scalar>> det(const tmp<Field<sphericalTensor>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, sphericalTensor>::New(tf);
		det(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	TEMPLATE void inv(Field<sphericalTensor>& res, const UList<sphericalTensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(sphericalTensor, res, =, ::tnbLib::inv, sphericalTensor, f)
	}

	TEMPLATE tmp<Field<sphericalTensor>> inv(const UList<sphericalTensor>& f)
	{
		tmp<Field<sphericalTensor>> tRes(new Field<sphericalTensor>(f.size()));
		inv(tRes.ref(), f);
		return tRes;
	}

	TEMPLATE tmp<Field<sphericalTensor>> inv(const tmp<Field<sphericalTensor>>& tf)
	{
		tmp<Field<sphericalTensor>> tRes = reuseTmp<sphericalTensor, sphericalTensor>::New(tf);
		inv(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

		
	TEMPLATE void divide(Field<sphericalTensor>& res, const UList<scalar>& f1, const UList<sphericalTensor>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(sphericalTensor, res, =, scalar, f1, /, sphericalTensor, f2)
	}

	TEMPLATE tmp<Field<sphericalTensor>> operator /(const UList<scalar>& f1, const UList<sphericalTensor>& f2)
	{
		tmp<Field<sphericalTensor>> tRes(new Field<sphericalTensor>(f1.size()));
		divide(tRes.ref(), f1, f2);
		return tRes;
	}

	TEMPLATE tmp<Field<sphericalTensor>> operator /(const UList<scalar>& f1, const tmp<Field<sphericalTensor>>& tf2)
	{
		tmp<Field<sphericalTensor>> tRes = reuseTmp<sphericalTensor, sphericalTensor>::New(tf2);
		divide(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	TEMPLATE tmp<Field<sphericalTensor>> operator /(const tmp<Field<scalar>>& tf1, const UList<sphericalTensor>& f2)
	{
		tmp<Field<sphericalTensor>> tRes = reuseTmp<sphericalTensor, scalar>::New(tf1);
		divide(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	TEMPLATE tmp<Field<sphericalTensor>> operator /(const tmp<Field<scalar>>& tf1, const tmp<Field<sphericalTensor>>& tf2)
	{
		tmp<Field<sphericalTensor>> tRes = reuseTmpTmp<sphericalTensor, scalar, scalar, sphericalTensor>::New(tf1, tf2);
		divide(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}
		
	TEMPLATE void divide(Field<sphericalTensor>& res, const scalar& s1, const UList<sphericalTensor>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(sphericalTensor, res, =, scalar, s1, /, sphericalTensor, f2)
	}

	TEMPLATE tmp<Field<sphericalTensor>> operator /(const scalar& s1, const UList<sphericalTensor>& f2)
	{
		tmp<Field<sphericalTensor>> tRes(new Field<sphericalTensor>(f2.size()));
		divide(tRes.ref(), s1, f2);
		return tRes;
	}

	TEMPLATE tmp<Field<sphericalTensor>> operator /(const scalar& s1, const tmp<Field<sphericalTensor>>& tf2)
	{
		tmp<Field<sphericalTensor>> tRes = reuseTmp<sphericalTensor, sphericalTensor>::New(tf2);
		divide(tRes.ref(), s1, tf2());
		tf2.clear();
		return tRes;
	} 
	
	TEMPLATE void divide(Field<sphericalTensor>& res, const UList<scalar>& f1, const sphericalTensor& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(sphericalTensor, res, =, scalar, f1, /, sphericalTensor, s2)
	}

	TEMPLATE tmp<Field<sphericalTensor>> operator /(const UList<scalar>& f1, const sphericalTensor& s2)
	{
		tmp<Field<sphericalTensor>> tRes(new Field<sphericalTensor>(f1.size()));
		divide(tRes.ref(), f1, s2);
		return tRes;
	}

	TEMPLATE tmp<Field<sphericalTensor>> operator /(const tmp<Field<scalar>>& tf1, const sphericalTensor& s2)
	{
		tmp<Field<sphericalTensor>> tRes = reuseTmp<sphericalTensor, scalar>::New(tf1);
		divide(tRes.ref(), tf1(), s2);
		tf1.clear();
		return tRes;
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


	template<>
	tmp<Field<sphericalTensor>> transformFieldMask<sphericalTensor>
		(
			const symmTensorField& stf
			)
	{
		return sph(stf);
	}

	template<>
	tmp<Field<sphericalTensor>> transformFieldMask<sphericalTensor>
		(
			const tmp<symmTensorField>& tstf
			)
	{
		tmp<Field<sphericalTensor>> ret =
			transformFieldMask<sphericalTensor>(tstf());
		tstf.clear();
		return ret;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <undefFieldFunctionsM.hxx>

// ************************************************************************* //