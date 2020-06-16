#include <symmTensorField.hxx>

#include <transformField.hxx>

#define TEMPLATE
#include <FieldFunctionsM.cxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * global functions  * * * * * * * * * * * * * //

	void sqr(Field<symmTensor>& res, const UList<vector>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(symmTensor, res, =, ::tnbLib::sqr, vector, f)
	}

	tmp<Field<symmTensor>> sqr(const UList<vector>& f)
	{
		tmp<Field<symmTensor>> tRes(new Field<symmTensor>(f.size()));
		sqr(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<symmTensor>> sqr(const tmp<Field<vector>>& tf)
	{
		tmp<Field<symmTensor>> tRes = reuseTmp<symmTensor, vector>::New(tf);
		sqr(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void innerSqr(Field<symmTensor>& res, const UList<symmTensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(symmTensor, res, =, ::tnbLib::innerSqr, symmTensor, f)
	}

	tmp<Field<symmTensor>> innerSqr(const UList<symmTensor>& f)
	{
		tmp<Field<symmTensor>> tRes(new Field<symmTensor>(f.size()));
		innerSqr(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<symmTensor>> innerSqr(const tmp<Field<symmTensor>>& tf)
	{
		tmp<Field<symmTensor>> tRes = reuseTmp<symmTensor, symmTensor>::New(tf);
		innerSqr(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

		
	void tr(Field<scalar>& res, const UList<symmTensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::tr, symmTensor, f)
	}

	tmp<Field<scalar>> tr(const UList<symmTensor>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		tr(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> tr(const tmp<Field<symmTensor>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, symmTensor>::New(tf);
		tr(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void sph(Field<sphericalTensor>& res, const UList<symmTensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(sphericalTensor, res, =, ::tnbLib::sph, symmTensor, f)
	}

	tmp<Field<sphericalTensor>> sph(const UList<symmTensor>& f)
	{
		tmp<Field<sphericalTensor>> tRes(new Field<sphericalTensor>(f.size()));
		sph(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<sphericalTensor>> sph(const tmp<Field<symmTensor>>& tf)
	{
		tmp<Field<sphericalTensor>> tRes = reuseTmp<sphericalTensor, symmTensor>::New(tf);
		sph(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void symm(Field<symmTensor>& res, const UList<symmTensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(symmTensor, res, =, ::tnbLib::symm, symmTensor, f)
	}

	tmp<Field<symmTensor>> symm(const UList<symmTensor>& f)
	{
		tmp<Field<symmTensor>> tRes(new Field<symmTensor>(f.size()));
		symm(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<symmTensor>> symm(const tmp<Field<symmTensor>>& tf)
	{
		tmp<Field<symmTensor>> tRes = reuseTmp<symmTensor, symmTensor>::New(tf);
		symm(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void twoSymm(Field<symmTensor>& res, const UList<symmTensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(symmTensor, res, =, ::tnbLib::twoSymm, symmTensor, f)
	}

	tmp<Field<symmTensor>> twoSymm(const UList<symmTensor>& f)
	{
		tmp<Field<symmTensor>> tRes(new Field<symmTensor>(f.size()));
		twoSymm(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<symmTensor>> twoSymm(const tmp<Field<symmTensor>>& tf)
	{
		tmp<Field<symmTensor>> tRes = reuseTmp<symmTensor, symmTensor>::New(tf);
		twoSymm(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void dev(Field<symmTensor>& res, const UList<symmTensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(symmTensor, res, =, ::tnbLib::dev, symmTensor, f)
	}

	tmp<Field<symmTensor>> dev(const UList<symmTensor>& f)
	{
		tmp<Field<symmTensor>> tRes(new Field<symmTensor>(f.size()));
		dev(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<symmTensor>> dev(const tmp<Field<symmTensor>>& tf)
	{
		tmp<Field<symmTensor>> tRes = reuseTmp<symmTensor, symmTensor>::New(tf);
		dev(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void dev2(Field<symmTensor>& res, const UList<symmTensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(symmTensor, res, =, ::tnbLib::dev2, symmTensor, f)
	}

	tmp<Field<symmTensor>> dev2(const UList<symmTensor>& f)
	{
		tmp<Field<symmTensor>> tRes(new Field<symmTensor>(f.size()));
		dev2(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<symmTensor>> dev2(const tmp<Field<symmTensor>>& tf)
	{
		tmp<Field<symmTensor>> tRes = reuseTmp<symmTensor, symmTensor>::New(tf);
		dev2(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void det(Field<scalar>& res, const UList<symmTensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::det, symmTensor, f)
	}

	tmp<Field<scalar>> det(const UList<symmTensor>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		det(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> det(const tmp<Field<symmTensor>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, symmTensor>::New(tf);
		det(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void cof(Field<symmTensor>& res, const UList<symmTensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(symmTensor, res, =, ::tnbLib::cof, symmTensor, f)
	}

	tmp<Field<symmTensor>> cof(const UList<symmTensor>& f)
	{
		tmp<Field<symmTensor>> tRes(new Field<symmTensor>(f.size()));
		cof(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<symmTensor>> cof(const tmp<Field<symmTensor>>& tf)
	{
		tmp<Field<symmTensor>> tRes = reuseTmp<symmTensor, symmTensor>::New(tf);
		cof(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

		void inv(Field<symmTensor>& tf, const UList<symmTensor>& tf1)
	{
		if (tf.empty())
		{
			return;
		}

		scalar scale = magSqr(tf1[0]);
		Vector<bool> removeCmpts
		(
			magSqr(tf1[0].xx()) / scale < small,
			magSqr(tf1[0].yy()) / scale < small,
			magSqr(tf1[0].zz()) / scale < small
		);

		if (removeCmpts.x() || removeCmpts.y() || removeCmpts.z())
		{
			symmTensorField tf1Plus(tf1);

			if (removeCmpts.x())
			{
				tf1Plus += symmTensor(1, 0, 0, 0, 0, 0);
			}

			if (removeCmpts.y())
			{
				tf1Plus += symmTensor(0, 0, 0, 1, 0, 0);
			}

			if (removeCmpts.z())
			{
				tf1Plus += symmTensor(0, 0, 0, 0, 0, 1);
			}

			TFOR_ALL_F_OP_FUNC_F(symmTensor, tf, =, inv, symmTensor, tf1Plus)

				if (removeCmpts.x())
				{
					tf -= symmTensor(1, 0, 0, 0, 0, 0);
				}

			if (removeCmpts.y())
			{
				tf -= symmTensor(0, 0, 0, 1, 0, 0);
			}

			if (removeCmpts.z())
			{
				tf -= symmTensor(0, 0, 0, 0, 0, 1);
			}
		}
		else
		{
			TFOR_ALL_F_OP_FUNC_F(symmTensor, tf, =, inv, symmTensor, tf1)
		}
	}

	tmp<symmTensorField> inv(const UList<symmTensor>& tf)
	{
		tmp<symmTensorField> result(new symmTensorField(tf.size()));
		inv(result.ref(), tf);
		return result;
	}

	tmp<symmTensorField> inv(const tmp<symmTensorField>& tf)
	{
		tmp<symmTensorField> tRes = New(tf);
		inv(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}


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
	tmp<Field<symmTensor>> transformFieldMask<symmTensor>
		(
			const symmTensorField& stf
			)
	{
		return stf;
	}

	template<>
	tmp<Field<symmTensor>> transformFieldMask<symmTensor>
		(
			const tmp<symmTensorField>& tstf
			)
	{
		return tstf;
	}


	// * * * * * * * * * * * * * * * global operators  * * * * * * * * * * * * * //

	void hdual(Field<vector>& res, const UList<symmTensor>& f)
	{
		TFOR_ALL_F_OP_OP_F(vector, res, =, *, symmTensor, f)
	}

	tmp<Field<vector>> operator *(const UList<symmTensor>& f)
	{
		tmp<Field<vector>> tRes(new Field<vector>(f.size()));
		hdual(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<vector>> operator *(const tmp<Field<symmTensor>>& tf)
	{
		tmp<Field<vector>> tRes = reuseTmp<vector, symmTensor>::New(tf);
		hdual(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

		
	void dot(Field<tensor>& res, const UList<symmTensor>& f1, const UList<symmTensor>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor, res, =, symmTensor, f1, &, symmTensor, f2)
	}

	tmp<Field<tensor>> operator &(const UList<symmTensor>& f1, const UList<symmTensor>& f2)
	{
		tmp<Field<tensor>> tRes(new Field<tensor>(f1.size()));
		dot(tRes.ref(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor>> operator &(const UList<symmTensor>& f1, const tmp<Field<symmTensor>>& tf2)
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, symmTensor>::New(tf2);
		dot(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	tmp<Field<tensor>> operator &(const tmp<Field<symmTensor>>& tf1, const UList<symmTensor>& f2)
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, symmTensor>::New(tf1);
		dot(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	tmp<Field<tensor>> operator &(const tmp<Field<symmTensor>>& tf1, const tmp<Field<symmTensor>>& tf2)
	{
		tmp<Field<tensor>> tRes = reuseTmpTmp<tensor, symmTensor, symmTensor, symmTensor>::New(tf1, tf2);
		dot(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}
		
	void dot(Field<tensor>& res, const symmTensor& s1, const UList<symmTensor>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor, res, =, symmTensor, s1, &, symmTensor, f2)
	}

	tmp<Field<tensor>> operator &(const symmTensor& s1, const UList<symmTensor>& f2)
	{
		tmp<Field<tensor>> tRes(new Field<tensor>(f2.size()));
		dot(tRes.ref(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor>> operator &(const symmTensor& s1, const tmp<Field<symmTensor>>& tf2)
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, symmTensor>::New(tf2);
		dot(tRes.ref(), s1, tf2());
		tf2.clear();
		return tRes;
	} 
	
	void dot(Field<tensor>& res, const UList<symmTensor>& f1, const symmTensor& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor, res, =, symmTensor, f1, &, symmTensor, s2)
	}

	tmp<Field<tensor>> operator &(const UList<symmTensor>& f1, const symmTensor& s2)
	{
		tmp<Field<tensor>> tRes(new Field<tensor>(f1.size()));
		dot(tRes.ref(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor>> operator &(const tmp<Field<symmTensor>>& tf1, const symmTensor& s2)
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, symmTensor>::New(tf1);
		dot(tRes.ref(), tf1(), s2);
		tf1.clear();
		return tRes;
	}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <undefFieldFunctionsM.hxx>

// ************************************************************************* //