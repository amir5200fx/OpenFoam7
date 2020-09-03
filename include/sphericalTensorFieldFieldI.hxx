#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * global functions  * * * * * * * * * * * * * //

	template<template<class> class Field>
	void tr(FieldField<Field, scalar>& res, const FieldField<Field, sphericalTensor>& f)
	{
		forAll(res, i) { tr(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> tr(const FieldField<Field, sphericalTensor>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		tr(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> tr(const tmp<FieldField<Field, sphericalTensor>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tf));
		tr(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void sph(FieldField<Field, sphericalTensor>& res, const FieldField<Field, sphericalTensor>& f)
	{
		forAll(res, i) { sph(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, sphericalTensor>> sph(const FieldField<Field, sphericalTensor>& f)
	{
		tmp<FieldField<Field, sphericalTensor>> tRes(FieldField<Field, sphericalTensor>::NewCalculatedType(f));
		sph(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, sphericalTensor>> sph(const tmp<FieldField<Field, sphericalTensor>>& tf)
	{
		tmp<FieldField<Field, sphericalTensor>> tRes(New(tf));
		sph(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void det(FieldField<Field, scalar>& res, const FieldField<Field, sphericalTensor>& f)
	{
		forAll(res, i) { det(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> det(const FieldField<Field, sphericalTensor>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		det(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> det(const tmp<FieldField<Field, sphericalTensor>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(New(tf));
		det(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}

	template<template<class> class Field>
	void inv(FieldField<Field, sphericalTensor>& res, const FieldField<Field, sphericalTensor>& f)
	{
		forAll(res, i) { inv(res[i], f[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, sphericalTensor>> inv(const FieldField<Field, sphericalTensor>& f)
	{
		tmp<FieldField<Field, sphericalTensor>> tRes(FieldField<Field, sphericalTensor>::NewCalculatedType(f));
		inv(tRes.ref(), f);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, sphericalTensor>> inv(const tmp<FieldField<Field, sphericalTensor>>& tf)
	{
		tmp<FieldField<Field, sphericalTensor>> tRes(New(tf));
		inv(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}


	// * * * * * * * * * * * * * * * global operators  * * * * * * * * * * * * * //

	template<template<class> class Field>
	void divide(FieldField<Field, sphericalTensor>& f, const FieldField<Field, scalar>& f1,
		const FieldField<Field, sphericalTensor>& f2)
	{
		forAll(f, i) { divide(f[i], f1[i], f2[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, sphericalTensor>> operator /(const FieldField<Field, scalar>& f1,
		const FieldField<Field, sphericalTensor>& f2)
	{
		tmp<FieldField<Field, sphericalTensor>> tRes(FieldField<Field, sphericalTensor>::NewCalculatedType(f1));
		divide(tRes.ref(), f1, f2);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, sphericalTensor>> operator /(const FieldField<Field, scalar>& f1,
		const tmp<FieldField<Field, sphericalTensor>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor>> tRes(reuseTmpFieldField<Field, sphericalTensor, sphericalTensor>::New(tf2));
		divide(tRes.ref(), f1, tf2());
		tf2.clear();
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, sphericalTensor>> operator /(const tmp<FieldField<Field, scalar>>& tf1,
		const FieldField<Field, sphericalTensor>& f2)
	{
		tmp<FieldField<Field, sphericalTensor>> tRes(reuseTmpFieldField<Field, sphericalTensor, scalar>::New(tf1));
		divide(tRes.ref(), tf1(), f2);
		tf1.clear();
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, sphericalTensor>> operator /(const tmp<FieldField<Field, scalar>>& tf1,
		const tmp<FieldField<Field, sphericalTensor>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor>> tRes(
			reuseTmpTmpFieldField<Field, sphericalTensor, scalar, scalar, sphericalTensor>::New(tf1, tf2));
		divide(tRes.ref(), tf1(), tf2());
		tf1.clear();
		tf2.clear();
		return tRes;
	}

	template<template<class> class Field>
	void divide(FieldField<Field, sphericalTensor>& f, const scalar& s, const FieldField<Field, sphericalTensor>& f2)
	{
		forAll(f, i) { divide(f[i], s, f2[i]); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, sphericalTensor>> operator /(const scalar& s, const FieldField<Field, sphericalTensor>& f2)
	{
		tmp<FieldField<Field, sphericalTensor>> tRes(FieldField<Field, sphericalTensor>::NewCalculatedType(f2));
		divide(tRes.ref(), s, f2);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, sphericalTensor>> operator /(const scalar& s, const tmp<FieldField<Field, sphericalTensor>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor>> tRes(reuseTmpFieldField<Field, sphericalTensor, sphericalTensor>::New(tf2));
		divide(tRes.ref(), s, tf2());
		tf2.clear();
		return tRes;
	}

	template<template<class> class Field>
	void divide(FieldField<Field, sphericalTensor>& f, const FieldField<Field, scalar>& f1, const sphericalTensor& s)
	{
		forAll(f, i) { divide(f[i], f1[i], s); }
	}

	template<template<class> class Field>
	tmp<FieldField<Field, sphericalTensor>> operator /(const FieldField<Field, scalar>& f1, const sphericalTensor& s)
	{
		tmp<FieldField<Field, sphericalTensor>> tRes(FieldField<Field, scalar>::NewCalculatedType(f1));
		divide(tRes.ref(), f1, s);
		return tRes;
	}

	template<template<class> class Field>
	tmp<FieldField<Field, sphericalTensor>> operator /(const tmp<FieldField<Field, scalar>>& tf1, const sphericalTensor& s)
	{
		tmp<FieldField<Field, sphericalTensor>> tRes(reuseTmpFieldField<Field, sphericalTensor, scalar>::New(tf1));
		divide(tRes.ref(), tf1(), s);
		tf1.clear();
		return tRes;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //