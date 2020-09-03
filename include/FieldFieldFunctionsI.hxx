#pragma once
#include <PstreamReduceOps.hxx>
#include <FieldFieldReuseFunctions.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/* * * * * * * * * * * * * * * * Global functions  * * * * * * * * * * * * * */

	template<template<class> class Field, class Type>
	void component
	(
		FieldField<Field, typename FieldField<Field, Type>::cmptType>& sf,
		const FieldField<Field, Type>& f,
		const direction d
	)
	{
		forAll(sf, i)
		{
			component(sf[i], f[i], d);
		}
	}


	template<template<class> class Field, class Type>
	void T(FieldField<Field, Type>& f1, const FieldField<Field, Type>& f2)
	{
		forAll(f1, i)
		{
			T(f1[i], f2[i]);
		}
	}


	template<template<class> class Field, class Type, direction r>
	void pow
	(
		FieldField<Field, typename powProduct<Type, r>::type>& f,
		const FieldField<Field, Type>& vf
	)
	{
		forAll(f, i)
		{
			pow(f[i], vf[i]);
		}
	}

	template<template<class> class Field, class Type, direction r>
	tmp<FieldField<Field, typename powProduct<Type, r>::type>>
		pow
		(
			const FieldField<Field, Type>& f, typename powProduct<Type, r>::type
		)
	{
		typedef typename powProduct<Type, r>::type powProductType;
		tmp<FieldField<Field, powProductType>> tRes
		(
			FieldField<Field, powProductType>::NewCalculatedType(f)
		);
		pow<Type, r>(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field, class Type, direction r>
	tmp<FieldField<Field, typename powProduct<Type, r>::type>>
		pow
		(
			const tmp<FieldField<Field, Type>>& tf, typename powProduct<Type, r>::type
		)
	{
		typedef typename powProduct<Type, r>::type powProductType;
		tmp<FieldField<Field, powProductType>> tRes
		(
			reuseTmpFieldField<Field, powProductType, Type>::New(tf)
		);
		pow<Type, r>(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}


	template<template<class> class Field, class Type>
	void sqr
	(
		FieldField<Field, typename outerProduct<Type, Type>::type>& f,
		const FieldField<Field, Type>& vf
	)
	{
		forAll(f, i)
		{
			sqr(f[i], vf[i]);
		}
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, typename outerProduct<Type, Type>::type>>
		sqr(const FieldField<Field, Type>& f)
	{
		typedef typename outerProduct<Type, Type>::type outerProductType;
		tmp<FieldField<Field, outerProductType>> tRes
		(
			FieldField<Field, outerProductType>::NewCalculatedType(f)
		);
		sqr(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, typename outerProduct<Type, Type>::type>>
		sqr(const tmp<FieldField<Field, Type>>& tf)
	{
		typedef typename outerProduct<Type, Type>::type outerProductType;
		tmp<FieldField<Field, outerProductType>> tRes
		(
			reuseTmpFieldField<Field, outerProductType, Type>::New(tf)
		);
		sqr(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}


	template<template<class> class Field, class Type>
	void magSqr(FieldField<Field, scalar>& sf, const FieldField<Field, Type>& f)
	{
		forAll(sf, i)
		{
			magSqr(sf[i], f[i]);
		}
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, scalar>> magSqr(const FieldField<Field, Type>& f)
	{
		tmp<FieldField<Field, scalar>> tRes
		(
			FieldField<Field, scalar>::NewCalculatedType(f)
		);

		magSqr(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, scalar>> magSqr(const tmp<FieldField<Field, Type>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes
		(
			reuseTmpFieldField<Field, scalar, Type>::New(tf)
		);

		magSqr(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}


	template<template<class> class Field, class Type>
	void mag(FieldField<Field, scalar>& sf, const FieldField<Field, Type>& f)
	{
		forAll(sf, i)
		{
			mag(sf[i], f[i]);
		}
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, scalar>> mag(const FieldField<Field, Type>& f)
	{
		tmp<FieldField<Field, scalar>> tRes
		(
			FieldField<Field, scalar>::NewCalculatedType(f)
		);

		mag(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, scalar>> mag(const tmp<FieldField<Field, Type>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes
		(
			reuseTmpFieldField<Field, scalar, Type>::New(tf)
		);

		mag(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}


	template<template<class> class Field, class Type>
	void cmptMax
	(
		FieldField<Field, typename FieldField<Field, Type>::cmptType>& cf,
		const FieldField<Field, Type>& f
	)
	{
		forAll(cf, i)
		{
			cmptMax(cf[i], f[i]);
		}
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, typename FieldField<Field, Type>::cmptType>> cmptMax
	(
		const FieldField<Field, Type>& f
	)
	{
		typedef typename FieldField<Field, Type>::cmptType cmptType;
		tmp<FieldField<Field, cmptType>> tRes
		(
			FieldField<Field, cmptType>::NewCalculatedType(f)
		);
		cmptMax(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, typename FieldField<Field, Type>::cmptType>> cmptMax
	(
		const tmp<FieldField<Field, Type>>& tf
	)
	{
		typedef typename FieldField<Field, Type>::cmptType cmptType;
		tmp<FieldField<Field, cmptType>> tRes
		(
			reuseTmpFieldField<Field, cmptType, Type>::New(tf)
		);
		cmptMax(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}


	template<template<class> class Field, class Type>
	void cmptMin
	(
		FieldField<Field, typename FieldField<Field, Type>::cmptType>& cf,
		const FieldField<Field, Type>& f
	)
	{
		forAll(cf, i)
		{
			cmptMin(cf[i], f[i]);
		}
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, typename FieldField<Field, Type>::cmptType>> cmptMin
	(
		const FieldField<Field, Type>& f
	)
	{
		typedef typename FieldField<Field, Type>::cmptType cmptType;
		tmp<FieldField<Field, cmptType>> tRes
		(
			FieldField<Field, cmptType>::NewCalculatedType(f)
		);
		cmptMin(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, typename FieldField<Field, Type>::cmptType>> cmptMin
	(
		const tmp<FieldField<Field, Type>>& tf
	)
	{
		typedef typename FieldField<Field, Type>::cmptType cmptType;
		tmp<FieldField<Field, cmptType>> tRes
		(
			reuseTmpFieldField<Field, cmptType, Type>::New(tf)
		);
		cmptMin(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}


	template<template<class> class Field, class Type>
	void cmptAv
	(
		FieldField<Field, typename FieldField<Field, Type>::cmptType>& cf,
		const FieldField<Field, Type>& f
	)
	{
		forAll(cf, i)
		{
			cmptAv(cf[i], f[i]);
		}
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, typename FieldField<Field, Type>::cmptType>> cmptAv
	(
		const FieldField<Field, Type>& f
	)
	{
		typedef typename FieldField<Field, Type>::cmptType cmptType;
		tmp<FieldField<Field, cmptType>> tRes
		(
			FieldField<Field, cmptType>::NewCalculatedType(f)
		);
		cmptAv(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, typename FieldField<Field, Type>::cmptType>> cmptAv
	(
		const tmp<FieldField<Field, Type>>& tf
	)
	{
		typedef typename FieldField<Field, Type>::cmptType cmptType;
		tmp<FieldField<Field, cmptType>> tRes
		(
			reuseTmpFieldField<Field, cmptType, Type>::New(tf)
		);
		cmptAv(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}


	template<template<class> class Field, class Type>
	void cmptMag
	(
		FieldField<Field, Type>& cf,
		const FieldField<Field, Type>& f
	)
	{
		forAll(cf, i)
		{
			cmptMag(cf[i], f[i]);
		}
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptMag
	(
		const FieldField<Field, Type>& f
	)
	{
		tmp<FieldField<Field, Type>> tRes
		(
			FieldField<Field, Type>::NewCalculatedType(f)
		);
		cmptMag(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptMag
	(
		const tmp<FieldField<Field, Type>>& tf
	)
	{
		tmp<FieldField<Field, Type>> tRes(New(tf));
		cmptMag(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}


//#define TMP_UNARY_FUNCTION(returnType, func)                                   \
//                                                                               \
//template<template<class> class Field, class Type>                              \
//returnType func(const tmp<FieldField<Field, Type>>& tf1)                       \
//{                                                                              \
//    returnType res = func(tf1());                                              \
//    tf1.clear();                                                               \
//    return res;                                                                \
//}

	template<template<class> class Field, class Type>
	Type max(const FieldField<Field, Type>& f)
	{
		label i = 0;
		while (i < f.size() && !f[i].size()) i++;

		if (i < f.size())
		{
			Type Max(max(f[i]));

			for (label j = i + 1; j < f.size(); j++)
			{
				if (f[j].size())
				{
					Max = max(max(f[j]), Max);
				}
			}

			return Max;
		}
		else
		{
			return pTraits<Type>::min;
		}
	}

	template <template<class> class Field, class Type>
	Type max(const tmp<FieldField<Field, Type>>& tf1)
	{
		Type res = max(tf1());
		tf1.clear();
		return res;
	}

	template<template<class> class Field, class Type>
	Type min(const FieldField<Field, Type>& f)
	{
		label i = 0;
		while (i < f.size() && !f[i].size()) i++;

		if (i < f.size())
		{
			label i = 0;
			while (!f[i].size()) i++;

			Type Min(min(f[i]));

			for (label j = i + 1; j < f.size(); j++)
			{
				if (f[j].size())
				{
					Min = min(min(f[j]), Min);
				}
			}

			return Min;
		}
		else
		{
			return pTraits<Type>::max;
		}
	}

	template <template<class> class Field, class Type>
	Type min(const tmp<FieldField<Field, Type>>& tf1)
	{
		Type res = min(tf1());
		tf1.clear();
		return res;
	}

	template<template<class> class Field, class Type>
	Type sum(const FieldField<Field, Type>& f)
	{
		if (f.size())
		{
			Type Sum = Zero;

			forAll(f, i)
			{
				Sum += sum(f[i]);
			}

			return Sum;
		}
		else
		{
			return Zero;
		}
	}

	template <template<class> class Field, class Type>
	Type sum(const tmp<FieldField<Field, Type>>& tf1)
	{
		Type res = sum(tf1());
		tf1.clear();
		return res;
	}

	template<template<class> class Field, class Type>
	scalar sumMag(const FieldField<Field, Type>& f)
	{
		if (f.size())
		{
			scalar SumMag = 0.0;

			forAll(f, i)
			{
				SumMag += sumMag(f[i]);
			}

			return SumMag;
		}
		else
		{
			return 0.0;
		}
	}

	template <template<class> class Field, class Type>
	scalar sumMag(const tmp<FieldField<Field, Type>>& tf1)
	{
		scalar res = sumMag(tf1());
		tf1.clear();
		return res;
	}

	template<template<class> class Field, class Type>
	Type average(const FieldField<Field, Type>& f)
	{
		if (f.size())
		{
			label n = 0;

			forAll(f, i)
			{
				n += f[i].size();
			}

			if (n == 0)
			{
				WarningInFunction
					<< "empty fieldField, returning zero" << endl;

				return Zero;
			}

			Type avrg = sum(f) / n;

			return avrg;
		}
		else
		{
			WarningInFunction
				<< "empty fieldField, returning zero" << endl;

			return Zero;
		}
	}

	template <template<class> class Field, class Type>
	Type average(const tmp<FieldField<Field, Type>>& tf1)
	{
		Type res = average(tf1());
		tf1.clear();
		return res;
	}


//#define G_UNARY_FUNCTION(returnType, gFunc, func, rFunc)                       \
//                                                                               \
//template<template<class> class Field, class Type>                              \
//returnType gFunc(const FieldField<Field, Type>& f)                             \
//{                                                                              \
//    returnType res = func(f);                                                  \
//    reduce(res, rFunc##Op<Type>());                                            \
//    return res;                                                                \
//}                                                                              \
//TMP_UNARY_FUNCTION(returnType, gFunc)


	template <template<class> class Field, class Type>
	Type gMax(const FieldField<Field, Type>& f)
	{
		Type res = max(f);
		reduce(res, maxOp<Type>());
		return res;
	}

	template <template<class> class Field, class Type>
	Type gMax(const tmp<FieldField<Field, Type>>& tf1)
	{
		Type res = gMax(tf1());
		tf1.clear();
		return res;
	}

	template <template<class> class Field, class Type>
	Type gMin(const FieldField<Field, Type>& f)
	{
		Type res = min(f);
		reduce(res, minOp<Type>());
		return res;
	}

	template <template<class> class Field, class Type>
	Type gMin(const tmp<FieldField<Field, Type>>& tf1)
	{
		Type res = gMin(tf1());
		tf1.clear();
		return res;
	}

	template <template<class> class Field, class Type>
	Type gSum(const FieldField<Field, Type>& f)
	{
		Type res = sum(f);
		reduce(res, sumOp<Type>());
		return res;
	}

	template <template<class> class Field, class Type>
	Type gSum(const tmp<FieldField<Field, Type>>& tf1)
	{
		Type res = gSum(tf1());
		tf1.clear();
		return res;
	}

	template <template<class> class Field, class Type>
	scalar gSumMag(const FieldField<Field, Type>& f)
	{
		scalar res = sumMag(f);
		reduce(res, sumOp<Type>());
		return res;
	}

	template <template<class> class Field, class Type>
	scalar gSumMag(const tmp<FieldField<Field, Type>>& tf1)
	{
		scalar res = gSumMag(tf1());
		tf1.clear();
		return res;
	}

#undef G_UNARY_FUNCTION


	template<template<class> class Field, class Type>
	Type gAverage(const FieldField<Field, Type>& f)
	{
		label n = 0;

		forAll(f, i)
		{
			n += f[i].size();
		}

		reduce(n, sumOp<label>());

		if (n > 0)
		{
			Type avrg = gSum(f) / n;

			return avrg;
		}
		else
		{
			WarningInFunction
				<< "empty fieldField, returning zero" << endl;

			return Zero;
		}
	}

	template <template<class> class Field, class Type>
	Type gAverage(const tmp<FieldField<Field, Type>>& tf1)
	{
		Type res = gAverage(tf1());
		tf1.clear();
		return res;
	}

#undef TMP_UNARY_FUNCTION


	template<template<class> class Field, class Type>
	void max(FieldField<Field, Type>& f, const FieldField<Field, Type>& f1, const FieldField<Field, Type>& f2)
	{
		forAll(f, i) { max(f[i], f1[i], f2[i]); }
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> max(const FieldField<Field, Type>& f1, const FieldField<Field, Type>& f2)
	{
		tmp<FieldField<Field, Type>> tRes(FieldField<Field, Type>::NewCalculatedType(f1));
		max(tRes.ref(), f1, f2);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> max(const FieldField<Field, Type>& f1, const tmp<FieldField<Field, Type>>& tf2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf2));
		max(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> max(const tmp<FieldField<Field, Type>>& tf1, const FieldField<Field, Type>& f2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf1));
		max(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> max(const tmp<FieldField<Field, Type>>& tf1, const tmp<FieldField<Field, Type>>& tf2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpTmpFieldField<Field, Type, Type, Type, Type>::New(tf1, tf2));
		max(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}

	template<template<class> class Field, class Type>
	void min(FieldField<Field, Type>& f, const FieldField<Field, Type>& f1, const FieldField<Field, Type>& f2)
	{
		forAll(f, i) { min(f[i], f1[i], f2[i]); }
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> min(const FieldField<Field, Type>& f1, const FieldField<Field, Type>& f2)
	{
		tmp<FieldField<Field, Type>> tRes(FieldField<Field, Type>::NewCalculatedType(f1));
		min(tRes.ref(), f1, f2);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> min(const FieldField<Field, Type>& f1, const tmp<FieldField<Field, Type>>& tf2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf2));
		min(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> min(const tmp<FieldField<Field, Type>>& tf1, const FieldField<Field, Type>& f2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf1));
		min(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> min(const tmp<FieldField<Field, Type>>& tf1, const tmp<FieldField<Field, Type>>& tf2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpTmpFieldField<Field, Type, Type, Type, Type>::New(tf1, tf2));
		min(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}

	template<template<class> class Field, class Type>
	void cmptMultiply(FieldField<Field, Type>& f, const FieldField<Field, Type>& f1, const FieldField<Field, Type>& f2)
	{
		forAll(f, i) { cmptMultiply(f[i], f1[i], f2[i]); }
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptMultiply(const FieldField<Field, Type>& f1, const FieldField<Field, Type>& f2)
	{
		tmp<FieldField<Field, Type>> tRes(FieldField<Field, Type>::NewCalculatedType(f1));
		cmptMultiply(tRes.ref(), f1, f2);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptMultiply(const FieldField<Field, Type>& f1, const tmp<FieldField<Field, Type>>& tf2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf2));
		cmptMultiply(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptMultiply(const tmp<FieldField<Field, Type>>& tf1, const FieldField<Field, Type>& f2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf1));
		cmptMultiply(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptMultiply(const tmp<FieldField<Field, Type>>& tf1,
		const tmp<FieldField<Field, Type>>& tf2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpTmpFieldField<Field, Type, Type, Type, Type>::New(tf1, tf2));
		cmptMultiply(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}

	template<template<class> class Field, class Type>
	void cmptDivide(FieldField<Field, Type>& f, const FieldField<Field, Type>& f1, const FieldField<Field, Type>& f2)
	{
		forAll(f, i) { cmptDivide(f[i], f1[i], f2[i]); }
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptDivide(const FieldField<Field, Type>& f1, const FieldField<Field, Type>& f2)
	{
		tmp<FieldField<Field, Type>> tRes(FieldField<Field, Type>::NewCalculatedType(f1));
		cmptDivide(tRes.ref(), f1, f2);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptDivide(const FieldField<Field, Type>& f1, const tmp<FieldField<Field, Type>>& tf2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf2));
		cmptDivide(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptDivide(const tmp<FieldField<Field, Type>>& tf1, const FieldField<Field, Type>& f2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf1));
		cmptDivide(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptDivide(const tmp<FieldField<Field, Type>>& tf1,
		const tmp<FieldField<Field, Type>>& tf2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpTmpFieldField<Field, Type, Type, Type, Type>::New(tf1, tf2));
		cmptDivide(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}

	template<template<class> class Field, class Type>
	void max(FieldField<Field, Type>& f, const Type& s, const FieldField<Field, Type>& f2)
	{
		forAll(f, i) { max(f[i], s, f2[i]); }
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> max(const Type& s, const FieldField<Field, Type>& f2)
	{
		tmp<FieldField<Field, Type>> tRes(FieldField<Field, Type>::NewCalculatedType(f2));
		max(tRes.ref(), s, f2);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> max(const Type& s, const tmp<FieldField<Field, Type>>& tf2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf2));
		max(tRes.ref(), s, tf2());
		tf2.clear();
		return tRes;
	}

	template<template<class> class Field, class Type>
	void max(FieldField<Field, Type>& f, const FieldField<Field, Type>& f1, const Type& s)
	{
		forAll(f, i) { max(f[i], f1[i], s); }
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> max(const FieldField<Field, Type>& f1, const Type& s)
	{
		tmp<FieldField<Field, Type>> tRes(FieldField<Field, Type>::NewCalculatedType(f1));
		max(tRes.ref(), f1, s);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> max(const tmp<FieldField<Field, Type>>& tf1, const Type& s)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf1));
		max(tRes.ref(), tf1(), s);
		tf1.clear();
		return tRes;
	}

	template<template<class> class Field, class Type>
	void min(FieldField<Field, Type>& f, const Type& s, const FieldField<Field, Type>& f2)
	{
		forAll(f, i) { min(f[i], s, f2[i]); }
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> min(const Type& s, const FieldField<Field, Type>& f2)
	{
		tmp<FieldField<Field, Type>> tRes(FieldField<Field, Type>::NewCalculatedType(f2));
		min(tRes.ref(), s, f2);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> min(const Type& s, const tmp<FieldField<Field, Type>>& tf2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf2));
		min(tRes.ref(), s, tf2());
		tf2.clear();
		return tRes;
	}

	template<template<class> class Field, class Type>
	void min(FieldField<Field, Type>& f, const FieldField<Field, Type>& f1, const Type& s)
	{
		forAll(f, i) { min(f[i], f1[i], s); }
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> min(const FieldField<Field, Type>& f1, const Type& s)
	{
		tmp<FieldField<Field, Type>> tRes(FieldField<Field, Type>::NewCalculatedType(f1));
		min(tRes.ref(), f1, s);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> min(const tmp<FieldField<Field, Type>>& tf1, const Type& s)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf1));
		min(tRes.ref(), tf1(), s);
		tf1.clear();
		return tRes;
	}

	template<template<class> class Field, class Type>
	void cmptMultiply(FieldField<Field, Type>& f, const Type& s, const FieldField<Field, Type>& f2)
	{
		forAll(f, i) { cmptMultiply(f[i], s, f2[i]); }
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptMultiply(const Type& s, const FieldField<Field, Type>& f2)
	{
		tmp<FieldField<Field, Type>> tRes(FieldField<Field, Type>::NewCalculatedType(f2));
		cmptMultiply(tRes.ref(), s, f2);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptMultiply(const Type& s, const tmp<FieldField<Field, Type>>& tf2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf2));
		cmptMultiply(tRes.ref(), s, tf2());
		tf2.clear();
		return tRes;
	}

	template<template<class> class Field, class Type>
	void cmptMultiply(FieldField<Field, Type>& f, const FieldField<Field, Type>& f1, const Type& s)
	{
		forAll(f, i) { cmptMultiply(f[i], f1[i], s); }
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptMultiply(const FieldField<Field, Type>& f1, const Type& s)
	{
		tmp<FieldField<Field, Type>> tRes(FieldField<Field, Type>::NewCalculatedType(f1));
		cmptMultiply(tRes.ref(), f1, s);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptMultiply(const tmp<FieldField<Field, Type>>& tf1, const Type& s)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf1));
		cmptMultiply(tRes.ref(), tf1(), s);
		tf1.clear();
		return tRes;
	}

	template<template<class> class Field, class Type>
	void cmptDivide(FieldField<Field, Type>& f, const Type& s, const FieldField<Field, Type>& f2)
	{
		forAll(f, i) { cmptDivide(f[i], s, f2[i]); }
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptDivide(const Type& s, const FieldField<Field, Type>& f2)
	{
		tmp<FieldField<Field, Type>> tRes(FieldField<Field, Type>::NewCalculatedType(f2));
		cmptDivide(tRes.ref(), s, f2);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptDivide(const Type& s, const tmp<FieldField<Field, Type>>& tf2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf2));
		cmptDivide(tRes.ref(), s, tf2());
		tf2.clear();
		return tRes;
	}

	template<template<class> class Field, class Type>
	void cmptDivide(FieldField<Field, Type>& f, const FieldField<Field, Type>& f1, const Type& s)
	{
		forAll(f, i) { cmptDivide(f[i], f1[i], s); }
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptDivide(const FieldField<Field, Type>& f1, const Type& s)
	{
		tmp<FieldField<Field, Type>> tRes(FieldField<Field, Type>::NewCalculatedType(f1));
		cmptDivide(tRes.ref(), f1, s);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptDivide(const tmp<FieldField<Field, Type>>& tf1, const Type& s)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf1));
		cmptDivide(tRes.ref(), tf1(), s);
		tf1.clear();
		return tRes;
	}


	/* * * * * * * * * * * * * * * * Global operators  * * * * * * * * * * * * * */

	template<template<class> class Field, class Type>
	void negate(FieldField<Field, Type>& res, const FieldField<Field, Type>& f)
	{
		forAll(res, i) { negate(res[i], f[i]); }
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> operator -(const FieldField<Field, Type>& f)
	{
		tmp<FieldField<Field, Type>> tRes(FieldField<Field, Type>::NewCalculatedType(f));
		negate(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> operator -(const tmp<FieldField<Field, Type>>& tf)
	{
		tmp<FieldField<Field, Type>> tRes(New(tf));
		negate(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field, class Type>
	void multiply(FieldField<Field, Type>& f, const FieldField<Field, Type>& f1, const FieldField<Field, scalar>& f2)
	{
		forAll(f, i) { multiply(f[i], f1[i], f2[i]); }
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> operator *(const FieldField<Field, Type>& f1, const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, Type>> tRes(FieldField<Field, Type>::NewCalculatedType(f1));
		multiply(tRes.ref(), f1, f2);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> operator *(const FieldField<Field, Type>& f1, const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, scalar>::New(tf2));
		multiply(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> operator *(const tmp<FieldField<Field, Type>>& tf1, const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf1));
		multiply(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> operator *(const tmp<FieldField<Field, Type>>& tf1,
		const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpTmpFieldField<Field, Type, Type, Type, scalar>::New(tf1, tf2));
		multiply(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}

	template<template<class> class Field, class Type>
	void multiply(FieldField<Field, Type>& f, const FieldField<Field, scalar>& f1, const FieldField<Field, Type>& f2)
	{
		forAll(f, i) { multiply(f[i], f1[i], f2[i]); }
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> operator *(const FieldField<Field, scalar>& f1, const FieldField<Field, Type>& f2)
	{
		tmp<FieldField<Field, Type>> tRes(FieldField<Field, Type>::NewCalculatedType(f1));
		multiply(tRes.ref(), f1, f2);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> operator *(const FieldField<Field, scalar>& f1, const tmp<FieldField<Field, Type>>& tf2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf2));
		multiply(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> operator *(const tmp<FieldField<Field, scalar>>& tf1, const FieldField<Field, Type>& f2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, scalar>::New(tf1));
		multiply(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> operator *(const tmp<FieldField<Field, scalar>>& tf1,
		const tmp<FieldField<Field, Type>>& tf2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpTmpFieldField<Field, Type, scalar, scalar, Type>::New(tf1, tf2));
		multiply(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}

	template<template<class> class Field, class Type>
	void divide(FieldField<Field, Type>& f, const FieldField<Field, Type>& f1, const FieldField<Field, scalar>& f2)
	{
		forAll(f, i) { divide(f[i], f1[i], f2[i]); }
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> operator /(const FieldField<Field, Type>& f1, const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, Type>> tRes(FieldField<Field, Type>::NewCalculatedType(f1));
		divide(tRes.ref(), f1, f2);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> operator /(const FieldField<Field, Type>& f1, const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, scalar>::New(tf2));
		divide(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> operator /(const tmp<FieldField<Field, Type>>& tf1, const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf1));
		divide(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> operator /(const tmp<FieldField<Field, Type>>& tf1,
		const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpTmpFieldField<Field, Type, Type, Type, scalar>::New(tf1, tf2));
		divide(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}

	template<template<class> class Field, class Type>
	void multiply(FieldField<Field, Type>& f, const scalar& s, const FieldField<Field, Type>& f2)
	{
		forAll(f, i) { multiply(f[i], s, f2[i]); }
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> operator *(const scalar& s, const FieldField<Field, Type>& f2)
	{
		tmp<FieldField<Field, Type>> tRes(FieldField<Field, Type>::NewCalculatedType(f2));
		multiply(tRes.ref(), s, f2);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> operator *(const scalar& s, const tmp<FieldField<Field, Type>>& tf2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf2));
		multiply(tRes.ref(), s, tf2());
		tf2.clear();
		return tRes;
	}

	template<template<class> class Field, class Type>
	void multiply(FieldField<Field, Type>& f, const FieldField<Field, Type>& f1, const scalar& s)
	{
		forAll(f, i) { multiply(f[i], f1[i], s); }
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> operator *(const FieldField<Field, Type>& f1, const scalar& s)
	{
		tmp<FieldField<Field, Type>> tRes(FieldField<Field, Type>::NewCalculatedType(f1));
		multiply(tRes.ref(), f1, s);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> operator *(const tmp<FieldField<Field, Type>>& tf1, const scalar& s)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf1));
		multiply(tRes.ref(), tf1(), s);
		tf1.clear();
		return tRes;
	}

	template<template<class> class Field, class Type>
	void divide(FieldField<Field, Type>& f, const FieldField<Field, Type>& f1, const scalar& s)
	{
		forAll(f, i) { divide(f[i], f1[i], s); }
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> operator /(const FieldField<Field, Type>& f1, const scalar& s)
	{
		tmp<FieldField<Field, Type>> tRes(FieldField<Field, Type>::NewCalculatedType(f1));
		divide(tRes.ref(), f1, s);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> operator /(const tmp<FieldField<Field, Type>>& tf1, const scalar& s)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf1));
		divide(tRes.ref(), tf1(), s);
		tf1.clear();
		return tRes;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#define PRODUCT_OPERATOR(product, op, opFunc)                                  \
//                                                                               \
//template                                                                       \
//<                                                                              \
//    template<class> class Field1,                                              \
//    template<class> class Field2,                                              \
//    class Type1,                                                               \
//    class Type2                                                                \
//>                                                                              \
//void opFunc                                                                    \
//(                                                                              \
//    FieldField<Field1, typename product<Type1, Type2>::type>& f,               \
//    const FieldField<Field1, Type1>& f1,                                       \
//    const FieldField<Field2, Type2>& f2                                        \
//)                                                                              \
//{                                                                              \
//    forAll(f, i)                                                               \
//    {                                                                          \
//        opFunc(f[i], f1[i], f2[i]);                                            \
//    }                                                                          \
//}                                                                              \
//                                                                               \
//template                                                                       \
//<                                                                              \
//    template<class> class Field1,                                              \
//    template<class> class Field2,                                              \
//    class Type1,                                                               \
//    class Type2                                                                \
//>                                                                              \
//tmp<FieldField<Field1, typename product<Type1, Type2>::type>>                  \
//operator op                                                                    \
//(                                                                              \
//    const FieldField<Field1, Type1>& f1,                                       \
//    const FieldField<Field2, Type2>& f2                                        \
//)                                                                              \
//{                                                                              \
//    typedef typename product<Type1, Type2>::type productType;                  \
//    tmp<FieldField<Field1, productType>> tRes                                  \
//    (                                                                          \
//        FieldField<Field1, productType>::NewCalculatedType(f1)                 \
//    );                                                                         \
//    opFunc(tRes.ref(), f1, f2);                                                \
//    return tRes;                                                               \
//}                                                                              \
//                                                                               \
//template<template<class> class Field, class Type1, class Type2>                \
//tmp<FieldField<Field, typename product<Type1, Type2>::type>>                   \
//operator op                                                                    \
//(                                                                              \
//    const FieldField<Field, Type1>& f1,                                        \
//    const tmp<FieldField<Field, Type2>>& tf2                                   \
//)                                                                              \
//{                                                                              \
//    typedef typename product<Type1, Type2>::type productType;                  \
//    tmp<FieldField<Field, productType>> tRes                                   \
//    (                                                                          \
//        reuseTmpFieldField<Field, productType, Type2>::New(tf2)                \
//    );                                                                         \
//    opFunc(tRes.ref(), f1, tf2());                                             \
//    tf2.clear();                                                               \
//    return tRes;                                                               \
//}                                                                              \
//                                                                               \
//template                                                                       \
//<                                                                              \
//    template<class> class Field1,                                              \
//    template<class> class Field2,                                              \
//    class Type1,                                                               \
//    class Type2                                                                \
//>                                                                              \
//tmp<FieldField<Field, typename product<Type1, Type2>::type>>                   \
//operator op                                                                    \
//(                                                                              \
//    const FieldField<Field1, Type1>& f1,                                       \
//    const tmp<FieldField<Field2, Type2>>& tf2                                  \
//)                                                                              \
//{                                                                              \
//    typedef typename product<Type1, Type2>::type productType;                  \
//    tmp<FieldField<Field1, productType>> tRes                                  \
//    (                                                                          \
//        FieldField<Field1, productType>::NewCalculatedType(f1)                 \
//    );                                                                         \
//    opFunc(tRes.ref(), f1, tf2());                                             \
//    tf2.clear();                                                               \
//    return tRes;                                                               \
//}                                                                              \
//                                                                               \
//template                                                                       \
//<                                                                              \
//    template<class> class Field1,                                              \
//    template<class> class Field2,                                              \
//    class Type1,                                                               \
//    class Type2                                                                \
//>                                                                              \
//tmp<FieldField<Field1, typename product<Type1, Type2>::type>>                  \
//operator op                                                                    \
//(                                                                              \
//    const tmp<FieldField<Field1, Type1>>& tf1,                                 \
//    const FieldField<Field2, Type2>& f2                                        \
//)                                                                              \
//{                                                                              \
//    typedef typename product<Type1, Type2>::type productType;                  \
//    tmp<FieldField<Field1, productType>> tRes                                  \
//    (                                                                          \
//        reuseTmpFieldField<Field1, productType, Type1>::New(tf1)               \
//    );                                                                         \
//    opFunc(tRes.ref(), tf1(), f2);                                             \
//    tf1.clear();                                                               \
//    return tRes;                                                               \
//}                                                                              \
//                                                                               \
//template                                                                       \
//<                                                                              \
//    template<class> class Field1,                                              \
//    template<class> class Field2,                                              \
//    class Type1,                                                               \
//    class Type2                                                                \
//>                                                                              \
//tmp<FieldField<Field1, typename product<Type1, Type2>::type>>                  \
//operator op                                                                    \
//(                                                                              \
//    const tmp<FieldField<Field1, Type1>>& tf1,                                 \
//    const tmp<FieldField<Field2, Type2>>& tf2                                  \
//)                                                                              \
//{                                                                              \
//    typedef typename product<Type1, Type2>::type productType;                  \
//    tmp<FieldField<Field1, productType>> tRes                                  \
//    (                                                                          \
//        reuseTmpTmpFieldField<Field1, productType, Type1, Type1, Type2>::New   \
//        (tf1, tf2)                                                             \
//    );                                                                         \
//    opFunc(tRes.ref(), tf1(), tf2());                                          \
//    tf1.clear();                                                               \
//    tf2.clear();                                                               \
//    return tRes;                                                               \
//}                                                                              \
//                                                                               \
//template                                                                       \
//<                                                                              \
//    template<class> class Field,                                               \
//    class Type,                                                                \
//    class Form,                                                                \
//    class Cmpt,                                                                \
//    direction nCmpt                                                            \
//>                                                                              \
//void opFunc                                                                    \
//(                                                                              \
//    FieldField<Field, typename product<Type, Form>::type>& f,                  \
//    const FieldField<Field, Type>& f1,                                         \
//    const VectorSpace<Form,Cmpt,nCmpt>& vs                                     \
//)                                                                              \
//{                                                                              \
//    forAll(f, i)                                                               \
//    {                                                                          \
//        opFunc(f[i], f1[i], vs);                                               \
//    }                                                                          \
//}                                                                              \
//                                                                               \
//template                                                                       \
//<                                                                              \
//    template<class> class Field,                                               \
//    class Type,                                                                \
//    class Form,                                                                \
//    class Cmpt,                                                                \
//    direction nCmpt                                                            \
//>                                                                              \
//tmp<FieldField<Field, typename product<Type, Form>::type>>                     \
//operator op                                                                    \
//(                                                                              \
//    const FieldField<Field, Type>& f1,                                         \
//    const VectorSpace<Form,Cmpt,nCmpt>& vs                                     \
//)                                                                              \
//{                                                                              \
//    typedef typename product<Type, Form>::type productType;                    \
//    tmp<FieldField<Field, productType>> tRes                                   \
//    (                                                                          \
//        FieldField<Field, productType>::NewCalculatedType(f1)                  \
//    );                                                                         \
//    opFunc(tRes.ref(), f1, static_cast<const Form&>(vs));                      \
//    return tRes;                                                               \
//}                                                                              \
//                                                                               \
//template                                                                       \
//<                                                                              \
//    template<class> class Field,                                               \
//    class Type,                                                                \
//    class Form,                                                                \
//    class Cmpt,                                                                \
//    direction nCmpt                                                            \
//>                                                                              \
//tmp<FieldField<Field, typename product<Type, Form>::type>>                     \
//operator op                                                                    \
//(                                                                              \
//    const tmp<FieldField<Field, Type>>& tf1,                                   \
//    const VectorSpace<Form,Cmpt,nCmpt>& vs                                     \
//)                                                                              \
//{                                                                              \
//    typedef typename product<Type, Form>::type productType;                    \
//    tmp<FieldField<Field, productType>> tRes                                   \
//    (                                                                          \
//        reuseTmpFieldField<Field, productType, Type>::New(tf1)                 \
//    );                                                                         \
//    opFunc(tRes.ref(), tf1(), static_cast<const Form&>(vs));                   \
//    tf1.clear();                                                               \
//    return tRes;                                                               \
//}                                                                              \
//                                                                               \
//template                                                                       \
//<                                                                              \
//    template<class> class Field,                                               \
//    class Type,                                                                \
//    class Form,                                                                \
//    class Cmpt,                                                                \
//    direction nCmpt                                                            \
//>                                                                              \
//void opFunc                                                                    \
//(                                                                              \
//    FieldField<Field, typename product<Form, Type>::type>& f,                  \
//    const VectorSpace<Form,Cmpt,nCmpt>& vs,                                    \
//    const FieldField<Field, Type>& f1                                          \
//)                                                                              \
//{                                                                              \
//    forAll(f, i)                                                               \
//    {                                                                          \
//        opFunc(f[i], vs, f1[i]);                                               \
//    }                                                                          \
//}                                                                              \
//                                                                               \
//template                                                                       \
//<                                                                              \
//    template<class> class Field,                                               \
//    class Type,                                                                \
//    class Form,                                                                \
//    class Cmpt,                                                                \
//    direction nCmpt                                                            \
//>                                                                              \
//tmp<FieldField<Field, typename product<Form, Type>::type>>                     \
//operator op                                                                    \
//(                                                                              \
//    const VectorSpace<Form,Cmpt,nCmpt>& vs,                                    \
//    const FieldField<Field, Type>& f1                                          \
//)                                                                              \
//{                                                                              \
//    typedef typename product<Form, Type>::type productType;                    \
//    tmp<FieldField<Field, productType>> tRes                                   \
//    (                                                                          \
//        FieldField<Field, productType>::NewCalculatedType(f1)                  \
//    );                                                                         \
//    opFunc(tRes.ref(), static_cast<const Form&>(vs), f1);                      \
//    return tRes;                                                               \
//}                                                                              \
//                                                                               \
//template                                                                       \
//<                                                                              \
//    template<class> class Field,                                               \
//    class Type,                                                                \
//    class Form,                                                                \
//    class Cmpt,                                                                \
//    direction nCmpt                                                            \
//>                                                                              \
//tmp<FieldField<Field, typename product<Form, Type>::type>>                     \
//operator op                                                                    \
//(                                                                              \
//    const VectorSpace<Form,Cmpt,nCmpt>& vs,                                    \
//    const tmp<FieldField<Field, Type>>& tf1                                    \
//)                                                                              \
//{                                                                              \
//    typedef typename product<Form, Type>::type productType;                    \
//    tmp<FieldField<Field, productType>> tRes                                   \
//    (                                                                          \
//        reuseTmpFieldField<Field, productType, Type>::New(tf1)                 \
//    );                                                                         \
//    opFunc(tRes.ref(), static_cast<const Form&>(vs), tf1());                   \
//    tf1.clear();                                                               \
//    return tRes;                                                               \
//}


	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	void add(FieldField<Field1, typename typeOfSum<Type1, Type2>::type>& f, const FieldField<Field1, Type1>& f1,
		const FieldField<Field2, Type2>& f2)
	{
		forAll(f, i) { add(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field1, typename typeOfSum<Type1, Type2>::type>> operator +(
		const FieldField<Field1, Type1>& f1, const FieldField<Field2, Type2>& f2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		tmp<FieldField<Field1, productType>> tRes(FieldField<Field1, productType>::NewCalculatedType(f1));
		add(tRes.ref(), f1, f2);
		return tRes;
	}

	template <template<class> class Field, class Type1, class Type2>
	tmp<FieldField<Field, typename typeOfSum<Type1, Type2>::type>> operator +(
		const FieldField<Field, Type1>& f1, const tmp<FieldField<Field, Type2>>& tf2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		tmp<FieldField<Field, productType>> tRes(reuseTmpFieldField<Field, productType, Type2>::New(tf2));
		add(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field, typename typeOfSum<Type1, Type2>::type>> operator +(
		const FieldField<Field1, Type1>& f1, const tmp<FieldField<Field2, Type2>>& tf2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		tmp<FieldField<Field1, productType>> tRes(FieldField<Field1, productType>::NewCalculatedType(f1));
		add(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field1, typename typeOfSum<Type1, Type2>::type>> operator +(
		const tmp<FieldField<Field1, Type1>>& tf1, const FieldField<Field2, Type2>& f2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		tmp<FieldField<Field1, productType>> tRes(reuseTmpFieldField<Field1, productType, Type1>::New(tf1));
		add(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field1, typename typeOfSum<Type1, Type2>::type>> operator +(
		const tmp<FieldField<Field1, Type1>>& tf1, const tmp<FieldField<Field2, Type2>>& tf2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		tmp<FieldField<Field1, productType>> tRes(
			reuseTmpTmpFieldField<Field1, productType, Type1, Type1, Type2>::New(tf1, tf2));
		add(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	void add(FieldField<Field, typename typeOfSum<Type, Form>::type>& f, const FieldField<Field, Type>& f1,
		const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		forAll(f, i) { add(f[i], f1[i], vs); }
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename typeOfSum<Type, Form>::type>> operator +(
		const FieldField<Field, Type>& f1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		typedef typename typeOfSum<Type, Form>::type productType;
		tmp<FieldField<Field, productType>> tRes(FieldField<Field, productType>::NewCalculatedType(f1));
		add(tRes.ref(), f1, static_cast<const Form&>(vs));
		return tRes;
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename typeOfSum<Type, Form>::type>> operator +(
		const tmp<FieldField<Field, Type>>& tf1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		typedef typename typeOfSum<Type, Form>::type productType;
		tmp<FieldField<Field, productType>> tRes(reuseTmpFieldField<Field, productType, Type>::New(tf1));
		add(tRes.ref(), tf1(), static_cast<const Form&>(vs));
		tf1.clear();
		return tRes;
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	void add(FieldField<Field, typename typeOfSum<Form, Type>::type>& f, const VectorSpace<Form, Cmpt, nCmpt>& vs,
		const FieldField<Field, Type>& f1)
	{
		forAll(f, i) { add(f[i], vs, f1[i]); }
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename typeOfSum<Form, Type>::type>> operator +(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const FieldField<Field, Type>& f1)
	{
		typedef typename typeOfSum<Form, Type>::type productType;
		tmp<FieldField<Field, productType>> tRes(FieldField<Field, productType>::NewCalculatedType(f1));
		add(tRes.ref(), static_cast<const Form&>(vs), f1);
		return tRes;
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename typeOfSum<Form, Type>::type>> operator +(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<FieldField<Field, Type>>& tf1)
	{
		typedef typename typeOfSum<Form, Type>::type productType;
		tmp<FieldField<Field, productType>> tRes(reuseTmpFieldField<Field, productType, Type>::New(tf1));
		add(tRes.ref(), static_cast<const Form&>(vs), tf1());
		tf1.clear();
		return tRes;
	}

	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	void subtract(FieldField<Field1, typename typeOfSum<Type1, Type2>::type>& f, const FieldField<Field1, Type1>& f1,
		const FieldField<Field2, Type2>& f2)
	{
		forAll(f, i) { subtract(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field1, typename typeOfSum<Type1, Type2>::type>> operator -(
		const FieldField<Field1, Type1>& f1, const FieldField<Field2, Type2>& f2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		tmp<FieldField<Field1, productType>> tRes(FieldField<Field1, productType>::NewCalculatedType(f1));
		subtract(tRes.ref(), f1, f2);
		return tRes;
	}

	template <template<class> class Field, class Type1, class Type2>
	tmp<FieldField<Field, typename typeOfSum<Type1, Type2>::type>> operator -(
		const FieldField<Field, Type1>& f1, const tmp<FieldField<Field, Type2>>& tf2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		tmp<FieldField<Field, productType>> tRes(reuseTmpFieldField<Field, productType, Type2>::New(tf2));
		subtract(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field, typename typeOfSum<Type1, Type2>::type>> operator -(
		const FieldField<Field1, Type1>& f1, const tmp<FieldField<Field2, Type2>>& tf2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		tmp<FieldField<Field1, productType>> tRes(FieldField<Field1, productType>::NewCalculatedType(f1));
		subtract(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field1, typename typeOfSum<Type1, Type2>::type>> operator -(
		const tmp<FieldField<Field1, Type1>>& tf1, const FieldField<Field2, Type2>& f2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		tmp<FieldField<Field1, productType>> tRes(reuseTmpFieldField<Field1, productType, Type1>::New(tf1));
		subtract(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field1, typename typeOfSum<Type1, Type2>::type>> operator -(
		const tmp<FieldField<Field1, Type1>>& tf1, const tmp<FieldField<Field2, Type2>>& tf2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		tmp<FieldField<Field1, productType>> tRes(
			reuseTmpTmpFieldField<Field1, productType, Type1, Type1, Type2>::New(tf1, tf2));
		subtract(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	void subtract(FieldField<Field, typename typeOfSum<Type, Form>::type>& f, const FieldField<Field, Type>& f1,
		const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		forAll(f, i) { subtract(f[i], f1[i], vs); }
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename typeOfSum<Type, Form>::type>> operator -(
		const FieldField<Field, Type>& f1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		typedef typename typeOfSum<Type, Form>::type productType;
		tmp<FieldField<Field, productType>> tRes(FieldField<Field, productType>::NewCalculatedType(f1));
		subtract(tRes.ref(), f1, static_cast<const Form&>(vs));
		return tRes;
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename typeOfSum<Type, Form>::type>> operator -(
		const tmp<FieldField<Field, Type>>& tf1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		typedef typename typeOfSum<Type, Form>::type productType;
		tmp<FieldField<Field, productType>> tRes(reuseTmpFieldField<Field, productType, Type>::New(tf1));
		subtract(tRes.ref(), tf1(), static_cast<const Form&>(vs));
		tf1.clear();
		return tRes;
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	void subtract(FieldField<Field, typename typeOfSum<Form, Type>::type>& f, const VectorSpace<Form, Cmpt, nCmpt>& vs,
		const FieldField<Field, Type>& f1)
	{
		forAll(f, i) { subtract(f[i], vs, f1[i]); }
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename typeOfSum<Form, Type>::type>> operator -(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const FieldField<Field, Type>& f1)
	{
		typedef typename typeOfSum<Form, Type>::type productType;
		tmp<FieldField<Field, productType>> tRes(FieldField<Field, productType>::NewCalculatedType(f1));
		subtract(tRes.ref(), static_cast<const Form&>(vs), f1);
		return tRes;
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename typeOfSum<Form, Type>::type>> operator -(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<FieldField<Field, Type>>& tf1)
	{
		typedef typename typeOfSum<Form, Type>::type productType;
		tmp<FieldField<Field, productType>> tRes(reuseTmpFieldField<Field, productType, Type>::New(tf1));
		subtract(tRes.ref(), static_cast<const Form&>(vs), tf1());
		tf1.clear();
		return tRes;
	}


	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	void outer(FieldField<Field1, typename outerProduct<Type1, Type2>::type>& f, const FieldField<Field1, Type1>& f1,
		const FieldField<Field2, Type2>& f2)
	{
		forAll(f, i) { outer(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field1, typename outerProduct<Type1, Type2>::type>> operator *(
		const FieldField<Field1, Type1>& f1, const FieldField<Field2, Type2>& f2)
	{
		typedef typename outerProduct<Type1, Type2>::type productType;
		tmp<FieldField<Field1, productType>> tRes(FieldField<Field1, productType>::NewCalculatedType(f1));
		outer(tRes.ref(), f1, f2);
		return tRes;
	}

	template <template<class> class Field, class Type1, class Type2>
	tmp<FieldField<Field, typename outerProduct<Type1, Type2>::type>> operator *(
		const FieldField<Field, Type1>& f1, const tmp<FieldField<Field, Type2>>& tf2)
	{
		typedef typename outerProduct<Type1, Type2>::type productType;
		tmp<FieldField<Field, productType>> tRes(reuseTmpFieldField<Field, productType, Type2>::New(tf2));
		outer(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field, typename outerProduct<Type1, Type2>::type>> operator *(
		const FieldField<Field1, Type1>& f1, const tmp<FieldField<Field2, Type2>>& tf2)
	{
		typedef typename outerProduct<Type1, Type2>::type productType;
		tmp<FieldField<Field1, productType>> tRes(FieldField<Field1, productType>::NewCalculatedType(f1));
		outer(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field1, typename outerProduct<Type1, Type2>::type>> operator *(
		const tmp<FieldField<Field1, Type1>>& tf1, const FieldField<Field2, Type2>& f2)
	{
		typedef typename outerProduct<Type1, Type2>::type productType;
		tmp<FieldField<Field1, productType>> tRes(reuseTmpFieldField<Field1, productType, Type1>::New(tf1));
		outer(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field1, typename outerProduct<Type1, Type2>::type>> operator *(
		const tmp<FieldField<Field1, Type1>>& tf1, const tmp<FieldField<Field2, Type2>>& tf2)
	{
		typedef typename outerProduct<Type1, Type2>::type productType;
		tmp<FieldField<Field1, productType>> tRes(
			reuseTmpTmpFieldField<Field1, productType, Type1, Type1, Type2>::New(tf1, tf2));
		outer(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	void outer(FieldField<Field, typename outerProduct<Type, Form>::type>& f, const FieldField<Field, Type>& f1,
		const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		forAll(f, i) { outer(f[i], f1[i], vs); }
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename outerProduct<Type, Form>::type>> operator *(
		const FieldField<Field, Type>& f1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		typedef typename outerProduct<Type, Form>::type productType;
		tmp<FieldField<Field, productType>> tRes(FieldField<Field, productType>::NewCalculatedType(f1));
		outer(tRes.ref(), f1, static_cast<const Form&>(vs));
		return tRes;
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename outerProduct<Type, Form>::type>> operator *(
		const tmp<FieldField<Field, Type>>& tf1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		typedef typename outerProduct<Type, Form>::type productType;
		tmp<FieldField<Field, productType>> tRes(reuseTmpFieldField<Field, productType, Type>::New(tf1));
		outer(tRes.ref(), tf1(), static_cast<const Form&>(vs));
		tf1.clear();
		return tRes;
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	void outer(FieldField<Field, typename outerProduct<Form, Type>::type>& f, const VectorSpace<Form, Cmpt, nCmpt>& vs,
		const FieldField<Field, Type>& f1)
	{
		forAll(f, i) { outer(f[i], vs, f1[i]); }
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename outerProduct<Form, Type>::type>> operator *(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const FieldField<Field, Type>& f1)
	{
		typedef typename outerProduct<Form, Type>::type productType;
		tmp<FieldField<Field, productType>> tRes(FieldField<Field, productType>::NewCalculatedType(f1));
		outer(tRes.ref(), static_cast<const Form&>(vs), f1);
		return tRes;
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename outerProduct<Form, Type>::type>> operator *(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<FieldField<Field, Type>>& tf1)
	{
		typedef typename outerProduct<Form, Type>::type productType;
		tmp<FieldField<Field, productType>> tRes(reuseTmpFieldField<Field, productType, Type>::New(tf1));
		outer(tRes.ref(), static_cast<const Form&>(vs), tf1());
		tf1.clear();
		return tRes;
	}

	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	void cross(FieldField<Field1, typename crossProduct<Type1, Type2>::type>& f, const FieldField<Field1, Type1>& f1,
		const FieldField<Field2, Type2>& f2)
	{
		forAll(f, i) { cross(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field1, typename crossProduct<Type1, Type2>::type>> operator ^(
		const FieldField<Field1, Type1>& f1, const FieldField<Field2, Type2>& f2)
	{
		typedef typename crossProduct<Type1, Type2>::type productType;
		tmp<FieldField<Field1, productType>> tRes(FieldField<Field1, productType>::NewCalculatedType(f1));
		cross(tRes.ref(), f1, f2);
		return tRes;
	}

	template <template<class> class Field, class Type1, class Type2>
	tmp<FieldField<Field, typename crossProduct<Type1, Type2>::type>> operator ^(
		const FieldField<Field, Type1>& f1, const tmp<FieldField<Field, Type2>>& tf2)
	{
		typedef typename crossProduct<Type1, Type2>::type productType;
		tmp<FieldField<Field, productType>> tRes(reuseTmpFieldField<Field, productType, Type2>::New(tf2));
		cross(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field, typename crossProduct<Type1, Type2>::type>> operator ^(
		const FieldField<Field1, Type1>& f1, const tmp<FieldField<Field2, Type2>>& tf2)
	{
		typedef typename crossProduct<Type1, Type2>::type productType;
		tmp<FieldField<Field1, productType>> tRes(FieldField<Field1, productType>::NewCalculatedType(f1));
		cross(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field1, typename crossProduct<Type1, Type2>::type>> operator ^(
		const tmp<FieldField<Field1, Type1>>& tf1, const FieldField<Field2, Type2>& f2)
	{
		typedef typename crossProduct<Type1, Type2>::type productType;
		tmp<FieldField<Field1, productType>> tRes(reuseTmpFieldField<Field1, productType, Type1>::New(tf1));
		cross(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field1, typename crossProduct<Type1, Type2>::type>> operator ^(
		const tmp<FieldField<Field1, Type1>>& tf1, const tmp<FieldField<Field2, Type2>>& tf2)
	{
		typedef typename crossProduct<Type1, Type2>::type productType;
		tmp<FieldField<Field1, productType>> tRes(
			reuseTmpTmpFieldField<Field1, productType, Type1, Type1, Type2>::New(tf1, tf2));
		cross(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	void cross(FieldField<Field, typename crossProduct<Type, Form>::type>& f, const FieldField<Field, Type>& f1,
		const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		forAll(f, i) { cross(f[i], f1[i], vs); }
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename crossProduct<Type, Form>::type>> operator ^(
		const FieldField<Field, Type>& f1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		typedef typename crossProduct<Type, Form>::type productType;
		tmp<FieldField<Field, productType>> tRes(FieldField<Field, productType>::NewCalculatedType(f1));
		cross(tRes.ref(), f1, static_cast<const Form&>(vs));
		return tRes;
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename crossProduct<Type, Form>::type>> operator ^(
		const tmp<FieldField<Field, Type>>& tf1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		typedef typename crossProduct<Type, Form>::type productType;
		tmp<FieldField<Field, productType>> tRes(reuseTmpFieldField<Field, productType, Type>::New(tf1));
		cross(tRes.ref(), tf1(), static_cast<const Form&>(vs));
		tf1.clear();
		return tRes;
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	void cross(FieldField<Field, typename crossProduct<Form, Type>::type>& f, const VectorSpace<Form, Cmpt, nCmpt>& vs,
		const FieldField<Field, Type>& f1)
	{
		forAll(f, i) { cross(f[i], vs, f1[i]); }
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename crossProduct<Form, Type>::type>> operator ^(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const FieldField<Field, Type>& f1)
	{
		typedef typename crossProduct<Form, Type>::type productType;
		tmp<FieldField<Field, productType>> tRes(FieldField<Field, productType>::NewCalculatedType(f1));
		cross(tRes.ref(), static_cast<const Form&>(vs), f1);
		return tRes;
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename crossProduct<Form, Type>::type>> operator ^(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<FieldField<Field, Type>>& tf1)
	{
		typedef typename crossProduct<Form, Type>::type productType;
		tmp<FieldField<Field, productType>> tRes(reuseTmpFieldField<Field, productType, Type>::New(tf1));
		cross(tRes.ref(), static_cast<const Form&>(vs), tf1());
		tf1.clear();
		return tRes;
	}

	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	void dot(FieldField<Field1, typename innerProduct<Type1, Type2>::type>& f, const FieldField<Field1, Type1>& f1,
		const FieldField<Field2, Type2>& f2)
	{
		forAll(f, i) { dot(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field1, typename innerProduct<Type1, Type2>::type>> operator &(
		const FieldField<Field1, Type1>& f1, const FieldField<Field2, Type2>& f2)
	{
		typedef typename innerProduct<Type1, Type2>::type productType;
		tmp<FieldField<Field1, productType>> tRes(FieldField<Field1, productType>::NewCalculatedType(f1));
		dot(tRes.ref(), f1, f2);
		return tRes;
	}

	template <template<class> class Field, class Type1, class Type2>
	tmp<FieldField<Field, typename innerProduct<Type1, Type2>::type>> operator &(
		const FieldField<Field, Type1>& f1, const tmp<FieldField<Field, Type2>>& tf2)
	{
		typedef typename innerProduct<Type1, Type2>::type productType;
		tmp<FieldField<Field, productType>> tRes(reuseTmpFieldField<Field, productType, Type2>::New(tf2));
		dot(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field, typename innerProduct<Type1, Type2>::type>> operator &(
		const FieldField<Field1, Type1>& f1, const tmp<FieldField<Field2, Type2>>& tf2)
	{
		typedef typename innerProduct<Type1, Type2>::type productType;
		tmp<FieldField<Field1, productType>> tRes(FieldField<Field1, productType>::NewCalculatedType(f1));
		dot(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field1, typename innerProduct<Type1, Type2>::type>> operator &(
		const tmp<FieldField<Field1, Type1>>& tf1, const FieldField<Field2, Type2>& f2)
	{
		typedef typename innerProduct<Type1, Type2>::type productType;
		tmp<FieldField<Field1, productType>> tRes(reuseTmpFieldField<Field1, productType, Type1>::New(tf1));
		dot(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field1, typename innerProduct<Type1, Type2>::type>> operator &(
		const tmp<FieldField<Field1, Type1>>& tf1, const tmp<FieldField<Field2, Type2>>& tf2)
	{
		typedef typename innerProduct<Type1, Type2>::type productType;
		tmp<FieldField<Field1, productType>> tRes(
			reuseTmpTmpFieldField<Field1, productType, Type1, Type1, Type2>::New(tf1, tf2));
		dot(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	void dot(FieldField<Field, typename innerProduct<Type, Form>::type>& f, const FieldField<Field, Type>& f1,
		const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		forAll(f, i) { dot(f[i], f1[i], vs); }
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename innerProduct<Type, Form>::type>> operator &(
		const FieldField<Field, Type>& f1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		typedef typename innerProduct<Type, Form>::type productType;
		tmp<FieldField<Field, productType>> tRes(FieldField<Field, productType>::NewCalculatedType(f1));
		dot(tRes.ref(), f1, static_cast<const Form&>(vs));
		return tRes;
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename innerProduct<Type, Form>::type>> operator &(
		const tmp<FieldField<Field, Type>>& tf1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		typedef typename innerProduct<Type, Form>::type productType;
		tmp<FieldField<Field, productType>> tRes(reuseTmpFieldField<Field, productType, Type>::New(tf1));
		dot(tRes.ref(), tf1(), static_cast<const Form&>(vs));
		tf1.clear();
		return tRes;
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	void dot(FieldField<Field, typename innerProduct<Form, Type>::type>& f, const VectorSpace<Form, Cmpt, nCmpt>& vs,
		const FieldField<Field, Type>& f1)
	{
		forAll(f, i) { dot(f[i], vs, f1[i]); }
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename innerProduct<Form, Type>::type>> operator &(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const FieldField<Field, Type>& f1)
	{
		typedef typename innerProduct<Form, Type>::type productType;
		tmp<FieldField<Field, productType>> tRes(FieldField<Field, productType>::NewCalculatedType(f1));
		dot(tRes.ref(), static_cast<const Form&>(vs), f1);
		return tRes;
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename innerProduct<Form, Type>::type>> operator &(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<FieldField<Field, Type>>& tf1)
	{
		typedef typename innerProduct<Form, Type>::type productType;
		tmp<FieldField<Field, productType>> tRes(reuseTmpFieldField<Field, productType, Type>::New(tf1));
		dot(tRes.ref(), static_cast<const Form&>(vs), tf1());
		tf1.clear();
		return tRes;
	}

	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	void dotdot(FieldField<Field1, typename scalarProduct<Type1, Type2>::type>& f, const FieldField<Field1, Type1>& f1,
		const FieldField<Field2, Type2>& f2)
	{
		forAll(f, i) { dotdot(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field1, typename scalarProduct<Type1, Type2>::type>> operator &&(
		const FieldField<Field1, Type1>& f1, const FieldField<Field2, Type2>& f2)
	{
		typedef typename scalarProduct<Type1, Type2>::type productType;
		tmp<FieldField<Field1, productType>> tRes(FieldField<Field1, productType>::NewCalculatedType(f1));
		dotdot(tRes.ref(), f1, f2);
		return tRes;
	}

	template <template<class> class Field, class Type1, class Type2>
	tmp<FieldField<Field, typename scalarProduct<Type1, Type2>::type>> operator &&(
		const FieldField<Field, Type1>& f1, const tmp<FieldField<Field, Type2>>& tf2)
	{
		typedef typename scalarProduct<Type1, Type2>::type productType;
		tmp<FieldField<Field, productType>> tRes(reuseTmpFieldField<Field, productType, Type2>::New(tf2));
		dotdot(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field, typename scalarProduct<Type1, Type2>::type>> operator &&(
		const FieldField<Field1, Type1>& f1, const tmp<FieldField<Field2, Type2>>& tf2)
	{
		typedef typename scalarProduct<Type1, Type2>::type productType;
		tmp<FieldField<Field1, productType>> tRes(FieldField<Field1, productType>::NewCalculatedType(f1));
		dotdot(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field1, typename scalarProduct<Type1, Type2>::type>> operator &&(
		const tmp<FieldField<Field1, Type1>>& tf1, const FieldField<Field2, Type2>& f2)
	{
		typedef typename scalarProduct<Type1, Type2>::type productType;
		tmp<FieldField<Field1, productType>> tRes(reuseTmpFieldField<Field1, productType, Type1>::New(tf1));
		dotdot(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field1, typename scalarProduct<Type1, Type2>::type>> operator &&(
		const tmp<FieldField<Field1, Type1>>& tf1, const tmp<FieldField<Field2, Type2>>& tf2)
	{
		typedef typename scalarProduct<Type1, Type2>::type productType;
		tmp<FieldField<Field1, productType>> tRes(
			reuseTmpTmpFieldField<Field1, productType, Type1, Type1, Type2>::New(tf1, tf2));
		dotdot(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	void dotdot(FieldField<Field, typename scalarProduct<Type, Form>::type>& f, const FieldField<Field, Type>& f1,
		const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		forAll(f, i) { dotdot(f[i], f1[i], vs); }
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename scalarProduct<Type, Form>::type>> operator &&(
		const FieldField<Field, Type>& f1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		typedef typename scalarProduct<Type, Form>::type productType;
		tmp<FieldField<Field, productType>> tRes(FieldField<Field, productType>::NewCalculatedType(f1));
		dotdot(tRes.ref(), f1, static_cast<const Form&>(vs));
		return tRes;
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename scalarProduct<Type, Form>::type>> operator &&(
		const tmp<FieldField<Field, Type>>& tf1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		typedef typename scalarProduct<Type, Form>::type productType;
		tmp<FieldField<Field, productType>> tRes(reuseTmpFieldField<Field, productType, Type>::New(tf1));
		dotdot(tRes.ref(), tf1(), static_cast<const Form&>(vs));
		tf1.clear();
		return tRes;
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	void dotdot(FieldField<Field, typename scalarProduct<Form, Type>::type>& f, const VectorSpace<Form, Cmpt, nCmpt>& vs,
		const FieldField<Field, Type>& f1)
	{
		forAll(f, i) { dotdot(f[i], vs, f1[i]); }
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename scalarProduct<Form, Type>::type>> operator &&(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const FieldField<Field, Type>& f1)
	{
		typedef typename scalarProduct<Form, Type>::type productType;
		tmp<FieldField<Field, productType>> tRes(FieldField<Field, productType>::NewCalculatedType(f1));
		dotdot(tRes.ref(), static_cast<const Form&>(vs), f1);
		return tRes;
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename scalarProduct<Form, Type>::type>> operator &&(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<FieldField<Field, Type>>& tf1)
	{
		typedef typename scalarProduct<Form, Type>::type productType;
		tmp<FieldField<Field, productType>> tRes(reuseTmpFieldField<Field, productType, Type>::New(tf1));
		dotdot(tRes.ref(), static_cast<const Form&>(vs), tf1());
		tf1.clear();
		return tRes;
	}

//#undef PRODUCT_OPERATOR


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //