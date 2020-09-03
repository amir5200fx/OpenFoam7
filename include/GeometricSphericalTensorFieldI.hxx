#pragma once
#include <GeometricFieldReuseFunctions.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * global functions  * * * * * * * * * * * * * //

	template<template<class> class PatchField, class GeoMesh>
	void tr(GeometricField<scalar, PatchField, GeoMesh>& res,
		const GeometricField<sphericalTensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::tr(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::tr(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> tr(const GeometricField<sphericalTensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New("tr" "(" + gf1.name() + ')', gf1.mesh(),
				transform(gf1.dimensions())));
		tnbLib::tr(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> tr(
		const tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<sphericalTensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, sphericalTensor, PatchField, GeoMesh>::New(
				tgf1, "tr" "(" + gf1.name() + ')', transform(gf1.dimensions())));
		tnbLib::tr(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void sph(GeometricField<sphericalTensor, PatchField, GeoMesh>& res,
		const GeometricField<sphericalTensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::sph(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::sph(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> sph(
		const GeometricField<sphericalTensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> tRes(
			GeometricField<sphericalTensor, PatchField, GeoMesh>::New("sph" "(" + gf1.name() + ')', gf1.mesh(),
				transform(gf1.dimensions())));
		tnbLib::sph(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> sph(
		const tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<sphericalTensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<sphericalTensor, sphericalTensor, PatchField, GeoMesh>::New(
				tgf1, "sph" "(" + gf1.name() + ')', transform(gf1.dimensions())));
		tnbLib::sph(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void det(GeometricField<scalar, PatchField, GeoMesh>& res,
		const GeometricField<sphericalTensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::det(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::det(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> det(const GeometricField<sphericalTensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New("det" "(" + gf1.name() + ')', gf1.mesh(), pow3(gf1.dimensions())));
		tnbLib::det(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> det(
		const tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<sphericalTensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, sphericalTensor, PatchField, GeoMesh>::New(
				tgf1, "det" "(" + gf1.name() + ')', pow3(gf1.dimensions())));
		tnbLib::det(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void inv(GeometricField<sphericalTensor, PatchField, GeoMesh>& res,
		const GeometricField<sphericalTensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::inv(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::inv(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> inv(
		const GeometricField<sphericalTensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> tRes(
			GeometricField<sphericalTensor, PatchField, GeoMesh>::New("inv" "(" + gf1.name() + ')', gf1.mesh(),
				inv(gf1.dimensions())));
		tnbLib::inv(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> inv(
		const tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<sphericalTensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<sphericalTensor, sphericalTensor, PatchField, GeoMesh>::New(
				tgf1, "inv" "(" + gf1.name() + ')', inv(gf1.dimensions())));
		tnbLib::inv(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}


	template<template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<sphericalTensor, PatchField, GeoMesh>& res,
		const GeometricField<scalar, PatchField, GeoMesh>& gf1,
		const GeometricField<sphericalTensor, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.primitiveFieldRef(), gf1.primitiveField(), gf2.primitiveField());
		tnbLib::divide(res.boundaryFieldRef(), gf1.boundaryField(), gf2.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> operator /(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1,
		const GeometricField<sphericalTensor, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> tRes(
			GeometricField<sphericalTensor, PatchField, GeoMesh>::New('(' + gf1.name() + '|' + gf2.name() + ')', gf1.mesh(),
				gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes.ref(), gf1, gf2);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> operator /(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<sphericalTensor, sphericalTensor, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes.ref(), gf1, gf2);
		tgf2.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1,
		const GeometricField<sphericalTensor, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<sphericalTensor, scalar, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes.ref(), gf1, gf2);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<sphericalTensor, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<sphericalTensor, scalar, scalar, sphericalTensor, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes.ref(), gf1, gf2);
		tgf1.clear();
		tgf2.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<sphericalTensor, PatchField, GeoMesh>& res, const dimensioned<scalar>& dt1,
		const GeometricField<sphericalTensor, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.primitiveFieldRef(), dt1.value(), gf2.primitiveField());
		tnbLib::divide(res.boundaryFieldRef(), dt1.value(), gf2.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> operator /(const dimensioned<scalar>& dt1,
		const GeometricField<
		sphericalTensor, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> tRes(
			GeometricField<sphericalTensor, PatchField, GeoMesh>::New('(' + dt1.name() + '|' + gf2.name() + ')', gf2.mesh(),
				dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes.ref(), dt1, gf2);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> operator /(const scalar& t1,
		const GeometricField<
		sphericalTensor, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<scalar>(t1) / gf2;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> operator /(const dimensioned<scalar>& dt1,
		const tmp<GeometricField<
		sphericalTensor, PatchField, GeoMesh>>&tgf2)
	{
		const GeometricField<sphericalTensor, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<sphericalTensor, sphericalTensor, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '|' + gf2.name() + ')', dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes.ref(), dt1, gf2);
		tgf2.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> operator /(const scalar& t1,
		const tmp<GeometricField<
		sphericalTensor, PatchField, GeoMesh>>&tgf2)
	{
		return dimensioned<scalar>(t1) / tgf2;
	}

	template<template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<sphericalTensor, PatchField, GeoMesh>& res,
		const GeometricField<scalar, PatchField, GeoMesh>& gf1, const dimensioned<sphericalTensor>& dt2)
	{
		tnbLib::divide(res.primitiveFieldRef(), gf1.primitiveField(), dt2.value());
		tnbLib::divide(res.boundaryFieldRef(), gf1.boundaryField(), dt2.value());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> operator /(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1, const dimensioned<sphericalTensor>& dt2)
	{
		tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> tRes(
			GeometricField<sphericalTensor, PatchField, GeoMesh>::New('(' + gf1.name() + '|' + dt2.name() + ')', gf1.mesh(),
				gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes.ref(), gf1, dt2);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> operator /(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1, const sphericalTensor& t2)
	{
		return gf1 / dimensioned<sphericalTensor>(t2);
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const dimensioned<sphericalTensor>& dt2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<sphericalTensor, scalar, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '|' + dt2.name() + ')', gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes.ref(), gf1, dt2);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const sphericalTensor& t2)
	{
		return tgf1 / dimensioned<sphericalTensor>(t2);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //