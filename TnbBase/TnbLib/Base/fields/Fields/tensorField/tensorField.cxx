#include <tensorField.hxx>

#include <transformField.hxx>

#define TEMPLATE
#include <FieldFunctionsM.cxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * global functions  * * * * * * * * * * * * * //

	void tr(Field<scalar>& res, const UList<tensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::tr, tensor, f)
	}

	tmp<Field<scalar>> tr(const UList<tensor>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		tr(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> tr(const tmp<Field<tensor>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, tensor>::New(tf);
		tr(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void sph(Field<sphericalTensor>& res, const UList<tensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(sphericalTensor, res, =, ::tnbLib::sph, tensor, f)
	}

	tmp<Field<sphericalTensor>> sph(const UList<tensor>& f)
	{
		tmp<Field<sphericalTensor>> tRes(new Field<sphericalTensor>(f.size()));
		sph(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<sphericalTensor>> sph(const tmp<Field<tensor>>& tf)
	{
		tmp<Field<sphericalTensor>> tRes = reuseTmp<sphericalTensor, tensor>::New(tf);
		sph(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void symm(Field<symmTensor>& res, const UList<tensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(symmTensor, res, =, ::tnbLib::symm, tensor, f)
	}

	tmp<Field<symmTensor>> symm(const UList<tensor>& f)
	{
		tmp<Field<symmTensor>> tRes(new Field<symmTensor>(f.size()));
		symm(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<symmTensor>> symm(const tmp<Field<tensor>>& tf)
	{
		tmp<Field<symmTensor>> tRes = reuseTmp<symmTensor, tensor>::New(tf);
		symm(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void twoSymm(Field<symmTensor>& res, const UList<tensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(symmTensor, res, =, ::tnbLib::twoSymm, tensor, f)
	}

	tmp<Field<symmTensor>> twoSymm(const UList<tensor>& f)
	{
		tmp<Field<symmTensor>> tRes(new Field<symmTensor>(f.size()));
		twoSymm(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<symmTensor>> twoSymm(const tmp<Field<tensor>>& tf)
	{
		tmp<Field<symmTensor>> tRes = reuseTmp<symmTensor, tensor>::New(tf);
		twoSymm(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void skew(Field<tensor>& res, const UList<tensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(tensor, res, =, ::tnbLib::skew, tensor, f)
	}

	tmp<Field<tensor>> skew(const UList<tensor>& f)
	{
		tmp<Field<tensor>> tRes(new Field<tensor>(f.size()));
		skew(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<tensor>> skew(const tmp<Field<tensor>>& tf)
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, tensor>::New(tf);
		skew(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void dev(Field<tensor>& res, const UList<tensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(tensor, res, =, ::tnbLib::dev, tensor, f)
	}

	tmp<Field<tensor>> dev(const UList<tensor>& f)
	{
		tmp<Field<tensor>> tRes(new Field<tensor>(f.size()));
		dev(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<tensor>> dev(const tmp<Field<tensor>>& tf)
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, tensor>::New(tf);
		dev(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void dev2(Field<tensor>& res, const UList<tensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(tensor, res, =, ::tnbLib::dev2, tensor, f)
	}

	tmp<Field<tensor>> dev2(const UList<tensor>& f)
	{
		tmp<Field<tensor>> tRes(new Field<tensor>(f.size()));
		dev2(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<tensor>> dev2(const tmp<Field<tensor>>& tf)
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, tensor>::New(tf);
		dev2(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void det(Field<scalar>& res, const UList<tensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::det, tensor, f)
	}

	tmp<Field<scalar>> det(const UList<tensor>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		det(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> det(const tmp<Field<tensor>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, tensor>::New(tf);
		det(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void cof(Field<tensor>& res, const UList<tensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(tensor, res, =, ::tnbLib::cof, tensor, f)
	}

	tmp<Field<tensor>> cof(const UList<tensor>& f)
	{
		tmp<Field<tensor>> tRes(new Field<tensor>(f.size()));
		cof(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<tensor>> cof(const tmp<Field<tensor>>& tf)
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, tensor>::New(tf);
		cof(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

		void inv(Field<tensor>& tf, const UList<tensor>& tf1)
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
			tensorField tf1Plus(tf1);

			if (removeCmpts.x())
			{
				tf1Plus += tensor(1, 0, 0, 0, 0, 0, 0, 0, 0);
			}

			if (removeCmpts.y())
			{
				tf1Plus += tensor(0, 0, 0, 0, 1, 0, 0, 0, 0);
			}

			if (removeCmpts.z())
			{
				tf1Plus += tensor(0, 0, 0, 0, 0, 0, 0, 0, 1);
			}

			TFOR_ALL_F_OP_FUNC_F(tensor, tf, =, inv, tensor, tf1Plus)

				if (removeCmpts.x())
				{
					tf -= tensor(1, 0, 0, 0, 0, 0, 0, 0, 0);
				}

			if (removeCmpts.y())
			{
				tf -= tensor(0, 0, 0, 0, 1, 0, 0, 0, 0);
			}

			if (removeCmpts.z())
			{
				tf -= tensor(0, 0, 0, 0, 0, 0, 0, 0, 1);
			}
		}
		else
		{
			TFOR_ALL_F_OP_FUNC_F(tensor, tf, =, inv, tensor, tf1)
		}
	}

	tmp<tensorField> inv(const UList<tensor>& tf)
	{
		tmp<tensorField> result(new tensorField(tf.size()));
		inv(result.ref(), tf);
		return result;
	}

	tmp<tensorField> inv(const tmp<tensorField>& tf)
	{
		tmp<tensorField> tRes = New(tf);
		inv(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	void eigenValues(Field<vector>& res, const UList<tensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(vector, res, =, ::tnbLib::eigenValues, tensor, f)
	}

	tmp<Field<vector>> eigenValues(const UList<tensor>& f)
	{
		tmp<Field<vector>> tRes(new Field<vector>(f.size()));
		eigenValues(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<vector>> eigenValues(const tmp<Field<tensor>>& tf)
	{
		tmp<Field<vector>> tRes = reuseTmp<vector, tensor>::New(tf);
		eigenValues(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void eigenVectors(Field<tensor>& res, const UList<tensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(tensor, res, =, ::tnbLib::eigenVectors, tensor, f)
	}

	tmp<Field<tensor>> eigenVectors(const UList<tensor>& f)
	{
		tmp<Field<tensor>> tRes(new Field<tensor>(f.size()));
		eigenVectors(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<tensor>> eigenVectors(const tmp<Field<tensor>>& tf)
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, tensor>::New(tf);
		eigenVectors(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

		
	void eigenValues(Field<vector>& res, const UList<symmTensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(vector, res, =, ::tnbLib::eigenValues, symmTensor, f)
	}

	tmp<Field<vector>> eigenValues(const UList<symmTensor>& f)
	{
		tmp<Field<vector>> tRes(new Field<vector>(f.size()));
		eigenValues(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<vector>> eigenValues(const tmp<Field<symmTensor>>& tf)
	{
		tmp<Field<vector>> tRes = reuseTmp<vector, symmTensor>::New(tf);
		eigenValues(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void eigenVectors(Field<tensor>& res, const UList<symmTensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(tensor, res, =, ::tnbLib::eigenVectors, symmTensor, f)
	}

	tmp<Field<tensor>> eigenVectors(const UList<symmTensor>& f)
	{
		tmp<Field<tensor>> tRes(new Field<tensor>(f.size()));
		eigenVectors(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<tensor>> eigenVectors(const tmp<Field<symmTensor>>& tf)
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, symmTensor>::New(tf);
		eigenVectors(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}


	// moved to the symmTransformField.cxx file by amir
		/*template<>
	tmp<Field<tensor>> transformFieldMask<tensor>
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
	tmp<Field<tensor>> transformFieldMask<tensor>
		(
			const tmp<symmTensorField>& tstf
			)
	{
		tmp<Field<tensor>> ret = transformFieldMask<tensor>(tstf());
		tstf.clear();
		return ret;
	}*/


	// * * * * * * * * * * * * * * * global operators  * * * * * * * * * * * * * //

	void hdual(Field<vector>& res, const UList<tensor>& f)
	{
		TFOR_ALL_F_OP_OP_F(vector, res, =, *, tensor, f)
	}

	tmp<Field<vector>> operator *(const UList<tensor>& f)
	{
		tmp<Field<vector>> tRes(new Field<vector>(f.size()));
		hdual(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<vector>> operator *(const tmp<Field<tensor>>& tf)
	{
		tmp<Field<vector>> tRes = reuseTmp<vector, tensor>::New(tf);
		hdual(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void hdual(Field<tensor>& res, const UList<vector>& f)
	{
		TFOR_ALL_F_OP_OP_F(tensor, res, =, *, vector, f)
	}

	tmp<Field<tensor>> operator *(const UList<vector>& f)
	{
		tmp<Field<tensor>> tRes(new Field<tensor>(f.size()));
		hdual(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<tensor>> operator *(const tmp<Field<vector>>& tf)
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, vector>::New(tf);
		hdual(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

		
	void divide(Field<vector>& res, const UList<vector>& f1, const UList<tensor>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(vector, res, =, vector, f1, /, tensor, f2)
	}

	tmp<Field<vector>> operator /(const UList<vector>& f1, const UList<tensor>& f2)
	{
		tmp<Field<vector>> tRes(new Field<vector>(f1.size()));
		divide(tRes.ref(), f1, f2);
		return tRes;
	}

	tmp<Field<vector>> operator /(const UList<vector>& f1, const tmp<Field<tensor>>& tf2)
	{
		tmp<Field<vector>> tRes = reuseTmp<vector, tensor>::New(tf2);
		divide(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	tmp<Field<vector>> operator /(const tmp<Field<vector>>& tf1, const UList<tensor>& f2)
	{
		tmp<Field<vector>> tRes = reuseTmp<vector, vector>::New(tf1);
		divide(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	tmp<Field<vector>> operator /(const tmp<Field<vector>>& tf1, const tmp<Field<tensor>>& tf2)
	{
		tmp<Field<vector>> tRes = reuseTmpTmp<vector, vector, vector, tensor>::New(tf1, tf2);
		divide(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}
		
	void divide(Field<vector>& res, const vector& s1, const UList<tensor>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(vector, res, =, vector, s1, /, tensor, f2)
	}

	tmp<Field<vector>> operator /(const vector& s1, const UList<tensor>& f2)
	{
		tmp<Field<vector>> tRes(new Field<vector>(f2.size()));
		divide(tRes.ref(), s1, f2);
		return tRes;
	}

	tmp<Field<vector>> operator /(const vector& s1, const tmp<Field<tensor>>& tf2)
	{
		tmp<Field<vector>> tRes = reuseTmp<vector, tensor>::New(tf2);
		divide(tRes.ref(), s1, tf2());
		tf2.clear();
		return tRes;
	} 
	
	void divide(Field<vector>& res, const UList<vector>& f1, const tensor& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(vector, res, =, vector, f1, /, tensor, s2)
	}

	tmp<Field<vector>> operator /(const UList<vector>& f1, const tensor& s2)
	{
		tmp<Field<vector>> tRes(new Field<vector>(f1.size()));
		divide(tRes.ref(), f1, s2);
		return tRes;
	}

	tmp<Field<vector>> operator /(const tmp<Field<vector>>& tf1, const tensor& s2)
	{
		tmp<Field<vector>> tRes = reuseTmp<vector, vector>::New(tf1);
		divide(tRes.ref(), tf1(), s2);
		tf1.clear();
		return tRes;
	}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#include "undefFieldFunctionsM.H"

// ************************************************************************* //