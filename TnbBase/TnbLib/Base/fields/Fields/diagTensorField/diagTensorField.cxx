#include <diagTensorField.hxx>

#define TEMPLATE
#include <FieldFunctionsM.cxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * global functions  * * * * * * * * * * * * * //

	void diag(Field<diagTensor>& res, const UList<tensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(diagTensor, res, =, ::tnbLib::diag, tensor, f)
	}

	tmp<Field<diagTensor>> diag(const UList<tensor>& f)
	{
		tmp<Field<diagTensor>> tRes(new Field<diagTensor>(f.size()));
		diag(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<diagTensor>> diag(const tmp<Field<tensor>>& tf)
	{
		tmp<Field<diagTensor>> tRes = reuseTmp<diagTensor, tensor>::New(tf);
		diag(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void tr(Field<scalar>& res, const UList<diagTensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::tr, diagTensor, f)
	}

	tmp<Field<scalar>> tr(const UList<diagTensor>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		tr(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> tr(const tmp<Field<diagTensor>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, diagTensor>::New(tf);
		tr(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void sph(Field<sphericalTensor>& res, const UList<diagTensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(sphericalTensor, res, =, ::tnbLib::sph, diagTensor, f)
	}

	tmp<Field<sphericalTensor>> sph(const UList<diagTensor>& f)
	{
		tmp<Field<sphericalTensor>> tRes(new Field<sphericalTensor>(f.size()));
		sph(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<sphericalTensor>> sph(const tmp<Field<diagTensor>>& tf)
	{
		tmp<Field<sphericalTensor>> tRes = reuseTmp<sphericalTensor, diagTensor>::New(tf);
		sph(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void det(Field<scalar>& res, const UList<diagTensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::det, diagTensor, f)
	}

	tmp<Field<scalar>> det(const UList<diagTensor>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		det(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> det(const tmp<Field<diagTensor>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, diagTensor>::New(tf);
		det(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void inv(Field<diagTensor>& res, const UList<diagTensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(diagTensor, res, =, ::tnbLib::inv, diagTensor, f)
	}

	tmp<Field<diagTensor>> inv(const UList<diagTensor>& f)
	{
		tmp<Field<diagTensor>> tRes(new Field<diagTensor>(f.size()));
		inv(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<diagTensor>> inv(const tmp<Field<diagTensor>>& tf)
	{
		tmp<Field<diagTensor>> tRes = reuseTmp<diagTensor, diagTensor>::New(tf);
		inv(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}


		
	void add(Field<tensor>& res, const UList<diagTensor>& f1, const UList<tensor>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor, res, =, diagTensor, f1, +, tensor, f2)
	}

	tmp<Field<tensor>> operator +(const UList<diagTensor>& f1, const UList<tensor>& f2)
	{
		tmp<Field<tensor>> tRes(new Field<tensor>(f1.size()));
		add(tRes.ref(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor>> operator +(const UList<diagTensor>& f1, const tmp<Field<tensor>>& tf2)
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, tensor>::New(tf2);
		add(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	tmp<Field<tensor>> operator +(const tmp<Field<diagTensor>>& tf1, const UList<tensor>& f2)
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, diagTensor>::New(tf1);
		add(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	tmp<Field<tensor>> operator +(const tmp<Field<diagTensor>>& tf1, const tmp<Field<tensor>>& tf2)
	{
		tmp<Field<tensor>> tRes = reuseTmpTmp<tensor, diagTensor, diagTensor, tensor>::New(tf1, tf2);
		add(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}
		
	void subtract(Field<tensor>& res, const UList<diagTensor>& f1, const UList<tensor>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(tensor, res, =, diagTensor, f1, -, tensor, f2)
	}

	tmp<Field<tensor>> operator -(const UList<diagTensor>& f1, const UList<tensor>& f2)
	{
		tmp<Field<tensor>> tRes(new Field<tensor>(f1.size()));
		subtract(tRes.ref(), f1, f2);
		return tRes;
	}

	tmp<Field<tensor>> operator -(const UList<diagTensor>& f1, const tmp<Field<tensor>>& tf2)
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, tensor>::New(tf2);
		subtract(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	tmp<Field<tensor>> operator -(const tmp<Field<diagTensor>>& tf1, const UList<tensor>& f2)
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, diagTensor>::New(tf1);
		subtract(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	tmp<Field<tensor>> operator -(const tmp<Field<diagTensor>>& tf1, const tmp<Field<tensor>>& tf2)
	{
		tmp<Field<tensor>> tRes = reuseTmpTmp<tensor, diagTensor, diagTensor, tensor>::New(tf1, tf2);
		subtract(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}

		
	void add(Field<tensor>& res, const diagTensor& s1, const UList<tensor>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor, res, =, diagTensor, s1, +, tensor, f2)
	}

	tmp<Field<tensor>> operator +(const diagTensor& s1, const UList<tensor>& f2)
	{
		tmp<Field<tensor>> tRes(new Field<tensor>(f2.size()));
		add(tRes.ref(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor>> operator +(const diagTensor& s1, const tmp<Field<tensor>>& tf2)
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, tensor>::New(tf2);
		add(tRes.ref(), s1, tf2());
		tf2.clear();
		return tRes;
	} 
	
	void add(Field<tensor>& res, const UList<diagTensor>& f1, const tensor& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor, res, =, diagTensor, f1, +, tensor, s2)
	}

	tmp<Field<tensor>> operator +(const UList<diagTensor>& f1, const tensor& s2)
	{
		tmp<Field<tensor>> tRes(new Field<tensor>(f1.size()));
		add(tRes.ref(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor>> operator +(const tmp<Field<diagTensor>>& tf1, const tensor& s2)
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, diagTensor>::New(tf1);
		add(tRes.ref(), tf1(), s2);
		tf1.clear();
		return tRes;
	}
		
	void subtract(Field<tensor>& res, const diagTensor& s1, const UList<tensor>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(tensor, res, =, diagTensor, s1, -, tensor, f2)
	}

	tmp<Field<tensor>> operator -(const diagTensor& s1, const UList<tensor>& f2)
	{
		tmp<Field<tensor>> tRes(new Field<tensor>(f2.size()));
		subtract(tRes.ref(), s1, f2);
		return tRes;
	}

	tmp<Field<tensor>> operator -(const diagTensor& s1, const tmp<Field<tensor>>& tf2)
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, tensor>::New(tf2);
		subtract(tRes.ref(), s1, tf2());
		tf2.clear();
		return tRes;
	} 
	
	void subtract(Field<tensor>& res, const UList<diagTensor>& f1, const tensor& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(tensor, res, =, diagTensor, f1, -, tensor, s2)
	}

	tmp<Field<tensor>> operator -(const UList<diagTensor>& f1, const tensor& s2)
	{
		tmp<Field<tensor>> tRes(new Field<tensor>(f1.size()));
		subtract(tRes.ref(), f1, s2);
		return tRes;
	}

	tmp<Field<tensor>> operator -(const tmp<Field<diagTensor>>& tf1, const tensor& s2)
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, diagTensor>::New(tf1);
		subtract(tRes.ref(), tf1(), s2);
		tf1.clear();
		return tRes;
	}

		
	void divide(Field<vector>& res, const UList<vector>& f1, const UList<diagTensor>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(vector, res, =, vector, f1, /, diagTensor, f2)
	}

	tmp<Field<vector>> operator /(const UList<vector>& f1, const UList<diagTensor>& f2)
	{
		tmp<Field<vector>> tRes(new Field<vector>(f1.size()));
		divide(tRes.ref(), f1, f2);
		return tRes;
	}

	tmp<Field<vector>> operator /(const UList<vector>& f1, const tmp<Field<diagTensor>>& tf2)
	{
		tmp<Field<vector>> tRes = reuseTmp<vector, diagTensor>::New(tf2);
		divide(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	tmp<Field<vector>> operator /(const tmp<Field<vector>>& tf1, const UList<diagTensor>& f2)
	{
		tmp<Field<vector>> tRes = reuseTmp<vector, vector>::New(tf1);
		divide(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	tmp<Field<vector>> operator /(const tmp<Field<vector>>& tf1, const tmp<Field<diagTensor>>& tf2)
	{
		tmp<Field<vector>> tRes = reuseTmpTmp<vector, vector, vector, diagTensor>::New(tf1, tf2);
		divide(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}
		
	void divide(Field<vector>& res, const vector& s1, const UList<diagTensor>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(vector, res, =, vector, s1, /, diagTensor, f2)
	}

	tmp<Field<vector>> operator /(const vector& s1, const UList<diagTensor>& f2)
	{
		tmp<Field<vector>> tRes(new Field<vector>(f2.size()));
		divide(tRes.ref(), s1, f2);
		return tRes;
	}

	tmp<Field<vector>> operator /(const vector& s1, const tmp<Field<diagTensor>>& tf2)
	{
		tmp<Field<vector>> tRes = reuseTmp<vector, diagTensor>::New(tf2);
		divide(tRes.ref(), s1, tf2());
		tf2.clear();
		return tRes;
	} 
	
	void divide(Field<vector>& res, const UList<vector>& f1, const diagTensor& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(vector, res, =, vector, f1, /, diagTensor, s2)
	}

	tmp<Field<vector>> operator /(const UList<vector>& f1, const diagTensor& s2)
	{
		tmp<Field<vector>> tRes(new Field<vector>(f1.size()));
		divide(tRes.ref(), f1, s2);
		return tRes;
	}

	tmp<Field<vector>> operator /(const tmp<Field<vector>>& tf1, const diagTensor& s2)
	{
		tmp<Field<vector>> tRes = reuseTmp<vector, vector>::New(tf1);
		divide(tRes.ref(), tf1(), s2);
		tf1.clear();
		return tRes;
	}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <undefFieldFunctionsM.hxx>

// ************************************************************************* //