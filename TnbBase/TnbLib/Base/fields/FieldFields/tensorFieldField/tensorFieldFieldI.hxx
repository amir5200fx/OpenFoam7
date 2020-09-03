#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * global operators  * * * * * * * * * * * * * //

	template<template<class> class Field>
	void tr(FieldField<Field, scalar>& res, const FieldField<Field, tensor>& f)
	{
		forAll(res, i) { tr(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> tr(const FieldField<Field, tensor>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		tr(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> tr(const tmp<FieldField<Field, tensor>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tf));
		tr(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void sph(FieldField<Field, sphericalTensor>& res, const FieldField<Field, tensor>& f)
	{
		forAll(res, i) { sph(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, sphericalTensor>> sph(const FieldField<Field, tensor>& f)
	{
		tmp<FieldField<Field, sphericalTensor>> tRes(FieldField<Field, sphericalTensor>::NewCalculatedType(f));
		sph(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, sphericalTensor>> sph(const tmp<FieldField<Field, tensor>>& tf)
	{
		tmp<FieldField<Field, sphericalTensor>> tRes(New(tf));
		sph(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void symm(FieldField<Field, symmTensor>& res, const FieldField<Field, tensor>& f)
	{
		forAll(res, i) { symm(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, symmTensor>> symm(const FieldField<Field, tensor>& f)
	{
		tmp<FieldField<Field, symmTensor>> tRes(FieldField<Field, symmTensor>::NewCalculatedType(f));
		symm(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, symmTensor>> symm(const tmp<FieldField<Field, tensor>>& tf)
	{
		tmp<FieldField<Field, symmTensor>> tRes(New(tf));
		symm(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void twoSymm(FieldField<Field, symmTensor>& res, const FieldField<Field, tensor>& f)
	{
		forAll(res, i) { twoSymm(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, symmTensor>> twoSymm(const FieldField<Field, tensor>& f)
	{
		tmp<FieldField<Field, symmTensor>> tRes(FieldField<Field, symmTensor>::NewCalculatedType(f));
		twoSymm(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, symmTensor>> twoSymm(const tmp<FieldField<Field, tensor>>& tf)
	{
		tmp<FieldField<Field, symmTensor>> tRes(New(tf));
		twoSymm(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void skew(FieldField<Field, tensor>& res, const FieldField<Field, tensor>& f)
	{
		forAll(res, i) { skew(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, tensor>> skew(const FieldField<Field, tensor>& f)
	{
		tmp<FieldField<Field, tensor>> tRes(FieldField<Field, tensor>::NewCalculatedType(f));
		skew(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, tensor>> skew(const tmp<FieldField<Field, tensor>>& tf)
	{
		tmp<FieldField<Field, tensor>> tRes(New(tf));
		skew(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void dev(FieldField<Field, tensor>& res, const FieldField<Field, tensor>& f)
	{
		forAll(res, i) { dev(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, tensor>> dev(const FieldField<Field, tensor>& f)
	{
		tmp<FieldField<Field, tensor>> tRes(FieldField<Field, tensor>::NewCalculatedType(f));
		dev(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, tensor>> dev(const tmp<FieldField<Field, tensor>>& tf)
	{
		tmp<FieldField<Field, tensor>> tRes(New(tf));
		dev(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void dev2(FieldField<Field, tensor>& res, const FieldField<Field, tensor>& f)
	{
		forAll(res, i) { dev2(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, tensor>> dev2(const FieldField<Field, tensor>& f)
	{
		tmp<FieldField<Field, tensor>> tRes(FieldField<Field, tensor>::NewCalculatedType(f));
		dev2(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, tensor>> dev2(const tmp<FieldField<Field, tensor>>& tf)
	{
		tmp<FieldField<Field, tensor>> tRes(New(tf));
		dev2(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void det(FieldField<Field, scalar>& res, const FieldField<Field, tensor>& f)
	{
		forAll(res, i) { det(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> det(const FieldField<Field, tensor>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		det(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> det(const tmp<FieldField<Field, tensor>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tf));
		det(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void cof(FieldField<Field, tensor>& res, const FieldField<Field, tensor>& f)
	{
		forAll(res, i) { cof(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, tensor>> cof(const FieldField<Field, tensor>& f)
	{
		tmp<FieldField<Field, tensor>> tRes(FieldField<Field, tensor>::NewCalculatedType(f));
		cof(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, tensor>> cof(const tmp<FieldField<Field, tensor>>& tf)
	{
		tmp<FieldField<Field, tensor>> tRes(New(tf));
		cof(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void inv(FieldField<Field, tensor>& res, const FieldField<Field, tensor>& f)
	{
		forAll(res, i) { inv(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, tensor>> inv(const FieldField<Field, tensor>& f)
	{
		tmp<FieldField<Field, tensor>> tRes(FieldField<Field, tensor>::NewCalculatedType(f));
		inv(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, tensor>> inv(const tmp<FieldField<Field, tensor>>& tf)
	{
		tmp<FieldField<Field, tensor>> tRes(New(tf));
		inv(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void eigenValues(FieldField<Field, vector>& res, const FieldField<Field, tensor>& f)
	{
		forAll(res, i) { eigenValues(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, vector>> eigenValues(const FieldField<Field, tensor>& f)
	{
		tmp<FieldField<Field, vector>> tRes(FieldField<Field, vector>::NewCalculatedType(f));
		eigenValues(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, vector>> eigenValues(const tmp<FieldField<Field, tensor>>& tf)
	{
		tmp<FieldField<Field, vector>> tRes(New(tf));
		eigenValues(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void eigenVectors(FieldField<Field, tensor>& res, const FieldField<Field, tensor>& f)
	{
		forAll(res, i) { eigenVectors(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, tensor>> eigenVectors(const FieldField<Field, tensor>& f)
	{
		tmp<FieldField<Field, tensor>> tRes(FieldField<Field, tensor>::NewCalculatedType(f));
		eigenVectors(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, tensor>> eigenVectors(const tmp<FieldField<Field, tensor>>& tf)
	{
		tmp<FieldField<Field, tensor>> tRes(New(tf));
		eigenVectors(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void eigenValues(FieldField<Field, vector>& res, const FieldField<Field, symmTensor>& f)
	{
		forAll(res, i) { eigenValues(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, vector>> eigenValues(const FieldField<Field, symmTensor>& f)
	{
		tmp<FieldField<Field, vector>> tRes(FieldField<Field, vector>::NewCalculatedType(f));
		eigenValues(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, vector>> eigenValues(const tmp<FieldField<Field, symmTensor>>& tf)
	{
		tmp<FieldField<Field, vector>> tRes(New(tf));
		eigenValues(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void eigenVectors(FieldField<Field, symmTensor>& res, const FieldField<Field, symmTensor>& f)
	{
		forAll(res, i) { eigenVectors(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, symmTensor>> eigenVectors(const FieldField<Field, symmTensor>& f)
	{
		tmp<FieldField<Field, symmTensor>> tRes(FieldField<Field, symmTensor>::NewCalculatedType(f));
		eigenVectors(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, symmTensor>> eigenVectors(const tmp<FieldField<Field, symmTensor>>& tf)
	{
		tmp<FieldField<Field, symmTensor>> tRes(New(tf));
		eigenVectors(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}


	// * * * * * * * * * * * * * * * global operators  * * * * * * * * * * * * * //

	template<template<class> class Field>
	void hdual(FieldField<Field, vector>& res, const FieldField<Field, tensor>& f)
	{
		forAll(res, i) { hdual(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, vector>> operator *(const FieldField<Field, tensor>& f)
	{
		tmp<FieldField<Field, vector>> tRes(FieldField<Field, tensor>::NewCalculatedType(f));
		hdual(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, vector>> operator *(const tmp<FieldField<Field, tensor>>& tf)
	{
		tmp<FieldField<Field, vector>> tRes(New(tf));
		hdual(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void hdual(FieldField<Field, tensor>& res, const FieldField<Field, vector>& f)
	{
		forAll(res, i) { hdual(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, tensor>> operator *(const FieldField<Field, vector>& f)
	{
		tmp<FieldField<Field, tensor>> tRes(FieldField<Field, vector>::NewCalculatedType(f));
		hdual(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, tensor>> operator *(const tmp<FieldField<Field, vector>>& tf)
	{
		tmp<FieldField<Field, tensor>> tRes(New(tf));
		hdual(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void divide(FieldField<Field, vector>& f, const FieldField<Field, vector>& f1, const FieldField<Field, tensor>& f2)
	{
		forAll(f, i) { divide(f[i], f1[i], f2[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, vector>> operator /(const FieldField<Field, vector>& f1, const FieldField<Field, tensor>& f2)
	{
		tmp<FieldField<Field, vector>> tRes(FieldField<Field, vector>::NewCalculatedType(f1));
		divide(tRes.ref(), f1, f2);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, vector>> operator /(const FieldField<Field, vector>& f1,
		const tmp<FieldField<Field, tensor>>& tf2)
	{
		tmp<FieldField<Field, vector>> tRes(reuseTmpFieldField<Field, vector, tensor>::New(tf2));
		divide(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, vector>> operator /(const tmp<FieldField<Field, vector>>& tf1,
		const FieldField<Field, tensor>& f2)
	{
		tmp<FieldField<Field, vector>> tRes(reuseTmpFieldField<Field, vector, vector>::New(tf1));
		divide(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, vector>> operator /(const tmp<FieldField<Field, vector>>& tf1,
		const tmp<FieldField<Field, tensor>>& tf2)
	{
		tmp<FieldField<Field, vector>> tRes(reuseTmpTmpFieldField<Field, vector, vector, vector, tensor>::New(tf1, tf2));
		divide(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}

	template<template<class> class Field>
	void divide(FieldField<Field, vector>& f, const vector& s, const FieldField<Field, tensor>& f2)
	{
		forAll(f, i) { divide(f[i], s, f2[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, vector>> operator /(const vector& s, const FieldField<Field, tensor>& f2)
	{
		tmp<FieldField<Field, vector>> tRes(FieldField<Field, tensor>::NewCalculatedType(f2));
		divide(tRes.ref(), s, f2);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, vector>> operator /(const vector& s, const tmp<FieldField<Field, tensor>>& tf2)
	{
		tmp<FieldField<Field, vector>> tRes(reuseTmpFieldField<Field, vector, tensor>::New(tf2));
		divide(tRes.ref(), s, tf2());
		tf2.clear();
		return tRes;
	}

	template<template<class> class Field>
	void divide(FieldField<Field, vector>& f, const FieldField<Field, vector>& f1, const tensor& s)
	{
		forAll(f, i) { divide(f[i], f1[i], s); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, vector>> operator /(const FieldField<Field, vector>& f1, const tensor& s)
	{
		tmp<FieldField<Field, vector>> tRes(FieldField<Field, vector>::NewCalculatedType(f1));
		divide(tRes.ref(), f1, s);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, vector>> operator /(const tmp<FieldField<Field, vector>>& tf1, const tensor& s)
	{
		tmp<FieldField<Field, vector>> tRes(reuseTmpFieldField<Field, vector, vector>::New(tf1));
		divide(tRes.ref(), tf1(), s);
		tf1.clear();
		return tRes;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //