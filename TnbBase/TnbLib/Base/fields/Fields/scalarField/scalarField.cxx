#include <scalarField.hxx>

#include <unitConversion.hxx>

#define TEMPLATE
#include <FieldFunctionsM.cxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<>
	tmp<scalarField> scalarField::component(const direction) const
	{
		return *this;
	}

	void component(scalarField& sf, const UList<scalar>& f, const direction)
	{
		sf = f;
	}

	template<>
	void scalarField::replace(const direction, const UList<scalar>& sf)
	{
		*this = sf;
	}

	template<>
	void scalarField::replace(const direction, const scalar& s)
	{
		*this = s;
	}


	void stabilise(scalarField& res, const UList<scalar>& sf, const scalar s)
	{
		TFOR_ALL_F_OP_FUNC_S_F
		(
			scalar, res, =, ::tnbLib::stabilise, scalar, s, scalar, sf
		)
	}

	tmp<scalarField> stabilise(const UList<scalar>& sf, const scalar s)
	{
		tmp<scalarField> tRes(new scalarField(sf.size()));
		stabilise(tRes.ref(), sf, s);
		return tRes;
	}

	tmp<scalarField> stabilise(const tmp<scalarField>& tsf, const scalar s)
	{
		tmp<scalarField> tRes = New(tsf);
		stabilise(tRes.ref(), tsf(), s);
		tsf.clear();
		return tRes;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<>
	scalar sumProd(const UList<scalar>& f1, const UList<scalar>& f2)
	{
		if (f1.size() && (f1.size() == f2.size()))
		{
			scalar SumProd = 0.0;
			TFOR_ALL_S_OP_F_OP_F(scalar, SumProd, +=, scalar, f1, *, scalar, f2)
				return SumProd;
		}
		else
		{
			return 0.0;
		}
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void add(Field<scalar>& res, const scalar& s1, const UList<scalar>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(scalar, res, =, scalar, s1, +, scalar, f2)
	}

	tmp<Field<scalar>> operator +(const scalar& s1, const UList<scalar>& f2)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f2.size()));
		add(tRes.ref(), s1, f2);
		return tRes;
	}

	tmp<Field<scalar>> operator +(const scalar& s1, const tmp<Field<scalar>>& tf2)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf2);
		add(tRes.ref(), s1, tf2());
		tf2.clear();
		return tRes;
	} 
	
	void add(Field<scalar>& res, const UList<scalar>& f1, const scalar& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(scalar, res, =, scalar, f1, +, scalar, s2)
	}

	tmp<Field<scalar>> operator +(const UList<scalar>& f1, const scalar& s2)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f1.size()));
		add(tRes.ref(), f1, s2);
		return tRes;
	}

	tmp<Field<scalar>> operator +(const tmp<Field<scalar>>& tf1, const scalar& s2)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf1);
		add(tRes.ref(), tf1(), s2);
		tf1.clear();
		return tRes;
	}
		
	void subtract(Field<scalar>& res, const scalar& s1, const UList<scalar>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(scalar, res, =, scalar, s1, -, scalar, f2)
	}

	tmp<Field<scalar>> operator -(const scalar& s1, const UList<scalar>& f2)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f2.size()));
		subtract(tRes.ref(), s1, f2);
		return tRes;
	}

	tmp<Field<scalar>> operator -(const scalar& s1, const tmp<Field<scalar>>& tf2)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf2);
		subtract(tRes.ref(), s1, tf2());
		tf2.clear();
		return tRes;
	} 
	
	void subtract(Field<scalar>& res, const UList<scalar>& f1, const scalar& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(scalar, res, =, scalar, f1, -, scalar, s2)
	}

	tmp<Field<scalar>> operator -(const UList<scalar>& f1, const scalar& s2)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f1.size()));
		subtract(tRes.ref(), f1, s2);
		return tRes;
	}

	tmp<Field<scalar>> operator -(const tmp<Field<scalar>>& tf1, const scalar& s2)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf1);
		subtract(tRes.ref(), tf1(), s2);
		tf1.clear();
		return tRes;
	}

		
	void multiply(Field<scalar>& res, const UList<scalar>& f1, const UList<scalar>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(scalar, res, =, scalar, f1, *, scalar, f2)
	}

	tmp<Field<scalar>> operator *(const UList<scalar>& f1, const UList<scalar>& f2)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f1.size()));
		multiply(tRes.ref(), f1, f2);
		return tRes;
	}

	tmp<Field<scalar>> operator *(const UList<scalar>& f1, const tmp<Field<scalar>>& tf2)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf2);
		multiply(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	tmp<Field<scalar>> operator *(const tmp<Field<scalar>>& tf1, const UList<scalar>& f2)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf1);
		multiply(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	tmp<Field<scalar>> operator *(const tmp<Field<scalar>>& tf1, const tmp<Field<scalar>>& tf2)
	{
		tmp<Field<scalar>> tRes = reuseTmpTmp<scalar, scalar, scalar, scalar>::New(tf1, tf2);
		multiply(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}
		
	void divide(Field<scalar>& res, const UList<scalar>& f1, const UList<scalar>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(scalar, res, =, scalar, f1, /, scalar, f2)
	}

	tmp<Field<scalar>> operator /(const UList<scalar>& f1, const UList<scalar>& f2)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f1.size()));
		divide(tRes.ref(), f1, f2);
		return tRes;
	}

	tmp<Field<scalar>> operator /(const UList<scalar>& f1, const tmp<Field<scalar>>& tf2)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf2);
		divide(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	tmp<Field<scalar>> operator /(const tmp<Field<scalar>>& tf1, const UList<scalar>& f2)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf1);
		divide(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	tmp<Field<scalar>> operator /(const tmp<Field<scalar>>& tf1, const tmp<Field<scalar>>& tf2)
	{
		tmp<Field<scalar>> tRes = reuseTmpTmp<scalar, scalar, scalar, scalar>::New(tf1, tf2);
		divide(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}

		
	void divide(Field<scalar>& res, const scalar& s1, const UList<scalar>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(scalar, res, =, scalar, s1, /, scalar, f2)
	}

	tmp<Field<scalar>> operator /(const scalar& s1, const UList<scalar>& f2)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f2.size()));
		divide(tRes.ref(), s1, f2);
		return tRes;
	}

	tmp<Field<scalar>> operator /(const scalar& s1, const tmp<Field<scalar>>& tf2)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf2);
		divide(tRes.ref(), s1, tf2());
		tf2.clear();
		return tRes;
	}

		
	void pow(Field<scalar>& res, const UList<scalar>& f1, const UList<scalar>& f2)
	{
		TFOR_ALL_F_OP_FUNC_F_F ( scalar, res, =, ::tnbLib::pow, scalar, f1, scalar, f2 )
	}

	tmp<Field<scalar>> pow(const UList<scalar>& f1, const UList<scalar>& f2)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f1.size()));
		pow(tRes.ref(), f1, f2);
		return tRes;
	}

	tmp<Field<scalar>> pow(const UList<scalar>& f1, const tmp<Field<scalar>>& tf2)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf2);
		pow(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	tmp<Field<scalar>> pow(const tmp<Field<scalar>>& tf1, const UList<scalar>& f2)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf1);
		pow(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	tmp<Field<scalar>> pow(const tmp<Field<scalar>>& tf1, const tmp<Field<scalar>>& tf2)
	{
		tmp<Field<scalar>> tRes = reuseTmpTmp<scalar, scalar, scalar, scalar>::New(tf1, tf2);
		pow(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}
		
	void pow(Field<scalar>& res, const scalar& s1, const UList<scalar>& f2)
	{
		TFOR_ALL_F_OP_FUNC_S_F ( scalar, res, =, ::tnbLib::pow, scalar, s1, scalar, f2 )
	}

	tmp<Field<scalar>> pow(const scalar& s1, const UList<scalar>& f2)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f2.size()));
		pow(tRes.ref(), s1, f2);
		return tRes;
	}

	tmp<Field<scalar>> pow(const scalar& s1, const tmp<Field<scalar>>& tf2)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf2);
		pow(tRes.ref(), s1, tf2());
		tf2.clear();
		return tRes;
	} 
	
	void pow(Field<scalar>& res, const UList<scalar>& f1, const scalar& s2)
	{
		TFOR_ALL_F_OP_FUNC_F_S ( scalar, res, =, ::tnbLib::pow, scalar, f1, scalar, s2 )
	}

	tmp<Field<scalar>> pow(const UList<scalar>& f1, const scalar& s2)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f1.size()));
		pow(tRes.ref(), f1, s2);
		return tRes;
	}

	tmp<Field<scalar>> pow(const tmp<Field<scalar>>& tf1, const scalar& s2)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf1);
		pow(tRes.ref(), tf1(), s2);
		tf1.clear();
		return tRes;
	}

		
	void atan2(Field<scalar>& res, const UList<scalar>& f1, const UList<scalar>& f2)
	{
		TFOR_ALL_F_OP_FUNC_F_F ( scalar, res, =, ::tnbLib::atan2, scalar, f1, scalar, f2 )
	}

	tmp<Field<scalar>> atan2(const UList<scalar>& f1, const UList<scalar>& f2)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f1.size()));
		atan2(tRes.ref(), f1, f2);
		return tRes;
	}

	tmp<Field<scalar>> atan2(const UList<scalar>& f1, const tmp<Field<scalar>>& tf2)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf2);
		atan2(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	tmp<Field<scalar>> atan2(const tmp<Field<scalar>>& tf1, const UList<scalar>& f2)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf1);
		atan2(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	tmp<Field<scalar>> atan2(const tmp<Field<scalar>>& tf1, const tmp<Field<scalar>>& tf2)
	{
		tmp<Field<scalar>> tRes = reuseTmpTmp<scalar, scalar, scalar, scalar>::New(tf1, tf2);
		atan2(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}
		
	void atan2(Field<scalar>& res, const scalar& s1, const UList<scalar>& f2)
	{
		TFOR_ALL_F_OP_FUNC_S_F ( scalar, res, =, ::tnbLib::atan2, scalar, s1, scalar, f2 )
	}

	tmp<Field<scalar>> atan2(const scalar& s1, const UList<scalar>& f2)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f2.size()));
		atan2(tRes.ref(), s1, f2);
		return tRes;
	}

	tmp<Field<scalar>> atan2(const scalar& s1, const tmp<Field<scalar>>& tf2)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf2);
		atan2(tRes.ref(), s1, tf2());
		tf2.clear();
		return tRes;
	} 
	
	void atan2(Field<scalar>& res, const UList<scalar>& f1, const scalar& s2)
	{
		TFOR_ALL_F_OP_FUNC_F_S ( scalar, res, =, ::tnbLib::atan2, scalar, f1, scalar, s2 )
	}

	tmp<Field<scalar>> atan2(const UList<scalar>& f1, const scalar& s2)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f1.size()));
		atan2(tRes.ref(), f1, s2);
		return tRes;
	}

	tmp<Field<scalar>> atan2(const tmp<Field<scalar>>& tf1, const scalar& s2)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf1);
		atan2(tRes.ref(), tf1(), s2);
		tf1.clear();
		return tRes;
	}

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		
	void pow3(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::pow3, scalar, f)
	}

	tmp<Field<scalar>> pow3(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		pow3(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> pow3(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		pow3(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void pow4(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::pow4, scalar, f)
	}

	tmp<Field<scalar>> pow4(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		pow4(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> pow4(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		pow4(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void pow5(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::pow5, scalar, f)
	}

	tmp<Field<scalar>> pow5(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		pow5(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> pow5(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		pow5(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void pow6(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::pow6, scalar, f)
	}

	tmp<Field<scalar>> pow6(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		pow6(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> pow6(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		pow6(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void pow025(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::pow025, scalar, f)
	}

	tmp<Field<scalar>> pow025(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		pow025(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> pow025(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		pow025(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void sqrt(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::sqrt, scalar, f)
	}

	tmp<Field<scalar>> sqrt(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		sqrt(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> sqrt(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		sqrt(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void cbrt(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::cbrt, scalar, f)
	}

	tmp<Field<scalar>> cbrt(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		cbrt(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> cbrt(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		cbrt(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void sign(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::sign, scalar, f)
	}

	tmp<Field<scalar>> sign(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		sign(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> sign(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		sign(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void pos(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::pos, scalar, f)
	}

	tmp<Field<scalar>> pos(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		pos(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> pos(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		pos(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void pos0(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::pos0, scalar, f)
	}

	tmp<Field<scalar>> pos0(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		pos0(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> pos0(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		pos0(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void neg(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::neg, scalar, f)
	}

	tmp<Field<scalar>> neg(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		neg(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> neg(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		neg(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void neg0(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::neg0, scalar, f)
	}

	tmp<Field<scalar>> neg0(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		neg0(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> neg0(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		neg0(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void posPart(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::posPart, scalar, f)
	}

	tmp<Field<scalar>> posPart(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		posPart(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> posPart(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		posPart(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void negPart(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::negPart, scalar, f)
	}

	tmp<Field<scalar>> negPart(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		negPart(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> negPart(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		negPart(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void exp(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::exp, scalar, f)
	}

	tmp<Field<scalar>> exp(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		exp(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> exp(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		exp(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void log(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::log, scalar, f)
	}

	tmp<Field<scalar>> log(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		log(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> log(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		log(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void log10(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::log10, scalar, f)
	}

	tmp<Field<scalar>> log10(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		log10(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> log10(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		log10(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void sin(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::sin, scalar, f)
	}

	tmp<Field<scalar>> sin(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		sin(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> sin(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		sin(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void cos(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::cos, scalar, f)
	}

	tmp<Field<scalar>> cos(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		cos(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> cos(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		cos(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void tan(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::tan, scalar, f)
	}

	tmp<Field<scalar>> tan(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		tan(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> tan(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		tan(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void asin(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::asin, scalar, f)
	}

	tmp<Field<scalar>> asin(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		asin(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> asin(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		asin(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void acos(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::acos, scalar, f)
	}

	tmp<Field<scalar>> acos(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		acos(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> acos(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		acos(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void atan(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::atan, scalar, f)
	}

	tmp<Field<scalar>> atan(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		atan(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> atan(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		atan(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void sinh(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::sinh, scalar, f)
	}

	tmp<Field<scalar>> sinh(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		sinh(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> sinh(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		sinh(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void cosh(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::cosh, scalar, f)
	}

	tmp<Field<scalar>> cosh(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		cosh(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> cosh(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		cosh(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void tanh(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::tanh, scalar, f)
	}

	tmp<Field<scalar>> tanh(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		tanh(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> tanh(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		tanh(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void asinh(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::asinh, scalar, f)
	}

	tmp<Field<scalar>> asinh(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		asinh(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> asinh(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		asinh(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void acosh(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::acosh, scalar, f)
	}

	tmp<Field<scalar>> acosh(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		acosh(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> acosh(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		acosh(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void atanh(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::atanh, scalar, f)
	}

	tmp<Field<scalar>> atanh(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		atanh(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> atanh(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		atanh(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void erf(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::erf, scalar, f)
	}

	tmp<Field<scalar>> erf(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		erf(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> erf(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		erf(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void erfc(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::erfc, scalar, f)
	}

	tmp<Field<scalar>> erfc(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		erfc(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> erfc(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		erfc(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void lgamma(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::lgamma, scalar, f)
	}

	tmp<Field<scalar>> lgamma(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		lgamma(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> lgamma(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		lgamma(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void j0(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::j0, scalar, f)
	}

	tmp<Field<scalar>> j0(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		j0(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> j0(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		j0(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void j1(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::j1, scalar, f)
	}

	tmp<Field<scalar>> j1(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		j1(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> j1(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		j1(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void y0(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::y0, scalar, f)
	}

	tmp<Field<scalar>> y0(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		y0(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> y0(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		y0(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void y1(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::y1, scalar, f)
	}

	tmp<Field<scalar>> y1(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		y1(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> y1(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		y1(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

		
	void degToRad(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::degToRad, scalar, f)
	}

	tmp<Field<scalar>> degToRad(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		degToRad(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> degToRad(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		degToRad(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void radToDeg(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::radToDeg, scalar, f)
	}

	tmp<Field<scalar>> radToDeg(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		radToDeg(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> radToDeg(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		radToDeg(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void atmToPa(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::atmToPa, scalar, f)
	}

	tmp<Field<scalar>> atmToPa(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		atmToPa(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> atmToPa(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		atmToPa(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void paToAtm(Field<scalar>& res, const UList<scalar>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::paToAtm, scalar, f)
	}

	tmp<Field<scalar>> paToAtm(const UList<scalar>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		paToAtm(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<scalar>> paToAtm(const tmp<Field<scalar>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, scalar>::New(tf);
		paToAtm(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}


#define BesselFunc(func)                                                       \
void func(scalarField& res, const int n, const UList<scalar>& sf)              \
{                                                                              \
    TFOR_ALL_F_OP_FUNC_S_F(scalar, res, =, ::tnbLib::func, int, n, scalar, sf)   \
}                                                                              \
                                                                               \
tmp<scalarField> func(const int n, const UList<scalar>& sf)                    \
{                                                                              \
    tmp<scalarField> tRes(new scalarField(sf.size()));                         \
    func(tRes.ref(), n, sf);                                                   \
    return tRes;                                                               \
}                                                                              \
                                                                               \
tmp<scalarField> func(const int n, const tmp<scalarField>& tsf)                \
{                                                                              \
    tmp<scalarField> tRes = New(tsf);                                          \
    func(tRes.ref(), n, tsf());                                                \
    tsf.clear();                                                               \
    return tRes;                                                               \
}

		
	void jn(scalarField& res, const int n, const UList<scalar>& sf)
	{
		TFOR_ALL_F_OP_FUNC_S_F(scalar, res, =, ::tnbLib::jn, int, n, scalar, sf)
	}

	tmp<scalarField> jn(const int n, const UList<scalar>& sf)
	{
		tmp<scalarField> tRes(new scalarField(sf.size()));
		jn(tRes.ref(), n, sf);
		return tRes;
	}

	tmp<scalarField> jn(const int n, const tmp<scalarField>& tsf)
	{
		tmp<scalarField> tRes = New(tsf);
		jn(tRes.ref(), n, tsf());
		tsf.clear();
		return tRes;
	}
		
	void yn(scalarField& res, const int n, const UList<scalar>& sf)
	{
		TFOR_ALL_F_OP_FUNC_S_F(scalar, res, =, ::tnbLib::yn, int, n, scalar, sf)
	}

	tmp<scalarField> yn(const int n, const UList<scalar>& sf)
	{
		tmp<scalarField> tRes(new scalarField(sf.size()));
		yn(tRes.ref(), n, sf);
		return tRes;
	}

	tmp<scalarField> yn(const int n, const tmp<scalarField>& tsf)
	{
		tmp<scalarField> tRes = New(tsf);
		yn(tRes.ref(), n, tsf());
		tsf.clear();
		return tRes;
	}

#undef BesselFunc


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <undefFieldFunctionsM.hxx>

// ************************************************************************* //