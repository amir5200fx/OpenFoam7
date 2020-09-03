#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * global operators  * * * * * * * * * * * * * //

	template<template<class> class Field>
	void sqr(FieldField<Field, symmTensor>& res, const FieldField<Field, vector>& f)
	{
		forAll(res, i) { sqr(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, symmTensor>> sqr(const FieldField<Field, vector>& f)
	{
		tmp<FieldField<Field, symmTensor>> tRes(FieldField<Field, symmTensor>::NewCalculatedType(f));
		sqr(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, symmTensor>> sqr(const tmp<FieldField<Field, vector>>& tf)
	{
		tmp<FieldField<Field, symmTensor>> tRes(New(tf));
		sqr(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void innerSqr(FieldField<Field, symmTensor>& res, const FieldField<Field, symmTensor>& f)
	{
		forAll(res, i) { innerSqr(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, symmTensor>> innerSqr(const FieldField<Field, symmTensor>& f)
	{
		tmp<FieldField<Field, symmTensor>> tRes(FieldField<Field, symmTensor>::NewCalculatedType(f));
		innerSqr(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, symmTensor>> innerSqr(const tmp<FieldField<Field, symmTensor>>& tf)
	{
		tmp<FieldField<Field, symmTensor>> tRes(New(tf));
		innerSqr(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void tr(FieldField<Field, scalar>& res, const FieldField<Field, symmTensor>& f)
	{
		forAll(res, i) { tr(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> tr(const FieldField<Field, symmTensor>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		tr(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> tr(const tmp<FieldField<Field, symmTensor>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tf));
		tr(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void sph(FieldField<Field, sphericalTensor>& res, const FieldField<Field, symmTensor>& f)
	{
		forAll(res, i) { sph(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, sphericalTensor>> sph(const FieldField<Field, symmTensor>& f)
	{
		tmp<FieldField<Field, sphericalTensor>> tRes(FieldField<Field, sphericalTensor>::NewCalculatedType(f));
		sph(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, sphericalTensor>> sph(const tmp<FieldField<Field, symmTensor>>& tf)
	{
		tmp<FieldField<Field, sphericalTensor>> tRes(New(tf));
		sph(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void symm(FieldField<Field, symmTensor>& res, const FieldField<Field, symmTensor>& f)
	{
		forAll(res, i) { symm(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, symmTensor>> symm(const FieldField<Field, symmTensor>& f)
	{
		tmp<FieldField<Field, symmTensor>> tRes(FieldField<Field, symmTensor>::NewCalculatedType(f));
		symm(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, symmTensor>> symm(const tmp<FieldField<Field, symmTensor>>& tf)
	{
		tmp<FieldField<Field, symmTensor>> tRes(New(tf));
		symm(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void twoSymm(FieldField<Field, symmTensor>& res, const FieldField<Field, symmTensor>& f)
	{
		forAll(res, i) { twoSymm(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, symmTensor>> twoSymm(const FieldField<Field, symmTensor>& f)
	{
		tmp<FieldField<Field, symmTensor>> tRes(FieldField<Field, symmTensor>::NewCalculatedType(f));
		twoSymm(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, symmTensor>> twoSymm(const tmp<FieldField<Field, symmTensor>>& tf)
	{
		tmp<FieldField<Field, symmTensor>> tRes(New(tf));
		twoSymm(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void dev(FieldField<Field, symmTensor>& res, const FieldField<Field, symmTensor>& f)
	{
		forAll(res, i) { dev(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, symmTensor>> dev(const FieldField<Field, symmTensor>& f)
	{
		tmp<FieldField<Field, symmTensor>> tRes(FieldField<Field, symmTensor>::NewCalculatedType(f));
		dev(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, symmTensor>> dev(const tmp<FieldField<Field, symmTensor>>& tf)
	{
		tmp<FieldField<Field, symmTensor>> tRes(New(tf));
		dev(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void dev2(FieldField<Field, symmTensor>& res, const FieldField<Field, symmTensor>& f)
	{
		forAll(res, i) { dev2(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, symmTensor>> dev2(const FieldField<Field, symmTensor>& f)
	{
		tmp<FieldField<Field, symmTensor>> tRes(FieldField<Field, symmTensor>::NewCalculatedType(f));
		dev2(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, symmTensor>> dev2(const tmp<FieldField<Field, symmTensor>>& tf)
	{
		tmp<FieldField<Field, symmTensor>> tRes(New(tf));
		dev2(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void det(FieldField<Field, scalar>& res, const FieldField<Field, symmTensor>& f)
	{
		forAll(res, i) { det(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> det(const FieldField<Field, symmTensor>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		det(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> det(const tmp<FieldField<Field, symmTensor>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tf));
		det(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void cof(FieldField<Field, symmTensor>& res, const FieldField<Field, symmTensor>& f)
	{
		forAll(res, i) { cof(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, symmTensor>> cof(const FieldField<Field, symmTensor>& f)
	{
		tmp<FieldField<Field, symmTensor>> tRes(FieldField<Field, symmTensor>::NewCalculatedType(f));
		cof(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, symmTensor>> cof(const tmp<FieldField<Field, symmTensor>>& tf)
	{
		tmp<FieldField<Field, symmTensor>> tRes(New(tf));
		cof(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void inv(FieldField<Field, symmTensor>& res, const FieldField<Field, symmTensor>& f)
	{
		forAll(res, i) { inv(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, symmTensor>> inv(const FieldField<Field, symmTensor>& f)
	{
		tmp<FieldField<Field, symmTensor>> tRes(FieldField<Field, symmTensor>::NewCalculatedType(f));
		inv(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, symmTensor>> inv(const tmp<FieldField<Field, symmTensor>>& tf)
	{
		tmp<FieldField<Field, symmTensor>> tRes(New(tf));
		inv(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}


	// * * * * * * * * * * * * * * * global operators  * * * * * * * * * * * * * //

	template<template<class> class Field>
	void hdual(FieldField<Field, vector>& res, const FieldField<Field, symmTensor>& f)
	{
		forAll(res, i) { hdual(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, vector>> operator *(const FieldField<Field, symmTensor>& f)
	{
		tmp<FieldField<Field, vector>> tRes(FieldField<Field, symmTensor>::NewCalculatedType(f));
		hdual(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, vector>> operator *(const tmp<FieldField<Field, symmTensor>>& tf)
	{
		tmp<FieldField<Field, vector>> tRes(New(tf));
		hdual(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void dot(FieldField<Field, tensor>& f, const FieldField<Field, symmTensor>& f1,
		const FieldField<Field, symmTensor>& f2)
	{
		forAll(f, i) { dot(f[i], f1[i], f2[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, tensor>> operator &(const FieldField<Field, symmTensor>& f1,
		const FieldField<Field, symmTensor>& f2)
	{
		tmp<FieldField<Field, tensor>> tRes(FieldField<Field, tensor>::NewCalculatedType(f1));
		dot(tRes.ref(), f1, f2);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, tensor>> operator &(const FieldField<Field, symmTensor>& f1,
		const tmp<FieldField<Field, symmTensor>>& tf2)
	{
		tmp<FieldField<Field, tensor>> tRes(reuseTmpFieldField<Field, tensor, symmTensor>::New(tf2));
		dot(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, tensor>> operator &(const tmp<FieldField<Field, symmTensor>>& tf1,
		const FieldField<Field, symmTensor>& f2)
	{
		tmp<FieldField<Field, tensor>> tRes(reuseTmpFieldField<Field, tensor, symmTensor>::New(tf1));
		dot(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, tensor>> operator &(const tmp<FieldField<Field, symmTensor>>& tf1,
		const tmp<FieldField<Field, symmTensor>>& tf2)
	{
		tmp<FieldField<Field, tensor>> tRes(
			reuseTmpTmpFieldField<Field, tensor, symmTensor, symmTensor, symmTensor>::New(tf1, tf2));
		dot(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}

	template<template<class> class Field>
	void dot(FieldField<Field, tensor>& f, const symmTensor& s, const FieldField<Field, symmTensor>& f2)
	{
		forAll(f, i) { dot(f[i], s, f2[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, tensor>> operator &(const symmTensor& s, const FieldField<Field, symmTensor>& f2)
	{
		tmp<FieldField<Field, tensor>> tRes(FieldField<Field, symmTensor>::NewCalculatedType(f2));
		dot(tRes.ref(), s, f2);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, tensor>> operator &(const symmTensor& s, const tmp<FieldField<Field, symmTensor>>& tf2)
	{
		tmp<FieldField<Field, tensor>> tRes(reuseTmpFieldField<Field, tensor, symmTensor>::New(tf2));
		dot(tRes.ref(), s, tf2());
		tf2.clear();
		return tRes;
	}

	template<template<class> class Field>
	void dot(FieldField<Field, tensor>& f, const FieldField<Field, symmTensor>& f1, const symmTensor& s)
	{
		forAll(f, i) { dot(f[i], f1[i], s); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, tensor>> operator &(const FieldField<Field, symmTensor>& f1, const symmTensor& s)
	{
		tmp<FieldField<Field, tensor>> tRes(FieldField<Field, symmTensor>::NewCalculatedType(f1));
		dot(tRes.ref(), f1, s);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, tensor>> operator &(const tmp<FieldField<Field, symmTensor>>& tf1, const symmTensor& s)
	{
		tmp<FieldField<Field, tensor>> tRes(reuseTmpFieldField<Field, tensor, symmTensor>::New(tf1));
		dot(tRes.ref(), tf1(), s);
		tf1.clear();
		return tRes;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //