#pragma once
#include <FieldFieldReuseFunctions.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<template<class> class Field>
	void stabilise
	(
		FieldField<Field, scalar>& f,
		const FieldField<Field, scalar>& f1,
		const scalar s
	)
	{
		forAll(f, i)
		{
			stabilise(f[i], f1[i], s);
		}
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> stabilise
	(
		const FieldField<Field, scalar>& f1,
		const scalar s
	)
	{
		tmp<FieldField<Field, scalar>> tf
		(
			FieldField<Field, scalar>::NewCalculatedType(f1)
		);
		stabilise(tf(), f1, s);
		return tf;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> stabilise
	(
		const tmp<FieldField<Field, scalar>>& tf1,
		const scalar s
	)
	{
		tmp<FieldField<Field, scalar>> tf(tf1.ptr());
		stabilise(tf(), tf(), s);
		return tf;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<template<class> class Field>
	void add(FieldField<Field, scalar>& f, const scalar& s, const FieldField<Field, scalar>& f2)
	{
		forAll(f, i) { add(f[i], s, f2[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> operator +(const scalar& s, const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f2));
		add(tRes.ref(), s, f2);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> operator +(const scalar& s, const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf2));
		add(tRes.ref(), s, tf2());
		tf2.clear();
		return tRes;
	}

	template<template<class> class Field>
	void add(FieldField<Field, scalar>& f, const FieldField<Field, scalar>& f1, const scalar& s)
	{
		forAll(f, i) { add(f[i], f1[i], s); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> operator +(const FieldField<Field, scalar>& f1, const scalar& s)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f1));
		add(tRes.ref(), f1, s);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> operator +(const tmp<FieldField<Field, scalar>>& tf1, const scalar& s)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf1));
		add(tRes.ref(), tf1(), s);
		tf1.clear();
		return tRes;
	}

	template<template<class> class Field>
	void subtract(FieldField<Field, scalar>& f, const scalar& s, const FieldField<Field, scalar>& f2)
	{
		forAll(f, i) { subtract(f[i], s, f2[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> operator -(const scalar& s, const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f2));
		subtract(tRes.ref(), s, f2);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> operator -(const scalar& s, const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf2));
		subtract(tRes.ref(), s, tf2());
		tf2.clear();
		return tRes;
	}

	template<template<class> class Field>
	void subtract(FieldField<Field, scalar>& f, const FieldField<Field, scalar>& f1, const scalar& s)
	{
		forAll(f, i) { subtract(f[i], f1[i], s); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> operator -(const FieldField<Field, scalar>& f1, const scalar& s)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f1));
		subtract(tRes.ref(), f1, s);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> operator -(const tmp<FieldField<Field, scalar>>& tf1, const scalar& s)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf1));
		subtract(tRes.ref(), tf1(), s);
		tf1.clear();
		return tRes;
	}

	template<template<class> class Field>
	void multiply(FieldField<Field, scalar>& f, const FieldField<Field, scalar>& f1, const FieldField<Field, scalar>& f2)
	{
		forAll(f, i) { multiply(f[i], f1[i], f2[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> operator *(const FieldField<Field, scalar>& f1, const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f1));
		multiply(tRes.ref(), f1, f2);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> operator *(const FieldField<Field, scalar>& f1,
		const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf2));
		multiply(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> operator *(const tmp<FieldField<Field, scalar>>& tf1,
		const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf1));
		multiply(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> operator *(const tmp<FieldField<Field, scalar>>& tf1,
		const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpTmpFieldField<Field, scalar, scalar, scalar, scalar>::New(tf1, tf2));
		multiply(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}

	template<template<class> class Field>
	void divide(FieldField<Field, scalar>& f, const FieldField<Field, scalar>& f1, const FieldField<Field, scalar>& f2)
	{
		forAll(f, i) { divide(f[i], f1[i], f2[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> operator /(const FieldField<Field, scalar>& f1, const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f1));
		divide(tRes.ref(), f1, f2);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> operator /(const FieldField<Field, scalar>& f1,
		const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf2));
		divide(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> operator /(const tmp<FieldField<Field, scalar>>& tf1,
		const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf1));
		divide(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> operator /(const tmp<FieldField<Field, scalar>>& tf1,
		const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpTmpFieldField<Field, scalar, scalar, scalar, scalar>::New(tf1, tf2));
		divide(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}

	template<template<class> class Field>
	void divide(FieldField<Field, scalar>& f, const scalar& s, const FieldField<Field, scalar>& f2)
	{
		forAll(f, i) { divide(f[i], s, f2[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> operator /(const scalar& s, const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f2));
		divide(tRes.ref(), s, f2);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> operator /(const scalar& s, const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf2));
		divide(tRes.ref(), s, tf2());
		tf2.clear();
		return tRes;
	}

	template<template<class> class Field>
	void pow(FieldField<Field, scalar>& f, const FieldField<Field, scalar>& f1, const FieldField<Field, scalar>& f2)
	{
		forAll(f, i) { pow(f[i], f1[i], f2[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> pow(const FieldField<Field, scalar>& f1, const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f1));
		pow(tRes.ref(), f1, f2);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> pow(const FieldField<Field, scalar>& f1, const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf2));
		pow(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> pow(const tmp<FieldField<Field, scalar>>& tf1, const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf1));
		pow(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> pow(const tmp<FieldField<Field, scalar>>& tf1,
		const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpTmpFieldField<Field, scalar, scalar, scalar, scalar>::New(tf1, tf2));
		pow(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}

	template<template<class> class Field>
	void pow(FieldField<Field, scalar>& f, const scalar& s, const FieldField<Field, scalar>& f2)
	{
		forAll(f, i) { pow(f[i], s, f2[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> pow(const scalar& s, const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f2));
		pow(tRes.ref(), s, f2);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> pow(const scalar& s, const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf2));
		pow(tRes.ref(), s, tf2());
		tf2.clear();
		return tRes;
	}

	template<template<class> class Field>
	void pow(FieldField<Field, scalar>& f, const FieldField<Field, scalar>& f1, const scalar& s)
	{
		forAll(f, i) { pow(f[i], f1[i], s); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> pow(const FieldField<Field, scalar>& f1, const scalar& s)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f1));
		pow(tRes.ref(), f1, s);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> pow(const tmp<FieldField<Field, scalar>>& tf1, const scalar& s)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf1));
		pow(tRes.ref(), tf1(), s);
		tf1.clear();
		return tRes;
	}

	template<template<class> class Field>
	void atan2(FieldField<Field, scalar>& f, const FieldField<Field, scalar>& f1, const FieldField<Field, scalar>& f2)
	{
		forAll(f, i) { atan2(f[i], f1[i], f2[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> atan2(const FieldField<Field, scalar>& f1, const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f1));
		atan2(tRes.ref(), f1, f2);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> atan2(const FieldField<Field, scalar>& f1, const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf2));
		atan2(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> atan2(const tmp<FieldField<Field, scalar>>& tf1, const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf1));
		atan2(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> atan2(const tmp<FieldField<Field, scalar>>& tf1,
		const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpTmpFieldField<Field, scalar, scalar, scalar, scalar>::New(tf1, tf2));
		atan2(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}

	template<template<class> class Field>
	void atan2(FieldField<Field, scalar>& f, const scalar& s, const FieldField<Field, scalar>& f2)
	{
		forAll(f, i) { atan2(f[i], s, f2[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> atan2(const scalar& s, const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f2));
		atan2(tRes.ref(), s, f2);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> atan2(const scalar& s, const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf2));
		atan2(tRes.ref(), s, tf2());
		tf2.clear();
		return tRes;
	}

	template<template<class> class Field>
	void atan2(FieldField<Field, scalar>& f, const FieldField<Field, scalar>& f1, const scalar& s)
	{
		forAll(f, i) { atan2(f[i], f1[i], s); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> atan2(const FieldField<Field, scalar>& f1, const scalar& s)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f1));
		atan2(tRes.ref(), f1, s);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> atan2(const tmp<FieldField<Field, scalar>>& tf1, const scalar& s)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, scalar, scalar>::New(tf1));
		atan2(tRes.ref(), tf1(), s);
		tf1.clear();
		return tRes;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<template<class> class Field>
	void pow3(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { pow3(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> pow3(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		pow3(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> pow3(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tf));
		pow3(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void pow4(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { pow4(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> pow4(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		pow4(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> pow4(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tf));
		pow4(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void pow5(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { pow5(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> pow5(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		pow5(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> pow5(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tf));
		pow5(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void pow6(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { pow6(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> pow6(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		pow6(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> pow6(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tf));
		pow6(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void pow025(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { pow025(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> pow025(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		pow025(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> pow025(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tf));
		pow025(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void sqrt(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { sqrt(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> sqrt(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		sqrt(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> sqrt(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tf));
		sqrt(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void cbrt(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { cbrt(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> cbrt(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		cbrt(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> cbrt(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tf));
		cbrt(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void sign(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { sign(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> sign(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		sign(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> sign(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tf));
		sign(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void pos(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { pos(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> pos(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		pos(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> pos(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tf));
		pos(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void pos0(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { pos0(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> pos0(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		pos0(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> pos0(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tf));
		pos0(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void neg(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { neg(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> neg(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		neg(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> neg(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tf));
		neg(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void neg0(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { neg0(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> neg0(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		neg0(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> neg0(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tf));
		neg0(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void posPart(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { posPart(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> posPart(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		posPart(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> posPart(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tf));
		posPart(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void negPart(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { negPart(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> negPart(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		negPart(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> negPart(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tf));
		negPart(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void exp(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { exp(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> exp(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		exp(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> exp(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tf));
		exp(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void log(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { log(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> log(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		log(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> log(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tf));
		log(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void log10(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { log10(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> log10(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		log10(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> log10(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tf));
		log10(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void sin(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { sin(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> sin(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		sin(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> sin(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tf));
		sin(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void cos(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { cos(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> cos(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		cos(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> cos(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tf));
		cos(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void tan(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { tan(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> tan(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		tan(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> tan(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tf));
		tan(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void asin(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { asin(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> asin(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		asin(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> asin(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tf));
		asin(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void acos(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { acos(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> acos(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		acos(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> acos(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tf));
		acos(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void atan(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { atan(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> atan(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		atan(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> atan(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tf));
		atan(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void sinh(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { sinh(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> sinh(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		sinh(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> sinh(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tf));
		sinh(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void cosh(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { cosh(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> cosh(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		cosh(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> cosh(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tf));
		cosh(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void tanh(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { tanh(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> tanh(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		tanh(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> tanh(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tf));
		tanh(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void asinh(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { asinh(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> asinh(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		asinh(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> asinh(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tf));
		asinh(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void acosh(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { acosh(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> acosh(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		acosh(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> acosh(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tf));
		acosh(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void atanh(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { atanh(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> atanh(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		atanh(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> atanh(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tf));
		atanh(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void erf(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { erf(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> erf(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		erf(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> erf(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tf));
		erf(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void erfc(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { erfc(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> erfc(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		erfc(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> erfc(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tf));
		erfc(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void lgamma(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { lgamma(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> lgamma(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		lgamma(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> lgamma(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tf));
		lgamma(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void j0(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { j0(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> j0(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		j0(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> j0(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tf));
		j0(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void j1(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { j1(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> j1(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		j1(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> j1(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tf));
		j1(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void y0(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { y0(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> y0(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		y0(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> y0(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tf));
		y0(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void y1(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f)
	{
		forAll(res, i) { y1(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> y1(const FieldField<Field, scalar>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		y1(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> y1(const tmp<FieldField<Field, scalar>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tf));
		y1(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}


//#define BesselFunc(func)                                                       \
//                                                                               \
//template<template<class> class Field>                                          \
//void func                                                                      \
//(                                                                              \
//    FieldField<Field, scalar>& res,                                            \
//    const int n,                                                               \
//    const FieldField<Field, scalar>& sf                                        \
//)                                                                              \
//{                                                                              \
//    forAll(res, i)                                                             \
//    {                                                                          \
//        func(res[i], n, sf[i]);                                                \
//    }                                                                          \
//}                                                                              \
//                                                                               \
//template<template<class> class Field>                                          \
//tmp<FieldField<Field, scalar>> func                                            \
//(                                                                              \
//    const int n,                                                               \
//    const FieldField<Field, scalar>& sf                                        \
//)                                                                              \
//{                                                                              \
//    tmp<FieldField<Field, scalar>> tRes                                        \
//    (                                                                          \
//        FieldField<Field, scalar>::NewCalculatedType(sf)                       \
//    );                                                                         \
//    func(tRes(), n, sf);                                                       \
//    return tRes;                                                               \
//}                                                                              \
//                                                                               \
//template<template<class> class Field>                                          \
//tmp<FieldField<Field, scalar>> func                                            \
//(                                                                              \
//    const int n,                                                               \
//    const tmp<FieldField<Field, scalar>>& tsf                                  \
//)                                                                              \
//{                                                                              \
//    tmp<FieldField<Field, scalar>> tRes(New(tsf));                             \
//    func(tRes(), n, tsf());                                                    \
//    tsf.clear();                                                               \
//    return tRes;                                                               \
//}


	template <template<class> class Field>
	void jn(FieldField<Field, scalar>& res, const int n, const FieldField<Field, scalar>& sf)
	{
		forAll(res, i) { jn(res[i], n, sf[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> jn(const int n, const FieldField<Field, scalar>& sf)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(sf));
		jn(tRes(), n, sf);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> jn(const int n, const tmp<FieldField<Field, scalar>>& tsf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tsf));
		jn(tRes(), n, tsf());
		tsf.clear();
		return tRes;
	}

	template <template<class> class Field>
	void yn(FieldField<Field, scalar>& res, const int n, const FieldField<Field, scalar>& sf)
	{
		forAll(res, i) { yn(res[i], n, sf[i]); }
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> yn(const int n, const FieldField<Field, scalar>& sf)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(sf));
		yn(tRes(), n, sf);
		return tRes;
	}

	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> yn(const int n, const tmp<FieldField<Field, scalar>>& tsf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tsf));
		yn(tRes(), n, tsf());
		tsf.clear();
		return tRes;
	}

//#undef BesselFunc


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //