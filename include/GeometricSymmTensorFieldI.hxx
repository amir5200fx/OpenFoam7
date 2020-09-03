#pragma once
#include <symmTensorFieldField.hxx>
#include <GeometricFieldReuseFunctions.hxx>
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<template<class> class PatchField, class GeoMesh>
	void sqr(GeometricField<symmTensor, PatchField, GeoMesh>& res, const GeometricField<vector, PatchField, GeoMesh>& gf1)
	{
		tnbLib::sqr(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::sqr(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> sqr(const GeometricField<vector, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<symmTensor, PatchField, GeoMesh>> tRes(
			GeometricField<symmTensor, PatchField, GeoMesh>::
			New("sqr" "(" + gf1.name() + ')', gf1.mesh(), sqr(gf1.dimensions())));
		tnbLib::sqr(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> sqr(const tmp<GeometricField<vector, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<vector, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<symmTensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<symmTensor, vector, PatchField, GeoMesh>::New(tgf1, "sqr" "(" + gf1.name() + ')',
				sqr(gf1.dimensions())));
		tnbLib::sqr(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void innerSqr(GeometricField<symmTensor, PatchField, GeoMesh>& res,
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::innerSqr(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::innerSqr(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> innerSqr(
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<symmTensor, PatchField, GeoMesh>> tRes(
			GeometricField<symmTensor, PatchField, GeoMesh>::New("innerSqr" "(" + gf1.name() + ')', gf1.mesh(),
				sqr(gf1.dimensions())));
		tnbLib::innerSqr(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> innerSqr(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<symmTensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<symmTensor, symmTensor, PatchField, GeoMesh>::New(
				tgf1, "innerSqr" "(" + gf1.name() + ')', sqr(gf1.dimensions())));
		tnbLib::innerSqr(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void tr(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::tr(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::tr(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> tr(const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New("tr" "(" + gf1.name() + ')', gf1.mesh(),
				transform(gf1.dimensions())));
		tnbLib::tr(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> tr(const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, symmTensor, PatchField, GeoMesh>::New(tgf1, "tr" "(" + gf1.name() + ')',
				transform(gf1.dimensions())));
		tnbLib::tr(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void sph(GeometricField<sphericalTensor, PatchField, GeoMesh>& res,
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::sph(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::sph(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> sph(
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> tRes(
			GeometricField<sphericalTensor, PatchField, GeoMesh>::New("sph" "(" + gf1.name() + ')', gf1.mesh(),
				transform(gf1.dimensions())));
		tnbLib::sph(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> sph(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<sphericalTensor, symmTensor, PatchField, GeoMesh>::New(
				tgf1, "sph" "(" + gf1.name() + ')', transform(gf1.dimensions())));
		tnbLib::sph(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void symm(GeometricField<symmTensor, PatchField, GeoMesh>& res,
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::symm(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::symm(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> symm(const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<symmTensor, PatchField, GeoMesh>> tRes(
			GeometricField<symmTensor, PatchField, GeoMesh>::New("symm" "(" + gf1.name() + ')', gf1.mesh(),
				transform(gf1.dimensions())));
		tnbLib::symm(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> symm(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<symmTensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<symmTensor, symmTensor, PatchField, GeoMesh>::New(
				tgf1, "symm" "(" + gf1.name() + ')', transform(gf1.dimensions())));
		tnbLib::symm(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void twoSymm(GeometricField<symmTensor, PatchField, GeoMesh>& res,
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::twoSymm(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::twoSymm(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> twoSymm(
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<symmTensor, PatchField, GeoMesh>> tRes(
			GeometricField<symmTensor, PatchField, GeoMesh>::New("twoSymm" "(" + gf1.name() + ')', gf1.mesh(),
				transform(gf1.dimensions())));
		tnbLib::twoSymm(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> twoSymm(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<symmTensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<symmTensor, symmTensor, PatchField, GeoMesh>::New(
				tgf1, "twoSymm" "(" + gf1.name() + ')', transform(gf1.dimensions())));
		tnbLib::twoSymm(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void dev(GeometricField<symmTensor, PatchField, GeoMesh>& res,
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::dev(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::dev(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> dev(const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<symmTensor, PatchField, GeoMesh>> tRes(
			GeometricField<symmTensor, PatchField, GeoMesh>::New("dev" "(" + gf1.name() + ')', gf1.mesh(),
				transform(gf1.dimensions())));
		tnbLib::dev(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> dev(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<symmTensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<symmTensor, symmTensor, PatchField, GeoMesh>::New(
				tgf1, "dev" "(" + gf1.name() + ')', transform(gf1.dimensions())));
		tnbLib::dev(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void dev2(GeometricField<symmTensor, PatchField, GeoMesh>& res,
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::dev2(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::dev2(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> dev2(const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<symmTensor, PatchField, GeoMesh>> tRes(
			GeometricField<symmTensor, PatchField, GeoMesh>::New("dev2" "(" + gf1.name() + ')', gf1.mesh(),
				transform(gf1.dimensions())));
		tnbLib::dev2(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> dev2(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<symmTensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<symmTensor, symmTensor, PatchField, GeoMesh>::New(
				tgf1, "dev2" "(" + gf1.name() + ')', transform(gf1.dimensions())));
		tnbLib::dev2(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void det(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::det(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::det(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> det(const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New("det" "(" + gf1.name() + ')', gf1.mesh(), pow3(gf1.dimensions())));
		tnbLib::det(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> det(const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, symmTensor, PatchField, GeoMesh>::New(tgf1, "det" "(" + gf1.name() + ')',
				pow3(gf1.dimensions())));
		tnbLib::det(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void cof(GeometricField<symmTensor, PatchField, GeoMesh>& res,
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::cof(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::cof(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> cof(const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<symmTensor, PatchField, GeoMesh>> tRes(
			GeometricField<symmTensor, PatchField, GeoMesh>::New("cof" "(" + gf1.name() + ')', gf1.mesh(),
				pow2(gf1.dimensions())));
		tnbLib::cof(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> cof(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<symmTensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<symmTensor, symmTensor, PatchField, GeoMesh>::New(
				tgf1, "cof" "(" + gf1.name() + ')', pow2(gf1.dimensions())));
		tnbLib::cof(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void inv(GeometricField<symmTensor, PatchField, GeoMesh>& res,
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::inv(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::inv(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> inv(const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<symmTensor, PatchField, GeoMesh>> tRes(
			GeometricField<symmTensor, PatchField, GeoMesh>::
			New("inv" "(" + gf1.name() + ')', gf1.mesh(), inv(gf1.dimensions())));
		tnbLib::inv(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> inv(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<symmTensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<symmTensor, symmTensor, PatchField, GeoMesh>::New(
				tgf1, "inv" "(" + gf1.name() + ')', inv(gf1.dimensions())));
		tnbLib::inv(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}


	// * * * * * * * * * * * * * * * global operators  * * * * * * * * * * * * * //

	template<template<class> class PatchField, class GeoMesh>
	void hdual(GeometricField<vector, PatchField, GeoMesh>& res,
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::hdual(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::hdual(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector, PatchField, GeoMesh>> operator *(const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<vector, PatchField, GeoMesh>> tRes(
			GeometricField<vector, PatchField, GeoMesh>::New("*" + gf1.name(), gf1.mesh(), transform(gf1.dimensions())));
		tnbLib::hdual(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector, symmTensor, PatchField, GeoMesh>::New(
				tgf1, "*" + gf1.name(), transform(gf1.dimensions())));
		tnbLib::hdual(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void dot(GeometricField<tensor, PatchField, GeoMesh>& res, const GeometricField<symmTensor, PatchField, GeoMesh>& gf1,
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf2)
	{
		tnbLib::dot(res.primitiveFieldRef(), gf1.primitiveField(), gf2.primitiveField());
		tnbLib::dot(res.boundaryFieldRef(), gf1.boundaryField(), gf2.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> operator &(const GeometricField<symmTensor, PatchField, GeoMesh>& gf1,
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<tensor, PatchField, GeoMesh>> tRes(
			GeometricField<tensor, PatchField, GeoMesh>::New('(' + gf1.name() + '&' + gf2.name() + ')', gf1.mesh(),
				gf1.dimensions() & gf2.dimensions()));
		tnbLib::dot(tRes.ref(), gf1, gf2);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> operator &(const GeometricField<symmTensor, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>&
		tgf2)
	{
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<tensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<tensor, symmTensor, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + '&' + gf2.name() + ')',
				gf1.dimensions() & gf2.dimensions()));
		tnbLib::dot(tRes.ref(), gf1, gf2);
		tgf2.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> operator &(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tgf1,
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<tensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<tensor, symmTensor, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '&' + gf2.name() + ')',
				gf1.dimensions() & gf2.dimensions()));
		tnbLib::dot(tRes.ref(), gf1, gf2);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> operator &(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<tensor, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<tensor, symmTensor, symmTensor, symmTensor, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '&' + gf2.name() + ')', gf1.dimensions() & gf2.dimensions()));
		tnbLib::dot(tRes.ref(), gf1, gf2);
		tgf1.clear();
		tgf2.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void dot(GeometricField<tensor, PatchField, GeoMesh>& res, const dimensioned<symmTensor>& dt1,
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf2)
	{
		tnbLib::dot(res.primitiveFieldRef(), dt1.value(), gf2.primitiveField());
		tnbLib::dot(res.boundaryFieldRef(), dt1.value(), gf2.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> operator &(const dimensioned<symmTensor>& dt1,
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<tensor, PatchField, GeoMesh>> tRes(
			GeometricField<tensor, PatchField, GeoMesh>::New('(' + dt1.name() + '&' + gf2.name() + ')', gf2.mesh(),
				dt1.dimensions() & gf2.dimensions()));
		tnbLib::dot(tRes.ref(), dt1, gf2);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> operator &(const symmTensor& t1,
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<symmTensor>(t1) & gf2;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> operator &(const dimensioned<symmTensor>& dt1,
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>&
		tgf2)
	{
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<tensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<tensor, symmTensor, PatchField, GeoMesh>::New(tgf2, '(' + dt1.name() + '&' + gf2.name() + ')',
				dt1.dimensions() & gf2.dimensions()));
		tnbLib::dot(tRes.ref(), dt1, gf2);
		tgf2.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> operator &(const symmTensor& t1,
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>&
		tgf2) {
		return dimensioned<symmTensor>(t1) & tgf2;
	}

	template<template<class> class PatchField, class GeoMesh>
	void dot(GeometricField<tensor, PatchField, GeoMesh>& res, const GeometricField<symmTensor, PatchField, GeoMesh>& gf1,
		const dimensioned<symmTensor>& dt2)
	{
		tnbLib::dot(res.primitiveFieldRef(), gf1.primitiveField(), dt2.value());
		tnbLib::dot(res.boundaryFieldRef(), gf1.boundaryField(), dt2.value());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> operator &(const GeometricField<symmTensor, PatchField, GeoMesh>& gf1,
		const dimensioned<symmTensor>& dt2)
	{
		tmp<GeometricField<tensor, PatchField, GeoMesh>> tRes(
			GeometricField<tensor, PatchField, GeoMesh>::New('(' + gf1.name() + '&' + dt2.name() + ')', gf1.mesh(),
				gf1.dimensions() & dt2.dimensions()));
		tnbLib::dot(tRes.ref(), gf1, dt2);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> operator &(const GeometricField<symmTensor, PatchField, GeoMesh>& gf1,
		const symmTensor& t2)
	{
		return gf1 & dimensioned<symmTensor>(t2);
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> operator &(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tgf1, const dimensioned<symmTensor>& dt2)
	{
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<tensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<tensor, symmTensor, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '&' + dt2.name() + ')',
				gf1.dimensions() & dt2.dimensions()));
		tnbLib::dot(tRes.ref(), gf1, dt2);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> operator &(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tgf1, const symmTensor& t2)
	{
		return tgf1 & dimensioned<symmTensor>(t2);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //