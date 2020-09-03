#pragma once
#include <PstreamReduceOps.hxx>
#include <FieldReuseFunctions.hxx>
#include <FieldM.hxx>  // added by amir
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/* * * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * */

	template<class Type>
	void component
	(
		Field<typename Field<Type>::cmptType>& res,
		const UList<Type>& f,
		const direction d
	)
	{
		typedef typename Field<Type>::cmptType cmptType;
		TFOR_ALL_F_OP_F_FUNC_S
		(
			cmptType, res, =, Type, f, .component, const direction, d
		)
	}


	template<class Type>
	void T(Field<Type>& res, const UList<Type>& f)
	{
		TFOR_ALL_F_OP_F_FUNC(Type, res, =, Type, f, T)
	}


	template<class Type, direction r>
	void pow
	(
		Field<typename powProduct<Type, r>::type>& res,
		const UList<Type>& vf
	)
	{
		typedef typename powProduct<Type, r>::type powProductType;
		TFOR_ALL_F_OP_FUNC_F_S
		(
			powProductType, res, =, pow, Type, vf, powProductType,
			pTraits<powProductType>::zero
		)
	}

	template<class Type, direction r>
	tmp<Field<typename powProduct<Type, r>::type>>
		pow
		(
			const UList<Type>& f,
			typename powProduct<Type, r>::type
		)
	{
		typedef typename powProduct<Type, r>::type powProductType;
		tmp<Field<powProductType>> tRes
		(
			new Field<powProductType>(f.size())
		);
		pow<Type, r>(tRes.ref(), f);
		return tRes;
	}

	template<class Type, direction r>
	tmp<Field<typename powProduct<Type, r>::type>>
		pow
		(
			const tmp<Field<Type>>& tf,
			typename powProduct<Type, r>::type
		)
	{
		typedef typename powProduct<Type, r>::type powProductType;
		tmp<Field<powProductType>> tRes = reuseTmp<powProductType, Type>::New(tf);
		pow<Type, r>(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}


	template<class Type>
	void sqr
	(
		Field<typename outerProduct<Type, Type>::type>& res,
		const UList<Type>& vf
	)
	{
		typedef typename outerProduct<Type, Type>::type outerProductType;
		TFOR_ALL_F_OP_FUNC_F(outerProductType, res, =, sqr, Type, vf)
	}

	template<class Type>
	tmp<Field<typename outerProduct<Type, Type>::type>>
		sqr(const UList<Type>& f)
	{
		typedef typename outerProduct<Type, Type>::type outerProductType;
		tmp<Field<outerProductType>> tRes
		(
			new Field<outerProductType>(f.size())
		);
		sqr(tRes.ref(), f);
		return tRes;
	}

	template<class Type>
	tmp<Field<typename outerProduct<Type, Type>::type>>
		sqr(const tmp<Field<Type>>& tf)
	{
		typedef typename outerProduct<Type, Type>::type outerProductType;
		tmp<Field<outerProductType>> tRes =
			reuseTmp<outerProductType, Type>::New(tf);
		sqr(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}


	template<class Type>
	void magSqr(Field<scalar>& res, const UList<Type>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, magSqr, Type, f)
	}

	template<class Type>
	tmp<Field<scalar>> magSqr(const UList<Type>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		magSqr(tRes.ref(), f);
		return tRes;
	}

	template<class Type>
	tmp<Field<scalar>> magSqr(const tmp<Field<Type>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, Type>::New(tf);
		magSqr(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}


	template<class Type>
	void mag(Field<scalar>& res, const UList<Type>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, mag, Type, f)
	}

	template<class Type>
	tmp<Field<scalar>> mag(const UList<Type>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size()));
		mag(tRes.ref(), f);
		return tRes;
	}

	template<class Type>
	tmp<Field<scalar>> mag(const tmp<Field<Type>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, Type>::New(tf);
		mag(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}


	template<class Type>
	void cmptMax(Field<typename Field<Type>::cmptType>& res, const UList<Type>& f)
	{
		typedef typename Field<Type>::cmptType cmptType;
		TFOR_ALL_F_OP_FUNC_F(cmptType, res, =, cmptMax, Type, f)
	}

	template<class Type>
	tmp<Field<typename Field<Type>::cmptType>> cmptMax(const UList<Type>& f)
	{
		typedef typename Field<Type>::cmptType cmptType;
		tmp<Field<cmptType>> tRes(new Field<cmptType>(f.size()));
		cmptMax(tRes.ref(), f);
		return tRes;
	}

	template<class Type>
	tmp<Field<typename Field<Type>::cmptType>> cmptMax(const tmp<Field<Type>>& tf)
	{
		typedef typename Field<Type>::cmptType cmptType;
		tmp<Field<cmptType>> tRes = reuseTmp<cmptType, Type>::New(tf);
		cmptMax(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}


	template<class Type>
	void cmptMin(Field<typename Field<Type>::cmptType>& res, const UList<Type>& f)
	{
		typedef typename Field<Type>::cmptType cmptType;
		TFOR_ALL_F_OP_FUNC_F(cmptType, res, =, cmptMin, Type, f)
	}

	template<class Type>
	tmp<Field<typename Field<Type>::cmptType>> cmptMin(const UList<Type>& f)
	{
		typedef typename Field<Type>::cmptType cmptType;
		tmp<Field<cmptType>> tRes(new Field<cmptType>(f.size()));
		cmptMin(tRes.ref(), f);
		return tRes;
	}

	template<class Type>
	tmp<Field<typename Field<Type>::cmptType>> cmptMin(const tmp<Field<Type>>& tf)
	{
		typedef typename Field<Type>::cmptType cmptType;
		tmp<Field<cmptType>> tRes = reuseTmp<cmptType, Type>::New(tf);
		cmptMin(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}


	template<class Type>
	void cmptAv(Field<typename Field<Type>::cmptType>& res, const UList<Type>& f)
	{
		typedef typename Field<Type>::cmptType cmptType;
		TFOR_ALL_F_OP_FUNC_F(cmptType, res, =, cmptAv, Type, f)
	}

	template<class Type>
	tmp<Field<typename Field<Type>::cmptType>> cmptAv(const UList<Type>& f)
	{
		typedef typename Field<Type>::cmptType cmptType;
		tmp<Field<cmptType>> tRes(new Field<cmptType>(f.size()));
		cmptAv(tRes.ref(), f);
		return tRes;
	}

	template<class Type>
	tmp<Field<typename Field<Type>::cmptType>> cmptAv(const tmp<Field<Type>>& tf)
	{
		typedef typename Field<Type>::cmptType cmptType;
		tmp<Field<cmptType>> tRes = reuseTmp<cmptType, Type>::New(tf);
		cmptAv(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}


	template<class Type>
	void cmptMag(Field<Type>& res, const UList<Type>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(Type, res, =, cmptMag, Type, f)
	}

	template<class Type>
	tmp<Field<Type>> cmptMag(const UList<Type>& f)
	{
		tmp<Field<Type>> tRes(new Field<Type>(f.size()));
		cmptMag(tRes.ref(), f);
		return tRes;
	}

	template<class Type>
	tmp<Field<Type>> cmptMag(const tmp<Field<Type>>& tf)
	{
		tmp<Field<Type>> tRes = New(tf);
		cmptMag(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}


//#define TMP_UNARY_FUNCTION(ReturnType, Func)                                   \
//                                                                               \
//template<class Type>                                                           \
//ReturnType Func(const tmp<Field<Type>>& tf1)                                   \
//{                                                                              \
//    ReturnType res = Func(tf1());                                              \
//    tf1.clear();                                                               \
//    return res;                                                                \
//}

	template<class Type>
	Type max(const UList<Type>& f)
	{
		if (f.size())
		{
			Type Max(f[0]);
			TFOR_ALL_S_OP_FUNC_F_S(Type, Max, =, max, Type, f, Type, Max)
				return Max;
		}
		else
		{
			return pTraits<Type>::min;
		}
	}

	template<class Type> Type max(const tmp<Field<Type>>& tf1) { Type res = max(tf1()); tf1.clear(); return res; }

	template<class Type>
	Type min(const UList<Type>& f)
	{
		if (f.size())
		{
			Type Min(f[0]);
			TFOR_ALL_S_OP_FUNC_F_S(Type, Min, =, min, Type, f, Type, Min)
				return Min;
		}
		else
		{
			return pTraits<Type>::max;
		}
	}

	template<class Type> Type min(const tmp<Field<Type>>& tf1) { Type res = min(tf1()); tf1.clear(); return res; }

	template<class Type>
	Type sum(const UList<Type>& f)
	{
		if (f.size())
		{
			Type Sum = Zero;
			TFOR_ALL_S_OP_F(Type, Sum, +=, Type, f)
				return Sum;
		}
		else
		{
			return Zero;
		}
	}

	template<class Type> Type sum(const tmp<Field<Type>>& tf1) { Type res = sum(tf1()); tf1.clear(); return res; }

	template<class Type>
	Type maxMagSqr(const UList<Type>& f)
	{
		if (f.size())
		{
			Type Max(f[0]);
			TFOR_ALL_S_OP_FUNC_F_S
			(
				Type,
				Max,
				=,
				maxMagSqrOp<Type>(),
				Type,
				f,
				Type,
				Max
			)
				return Max;
		}
		else
		{
			return Zero;
		}
	}

	template <class Type>
	Type maxMagSqr(const tmp<Field<Type>>& tf1)
	{
		Type res = maxMagSqr(tf1());
		tf1.clear();
		return res;
	}

	template<class Type>
	Type minMagSqr(const UList<Type>& f)
	{
		if (f.size())
		{
			Type Min(f[0]);
			TFOR_ALL_S_OP_FUNC_F_S
			(
				Type,
				Min,
				=,
				minMagSqrOp<Type>(),
				Type,
				f,
				Type,
				Min
			)
				return Min;
		}
		else
		{
			return pTraits<Type>::rootMax;
		}
	}

	template <class Type>
	Type minMagSqr(const tmp<Field<Type>>& tf1)
	{
		Type res = minMagSqr(tf1());
		tf1.clear();
		return res;
	}

	template<class Type>
	scalar sumProd(const UList<Type>& f1, const UList<Type>& f2)
	{
		if (f1.size() && (f1.size() == f2.size()))
		{
			scalar SumProd = 0;
			TFOR_ALL_S_OP_F_OP_F(scalar, SumProd, +=, Type, f1, &&, Type, f2)
				return SumProd;
		}
		else
		{
			return 0;
		}
	}


	template<class Type>
	Type sumCmptProd(const UList<Type>& f1, const UList<Type>& f2)
	{
		if (f1.size() && (f1.size() == f2.size()))
		{
			Type SumProd = Zero;
			TFOR_ALL_S_OP_FUNC_F_F
			(
				Type,
				SumProd,
				+=,
				cmptMultiply,
				Type,
				f1,
				Type,
				f2
			)
				return SumProd;
		}
		else
		{
			return Zero;
		}
	}


	template<class Type>
	scalar sumSqr(const UList<Type>& f)
	{
		if (f.size())
		{
			scalar SumSqr = 0;
			TFOR_ALL_S_OP_FUNC_F(scalar, SumSqr, +=, sqr, Type, f)
				return SumSqr;
		}
		else
		{
			return 0;
		}
	}

	template <class Type>
	scalar sumSqr(const tmp<Field<Type>>& tf1)
	{
		scalar res = sumSqr(tf1());
		tf1.clear();
		return res;
	}

	template<class Type>
	scalar sumMag(const UList<Type>& f)
	{
		if (f.size())
		{
			scalar SumMag = 0;
			TFOR_ALL_S_OP_FUNC_F(scalar, SumMag, +=, mag, Type, f)
				return SumMag;
		}
		else
		{
			return 0;
		}
	}

	template <class Type>
	scalar sumMag(const tmp<Field<Type>>& tf1)
	{
		scalar res = sumMag(tf1());
		tf1.clear();
		return res;
	}


	template<class Type>
	Type sumCmptMag(const UList<Type>& f)
	{
		if (f.size())
		{
			Type SumMag = Zero;
			TFOR_ALL_S_OP_FUNC_F(scalar, SumMag, +=, cmptMag, Type, f)
				return SumMag;
		}
		else
		{
			return Zero;
		}
	}

	template <class Type>
	Type sumCmptMag(const tmp<Field<Type>>& tf1)
	{
		Type res = sumCmptMag(tf1());
		tf1.clear();
		return res;
	}

	template<class Type>
	Type average(const UList<Type>& f)
	{
		if (f.size())
		{
			Type avrg = sum(f) / f.size();

			return avrg;
		}
		else
		{
			WarningInFunction
				<< "empty field, returning zero" << endl;

			return Zero;
		}
	}

	template<class Type> Type average(const tmp<Field<Type>>& tf1) { Type res = average(tf1()); tf1.clear(); return res; }


//#define G_UNARY_FUNCTION(ReturnType, gFunc, Func, rFunc)                       \
//                                                                               \
//template<class Type>                                                           \
//ReturnType gFunc(const UList<Type>& f, const label comm)                       \
//{                                                                              \
//    ReturnType res = Func(f);                                                  \
//    reduce(res, rFunc##Op<Type>(), Pstream::msgType(), comm);                  \
//    return res;                                                                \
//}                                                                              \
//TMP_UNARY_FUNCTION(ReturnType, gFunc)


	template <class Type>
	Type gMax(const UList<Type>& f, const label comm)
	{
		Type res = max(f);
		reduce(res, maxOp<Type>(), Pstream::msgType(), comm);
		return res;
	}

	template<class Type> Type gMax(const tmp<Field<Type>>& tf1) { Type res = gMax(tf1()); tf1.clear(); return res; }

	template <class Type>
	Type gMin(const UList<Type>& f, const label comm)
	{
		Type res = min(f);
		reduce(res, minOp<Type>(), Pstream::msgType(), comm);
		return res;
	}

	template<class Type> Type gMin(const tmp<Field<Type>>& tf1) { Type res = gMin(tf1()); tf1.clear(); return res; }

	template <class Type>
	Type gSum(const UList<Type>& f, const label comm)
	{
		Type res = sum(f);
		reduce(res, sumOp<Type>(), Pstream::msgType(), comm);
		return res;
	}

	template<class Type> Type gSum(const tmp<Field<Type>>& tf1) { Type res = gSum(tf1()); tf1.clear(); return res; }

	template <class Type>
	Type gMaxMagSqr(const UList<Type>& f, const label comm)
	{
		Type res = maxMagSqr(f);
		reduce(res, maxMagSqrOp<Type>(), Pstream::msgType(), comm);
		return res;
	}

	template <class Type>
	Type gMaxMagSqr(const tmp<Field<Type>>& tf1)
	{
		Type res = gMaxMagSqr(tf1());
		tf1.clear();
		return res;
	}

	template <class Type>
	Type gMinMagSqr(const UList<Type>& f, const label comm)
	{
		Type res = minMagSqr(f);
		reduce(res, minMagSqrOp<Type>(), Pstream::msgType(), comm);
		return res;
	}

	template <class Type>
	Type gMinMagSqr(const tmp<Field<Type>>& tf1)
	{
		Type res = gMinMagSqr(tf1());
		tf1.clear();
		return res;
	}

	template <class Type>
	scalar gSumSqr(const UList<Type>& f, const label comm)
	{
		scalar res = sumSqr(f);
		reduce(res, sumOp<Type>(), Pstream::msgType(), comm);
		return res;
	}

	template <class Type>
	scalar gSumSqr(const tmp<Field<Type>>& tf1)
	{
		scalar res = gSumSqr(tf1());
		tf1.clear();
		return res;
	}

	template <class Type>
	scalar gSumMag(const UList<Type>& f, const label comm)
	{
		scalar res = sumMag(f);
		reduce(res, sumOp<Type>(), Pstream::msgType(), comm);
		return res;
	}

	template <class Type>
	scalar gSumMag(const tmp<Field<Type>>& tf1)
	{
		scalar res = gSumMag(tf1());
		tf1.clear();
		return res;
	}

	template <class Type>
	Type gSumCmptMag(const UList<Type>& f, const label comm)
	{
		Type res = sumCmptMag(f);
		reduce(res, sumOp<Type>(), Pstream::msgType(), comm);
		return res;
	}

	template <class Type>
	Type gSumCmptMag(const tmp<Field<Type>>& tf1)
	{
		Type res = gSumCmptMag(tf1());
		tf1.clear();
		return res;
	}

//#undef G_UNARY_FUNCTION

	template<class Type>
	scalar gSumProd
	(
		const UList<Type>& f1,
		const UList<Type>& f2,
		const label comm
	)
	{
		scalar SumProd = sumProd(f1, f2);
		reduce(SumProd, sumOp<scalar>(), Pstream::msgType(), comm);
		return SumProd;
	}

	template<class Type>
	Type gSumCmptProd
	(
		const UList<Type>& f1,
		const UList<Type>& f2,
		const label comm
	)
	{
		Type SumProd = sumCmptProd(f1, f2);
		reduce(SumProd, sumOp<Type>(), Pstream::msgType(), comm);
		return SumProd;
	}

	template<class Type>
	Type gAverage
	(
		const UList<Type>& f,
		const label comm
	)
	{
		label n = f.size();
		Type s = sum(f);
		sumReduce(s, n, Pstream::msgType(), comm);

		if (n > 0)
		{
			Type avrg = s / n;

			return avrg;
		}
		else
		{
			WarningInFunction
				<< "empty field, returning zero." << endl;

			return Zero;
		}
	}

	template <class Type>
	Type gAverage(const tmp<Field<Type>>& tf1)
	{
		Type res = gAverage(tf1());
		tf1.clear();
		return res;
	}

//#undef TMP_UNARY_FUNCTION


	template<class Type>
	void max(Field<Type>& res, const UList<Type>& f1, const UList<Type>& f2)
	{
		TFOR_ALL_F_OP_FUNC_F_F(Type, res, =, ::tnbLib::max, Type, f1, Type, f2)
	}

	template<class Type>
	tmp<Field<Type>> max(const UList<Type>& f1, const UList<Type>& f2)
	{
		tmp<Field<Type>> tRes(new Field<Type>(f1.size()));
		max(tRes.ref(), f1, f2);
		return tRes;
	}

	template<class Type>
	tmp<Field<Type>> max(const UList<Type>& f1, const tmp<Field<Type>>& tf2)
	{
		tmp<Field<Type>> tRes = reuseTmp<Type, Type>::New(tf2);
		max(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	template<class Type>
	tmp<Field<Type>> max(const tmp<Field<Type>>& tf1, const UList<Type>& f2)
	{
		tmp<Field<Type>> tRes = reuseTmp<Type, Type>::New(tf1);
		max(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	template<class Type>
	tmp<Field<Type>> max(const tmp<Field<Type>>& tf1, const tmp<Field<Type>>& tf2)
	{
		tmp<Field<Type>> tRes = reuseTmpTmp<Type, Type, Type, Type>::New(tf1, tf2);
		max(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}

	template<class Type>
	void min(Field<Type>& res, const UList<Type>& f1, const UList<Type>& f2)
	{
		TFOR_ALL_F_OP_FUNC_F_F(Type, res, =, ::tnbLib::min, Type, f1, Type, f2)
	}

	template<class Type>
	tmp<Field<Type>> min(const UList<Type>& f1, const UList<Type>& f2)
	{
		tmp<Field<Type>> tRes(new Field<Type>(f1.size()));
		min(tRes.ref(), f1, f2);
		return tRes;
	}

	template<class Type>
	tmp<Field<Type>> min(const UList<Type>& f1, const tmp<Field<Type>>& tf2)
	{
		tmp<Field<Type>> tRes = reuseTmp<Type, Type>::New(tf2);
		min(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	template<class Type>
	tmp<Field<Type>> min(const tmp<Field<Type>>& tf1, const UList<Type>& f2)
	{
		tmp<Field<Type>> tRes = reuseTmp<Type, Type>::New(tf1);
		min(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	template<class Type>
	tmp<Field<Type>> min(const tmp<Field<Type>>& tf1, const tmp<Field<Type>>& tf2)
	{
		tmp<Field<Type>> tRes = reuseTmpTmp<Type, Type, Type, Type>::New(tf1, tf2);
		min(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}

	template<class Type>
	void cmptMultiply(Field<Type>& res, const UList<Type>& f1, const UList<Type>& f2)
	{
		TFOR_ALL_F_OP_FUNC_F_F(Type, res, =, ::tnbLib::cmptMultiply, Type, f1, Type, f2)
	}

	template<class Type>
	tmp<Field<Type>> cmptMultiply(const UList<Type>& f1, const UList<Type>& f2)
	{
		tmp<Field<Type>> tRes(new Field<Type>(f1.size()));
		cmptMultiply(tRes.ref(), f1, f2);
		return tRes;
	}

	template<class Type>
	tmp<Field<Type>> cmptMultiply(const UList<Type>& f1, const tmp<Field<Type>>& tf2)
	{
		tmp<Field<Type>> tRes = reuseTmp<Type, Type>::New(tf2);
		cmptMultiply(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	template<class Type>
	tmp<Field<Type>> cmptMultiply(const tmp<Field<Type>>& tf1, const UList<Type>& f2)
	{
		tmp<Field<Type>> tRes = reuseTmp<Type, Type>::New(tf1);
		cmptMultiply(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	template<class Type>
	tmp<Field<Type>> cmptMultiply(const tmp<Field<Type>>& tf1, const tmp<Field<Type>>& tf2)
	{
		tmp<Field<Type>> tRes = reuseTmpTmp<Type, Type, Type, Type>::New(tf1, tf2);
		cmptMultiply(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}

	template<class Type>
	void cmptDivide(Field<Type>& res, const UList<Type>& f1, const UList<Type>& f2)
	{
		TFOR_ALL_F_OP_FUNC_F_F(Type, res, =, ::tnbLib::cmptDivide, Type, f1, Type, f2)
	}

	template<class Type>
	tmp<Field<Type>> cmptDivide(const UList<Type>& f1, const UList<Type>& f2)
	{
		tmp<Field<Type>> tRes(new Field<Type>(f1.size()));
		cmptDivide(tRes.ref(), f1, f2);
		return tRes;
	}

	template<class Type>
	tmp<Field<Type>> cmptDivide(const UList<Type>& f1, const tmp<Field<Type>>& tf2)
	{
		tmp<Field<Type>> tRes = reuseTmp<Type, Type>::New(tf2);
		cmptDivide(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	template<class Type>
	tmp<Field<Type>> cmptDivide(const tmp<Field<Type>>& tf1, const UList<Type>& f2)
	{
		tmp<Field<Type>> tRes = reuseTmp<Type, Type>::New(tf1);
		cmptDivide(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	template<class Type>
	tmp<Field<Type>> cmptDivide(const tmp<Field<Type>>& tf1, const tmp<Field<Type>>& tf2)
	{
		tmp<Field<Type>> tRes = reuseTmpTmp<Type, Type, Type, Type>::New(tf1, tf2);
		cmptDivide(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}


	template<class Type>
	void max(Field<Type>& res, const Type& s1, const UList<Type>& f2)
	{
		TFOR_ALL_F_OP_FUNC_S_F(Type, res, =, ::tnbLib::max, Type, s1, Type, f2)
	}

	template<class Type>
	tmp<Field<Type>> max(const Type& s1, const UList<Type>& f2)
	{
		tmp<Field<Type>> tRes(new Field<Type>(f2.size()));
		max(tRes.ref(), s1, f2);
		return tRes;
	}

	template<class Type>
	tmp<Field<Type>> max(const Type& s1, const tmp<Field<Type>>& tf2)
	{
		tmp<Field<Type>> tRes = reuseTmp<Type, Type>::New(tf2);
		max(tRes.ref(), s1, tf2());
		tf2.clear();
		return tRes;
	}

	template<class Type>
	void max(Field<Type>& res, const UList<Type>& f1, const Type& s2)
	{
		TFOR_ALL_F_OP_FUNC_F_S(Type, res, =, ::tnbLib::max, Type, f1, Type, s2)
	}

	template<class Type>
	tmp<Field<Type>> max(const UList<Type>& f1, const Type& s2)
	{
		tmp<Field<Type>> tRes(new Field<Type>(f1.size()));
		max(tRes.ref(), f1, s2);
		return tRes;
	}

	template<class Type>
	tmp<Field<Type>> max(const tmp<Field<Type>>& tf1, const Type& s2)
	{
		tmp<Field<Type>> tRes = reuseTmp<Type, Type>::New(tf1);
		max(tRes.ref(), tf1(), s2);
		tf1.clear();
		return tRes;
	}

	template<class Type>
	void min(Field<Type>& res, const Type& s1, const UList<Type>& f2)
	{
		TFOR_ALL_F_OP_FUNC_S_F(Type, res, =, ::tnbLib::min, Type, s1, Type, f2)
	}

	template<class Type>
	tmp<Field<Type>> min(const Type& s1, const UList<Type>& f2)
	{
		tmp<Field<Type>> tRes(new Field<Type>(f2.size()));
		min(tRes.ref(), s1, f2);
		return tRes;
	}

	template<class Type>
	tmp<Field<Type>> min(const Type& s1, const tmp<Field<Type>>& tf2)
	{
		tmp<Field<Type>> tRes = reuseTmp<Type, Type>::New(tf2);
		min(tRes.ref(), s1, tf2());
		tf2.clear();
		return tRes;
	}

	template<class Type>
	void min(Field<Type>& res, const UList<Type>& f1, const Type& s2)
	{
		TFOR_ALL_F_OP_FUNC_F_S(Type, res, =, ::tnbLib::min, Type, f1, Type, s2)
	}

	template<class Type>
	tmp<Field<Type>> min(const UList<Type>& f1, const Type& s2)
	{
		tmp<Field<Type>> tRes(new Field<Type>(f1.size()));
		min(tRes.ref(), f1, s2);
		return tRes;
	}

	template<class Type>
	tmp<Field<Type>> min(const tmp<Field<Type>>& tf1, const Type& s2)
	{
		tmp<Field<Type>> tRes = reuseTmp<Type, Type>::New(tf1);
		min(tRes.ref(), tf1(), s2);
		tf1.clear();
		return tRes;
	}

	template<class Type>
	void cmptMultiply(Field<Type>& res, const Type& s1, const UList<Type>& f2)
	{
		TFOR_ALL_F_OP_FUNC_S_F(Type, res, =, ::tnbLib::cmptMultiply, Type, s1, Type, f2)
	}

	template<class Type>
	tmp<Field<Type>> cmptMultiply(const Type& s1, const UList<Type>& f2)
	{
		tmp<Field<Type>> tRes(new Field<Type>(f2.size()));
		cmptMultiply(tRes.ref(), s1, f2);
		return tRes;
	}

	template<class Type>
	tmp<Field<Type>> cmptMultiply(const Type& s1, const tmp<Field<Type>>& tf2)
	{
		tmp<Field<Type>> tRes = reuseTmp<Type, Type>::New(tf2);
		cmptMultiply(tRes.ref(), s1, tf2());
		tf2.clear();
		return tRes;
	}

	template<class Type>
	void cmptMultiply(Field<Type>& res, const UList<Type>& f1, const Type& s2)
	{
		TFOR_ALL_F_OP_FUNC_F_S(Type, res, =, ::tnbLib::cmptMultiply, Type, f1, Type, s2)
	}

	template<class Type>
	tmp<Field<Type>> cmptMultiply(const UList<Type>& f1, const Type& s2)
	{
		tmp<Field<Type>> tRes(new Field<Type>(f1.size()));
		cmptMultiply(tRes.ref(), f1, s2);
		return tRes;
	}

	template<class Type>
	tmp<Field<Type>> cmptMultiply(const tmp<Field<Type>>& tf1, const Type& s2)
	{
		tmp<Field<Type>> tRes = reuseTmp<Type, Type>::New(tf1);
		cmptMultiply(tRes.ref(), tf1(), s2);
		tf1.clear();
		return tRes;
	}

	template<class Type>
	void cmptDivide(Field<Type>& res, const Type& s1, const UList<Type>& f2)
	{
		TFOR_ALL_F_OP_FUNC_S_F(Type, res, =, ::tnbLib::cmptDivide, Type, s1, Type, f2)
	}

	template<class Type>
	tmp<Field<Type>> cmptDivide(const Type& s1, const UList<Type>& f2)
	{
		tmp<Field<Type>> tRes(new Field<Type>(f2.size()));
		cmptDivide(tRes.ref(), s1, f2);
		return tRes;
	}

	template<class Type>
	tmp<Field<Type>> cmptDivide(const Type& s1, const tmp<Field<Type>>& tf2)
	{
		tmp<Field<Type>> tRes = reuseTmp<Type, Type>::New(tf2);
		cmptDivide(tRes.ref(), s1, tf2());
		tf2.clear();
		return tRes;
	}

	template<class Type>
	void cmptDivide(Field<Type>& res, const UList<Type>& f1, const Type& s2)
	{
		TFOR_ALL_F_OP_FUNC_F_S(Type, res, =, ::tnbLib::cmptDivide, Type, f1, Type, s2)
	}

	template<class Type>
	tmp<Field<Type>> cmptDivide(const UList<Type>& f1, const Type& s2)
	{
		tmp<Field<Type>> tRes(new Field<Type>(f1.size()));
		cmptDivide(tRes.ref(), f1, s2);
		return tRes;
	}

	template<class Type>
	tmp<Field<Type>> cmptDivide(const tmp<Field<Type>>& tf1, const Type& s2)
	{
		tmp<Field<Type>> tRes = reuseTmp<Type, Type>::New(tf1);
		cmptDivide(tRes.ref(), tf1(), s2);
		tf1.clear();
		return tRes;
	}


	/* * * * * * * * * * * * * * * * Global operators  * * * * * * * * * * * * * */


	template<class Type>
	void negate(Field<Type>& res, const UList<Type>& f)
	{
		TFOR_ALL_F_OP_OP_F(Type, res, =, -, Type, f)
	}

	template<class Type>
	tmp<Field<Type>> operator -(const UList<Type>& f)
	{
		tmp<Field<Type>> tRes(new Field<Type>(f.size()));
		negate(tRes.ref(), f);
		return tRes;
	}

	template<class Type>
	tmp<Field<Type>> operator -(const tmp<Field<Type>>& tf)
	{
		tmp<Field<Type>> tRes = reuseTmp<Type, Type>::New(tf);
		negate(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}


	template<class Type>
	void multiply(Field<Type>& res, const UList<Type>& f1, const UList<scalar>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(Type, res, =, Type, f1, *, scalar, f2)
	}

	template<class Type>
	tmp<Field<Type>> operator *(const UList<Type>& f1, const UList<scalar>& f2)
	{
		tmp<Field<Type>> tRes(new Field<Type>(f1.size()));
		multiply(tRes.ref(), f1, f2);
		return tRes;
	}

	template<class Type>
	tmp<Field<Type>> operator *(const UList<Type>& f1, const tmp<Field<scalar>>& tf2)
	{
		tmp<Field<Type>> tRes = reuseTmp<Type, scalar>::New(tf2);
		multiply(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	template<class Type>
	tmp<Field<Type>> operator *(const tmp<Field<Type>>& tf1, const UList<scalar>& f2)
	{
		tmp<Field<Type>> tRes = reuseTmp<Type, Type>::New(tf1);
		multiply(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	template<class Type>
	tmp<Field<Type>> operator *(const tmp<Field<Type>>& tf1, const tmp<Field<scalar>>& tf2)
	{
		tmp<Field<Type>> tRes = reuseTmpTmp<Type, Type, Type, scalar>::New(tf1, tf2);
		multiply(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}

	template<class Type>
	void multiply(Field<Type>& res, const UList<scalar>& f1, const UList<Type>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(Type, res, =, scalar, f1, *, Type, f2)
	}

	template<class Type>
	tmp<Field<Type>> operator *(const UList<scalar>& f1, const UList<Type>& f2)
	{
		tmp<Field<Type>> tRes(new Field<Type>(f1.size()));
		multiply(tRes.ref(), f1, f2);
		return tRes;
	}

	template<class Type>
	tmp<Field<Type>> operator *(const UList<scalar>& f1, const tmp<Field<Type>>& tf2)
	{
		tmp<Field<Type>> tRes = reuseTmp<Type, Type>::New(tf2);
		multiply(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	template<class Type>
	tmp<Field<Type>> operator *(const tmp<Field<scalar>>& tf1, const UList<Type>& f2)
	{
		tmp<Field<Type>> tRes = reuseTmp<Type, scalar>::New(tf1);
		multiply(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	template<class Type>
	tmp<Field<Type>> operator *(const tmp<Field<scalar>>& tf1, const tmp<Field<Type>>& tf2)
	{
		tmp<Field<Type>> tRes = reuseTmpTmp<Type, scalar, scalar, Type>::New(tf1, tf2);
		multiply(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}

	template<class Type>
	void divide(Field<Type>& res, const UList<Type>& f1, const UList<scalar>& f2)
	{
		TFOR_ALL_F_OP_F_OP_F(Type, res, =, Type, f1, / , scalar, f2)
	}

	template<class Type>
	tmp<Field<Type>> operator /(const UList<Type>& f1, const UList<scalar>& f2)
	{
		tmp<Field<Type>> tRes(new Field<Type>(f1.size()));
		divide(tRes.ref(), f1, f2);
		return tRes;
	}

	template<class Type>
	tmp<Field<Type>> operator /(const UList<Type>& f1, const tmp<Field<scalar>>& tf2)
	{
		tmp<Field<Type>> tRes = reuseTmp<Type, scalar>::New(tf2);
		divide(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	template<class Type>
	tmp<Field<Type>> operator /(const tmp<Field<Type>>& tf1, const UList<scalar>& f2)
	{
		tmp<Field<Type>> tRes = reuseTmp<Type, Type>::New(tf1);
		divide(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	template<class Type>
	tmp<Field<Type>> operator /(const tmp<Field<Type>>& tf1, const tmp<Field<scalar>>& tf2)
	{
		tmp<Field<Type>> tRes = reuseTmpTmp<Type, Type, Type, scalar>::New(tf1, tf2);
		divide(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}


	template<class Type>
	void multiply(Field<Type>& res, const scalar& s1, const UList<Type>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(Type, res, =, scalar, s1, *, Type, f2)
	}

	template<class Type>
	tmp<Field<Type>> operator *(const scalar& s1, const UList<Type>& f2)
	{
		tmp<Field<Type>> tRes(new Field<Type>(f2.size()));
		multiply(tRes.ref(), s1, f2);
		return tRes;
	}

	template<class Type>
	tmp<Field<Type>> operator *(const scalar& s1, const tmp<Field<Type>>& tf2)
	{
		tmp<Field<Type>> tRes = reuseTmp<Type, Type>::New(tf2);
		multiply(tRes.ref(), s1, tf2());
		tf2.clear();
		return tRes;
	}

	template<class Type>
	void multiply(Field<Type>& res, const UList<Type>& f1, const scalar& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(Type, res, =, Type, f1, *, scalar, s2)
	}

	template<class Type>
	tmp<Field<Type>> operator *(const UList<Type>& f1, const scalar& s2)
	{
		tmp<Field<Type>> tRes(new Field<Type>(f1.size()));
		multiply(tRes.ref(), f1, s2);
		return tRes;
	}

	template<class Type>
	tmp<Field<Type>> operator *(const tmp<Field<Type>>& tf1, const scalar& s2)
	{
		tmp<Field<Type>> tRes = reuseTmp<Type, Type>::New(tf1);
		multiply(tRes.ref(), tf1(), s2);
		tf1.clear();
		return tRes;
	}


	template<class Type>
	void divide(Field<Type>& res, const UList<Type>& f1, const scalar& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(Type, res, =, Type, f1, / , scalar, s2)
	}

	template<class Type>
	tmp<Field<Type>> operator /(const UList<Type>& f1, const scalar& s2)
	{
		tmp<Field<Type>> tRes(new Field<Type>(f1.size()));
		divide(tRes.ref(), f1, s2);
		return tRes;
	}

	template<class Type>
	tmp<Field<Type>> operator /(const tmp<Field<Type>>& tf1, const scalar& s2)
	{
		tmp<Field<Type>> tRes = reuseTmp<Type, Type>::New(tf1);
		divide(tRes.ref(), tf1(), s2);
		tf1.clear();
		return tRes;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#define PRODUCT_OPERATOR(product, Op, OpFunc)                                  \
//                                                                               \
//template<class Type1, class Type2>                                             \
//void OpFunc                                                                    \
//(                                                                              \
//    Field<typename product<Type1, Type2>::type>& res,                          \
//    const UList<Type1>& f1,                                                    \
//    const UList<Type2>& f2                                                     \
//)                                                                              \
//{                                                                              \
//    typedef typename product<Type1, Type2>::type productType;                  \
//    TFOR_ALL_F_OP_F_OP_F(productType, res, =, Type1, f1, Op, Type2, f2)        \
//}                                                                              \
//                                                                               \
//template<class Type1, class Type2>                                             \
//tmp<Field<typename product<Type1, Type2>::type>>                               \
//operator Op(const UList<Type1>& f1, const UList<Type2>& f2)                    \
//{                                                                              \
//    typedef typename product<Type1, Type2>::type productType;                  \
//    tmp<Field<productType>> tRes(new Field<productType>(f1.size()));           \
//    OpFunc(tRes.ref(), f1, f2);                                                \
//    return tRes;                                                               \
//}                                                                              \
//                                                                               \
//template<class Type1, class Type2>                                             \
//tmp<Field<typename product<Type1, Type2>::type>>                               \
//operator Op(const UList<Type1>& f1, const tmp<Field<Type2>>& tf2)              \
//{                                                                              \
//    typedef typename product<Type1, Type2>::type productType;                  \
//    tmp<Field<productType>> tRes = reuseTmp<productType, Type2>::New(tf2);     \
//    OpFunc(tRes.ref(), f1, tf2());                                             \
//    tf2.clear();                                                               \
//    return tRes;                                                               \
//}                                                                              \
//                                                                               \
//template<class Type1, class Type2>                                             \
//tmp<Field<typename product<Type1, Type2>::type>>                               \
//operator Op(const tmp<Field<Type1>>& tf1, const UList<Type2>& f2)              \
//{                                                                              \
//    typedef typename product<Type1, Type2>::type productType;                  \
//    tmp<Field<productType>> tRes = reuseTmp<productType, Type1>::New(tf1);     \
//    OpFunc(tRes.ref(), tf1(), f2);                                             \
//    tf1.clear();                                                               \
//    return tRes;                                                               \
//}                                                                              \
//                                                                               \
//template<class Type1, class Type2>                                             \
//tmp<Field<typename product<Type1, Type2>::type>>                               \
//operator Op(const tmp<Field<Type1>>& tf1, const tmp<Field<Type2>>& tf2)        \
//{                                                                              \
//    typedef typename product<Type1, Type2>::type productType;                  \
//    tmp<Field<productType>> tRes =                                             \
//        reuseTmpTmp<productType, Type1, Type1, Type2>::New(tf1, tf2);          \
//    OpFunc(tRes.ref(), tf1(), tf2());                                          \
//    tf1.clear();                                                               \
//    tf2.clear();                                                               \
//    return tRes;                                                               \
//}                                                                              \
//                                                                               \
//template<class Type, class Form, class Cmpt, direction nCmpt>                  \
//void OpFunc                                                                    \
//(                                                                              \
//    Field<typename product<Type, Form>::type>& res,                            \
//    const UList<Type>& f1,                                                     \
//    const VectorSpace<Form,Cmpt,nCmpt>& vs                                     \
//)                                                                              \
//{                                                                              \
//    typedef typename product<Type, Form>::type productType;                    \
//    TFOR_ALL_F_OP_F_OP_S                                                       \
//        (productType, res, =,Type, f1, Op, Form, static_cast<const Form&>(vs)) \
//}                                                                              \
//                                                                               \
//template<class Type, class Form, class Cmpt, direction nCmpt>                  \
//tmp<Field<typename product<Type, Form>::type>>                                 \
//operator Op(const UList<Type>& f1, const VectorSpace<Form,Cmpt,nCmpt>& vs)     \
//{                                                                              \
//    typedef typename product<Type, Form>::type productType;                    \
//    tmp<Field<productType>> tRes(new Field<productType>(f1.size()));           \
//    OpFunc(tRes.ref(), f1, static_cast<const Form&>(vs));                      \
//    return tRes;                                                               \
//}                                                                              \
//                                                                               \
//template<class Type, class Form, class Cmpt, direction nCmpt>                  \
//tmp<Field<typename product<Type, Form>::type>>                                 \
//operator Op                                                                    \
//(                                                                              \
//    const tmp<Field<Type>>& tf1,                                               \
//    const VectorSpace<Form,Cmpt,nCmpt>& vs                                     \
//)                                                                              \
//{                                                                              \
//    typedef typename product<Type, Form>::type productType;                    \
//    tmp<Field<productType>> tRes = reuseTmp<productType, Type>::New(tf1);      \
//    OpFunc(tRes.ref(), tf1(), static_cast<const Form&>(vs));                   \
//    tf1.clear();                                                               \
//    return tRes;                                                               \
//}                                                                              \
//                                                                               \
//template<class Form, class Cmpt, direction nCmpt, class Type>                  \
//void OpFunc                                                                    \
//(                                                                              \
//    Field<typename product<Form, Type>::type>& res,                            \
//    const VectorSpace<Form,Cmpt,nCmpt>& vs,                                    \
//    const UList<Type>& f1                                                      \
//)                                                                              \
//{                                                                              \
//    typedef typename product<Form, Type>::type productType;                    \
//    TFOR_ALL_F_OP_S_OP_F                                                       \
//        (productType, res, =,Form,static_cast<const Form&>(vs), Op, Type, f1)  \
//}                                                                              \
//                                                                               \
//template<class Form, class Cmpt, direction nCmpt, class Type>                  \
//tmp<Field<typename product<Form, Type>::type>>                                 \
//operator Op(const VectorSpace<Form,Cmpt,nCmpt>& vs, const UList<Type>& f1)     \
//{                                                                              \
//    typedef typename product<Form, Type>::type productType;                    \
//    tmp<Field<productType>> tRes(new Field<productType>(f1.size()));           \
//    OpFunc(tRes.ref(), static_cast<const Form&>(vs), f1);                      \
//    return tRes;                                                               \
//}                                                                              \
//                                                                               \
//template<class Form, class Cmpt, direction nCmpt, class Type>                  \
//tmp<Field<typename product<Form, Type>::type>>                                 \
//operator Op                                                                    \
//(                                                                              \
//    const VectorSpace<Form,Cmpt,nCmpt>& vs, const tmp<Field<Type>>& tf1        \
//)                                                                              \
//{                                                                              \
//    typedef typename product<Form, Type>::type productType;                    \
//    tmp<Field<productType>> tRes = reuseTmp<productType, Type>::New(tf1);      \
//    OpFunc(tRes.ref(), static_cast<const Form&>(vs), tf1());                   \
//    tf1.clear();                                                               \
//    return tRes;                                                               \
//}


	template <class Type1, class Type2>
	void add(Field<typename typeOfSum<Type1, Type2>::type>& res, const UList<Type1>& f1, const UList<Type2>& f2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		TFOR_ALL_F_OP_F_OP_F(productType, res, =, Type1, f1, +, Type2, f2)
	}

	template <class Type1, class Type2>
	tmp<Field<typename typeOfSum<Type1, Type2>::type>> operator +(const UList<Type1>& f1, const UList<Type2>& f2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		tmp<Field<productType>> tRes(new Field<productType>(f1.size()));
		add(tRes.ref(), f1, f2);
		return tRes;
	}

	template <class Type1, class Type2>
	tmp<Field<typename typeOfSum<Type1, Type2>::type>> operator +(const UList<Type1>& f1, const tmp<Field<Type2>>& tf2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		tmp<Field<productType>> tRes = reuseTmp<productType, Type2>::New(tf2);
		add(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	template <class Type1, class Type2>
	tmp<Field<typename typeOfSum<Type1, Type2>::type>> operator +(const tmp<Field<Type1>>& tf1, const UList<Type2>& f2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		tmp<Field<productType>> tRes = reuseTmp<productType, Type1>::New(tf1);
		add(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	template <class Type1, class Type2>
	tmp<Field<typename typeOfSum<Type1, Type2>::type>> operator +(const tmp<Field<Type1>>& tf1,
		const tmp<Field<Type2>>& tf2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		tmp<Field<productType>> tRes = reuseTmpTmp<productType, Type1, Type1, Type2>::New(tf1, tf2);
		add(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}

	template <class Type, class Form, class Cmpt, direction nCmpt>
	void add(Field<typename typeOfSum<Type, Form>::type>& res, const UList<Type>& f1,
		const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		typedef typename typeOfSum<Type, Form>::type productType;
		TFOR_ALL_F_OP_F_OP_S(productType, res, =, Type, f1, +, Form, static_cast<const Form&>(vs))
	}

	template <class Type, class Form, class Cmpt, direction nCmpt>
	tmp<Field<typename typeOfSum<Type, Form>::type>> operator +(const UList<Type>& f1,
		const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		typedef typename typeOfSum<Type, Form>::type productType;
		tmp<Field<productType>> tRes(new Field<productType>(f1.size()));
		add(tRes.ref(), f1, static_cast<const Form&>(vs));
		return tRes;
	}

	template <class Type, class Form, class Cmpt, direction nCmpt>
	tmp<Field<typename typeOfSum<Type, Form>::type>> operator +(const tmp<Field<Type>>& tf1,
		const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		typedef typename typeOfSum<Type, Form>::type productType;
		tmp<Field<productType>> tRes = reuseTmp<productType, Type>::New(tf1);
		add(tRes.ref(), tf1(), static_cast<const Form&>(vs));
		tf1.clear();
		return tRes;
	}

	template <class Form, class Cmpt, direction nCmpt, class Type>
	void add(Field<typename typeOfSum<Form, Type>::type>& res, const VectorSpace<Form, Cmpt, nCmpt>& vs,
		const UList<Type>& f1)
	{
		typedef typename typeOfSum<Form, Type>::type productType;
		TFOR_ALL_F_OP_S_OP_F(productType, res, =, Form, static_cast<const Form&>(vs), +, Type, f1)
	}

	template <class Form, class Cmpt, direction nCmpt, class Type>
	tmp<Field<typename typeOfSum<Form, Type>::type>> operator +(const VectorSpace<Form, Cmpt, nCmpt>& vs,
		const UList<Type>& f1)
	{
		typedef typename typeOfSum<Form, Type>::type productType;
		tmp<Field<productType>> tRes(new Field<productType>(f1.size()));
		add(tRes.ref(), static_cast<const Form&>(vs), f1);
		return tRes;
	}

	template <class Form, class Cmpt, direction nCmpt, class Type>
	tmp<Field<typename typeOfSum<Form, Type>::type>> operator +(const VectorSpace<Form, Cmpt, nCmpt>& vs,
		const tmp<Field<Type>>& tf1)
	{
		typedef typename typeOfSum<Form, Type>::type productType;
		tmp<Field<productType>> tRes = reuseTmp<productType, Type>::New(tf1);
		add(tRes.ref(), static_cast<const Form&>(vs), tf1());
		tf1.clear();
		return tRes;
	}

	template <class Type1, class Type2>
	void subtract(Field<typename typeOfSum<Type1, Type2>::type>& res, const UList<Type1>& f1, const UList<Type2>& f2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		TFOR_ALL_F_OP_F_OP_F(productType, res, =, Type1, f1, -, Type2, f2)
	}

	template <class Type1, class Type2>
	tmp<Field<typename typeOfSum<Type1, Type2>::type>> operator -(const UList<Type1>& f1, const UList<Type2>& f2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		tmp<Field<productType>> tRes(new Field<productType>(f1.size()));
		subtract(tRes.ref(), f1, f2);
		return tRes;
	}

	template <class Type1, class Type2>
	tmp<Field<typename typeOfSum<Type1, Type2>::type>> operator -(const UList<Type1>& f1, const tmp<Field<Type2>>& tf2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		tmp<Field<productType>> tRes = reuseTmp<productType, Type2>::New(tf2);
		subtract(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	template <class Type1, class Type2>
	tmp<Field<typename typeOfSum<Type1, Type2>::type>> operator -(const tmp<Field<Type1>>& tf1, const UList<Type2>& f2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		tmp<Field<productType>> tRes = reuseTmp<productType, Type1>::New(tf1);
		subtract(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	template <class Type1, class Type2>
	tmp<Field<typename typeOfSum<Type1, Type2>::type>> operator -(const tmp<Field<Type1>>& tf1,
		const tmp<Field<Type2>>& tf2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		tmp<Field<productType>> tRes = reuseTmpTmp<productType, Type1, Type1, Type2>::New(tf1, tf2);
		subtract(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}

	template <class Type, class Form, class Cmpt, direction nCmpt>
	void subtract(Field<typename typeOfSum<Type, Form>::type>& res, const UList<Type>& f1,
		const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		typedef typename typeOfSum<Type, Form>::type productType;
		TFOR_ALL_F_OP_F_OP_S(productType, res, =, Type, f1, -, Form, static_cast<const Form&>(vs))
	}

	template <class Type, class Form, class Cmpt, direction nCmpt>
	tmp<Field<typename typeOfSum<Type, Form>::type>> operator -(const UList<Type>& f1,
		const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		typedef typename typeOfSum<Type, Form>::type productType;
		tmp<Field<productType>> tRes(new Field<productType>(f1.size()));
		subtract(tRes.ref(), f1, static_cast<const Form&>(vs));
		return tRes;
	}

	template <class Type, class Form, class Cmpt, direction nCmpt>
	tmp<Field<typename typeOfSum<Type, Form>::type>> operator -(const tmp<Field<Type>>& tf1,
		const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		typedef typename typeOfSum<Type, Form>::type productType;
		tmp<Field<productType>> tRes = reuseTmp<productType, Type>::New(tf1);
		subtract(tRes.ref(), tf1(), static_cast<const Form&>(vs));
		tf1.clear();
		return tRes;
	}

	template <class Form, class Cmpt, direction nCmpt, class Type>
	void subtract(Field<typename typeOfSum<Form, Type>::type>& res, const VectorSpace<Form, Cmpt, nCmpt>& vs,
		const UList<Type>& f1)
	{
		typedef typename typeOfSum<Form, Type>::type productType;
		TFOR_ALL_F_OP_S_OP_F(productType, res, =, Form, static_cast<const Form&>(vs), -, Type, f1)
	}

	template <class Form, class Cmpt, direction nCmpt, class Type>
	tmp<Field<typename typeOfSum<Form, Type>::type>> operator -(const VectorSpace<Form, Cmpt, nCmpt>& vs,
		const UList<Type>& f1)
	{
		typedef typename typeOfSum<Form, Type>::type productType;
		tmp<Field<productType>> tRes(new Field<productType>(f1.size()));
		subtract(tRes.ref(), static_cast<const Form&>(vs), f1);
		return tRes;
	}

	template <class Form, class Cmpt, direction nCmpt, class Type>
	tmp<Field<typename typeOfSum<Form, Type>::type>> operator -(const VectorSpace<Form, Cmpt, nCmpt>& vs,
		const tmp<Field<Type>>& tf1)
	{
		typedef typename typeOfSum<Form, Type>::type productType;
		tmp<Field<productType>> tRes = reuseTmp<productType, Type>::New(tf1);
		subtract(tRes.ref(), static_cast<const Form&>(vs), tf1());
		tf1.clear();
		return tRes;
	}


	template <class Type1, class Type2>
	void outer(Field<typename outerProduct<Type1, Type2>::type>& res, const UList<Type1>& f1, const UList<Type2>& f2)
	{
		typedef typename outerProduct<Type1, Type2>::type productType;
		TFOR_ALL_F_OP_F_OP_F(productType, res, =, Type1, f1, *, Type2, f2)
	}

	template <class Type1, class Type2>
	tmp<Field<typename outerProduct<Type1, Type2>::type>> operator *(const UList<Type1>& f1, const UList<Type2>& f2)
	{
		typedef typename outerProduct<Type1, Type2>::type productType;
		tmp<Field<productType>> tRes(new Field<productType>(f1.size()));
		outer(tRes.ref(), f1, f2);
		return tRes;
	}

	template <class Type1, class Type2>
	tmp<Field<typename outerProduct<Type1, Type2>::type>> operator *(const UList<Type1>& f1, const tmp<Field<Type2>>& tf2)
	{
		typedef typename outerProduct<Type1, Type2>::type productType;
		tmp<Field<productType>> tRes = reuseTmp<productType, Type2>::New(tf2);
		outer(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	template <class Type1, class Type2>
	tmp<Field<typename outerProduct<Type1, Type2>::type>> operator *(const tmp<Field<Type1>>& tf1, const UList<Type2>& f2)
	{
		typedef typename outerProduct<Type1, Type2>::type productType;
		tmp<Field<productType>> tRes = reuseTmp<productType, Type1>::New(tf1);
		outer(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	template <class Type1, class Type2>
	tmp<Field<typename outerProduct<Type1, Type2>::type>> operator *(const tmp<Field<Type1>>& tf1,
		const tmp<Field<Type2>>& tf2)
	{
		typedef typename outerProduct<Type1, Type2>::type productType;
		tmp<Field<productType>> tRes = reuseTmpTmp<productType, Type1, Type1, Type2>::New(tf1, tf2);
		outer(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}

	template <class Type, class Form, class Cmpt, direction nCmpt>
	void outer(Field<typename outerProduct<Type, Form>::type>& res, const UList<Type>& f1,
		const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		typedef typename outerProduct<Type, Form>::type productType;
		TFOR_ALL_F_OP_F_OP_S(productType, res, =, Type, f1, *, Form, static_cast<const Form&>(vs))
	}

	template <class Type, class Form, class Cmpt, direction nCmpt>
	tmp<Field<typename outerProduct<Type, Form>::type>> operator *(const UList<Type>& f1,
		const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		typedef typename outerProduct<Type, Form>::type productType;
		tmp<Field<productType>> tRes(new Field<productType>(f1.size()));
		outer(tRes.ref(), f1, static_cast<const Form&>(vs));
		return tRes;
	}

	template <class Type, class Form, class Cmpt, direction nCmpt>
	tmp<Field<typename outerProduct<Type, Form>::type>> operator *(const tmp<Field<Type>>& tf1,
		const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		typedef typename outerProduct<Type, Form>::type productType;
		tmp<Field<productType>> tRes = reuseTmp<productType, Type>::New(tf1);
		outer(tRes.ref(), tf1(), static_cast<const Form&>(vs));
		tf1.clear();
		return tRes;
	}

	template <class Form, class Cmpt, direction nCmpt, class Type>
	void outer(Field<typename outerProduct<Form, Type>::type>& res, const VectorSpace<Form, Cmpt, nCmpt>& vs,
		const UList<Type>& f1)
	{
		typedef typename outerProduct<Form, Type>::type productType;
		TFOR_ALL_F_OP_S_OP_F(productType, res, =, Form, static_cast<const Form&>(vs), *, Type, f1)
	}

	template <class Form, class Cmpt, direction nCmpt, class Type>
	tmp<Field<typename outerProduct<Form, Type>::type>> operator *(const VectorSpace<Form, Cmpt, nCmpt>& vs,
		const UList<Type>& f1)
	{
		typedef typename outerProduct<Form, Type>::type productType;
		tmp<Field<productType>> tRes(new Field<productType>(f1.size()));
		outer(tRes.ref(), static_cast<const Form&>(vs), f1);
		return tRes;
	}

	template <class Form, class Cmpt, direction nCmpt, class Type>
	tmp<Field<typename outerProduct<Form, Type>::type>> operator *(const VectorSpace<Form, Cmpt, nCmpt>& vs,
		const tmp<Field<Type>>& tf1)
	{
		typedef typename outerProduct<Form, Type>::type productType;
		tmp<Field<productType>> tRes = reuseTmp<productType, Type>::New(tf1);
		outer(tRes.ref(), static_cast<const Form&>(vs), tf1());
		tf1.clear();
		return tRes;
	}

	template <class Type1, class Type2>
	void cross(Field<typename crossProduct<Type1, Type2>::type>& res, const UList<Type1>& f1, const UList<Type2>& f2)
	{
		typedef typename crossProduct<Type1, Type2>::type productType;
		TFOR_ALL_F_OP_F_OP_F(productType, res, =, Type1, f1, ^, Type2, f2)
	}

	template <class Type1, class Type2>
	tmp<Field<typename crossProduct<Type1, Type2>::type>> operator ^(const UList<Type1>& f1, const UList<Type2>& f2)
	{
		typedef typename crossProduct<Type1, Type2>::type productType;
		tmp<Field<productType>> tRes(new Field<productType>(f1.size()));
		cross(tRes.ref(), f1, f2);
		return tRes;
	}

	template <class Type1, class Type2>
	tmp<Field<typename crossProduct<Type1, Type2>::type>> operator ^(const UList<Type1>& f1, const tmp<Field<Type2>>& tf2)
	{
		typedef typename crossProduct<Type1, Type2>::type productType;
		tmp<Field<productType>> tRes = reuseTmp<productType, Type2>::New(tf2);
		cross(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	template <class Type1, class Type2>
	tmp<Field<typename crossProduct<Type1, Type2>::type>> operator ^(const tmp<Field<Type1>>& tf1, const UList<Type2>& f2)
	{
		typedef typename crossProduct<Type1, Type2>::type productType;
		tmp<Field<productType>> tRes = reuseTmp<productType, Type1>::New(tf1);
		cross(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	template <class Type1, class Type2>
	tmp<Field<typename crossProduct<Type1, Type2>::type>> operator ^(const tmp<Field<Type1>>& tf1,
		const tmp<Field<Type2>>& tf2)
	{
		typedef typename crossProduct<Type1, Type2>::type productType;
		tmp<Field<productType>> tRes = reuseTmpTmp<productType, Type1, Type1, Type2>::New(tf1, tf2);
		cross(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}

	template <class Type, class Form, class Cmpt, direction nCmpt>
	void cross(Field<typename crossProduct<Type, Form>::type>& res, const UList<Type>& f1,
		const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		typedef typename crossProduct<Type, Form>::type productType;
		TFOR_ALL_F_OP_F_OP_S(productType, res, =, Type, f1, ^, Form, static_cast<const Form&>(vs))
	}

	template <class Type, class Form, class Cmpt, direction nCmpt>
	tmp<Field<typename crossProduct<Type, Form>::type>> operator ^(const UList<Type>& f1,
		const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		typedef typename crossProduct<Type, Form>::type productType;
		tmp<Field<productType>> tRes(new Field<productType>(f1.size()));
		cross(tRes.ref(), f1, static_cast<const Form&>(vs));
		return tRes;
	}

	template <class Type, class Form, class Cmpt, direction nCmpt>
	tmp<Field<typename crossProduct<Type, Form>::type>> operator ^(const tmp<Field<Type>>& tf1,
		const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		typedef typename crossProduct<Type, Form>::type productType;
		tmp<Field<productType>> tRes = reuseTmp<productType, Type>::New(tf1);
		cross(tRes.ref(), tf1(), static_cast<const Form&>(vs));
		tf1.clear();
		return tRes;
	}

	template <class Form, class Cmpt, direction nCmpt, class Type>
	void cross(Field<typename crossProduct<Form, Type>::type>& res, const VectorSpace<Form, Cmpt, nCmpt>& vs,
		const UList<Type>& f1)
	{
		typedef typename crossProduct<Form, Type>::type productType;
		TFOR_ALL_F_OP_S_OP_F(productType, res, =, Form, static_cast<const Form&>(vs), ^, Type, f1)
	}

	template <class Form, class Cmpt, direction nCmpt, class Type>
	tmp<Field<typename crossProduct<Form, Type>::type>> operator ^(const VectorSpace<Form, Cmpt, nCmpt>& vs,
		const UList<Type>& f1)
	{
		typedef typename crossProduct<Form, Type>::type productType;
		tmp<Field<productType>> tRes(new Field<productType>(f1.size()));
		cross(tRes.ref(), static_cast<const Form&>(vs), f1);
		return tRes;
	}

	template <class Form, class Cmpt, direction nCmpt, class Type>
	tmp<Field<typename crossProduct<Form, Type>::type>> operator ^(const VectorSpace<Form, Cmpt, nCmpt>& vs,
		const tmp<Field<Type>>& tf1)
	{
		typedef typename crossProduct<Form, Type>::type productType;
		tmp<Field<productType>> tRes = reuseTmp<productType, Type>::New(tf1);
		cross(tRes.ref(), static_cast<const Form&>(vs), tf1());
		tf1.clear();
		return tRes;
	}

	template <class Type1, class Type2>
	void dot(Field<typename innerProduct<Type1, Type2>::type>& res, const UList<Type1>& f1, const UList<Type2>& f2)
	{
		typedef typename innerProduct<Type1, Type2>::type productType;
		TFOR_ALL_F_OP_F_OP_F(productType, res, =, Type1, f1, &, Type2, f2)
	}

	template <class Type1, class Type2>
	tmp<Field<typename innerProduct<Type1, Type2>::type>> operator &(const UList<Type1>& f1, const UList<Type2>& f2)
	{
		typedef typename innerProduct<Type1, Type2>::type productType;
		tmp<Field<productType>> tRes(new Field<productType>(f1.size()));
		dot(tRes.ref(), f1, f2);
		return tRes;
	}

	template <class Type1, class Type2>
	tmp<Field<typename innerProduct<Type1, Type2>::type>> operator &(const UList<Type1>& f1, const tmp<Field<Type2>>& tf2)
	{
		typedef typename innerProduct<Type1, Type2>::type productType;
		tmp<Field<productType>> tRes = reuseTmp<productType, Type2>::New(tf2);
		dot(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	template <class Type1, class Type2>
	tmp<Field<typename innerProduct<Type1, Type2>::type>> operator &(const tmp<Field<Type1>>& tf1, const UList<Type2>& f2)
	{
		typedef typename innerProduct<Type1, Type2>::type productType;
		tmp<Field<productType>> tRes = reuseTmp<productType, Type1>::New(tf1);
		dot(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	template <class Type1, class Type2>
	tmp<Field<typename innerProduct<Type1, Type2>::type>> operator &(const tmp<Field<Type1>>& tf1,
		const tmp<Field<Type2>>& tf2)
	{
		typedef typename innerProduct<Type1, Type2>::type productType;
		tmp<Field<productType>> tRes = reuseTmpTmp<productType, Type1, Type1, Type2>::New(tf1, tf2);
		dot(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}

	template <class Type, class Form, class Cmpt, direction nCmpt>
	void dot(Field<typename innerProduct<Type, Form>::type>& res, const UList<Type>& f1,
		const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		typedef typename innerProduct<Type, Form>::type productType;
		TFOR_ALL_F_OP_F_OP_S(productType, res, =, Type, f1, &, Form, static_cast<const Form&>(vs))
	}

	template <class Type, class Form, class Cmpt, direction nCmpt>
	tmp<Field<typename innerProduct<Type, Form>::type>> operator &(const UList<Type>& f1,
		const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		typedef typename innerProduct<Type, Form>::type productType;
		tmp<Field<productType>> tRes(new Field<productType>(f1.size()));
		dot(tRes.ref(), f1, static_cast<const Form&>(vs));
		return tRes;
	}

	template <class Type, class Form, class Cmpt, direction nCmpt>
	tmp<Field<typename innerProduct<Type, Form>::type>> operator &(const tmp<Field<Type>>& tf1,
		const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		typedef typename innerProduct<Type, Form>::type productType;
		tmp<Field<productType>> tRes = reuseTmp<productType, Type>::New(tf1);
		dot(tRes.ref(), tf1(), static_cast<const Form&>(vs));
		tf1.clear();
		return tRes;
	}

	template <class Form, class Cmpt, direction nCmpt, class Type>
	void dot(Field<typename innerProduct<Form, Type>::type>& res, const VectorSpace<Form, Cmpt, nCmpt>& vs,
		const UList<Type>& f1)
	{
		typedef typename innerProduct<Form, Type>::type productType;
		TFOR_ALL_F_OP_S_OP_F(productType, res, =, Form, static_cast<const Form&>(vs), &, Type, f1)
	}

	template <class Form, class Cmpt, direction nCmpt, class Type>
	tmp<Field<typename innerProduct<Form, Type>::type>> operator &(const VectorSpace<Form, Cmpt, nCmpt>& vs,
		const UList<Type>& f1)
	{
		typedef typename innerProduct<Form, Type>::type productType;
		tmp<Field<productType>> tRes(new Field<productType>(f1.size()));
		dot(tRes.ref(), static_cast<const Form&>(vs), f1);
		return tRes;
	}

	template <class Form, class Cmpt, direction nCmpt, class Type>
	tmp<Field<typename innerProduct<Form, Type>::type>> operator &(const VectorSpace<Form, Cmpt, nCmpt>& vs,
		const tmp<Field<Type>>& tf1)
	{
		typedef typename innerProduct<Form, Type>::type productType;
		tmp<Field<productType>> tRes = reuseTmp<productType, Type>::New(tf1);
		dot(tRes.ref(), static_cast<const Form&>(vs), tf1());
		tf1.clear();
		return tRes;
	}

	template <class Type1, class Type2>
	void dotdot(Field<typename scalarProduct<Type1, Type2>::type>& res, const UList<Type1>& f1, const UList<Type2>& f2)
	{
		typedef typename scalarProduct<Type1, Type2>::type productType;
		TFOR_ALL_F_OP_F_OP_F(productType, res, =, Type1, f1, &&, Type2, f2)
	}

	template <class Type1, class Type2>
	tmp<Field<typename scalarProduct<Type1, Type2>::type>> operator &&(const UList<Type1>& f1, const UList<Type2>& f2)
	{
		typedef typename scalarProduct<Type1, Type2>::type productType;
		tmp<Field<productType>> tRes(new Field<productType>(f1.size()));
		dotdot(tRes.ref(), f1, f2);
		return tRes;
	}

	template <class Type1, class Type2>
	tmp<Field<typename scalarProduct<Type1, Type2>::type>> operator &&(const UList<Type1>& f1,
		const tmp<Field<Type2>>& tf2)
	{
		typedef typename scalarProduct<Type1, Type2>::type productType;
		tmp<Field<productType>> tRes = reuseTmp<productType, Type2>::New(tf2);
		dotdot(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	template <class Type1, class Type2>
	tmp<Field<typename scalarProduct<Type1, Type2>::type>> operator &&(const tmp<Field<Type1>>& tf1,
		const UList<Type2>& f2)
	{
		typedef typename scalarProduct<Type1, Type2>::type productType;
		tmp<Field<productType>> tRes = reuseTmp<productType, Type1>::New(tf1);
		dotdot(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	template <class Type1, class Type2>
	tmp<Field<typename scalarProduct<Type1, Type2>::type>> operator &&(const tmp<Field<Type1>>& tf1,
		const tmp<Field<Type2>>& tf2)
	{
		typedef typename scalarProduct<Type1, Type2>::type productType;
		tmp<Field<productType>> tRes = reuseTmpTmp<productType, Type1, Type1, Type2>::New(tf1, tf2);
		dotdot(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}

	template <class Type, class Form, class Cmpt, direction nCmpt>
	void dotdot(Field<typename scalarProduct<Type, Form>::type>& res, const UList<Type>& f1,
		const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		typedef typename scalarProduct<Type, Form>::type productType;
		TFOR_ALL_F_OP_F_OP_S(productType, res, =, Type, f1, &&, Form, static_cast<const Form&>(vs))
	}

	template <class Type, class Form, class Cmpt, direction nCmpt>
	tmp<Field<typename scalarProduct<Type, Form>::type>> operator &&(const UList<Type>& f1,
		const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		typedef typename scalarProduct<Type, Form>::type productType;
		tmp<Field<productType>> tRes(new Field<productType>(f1.size()));
		dotdot(tRes.ref(), f1, static_cast<const Form&>(vs));
		return tRes;
	}

	template <class Type, class Form, class Cmpt, direction nCmpt>
	tmp<Field<typename scalarProduct<Type, Form>::type>> operator &&(const tmp<Field<Type>>& tf1,
		const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		typedef typename scalarProduct<Type, Form>::type productType;
		tmp<Field<productType>> tRes = reuseTmp<productType, Type>::New(tf1);
		dotdot(tRes.ref(), tf1(), static_cast<const Form&>(vs));
		tf1.clear();
		return tRes;
	}

	template <class Form, class Cmpt, direction nCmpt, class Type>
	void dotdot(Field<typename scalarProduct<Form, Type>::type>& res, const VectorSpace<Form, Cmpt, nCmpt>& vs,
		const UList<Type>& f1)
	{
		typedef typename scalarProduct<Form, Type>::type productType;
		TFOR_ALL_F_OP_S_OP_F(productType, res, =, Form, static_cast<const Form&>(vs), &&, Type, f1)
	}

	template <class Form, class Cmpt, direction nCmpt, class Type>
	tmp<Field<typename scalarProduct<Form, Type>::type>> operator &&(const VectorSpace<Form, Cmpt, nCmpt>& vs,
		const UList<Type>& f1)
	{
		typedef typename scalarProduct<Form, Type>::type productType;
		tmp<Field<productType>> tRes(new Field<productType>(f1.size()));
		dotdot(tRes.ref(), static_cast<const Form&>(vs), f1);
		return tRes;
	}

	template <class Form, class Cmpt, direction nCmpt, class Type>
	tmp<Field<typename scalarProduct<Form, Type>::type>> operator &&(const VectorSpace<Form, Cmpt, nCmpt>& vs,
		const tmp<Field<Type>>& tf1)
	{
		typedef typename scalarProduct<Form, Type>::type productType;
		tmp<Field<productType>> tRes = reuseTmp<productType, Type>::New(tf1);
		dotdot(tRes.ref(), static_cast<const Form&>(vs), tf1());
		tf1.clear();
		return tRes;
	}

//#undef PRODUCT_OPERATOR


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //