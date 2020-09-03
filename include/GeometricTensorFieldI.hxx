#pragma once
#include <tensorFieldField.hxx>
#include <GeometricFieldReuseFunctions.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<template<class> class PatchField, class GeoMesh>
	void T(GeometricField<tensor, PatchField, GeoMesh>& res, const GeometricField<tensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::T(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::T(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> T(const GeometricField<tensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<tensor, PatchField, GeoMesh>> tRes(
			GeometricField<tensor, PatchField, GeoMesh>::
			New("T" "(" + gf1.name() + ')', gf1.mesh(), transform(gf1.dimensions())));
		tnbLib::T(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> T(const tmp<GeometricField<tensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<tensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<tensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<tensor, tensor, PatchField, GeoMesh>::New(tgf1, "T" "(" + gf1.name() + ')',
				transform(gf1.dimensions())));
		tnbLib::T(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void tr(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<tensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::tr(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::tr(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> tr(const GeometricField<tensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New("tr" "(" + gf1.name() + ')', gf1.mesh(),
				transform(gf1.dimensions())));
		tnbLib::tr(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> tr(const tmp<GeometricField<tensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<tensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, tensor, PatchField, GeoMesh>::New(tgf1, "tr" "(" + gf1.name() + ')',
				transform(gf1.dimensions())));
		tnbLib::tr(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void sph(GeometricField<sphericalTensor, PatchField, GeoMesh>& res,
		const GeometricField<tensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::sph(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::sph(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> sph(const GeometricField<tensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> tRes(
			GeometricField<sphericalTensor, PatchField, GeoMesh>::New("sph" "(" + gf1.name() + ')', gf1.mesh(),
				transform(gf1.dimensions())));
		tnbLib::sph(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> sph(
		const tmp<GeometricField<tensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<tensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<sphericalTensor, tensor, PatchField, GeoMesh>::New(
				tgf1, "sph" "(" + gf1.name() + ')', transform(gf1.dimensions())));
		tnbLib::sph(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void symm(GeometricField<symmTensor, PatchField, GeoMesh>& res, const GeometricField<tensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::symm(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::symm(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> symm(const GeometricField<tensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<symmTensor, PatchField, GeoMesh>> tRes(
			GeometricField<symmTensor, PatchField, GeoMesh>::New("symm" "(" + gf1.name() + ')', gf1.mesh(),
				transform(gf1.dimensions())));
		tnbLib::symm(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> symm(const tmp<GeometricField<tensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<tensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<symmTensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<symmTensor, tensor, PatchField, GeoMesh>::New(tgf1, "symm" "(" + gf1.name() + ')',
				transform(gf1.dimensions())));
		tnbLib::symm(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void twoSymm(GeometricField<symmTensor, PatchField, GeoMesh>& res,
		const GeometricField<tensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::twoSymm(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::twoSymm(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> twoSymm(const GeometricField<tensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<symmTensor, PatchField, GeoMesh>> tRes(
			GeometricField<symmTensor, PatchField, GeoMesh>::New("twoSymm" "(" + gf1.name() + ')', gf1.mesh(),
				transform(gf1.dimensions())));
		tnbLib::twoSymm(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> twoSymm(
		const tmp<GeometricField<tensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<tensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<symmTensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<symmTensor, tensor, PatchField, GeoMesh>::New(tgf1, "twoSymm" "(" + gf1.name() + ')',
				transform(gf1.dimensions())));
		tnbLib::twoSymm(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void skew(GeometricField<tensor, PatchField, GeoMesh>& res, const GeometricField<tensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::skew(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::skew(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> skew(const GeometricField<tensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<tensor, PatchField, GeoMesh>> tRes(
			GeometricField<tensor, PatchField, GeoMesh>::New("skew" "(" + gf1.name() + ')', gf1.mesh(),
				transform(gf1.dimensions())));
		tnbLib::skew(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> skew(const tmp<GeometricField<tensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<tensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<tensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<tensor, tensor, PatchField, GeoMesh>::New(tgf1, "skew" "(" + gf1.name() + ')',
				transform(gf1.dimensions())));
		tnbLib::skew(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void dev(GeometricField<tensor, PatchField, GeoMesh>& res, const GeometricField<tensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::dev(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::dev(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> dev(const GeometricField<tensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<tensor, PatchField, GeoMesh>> tRes(
			GeometricField<tensor, PatchField, GeoMesh>::New("dev" "(" + gf1.name() + ')', gf1.mesh(),
				transform(gf1.dimensions())));
		tnbLib::dev(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> dev(const tmp<GeometricField<tensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<tensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<tensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<tensor, tensor, PatchField, GeoMesh>::New(tgf1, "dev" "(" + gf1.name() + ')',
				transform(gf1.dimensions())));
		tnbLib::dev(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void dev2(GeometricField<tensor, PatchField, GeoMesh>& res, const GeometricField<tensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::dev2(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::dev2(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> dev2(const GeometricField<tensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<tensor, PatchField, GeoMesh>> tRes(
			GeometricField<tensor, PatchField, GeoMesh>::New("dev2" "(" + gf1.name() + ')', gf1.mesh(),
				transform(gf1.dimensions())));
		tnbLib::dev2(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> dev2(const tmp<GeometricField<tensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<tensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<tensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<tensor, tensor, PatchField, GeoMesh>::New(tgf1, "dev2" "(" + gf1.name() + ')',
				transform(gf1.dimensions())));
		tnbLib::dev2(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void det(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<tensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::det(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::det(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> det(const GeometricField<tensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New("det" "(" + gf1.name() + ')', gf1.mesh(), pow3(gf1.dimensions())));
		tnbLib::det(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> det(const tmp<GeometricField<tensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<tensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, tensor, PatchField, GeoMesh>::New(tgf1, "det" "(" + gf1.name() + ')',
				pow3(gf1.dimensions())));
		tnbLib::det(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void cof(GeometricField<tensor, PatchField, GeoMesh>& res, const GeometricField<tensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::cof(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::cof(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> cof(const GeometricField<tensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<tensor, PatchField, GeoMesh>> tRes(
			GeometricField<tensor, PatchField, GeoMesh>::New("cof" "(" + gf1.name() + ')', gf1.mesh(), pow2(gf1.dimensions())));
		tnbLib::cof(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> cof(const tmp<GeometricField<tensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<tensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<tensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<tensor, tensor, PatchField, GeoMesh>::New(tgf1, "cof" "(" + gf1.name() + ')',
				pow2(gf1.dimensions())));
		tnbLib::cof(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void inv(GeometricField<tensor, PatchField, GeoMesh>& res, const GeometricField<tensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::inv(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::inv(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> inv(const GeometricField<tensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<tensor, PatchField, GeoMesh>> tRes(
			GeometricField<tensor, PatchField, GeoMesh>::New("inv" "(" + gf1.name() + ')', gf1.mesh(), inv(gf1.dimensions())));
		tnbLib::inv(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> inv(const tmp<GeometricField<tensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<tensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<tensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<tensor, tensor, PatchField, GeoMesh>::New(tgf1, "inv" "(" + gf1.name() + ')',
				inv(gf1.dimensions())));
		tnbLib::inv(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void eigenValues(GeometricField<vector, PatchField, GeoMesh>& res,
		const GeometricField<tensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::eigenValues(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::eigenValues(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector, PatchField, GeoMesh>> eigenValues(const GeometricField<tensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<vector, PatchField, GeoMesh>> tRes(
			GeometricField<vector, PatchField, GeoMesh>::New("eigenValues" "(" + gf1.name() + ')', gf1.mesh(),
				transform(gf1.dimensions())));
		tnbLib::eigenValues(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector, PatchField, GeoMesh>> eigenValues(
		const tmp<GeometricField<tensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<tensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector, tensor, PatchField, GeoMesh>::New(tgf1, "eigenValues" "(" + gf1.name() + ')',
				transform(gf1.dimensions())));
		tnbLib::eigenValues(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void eigenVectors(GeometricField<tensor, PatchField, GeoMesh>& res,
		const GeometricField<tensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::eigenVectors(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::eigenVectors(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> eigenVectors(const GeometricField<tensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<tensor, PatchField, GeoMesh>> tRes(
			GeometricField<tensor, PatchField, GeoMesh>::New("eigenVectors" "(" + gf1.name() + ')', gf1.mesh(),
				sign(gf1.dimensions())));
		tnbLib::eigenVectors(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> eigenVectors(
		const tmp<GeometricField<tensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<tensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<tensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<tensor, tensor, PatchField, GeoMesh>::New(tgf1, "eigenVectors" "(" + gf1.name() + ')',
				sign(gf1.dimensions())));
		tnbLib::eigenVectors(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void eigenValues(GeometricField<vector, PatchField, GeoMesh>& res,
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::eigenValues(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::eigenValues(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector, PatchField, GeoMesh>> eigenValues(
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<vector, PatchField, GeoMesh>> tRes(
			GeometricField<vector, PatchField, GeoMesh>::New("eigenValues" "(" + gf1.name() + ')', gf1.mesh(),
				transform(gf1.dimensions())));
		tnbLib::eigenValues(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector, PatchField, GeoMesh>> eigenValues(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector, symmTensor, PatchField, GeoMesh>::New(tgf1, "eigenValues" "(" + gf1.name() + ')',
				transform(gf1.dimensions())));
		tnbLib::eigenValues(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void eigenVectors(GeometricField<symmTensor, PatchField, GeoMesh>& res,
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::eigenVectors(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::eigenVectors(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> eigenVectors(
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<symmTensor, PatchField, GeoMesh>> tRes(
			GeometricField<symmTensor, PatchField, GeoMesh>::New("eigenVectors" "(" + gf1.name() + ')', gf1.mesh(),
				sign(gf1.dimensions())));
		tnbLib::eigenVectors(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> eigenVectors(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<symmTensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<symmTensor, symmTensor, PatchField, GeoMesh>::New(
				tgf1, "eigenVectors" "(" + gf1.name() + ')', sign(gf1.dimensions())));
		tnbLib::eigenVectors(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}


	// * * * * * * * * * * * * * * * global operators  * * * * * * * * * * * * * //

	template<template<class> class PatchField, class GeoMesh>
	void hdual(GeometricField<vector, PatchField, GeoMesh>& res, const GeometricField<tensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::hdual(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::hdual(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector, PatchField, GeoMesh>> operator *(const GeometricField<tensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<vector, PatchField, GeoMesh>> tRes(
			GeometricField<vector, PatchField, GeoMesh>::New("*" + gf1.name(), gf1.mesh(), transform(gf1.dimensions())));
		tnbLib::hdual(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<tensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<tensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector, tensor, PatchField, GeoMesh>::
			New(tgf1, "*" + gf1.name(), transform(gf1.dimensions())));
		tnbLib::hdual(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void hdual(GeometricField<tensor, PatchField, GeoMesh>& res, const GeometricField<vector, PatchField, GeoMesh>& gf1)
	{
		tnbLib::hdual(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::hdual(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> operator *(const GeometricField<vector, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<tensor, PatchField, GeoMesh>> tRes(
			GeometricField<tensor, PatchField, GeoMesh>::New("*" + gf1.name(), gf1.mesh(), transform(gf1.dimensions())));
		tnbLib::hdual(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<vector, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<vector, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<tensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<tensor, vector, PatchField, GeoMesh>::
			New(tgf1, "*" + gf1.name(), transform(gf1.dimensions())));
		tnbLib::hdual(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<vector, PatchField, GeoMesh>& res, const GeometricField<vector, PatchField, GeoMesh>& gf1,
		const GeometricField<tensor, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.primitiveFieldRef(), gf1.primitiveField(), gf2.primitiveField());
		tnbLib::divide(res.boundaryFieldRef(), gf1.boundaryField(), gf2.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector, PatchField, GeoMesh>> operator /(const GeometricField<vector, PatchField, GeoMesh>& gf1,
		const GeometricField<tensor, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector, PatchField, GeoMesh>> tRes(
			GeometricField<vector, PatchField, GeoMesh>::New('(' + gf1.name() + '|' + gf2.name() + ')', gf1.mesh(),
				gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes.ref(), gf1, gf2);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector, PatchField, GeoMesh>> operator /(const GeometricField<vector, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<tensor, PatchField, GeoMesh>>&
		tgf2)
	{
		const GeometricField<tensor, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector, tensor, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + '|' + gf2.name() + ')',
				gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes.ref(), gf1, gf2);
		tgf2.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<vector, PatchField, GeoMesh>>& tgf1, const GeometricField<tensor, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<vector, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector, vector, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '|' + gf2.name() + ')',
				gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes.ref(), gf1, gf2);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<vector, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<tensor, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<vector, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<tensor, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<vector, vector, vector, tensor, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes.ref(), gf1, gf2);
		tgf1.clear();
		tgf2.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<vector, PatchField, GeoMesh>& res, const dimensioned<vector>& dt1,
		const GeometricField<tensor, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.primitiveFieldRef(), dt1.value(), gf2.primitiveField());
		tnbLib::divide(res.boundaryFieldRef(), dt1.value(), gf2.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector, PatchField, GeoMesh>> operator /(const dimensioned<vector>& dt1,
		const GeometricField<tensor, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector, PatchField, GeoMesh>> tRes(
			GeometricField<vector, PatchField, GeoMesh>::New('(' + dt1.name() + '|' + gf2.name() + ')', gf2.mesh(),
				dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes.ref(), dt1, gf2);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector, PatchField, GeoMesh>> operator /(const vector& t1,
		const GeometricField<tensor, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<vector>(t1) / gf2;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector, PatchField, GeoMesh>> operator /(const dimensioned<vector>& dt1,
		const tmp<GeometricField<tensor, PatchField, GeoMesh>>&
		tgf2)
	{
		const GeometricField<tensor, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector, tensor, PatchField, GeoMesh>::New(tgf2, '(' + dt1.name() + '|' + gf2.name() + ')',
				dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes.ref(), dt1, gf2);
		tgf2.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector, PatchField, GeoMesh>> operator /(const vector& t1,
		const tmp<GeometricField<tensor, PatchField, GeoMesh>>&
		tgf2) {
		return dimensioned<vector>(t1) / tgf2;
	}

	template<template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<vector, PatchField, GeoMesh>& res, const GeometricField<vector, PatchField, GeoMesh>& gf1,
		const dimensioned<tensor>& dt2)
	{
		tnbLib::divide(res.primitiveFieldRef(), gf1.primitiveField(), dt2.value());
		tnbLib::divide(res.boundaryFieldRef(), gf1.boundaryField(), dt2.value());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector, PatchField, GeoMesh>> operator /(const GeometricField<vector, PatchField, GeoMesh>& gf1,
		const dimensioned<tensor>& dt2)
	{
		tmp<GeometricField<vector, PatchField, GeoMesh>> tRes(
			GeometricField<vector, PatchField, GeoMesh>::New('(' + gf1.name() + '|' + dt2.name() + ')', gf1.mesh(),
				gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes.ref(), gf1, dt2);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector, PatchField, GeoMesh>> operator /(const GeometricField<vector, PatchField, GeoMesh>& gf1,
		const tensor& t2) {
		return gf1 / dimensioned<tensor>(t2);
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<vector, PatchField, GeoMesh>>& tgf1, const dimensioned<tensor>& dt2)
	{
		const GeometricField<vector, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector, vector, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '|' + dt2.name() + ')',
				gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes.ref(), gf1, dt2);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<vector, PatchField, GeoMesh>>& tgf1, const tensor& t2)
	{
		return tgf1 / dimensioned<tensor>(t2);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //