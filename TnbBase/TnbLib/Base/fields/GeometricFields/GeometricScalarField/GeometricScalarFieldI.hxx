#pragma once
#include <GeometricFieldReuseFunctions.hxx>  // added by amir
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<template<class> class PatchField, class GeoMesh>
	void stabilise
	(
		GeometricField<scalar, PatchField, GeoMesh>& result,
		const GeometricField<scalar, PatchField, GeoMesh>& gsf,
		const dimensioned<scalar>& ds
	)
	{
		stabilise(result.primitiveFieldRef(), gsf.primitiveField(), ds.value());
		stabilise(result.boundaryFieldRef(), gsf.boundaryField(), ds.value());
	}


	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> stabilise
	(
		const GeometricField<scalar, PatchField, GeoMesh>& gsf,
		const dimensioned<scalar>& ds
	)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes
		(
			GeometricField<scalar, PatchField, GeoMesh>::New
			(
				"stabilise(" + gsf.name() + ',' + ds.name() + ')',
				gsf.mesh(),
				ds.dimensions() + gsf.dimensions()
			)
		);

		stabilise(tRes.ref(), gsf, ds);

		return tRes;
	}


	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> stabilise
	(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgsf,
		const dimensioned<scalar>& ds
	)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gsf = tgsf();

		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes
		(
			New
			(
				tgsf,
				"stabilise(" + gsf.name() + ',' + ds.name() + ')',
				ds.dimensions() + gsf.dimensions()
			)
		);

		stabilise(tRes.ref(), gsf, ds);

		tgsf.clear();

		return tRes;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<template<class> class PatchField, class GeoMesh>
	void add(GeometricField<scalar, PatchField, GeoMesh>& res, const dimensioned<scalar>& dt1,
		const GeometricField<scalar, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(res.primitiveFieldRef(), dt1.value(), gf2.primitiveField());
		tnbLib::add(res.boundaryFieldRef(), dt1.value(), gf2.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator +(const dimensioned<scalar>& dt1,
		const GeometricField<scalar, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New('(' + dt1.name() + '+' + gf2.name() + ')', gf2.mesh(),
				dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes.ref(), dt1, gf2);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator +(const scalar& t1,
		const GeometricField<scalar, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<scalar>(t1) + gf2;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator +(const dimensioned<scalar>& dt1,
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>&
		tgf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf2, '(' + dt1.name() + '+' + gf2.name() + ')',
				dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes.ref(), dt1, gf2);
		tgf2.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator +(const scalar& t1,
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>&
		tgf2) {
		return dimensioned<scalar>(t1) + tgf2;
	}

	template<template<class> class PatchField, class GeoMesh>
	void add(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1,
		const dimensioned<scalar>& dt2)
	{
		tnbLib::add(res.primitiveFieldRef(), gf1.primitiveField(), dt2.value());
		tnbLib::add(res.boundaryFieldRef(), gf1.boundaryField(), dt2.value());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator +(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
		const dimensioned<scalar>& dt2)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New('(' + gf1.name() + '+' + dt2.name() + ')', gf1.mesh(),
				gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes.ref(), gf1, dt2);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator +(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
		const scalar& t2) {
		return gf1 + dimensioned<scalar>(t2);
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const dimensioned<scalar>& dt2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '+' + dt2.name() + ')',
				gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes.ref(), gf1, dt2);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const scalar& t2)
	{
		return tgf1 + dimensioned<scalar>(t2);
	}

	template<template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<scalar, PatchField, GeoMesh>& res, const dimensioned<scalar>& dt1,
		const GeometricField<scalar, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(res.primitiveFieldRef(), dt1.value(), gf2.primitiveField());
		tnbLib::subtract(res.boundaryFieldRef(), dt1.value(), gf2.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator -(const dimensioned<scalar>& dt1,
		const GeometricField<scalar, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New('(' + dt1.name() + '-' + gf2.name() + ')', gf2.mesh(),
				dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes.ref(), dt1, gf2);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator -(const scalar& t1,
		const GeometricField<scalar, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<scalar>(t1) - gf2;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator -(const dimensioned<scalar>& dt1,
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>&
		tgf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf2, '(' + dt1.name() + '-' + gf2.name() + ')',
				dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes.ref(), dt1, gf2);
		tgf2.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator -(const scalar& t1,
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>&
		tgf2) {
		return dimensioned<scalar>(t1) - tgf2;
	}

	template<template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1,
		const dimensioned<scalar>& dt2)
	{
		tnbLib::subtract(res.primitiveFieldRef(), gf1.primitiveField(), dt2.value());
		tnbLib::subtract(res.boundaryFieldRef(), gf1.boundaryField(), dt2.value());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator -(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
		const dimensioned<scalar>& dt2)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New('(' + gf1.name() + '-' + dt2.name() + ')', gf1.mesh(),
				gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes.ref(), gf1, dt2);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator -(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
		const scalar& t2) {
		return gf1 - dimensioned<scalar>(t2);
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const dimensioned<scalar>& dt2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '-' + dt2.name() + ')',
				gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes.ref(), gf1, dt2);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const scalar& t2)
	{
		return tgf1 - dimensioned<scalar>(t2);
	}


	template<template<class> class PatchField, class GeoMesh>
	void multiply(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1,
		const GeometricField<scalar, PatchField, GeoMesh>& gf2)
	{
		tnbLib::multiply(res.primitiveFieldRef(), gf1.primitiveField(), gf2.primitiveField());
		tnbLib::multiply(res.boundaryFieldRef(), gf1.boundaryField(), gf2.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator *(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
		const GeometricField<scalar, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New('(' + gf1.name() + '*' + gf2.name() + ')', gf1.mesh(),
				gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes.ref(), gf1, gf2);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator *(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>&
		tgf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + '*' + gf2.name() + ')',
				gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes.ref(), gf1, gf2);
		tgf2.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const GeometricField<scalar, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '*' + gf2.name() + ')',
				gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes.ref(), gf1, gf2);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<scalar, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<scalar, scalar, scalar, scalar, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '*' + gf2.name() + ')', gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes.ref(), gf1, gf2);
		tgf1.clear();
		tgf2.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1,
		const GeometricField<scalar, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.primitiveFieldRef(), gf1.primitiveField(), gf2.primitiveField());
		tnbLib::divide(res.boundaryFieldRef(), gf1.boundaryField(), gf2.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator /(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
		const GeometricField<scalar, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New('(' + gf1.name() + '|' + gf2.name() + ')', gf1.mesh(),
				gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes.ref(), gf1, gf2);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator /(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>&
		tgf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + '|' + gf2.name() + ')',
				gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes.ref(), gf1, gf2);
		tgf2.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const GeometricField<scalar, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '|' + gf2.name() + ')',
				gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes.ref(), gf1, gf2);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<scalar, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<scalar, scalar, scalar, scalar, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes.ref(), gf1, gf2);
		tgf1.clear();
		tgf2.clear();
		return tRes;
	}


	template<template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<scalar, PatchField, GeoMesh>& res, const dimensioned<scalar>& dt1,
		const GeometricField<scalar, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.primitiveFieldRef(), dt1.value(), gf2.primitiveField());
		tnbLib::divide(res.boundaryFieldRef(), dt1.value(), gf2.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator /(const dimensioned<scalar>& dt1,
		const GeometricField<scalar, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New('(' + dt1.name() + '|' + gf2.name() + ')', gf2.mesh(),
				dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes.ref(), dt1, gf2);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator /(const scalar& t1,
		const GeometricField<scalar, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<scalar>(t1) / gf2;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator /(const dimensioned<scalar>& dt1,
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>&
		tgf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf2, '(' + dt1.name() + '|' + gf2.name() + ')',
				dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes.ref(), dt1, gf2);
		tgf2.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator /(const scalar& t1,
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>&
		tgf2) {
		return dimensioned<scalar>(t1) / tgf2;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<template<class> class PatchField, class GeoMesh>
	void pow
	(
		GeometricField<scalar, PatchField, GeoMesh>& Pow,
		const GeometricField<scalar, PatchField, GeoMesh>& gsf1,
		const GeometricField<scalar, PatchField, GeoMesh>& gsf2
	)
	{
		pow(Pow.primitiveFieldRef(), gsf1.primitiveField(), gsf2.primitiveField());
		pow(Pow.boundaryFieldRef(), gsf1.boundaryField(), gsf2.boundaryField());
	}


	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow
	(
		const GeometricField<scalar, PatchField, GeoMesh>& gsf1,
		const GeometricField<scalar, PatchField, GeoMesh>& gsf2
	)
	{
		if (!gsf1.dimensions().dimensionless())
		{
			FatalErrorInFunction
				<< "Base field is not dimensionless: " << gsf1.dimensions()
				<< exit(FatalError);
		}

		if (!gsf2.dimensions().dimensionless())
		{
			FatalErrorInFunction
				<< "Exponent field is not dimensionless: " << gsf2.dimensions()
				<< exit(FatalError);
		}

		tmp<GeometricField<scalar, PatchField, GeoMesh>> tPow
		(
			GeometricField<scalar, PatchField, GeoMesh>::New
			(
				"pow(" + gsf1.name() + ',' + gsf2.name() + ')',
				gsf1.mesh(),
				dimless
			)
		);

		pow(tPow.ref(), gsf1, gsf2);

		return tPow;
	}


	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow
	(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgsf1,
		const GeometricField<scalar, PatchField, GeoMesh>& gsf2
	)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gsf1 = tgsf1();

		if (!gsf1.dimensions().dimensionless())
		{
			FatalErrorInFunction
				<< "Base field is not dimensionless: " << gsf1.dimensions()
				<< exit(FatalError);
		}

		if (!gsf2.dimensions().dimensionless())
		{
			FatalErrorInFunction
				<< "Exponent field is not dimensionless: " << gsf2.dimensions()
				<< exit(FatalError);
		}

		tmp<GeometricField<scalar, PatchField, GeoMesh>> tPow
		(
			New
			(
				tgsf1,
				"pow(" + gsf1.name() + ',' + gsf2.name() + ')',
				dimless
			)
		);

		pow(tPow.ref(), gsf1, gsf2);

		tgsf1.clear();

		return tPow;
	}


	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow
	(
		const GeometricField<scalar, PatchField, GeoMesh>& gsf1,
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgsf2
	)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gsf2 = tgsf2();

		if (!gsf1.dimensions().dimensionless())
		{
			FatalErrorInFunction
				<< "Base field is not dimensionless: " << gsf1.dimensions()
				<< exit(FatalError);
		}

		if (!gsf2.dimensions().dimensionless())
		{
			FatalErrorInFunction
				<< "Exponent field is not dimensionless: " << gsf2.dimensions()
				<< exit(FatalError);
		}

		tmp<GeometricField<scalar, PatchField, GeoMesh>> tPow
		(
			New
			(
				tgsf2,
				"pow(" + gsf1.name() + ',' + gsf2.name() + ')',
				dimless
			)
		);

		pow(tPow.ref(), gsf1, gsf2);

		tgsf2.clear();

		return tPow;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow
	(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgsf1,
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgsf2
	)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gsf1 = tgsf1();
		const GeometricField<scalar, PatchField, GeoMesh>& gsf2 = tgsf2();

		if (!gsf1.dimensions().dimensionless())
		{
			FatalErrorInFunction
				<< "Base field is not dimensionless: " << gsf1.dimensions()
				<< exit(FatalError);
		}

		if (!gsf2.dimensions().dimensionless())
		{
			FatalErrorInFunction
				<< "Exponent field is not dimensionless: " << gsf2.dimensions()
				<< exit(FatalError);
		}

		tmp<GeometricField<scalar, PatchField, GeoMesh>> tPow
		(
			reuseTmpTmpGeometricField
			<scalar, scalar, scalar, scalar, PatchField, GeoMesh>::New
			(
				tgsf1,
				tgsf2,
				"pow(" + gsf1.name() + ',' + gsf2.name() + ')',
				dimless
			)
		);

		pow(tPow.ref(), gsf1, gsf2);

		tgsf1.clear();
		tgsf2.clear();

		return tPow;
	}


	template<template<class> class PatchField, class GeoMesh>
	void pow
	(
		GeometricField<scalar, PatchField, GeoMesh>& tPow,
		const GeometricField<scalar, PatchField, GeoMesh>& gsf,
		const dimensioned<scalar>& ds
	)
	{
		pow(tPow.primitiveFieldRef(), gsf.primitiveField(), ds.value());
		pow(tPow.boundaryFieldRef(), gsf.boundaryField(), ds.value());
	}


	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow
	(
		const GeometricField<scalar, PatchField, GeoMesh>& gsf,
		const dimensionedScalar& ds
	)
	{
		if (!ds.dimensions().dimensionless())
		{
			FatalErrorInFunction
				<< "Exponent is not dimensionless: " << ds.dimensions()
				<< exit(FatalError);
		}

		tmp<GeometricField<scalar, PatchField, GeoMesh>> tPow
		(
			GeometricField<scalar, PatchField, GeoMesh>::New
			(
				"pow(" + gsf.name() + ',' + ds.name() + ')',
				gsf.mesh(),
				pow(gsf.dimensions(), ds)
			)
		);

		pow(tPow.ref(), gsf, ds);

		return tPow;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow
	(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgsf,
		const dimensionedScalar& ds
	)
	{
		if (!ds.dimensions().dimensionless())
		{
			FatalErrorInFunction
				<< "Exponent is not dimensionless: " << ds.dimensions()
				<< exit(FatalError);
		}

		const GeometricField<scalar, PatchField, GeoMesh>& gsf = tgsf();

		tmp<GeometricField<scalar, PatchField, GeoMesh>> tPow
		(
			New
			(
				tgsf,
				"pow(" + gsf.name() + ',' + ds.name() + ')',
				pow(gsf.dimensions(), ds)
			)
		);

		pow(tPow.ref(), gsf, ds);

		tgsf.clear();

		return tPow;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow
	(
		const GeometricField<scalar, PatchField, GeoMesh>& gsf,
		const scalar& s
	)
	{
		return pow(gsf, dimensionedScalar(s));
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow
	(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgsf,
		const scalar& s
	)
	{
		return pow(tgsf, dimensionedScalar(s));
	}


	template<template<class> class PatchField, class GeoMesh>
	void pow
	(
		GeometricField<scalar, PatchField, GeoMesh>& tPow,
		const dimensioned<scalar>& ds,
		const GeometricField<scalar, PatchField, GeoMesh>& gsf
	)
	{
		pow(tPow.primitiveFieldRef(), ds.value(), gsf.primitiveField());
		pow(tPow.boundaryFieldRef(), ds.value(), gsf.boundaryField());
	}


	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow
	(
		const dimensionedScalar& ds,
		const GeometricField<scalar, PatchField, GeoMesh>& gsf
	)
	{
		if (!ds.dimensions().dimensionless())
		{
			FatalErrorInFunction
				<< "Base scalar is not dimensionless: " << ds.dimensions()
				<< exit(FatalError);
		}

		if (!gsf.dimensions().dimensionless())
		{
			FatalErrorInFunction
				<< "Exponent field is not dimensionless: " << gsf.dimensions()
				<< exit(FatalError);
		}

		tmp<GeometricField<scalar, PatchField, GeoMesh>> tPow
		(
			GeometricField<scalar, PatchField, GeoMesh>::New
			(
				"pow(" + ds.name() + ',' + gsf.name() + ')',
				gsf.mesh(),
				dimless
			)
		);

		pow(tPow.ref(), ds, gsf);

		return tPow;
	}


	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow
	(
		const dimensionedScalar& ds,
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgsf
	)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gsf = tgsf();

		if (!ds.dimensions().dimensionless())
		{
			FatalErrorInFunction
				<< "Base scalar is not dimensionless: " << ds.dimensions()
				<< exit(FatalError);
		}

		if (!gsf.dimensions().dimensionless())
		{
			FatalErrorInFunction
				<< "Exponent field is not dimensionless: " << gsf.dimensions()
				<< exit(FatalError);
		}

		tmp<GeometricField<scalar, PatchField, GeoMesh>> tPow
		(
			New
			(
				tgsf,
				"pow(" + ds.name() + ',' + gsf.name() + ')',
				dimless
			)
		);

		pow(tPow.ref(), ds, gsf);

		tgsf.clear();

		return tPow;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow
	(
		const scalar& s,
		const GeometricField<scalar, PatchField, GeoMesh>& gsf
	)
	{
		return pow(dimensionedScalar(s), gsf);
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow
	(
		const scalar& s,
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgsf
	)
	{
		return pow(dimensionedScalar(s), tgsf);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<template<class> class PatchField, class GeoMesh>
	void atan2
	(
		GeometricField<scalar, PatchField, GeoMesh>& Atan2,
		const GeometricField<scalar, PatchField, GeoMesh>& gsf1,
		const GeometricField<scalar, PatchField, GeoMesh>& gsf2
	)
	{
		atan2
		(
			Atan2.primitiveFieldRef(),
			gsf1.primitiveField(),
			gsf2.primitiveField()
		);
		atan2
		(
			Atan2.boundaryFieldRef(),
			gsf1.boundaryField(),
			gsf2.boundaryField()
		);
	}


	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> atan2
	(
		const GeometricField<scalar, PatchField, GeoMesh>& gsf1,
		const GeometricField<scalar, PatchField, GeoMesh>& gsf2
	)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tAtan2
		(
			GeometricField<scalar, PatchField, GeoMesh>::New
			(
				"atan2(" + gsf1.name() + ',' + gsf2.name() + ')',
				gsf1.mesh(),
				atan2(gsf1.dimensions(), gsf2.dimensions())
			)
		);

		atan2(tAtan2.ref(), gsf1, gsf2);

		return tAtan2;
	}


	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> atan2
	(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgsf1,
		const GeometricField<scalar, PatchField, GeoMesh>& gsf2
	)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gsf1 = tgsf1();

		tmp<GeometricField<scalar, PatchField, GeoMesh>> tAtan2
		(
			New
			(
				tgsf1,
				"atan2(" + gsf1.name() + ',' + gsf2.name() + ')',
				atan2(gsf1.dimensions(), gsf2.dimensions())
			)
		);

		atan2(tAtan2.ref(), gsf1, gsf2);

		tgsf1.clear();

		return tAtan2;
	}


	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> atan2
	(
		const GeometricField<scalar, PatchField, GeoMesh>& gsf1,
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgsf2
	)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gsf2 = tgsf2();

		tmp<GeometricField<scalar, PatchField, GeoMesh>> tAtan2
		(
			New
			(
				tgsf2,
				"atan2(" + gsf1.name() + ',' + gsf2.name() + ')',
				atan2(gsf1.dimensions(), gsf2.dimensions())
			)
		);

		atan2(tAtan2.ref(), gsf1, gsf2);

		tgsf2.clear();

		return tAtan2;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> atan2
	(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgsf1,
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgsf2
	)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gsf1 = tgsf1();
		const GeometricField<scalar, PatchField, GeoMesh>& gsf2 = tgsf2();

		tmp<GeometricField<scalar, PatchField, GeoMesh>> tAtan2
		(
			reuseTmpTmpGeometricField
			<scalar, scalar, scalar, scalar, PatchField, GeoMesh>::New
			(
				tgsf1,
				tgsf2,
				"atan2(" + gsf1.name() + ',' + gsf2.name() + ')',
				atan2(gsf1.dimensions(), gsf2.dimensions())
			)
		);

		atan2(tAtan2.ref(), gsf1, gsf2);

		tgsf1.clear();
		tgsf2.clear();

		return tAtan2;
	}


	template<template<class> class PatchField, class GeoMesh>
	void atan2
	(
		GeometricField<scalar, PatchField, GeoMesh>& tAtan2,
		const GeometricField<scalar, PatchField, GeoMesh>& gsf,
		const dimensioned<scalar>& ds
	)
	{
		atan2(tAtan2.primitiveFieldRef(), gsf.primitiveField(), ds.value());
		atan2(tAtan2.boundaryFieldRef(), gsf.boundaryField(), ds.value());
	}


	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> atan2
	(
		const GeometricField<scalar, PatchField, GeoMesh>& gsf,
		const dimensionedScalar& ds
	)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tAtan2
		(
			GeometricField<scalar, PatchField, GeoMesh>::New
			(
				"atan2(" + gsf.name() + ',' + ds.name() + ')',
				gsf.mesh(),
				atan2(gsf.dimensions(), ds)
			)
		);

		atan2(tAtan2.ref(), gsf, ds);

		return tAtan2;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> atan2
	(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgsf,
		const dimensionedScalar& ds
	)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gsf = tgsf();

		tmp<GeometricField<scalar, PatchField, GeoMesh>> tAtan2
		(
			New
			(
				tgsf,
				"atan2(" + gsf.name() + ',' + ds.name() + ')',
				atan2(gsf.dimensions(), ds)
			)
		);

		atan2(tAtan2.ref(), gsf, ds);

		tgsf.clear();

		return tAtan2;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> atan2
	(
		const GeometricField<scalar, PatchField, GeoMesh>& gsf,
		const scalar& s
	)
	{
		return atan2(gsf, dimensionedScalar(s));
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> atan2
	(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgsf,
		const scalar& s
	)
	{
		return atan2(tgsf, dimensionedScalar(s));
	}


	template<template<class> class PatchField, class GeoMesh>
	void atan2
	(
		GeometricField<scalar, PatchField, GeoMesh>& tAtan2,
		const dimensioned<scalar>& ds,
		const GeometricField<scalar, PatchField, GeoMesh>& gsf
	)
	{
		atan2(tAtan2.primitiveFieldRef(), ds.value(), gsf.primitiveField());
		atan2(tAtan2.boundaryFieldRef(), ds.value(), gsf.boundaryField());
	}


	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> atan2
	(
		const dimensionedScalar& ds,
		const GeometricField<scalar, PatchField, GeoMesh>& gsf
	)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tAtan2
		(
			GeometricField<scalar, PatchField, GeoMesh>::New
			(
				"atan2(" + ds.name() + ',' + gsf.name() + ')',
				gsf.mesh(),
				atan2(ds, gsf.dimensions())
			)
		);

		atan2(tAtan2.ref(), ds, gsf);

		return tAtan2;
	}


	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> atan2
	(
		const dimensionedScalar& ds,
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgsf
	)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gsf = tgsf();

		tmp<GeometricField<scalar, PatchField, GeoMesh>> tAtan2
		(
			New
			(
				tgsf,
				"atan2(" + ds.name() + ',' + gsf.name() + ')',
				atan2(ds, gsf.dimensions())
			)
		);

		atan2(tAtan2.ref(), ds, gsf);

		tgsf.clear();

		return tAtan2;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> atan2
	(
		const scalar& s,
		const GeometricField<scalar, PatchField, GeoMesh>& gsf
	)
	{
		return atan2(dimensionedScalar(s), gsf);
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> atan2
	(
		const scalar& s,
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgsf
	)
	{
		return atan2(dimensionedScalar(s), tgsf);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<template<class> class PatchField, class GeoMesh>
	void pow3(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::pow3(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::pow3(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow3(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New("pow3" "(" + gf1.name() + ')', gf1.mesh(), pow3(gf1.dimensions())));
		tnbLib::pow3(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow3(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "pow3" "(" + gf1.name() + ')',
				pow3(gf1.dimensions())));
		tnbLib::pow3(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void pow4(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::pow4(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::pow4(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow4(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New("pow4" "(" + gf1.name() + ')', gf1.mesh(), pow4(gf1.dimensions())));
		tnbLib::pow4(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow4(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "pow4" "(" + gf1.name() + ')',
				pow4(gf1.dimensions())));
		tnbLib::pow4(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void pow5(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::pow5(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::pow5(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow5(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New("pow5" "(" + gf1.name() + ')', gf1.mesh(), pow5(gf1.dimensions())));
		tnbLib::pow5(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow5(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "pow5" "(" + gf1.name() + ')',
				pow5(gf1.dimensions())));
		tnbLib::pow5(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void pow6(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::pow6(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::pow6(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow6(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New("pow6" "(" + gf1.name() + ')', gf1.mesh(), pow6(gf1.dimensions())));
		tnbLib::pow6(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow6(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "pow6" "(" + gf1.name() + ')',
				pow6(gf1.dimensions())));
		tnbLib::pow6(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void pow025(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::pow025(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::pow025(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow025(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New("pow025" "(" + gf1.name() + ')', gf1.mesh(),
				pow025(gf1.dimensions())));
		tnbLib::pow025(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow025(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "pow025" "(" + gf1.name() + ')',
				pow025(gf1.dimensions())));
		tnbLib::pow025(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void sqrt(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::sqrt(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::sqrt(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> sqrt(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New("sqrt" "(" + gf1.name() + ')', gf1.mesh(), sqrt(gf1.dimensions())));
		tnbLib::sqrt(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> sqrt(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "sqrt" "(" + gf1.name() + ')',
				sqrt(gf1.dimensions())));
		tnbLib::sqrt(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void cbrt(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::cbrt(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::cbrt(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> cbrt(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New("cbrt" "(" + gf1.name() + ')', gf1.mesh(), cbrt(gf1.dimensions())));
		tnbLib::cbrt(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> cbrt(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "cbrt" "(" + gf1.name() + ')',
				cbrt(gf1.dimensions())));
		tnbLib::cbrt(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void sign(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::sign(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::sign(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> sign(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New("sign" "(" + gf1.name() + ')', gf1.mesh(), sign(gf1.dimensions())));
		tnbLib::sign(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> sign(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "sign" "(" + gf1.name() + ')',
				sign(gf1.dimensions())));
		tnbLib::sign(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void pos(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::pos(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::pos(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pos(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New("pos" "(" + gf1.name() + ')', gf1.mesh(), pos(gf1.dimensions())));
		tnbLib::pos(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pos(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "pos" "(" + gf1.name() + ')',
				pos(gf1.dimensions())));
		tnbLib::pos(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void pos0(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::pos0(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::pos0(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pos0(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New("pos0" "(" + gf1.name() + ')', gf1.mesh(), pos0(gf1.dimensions())));
		tnbLib::pos0(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pos0(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "pos0" "(" + gf1.name() + ')',
				pos0(gf1.dimensions())));
		tnbLib::pos0(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void neg(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::neg(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::neg(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> neg(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New("neg" "(" + gf1.name() + ')', gf1.mesh(), neg(gf1.dimensions())));
		tnbLib::neg(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> neg(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "neg" "(" + gf1.name() + ')',
				neg(gf1.dimensions())));
		tnbLib::neg(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void neg0(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::neg0(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::neg0(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> neg0(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New("neg0" "(" + gf1.name() + ')', gf1.mesh(), neg0(gf1.dimensions())));
		tnbLib::neg0(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> neg0(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "neg0" "(" + gf1.name() + ')',
				neg0(gf1.dimensions())));
		tnbLib::neg0(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void posPart(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::posPart(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::posPart(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> posPart(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New("posPart" "(" + gf1.name() + ')', gf1.mesh(),
				posPart(gf1.dimensions())));
		tnbLib::posPart(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> posPart(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "posPart" "(" + gf1.name() + ')',
				posPart(gf1.dimensions())));
		tnbLib::posPart(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void negPart(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::negPart(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::negPart(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> negPart(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New("negPart" "(" + gf1.name() + ')', gf1.mesh(),
				negPart(gf1.dimensions())));
		tnbLib::negPart(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> negPart(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "negPart" "(" + gf1.name() + ')',
				negPart(gf1.dimensions())));
		tnbLib::negPart(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void exp(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::exp(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::exp(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> exp(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New("exp" "(" + gf1.name() + ')', gf1.mesh(), trans(gf1.dimensions())));
		tnbLib::exp(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> exp(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "exp" "(" + gf1.name() + ')',
				trans(gf1.dimensions())));
		tnbLib::exp(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void log(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::log(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::log(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> log(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New("log" "(" + gf1.name() + ')', gf1.mesh(), trans(gf1.dimensions())));
		tnbLib::log(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> log(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "log" "(" + gf1.name() + ')',
				trans(gf1.dimensions())));
		tnbLib::log(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void log10(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::log10(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::log10(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> log10(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::
			New("log10" "(" + gf1.name() + ')', gf1.mesh(), trans(gf1.dimensions())));
		tnbLib::log10(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> log10(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "log10" "(" + gf1.name() + ')',
				trans(gf1.dimensions())));
		tnbLib::log10(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void sin(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::sin(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::sin(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> sin(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New("sin" "(" + gf1.name() + ')', gf1.mesh(), trans(gf1.dimensions())));
		tnbLib::sin(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> sin(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "sin" "(" + gf1.name() + ')',
				trans(gf1.dimensions())));
		tnbLib::sin(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void cos(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::cos(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::cos(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> cos(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New("cos" "(" + gf1.name() + ')', gf1.mesh(), trans(gf1.dimensions())));
		tnbLib::cos(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> cos(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "cos" "(" + gf1.name() + ')',
				trans(gf1.dimensions())));
		tnbLib::cos(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void tan(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::tan(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::tan(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> tan(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New("tan" "(" + gf1.name() + ')', gf1.mesh(), trans(gf1.dimensions())));
		tnbLib::tan(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> tan(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "tan" "(" + gf1.name() + ')',
				trans(gf1.dimensions())));
		tnbLib::tan(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void asin(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::asin(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::asin(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> asin(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New("asin" "(" + gf1.name() + ')', gf1.mesh(),
				trans(gf1.dimensions())));
		tnbLib::asin(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> asin(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "asin" "(" + gf1.name() + ')',
				trans(gf1.dimensions())));
		tnbLib::asin(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void acos(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::acos(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::acos(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> acos(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New("acos" "(" + gf1.name() + ')', gf1.mesh(),
				trans(gf1.dimensions())));
		tnbLib::acos(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> acos(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "acos" "(" + gf1.name() + ')',
				trans(gf1.dimensions())));
		tnbLib::acos(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void atan(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::atan(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::atan(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> atan(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New("atan" "(" + gf1.name() + ')', gf1.mesh(),
				trans(gf1.dimensions())));
		tnbLib::atan(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> atan(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "atan" "(" + gf1.name() + ')',
				trans(gf1.dimensions())));
		tnbLib::atan(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void sinh(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::sinh(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::sinh(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> sinh(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New("sinh" "(" + gf1.name() + ')', gf1.mesh(),
				trans(gf1.dimensions())));
		tnbLib::sinh(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> sinh(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "sinh" "(" + gf1.name() + ')',
				trans(gf1.dimensions())));
		tnbLib::sinh(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void cosh(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::cosh(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::cosh(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> cosh(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New("cosh" "(" + gf1.name() + ')', gf1.mesh(),
				trans(gf1.dimensions())));
		tnbLib::cosh(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> cosh(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "cosh" "(" + gf1.name() + ')',
				trans(gf1.dimensions())));
		tnbLib::cosh(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void tanh(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::tanh(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::tanh(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> tanh(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New("tanh" "(" + gf1.name() + ')', gf1.mesh(),
				trans(gf1.dimensions())));
		tnbLib::tanh(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> tanh(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "tanh" "(" + gf1.name() + ')',
				trans(gf1.dimensions())));
		tnbLib::tanh(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void asinh(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::asinh(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::asinh(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> asinh(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::
			New("asinh" "(" + gf1.name() + ')', gf1.mesh(), trans(gf1.dimensions())));
		tnbLib::asinh(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> asinh(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "asinh" "(" + gf1.name() + ')',
				trans(gf1.dimensions())));
		tnbLib::asinh(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void acosh(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::acosh(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::acosh(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> acosh(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::
			New("acosh" "(" + gf1.name() + ')', gf1.mesh(), trans(gf1.dimensions())));
		tnbLib::acosh(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> acosh(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "acosh" "(" + gf1.name() + ')',
				trans(gf1.dimensions())));
		tnbLib::acosh(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void atanh(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::atanh(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::atanh(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> atanh(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::
			New("atanh" "(" + gf1.name() + ')', gf1.mesh(), trans(gf1.dimensions())));
		tnbLib::atanh(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> atanh(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "atanh" "(" + gf1.name() + ')',
				trans(gf1.dimensions())));
		tnbLib::atanh(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void erf(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::erf(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::erf(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> erf(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New("erf" "(" + gf1.name() + ')', gf1.mesh(), trans(gf1.dimensions())));
		tnbLib::erf(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> erf(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "erf" "(" + gf1.name() + ')',
				trans(gf1.dimensions())));
		tnbLib::erf(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void erfc(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::erfc(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::erfc(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> erfc(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New("erfc" "(" + gf1.name() + ')', gf1.mesh(),
				trans(gf1.dimensions())));
		tnbLib::erfc(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> erfc(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "erfc" "(" + gf1.name() + ')',
				trans(gf1.dimensions())));
		tnbLib::erfc(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void lgamma(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::lgamma(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::lgamma(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> lgamma(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New("lgamma" "(" + gf1.name() + ')', gf1.mesh(),
				trans(gf1.dimensions())));
		tnbLib::lgamma(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> lgamma(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "lgamma" "(" + gf1.name() + ')',
				trans(gf1.dimensions())));
		tnbLib::lgamma(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void j0(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::j0(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::j0(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> j0(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New("j0" "(" + gf1.name() + ')', gf1.mesh(), trans(gf1.dimensions())));
		tnbLib::j0(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> j0(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "j0" "(" + gf1.name() + ')',
				trans(gf1.dimensions())));
		tnbLib::j0(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void j1(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::j1(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::j1(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> j1(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New("j1" "(" + gf1.name() + ')', gf1.mesh(), trans(gf1.dimensions())));
		tnbLib::j1(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> j1(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "j1" "(" + gf1.name() + ')',
				trans(gf1.dimensions())));
		tnbLib::j1(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void y0(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::y0(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::y0(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> y0(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New("y0" "(" + gf1.name() + ')', gf1.mesh(), trans(gf1.dimensions())));
		tnbLib::y0(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> y0(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "y0" "(" + gf1.name() + ')',
				trans(gf1.dimensions())));
		tnbLib::y0(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	void y1(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tnbLib::y1(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::y1(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> y1(const GeometricField<scalar, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			GeometricField<scalar, PatchField, GeoMesh>::New("y1" "(" + gf1.name() + ')', gf1.mesh(), trans(gf1.dimensions())));
		tnbLib::y1(tRes.ref(), gf1);
		return tRes;
	}

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> y1(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, scalar, PatchField, GeoMesh>::New(tgf1, "y1" "(" + gf1.name() + ')',
				trans(gf1.dimensions())));
		tnbLib::y1(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#define BesselFunc(func)                                                       \
//                                                                               \
//template<template<class> class PatchField, class GeoMesh>                      \
//void func                                                                      \
//(                                                                              \
//    GeometricField<scalar, PatchField, GeoMesh>& gsf,                          \
//    const int n,                                                               \
//    const GeometricField<scalar, PatchField, GeoMesh>& gsf1                    \
//)                                                                              \
//{                                                                              \
//    func(gsf.primitiveFieldRef(), n, gsf1.primitiveField());                   \
//    func(gsf.boundaryFieldRef(), n, gsf1.boundaryField());                     \
//}                                                                              \
//                                                                               \
//template<template<class> class PatchField, class GeoMesh>                      \
//tmp<GeometricField<scalar, PatchField, GeoMesh>> func                          \
//(                                                                              \
//    const int n,                                                               \
//    const GeometricField<scalar, PatchField, GeoMesh>& gsf                     \
//)                                                                              \
//{                                                                              \
//    if (!gsf.dimensions().dimensionless())                                     \
//    {                                                                          \
//        FatalErrorInFunction                                                   \
//            << "gsf not dimensionless"                                         \
//            << abort(FatalError);                                              \
//    }                                                                          \
//                                                                               \
//    tmp<GeometricField<scalar, PatchField, GeoMesh>> tFunc                     \
//    (                                                                          \
//        GeometricField<scalar, PatchField, GeoMesh>::New                       \
//        (                                                                      \
//            #func "(" + gsf.name() + ')',                                      \
//            gsf.mesh(),                                                        \
//            dimless                                                            \
//        )                                                                      \
//    );                                                                         \
//                                                                               \
//    func(tFunc.ref(), n, gsf);                                                 \
//                                                                               \
//    return tFunc;                                                              \
//}                                                                              \
//                                                                               \
//template<template<class> class PatchField, class GeoMesh>                      \
//tmp<GeometricField<scalar, PatchField, GeoMesh>> func                          \
//(                                                                              \
//    const int n,                                                               \
//    const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgsf               \
//)                                                                              \
//{                                                                              \
//    const GeometricField<scalar, PatchField, GeoMesh>& gsf = tgsf();           \
//                                                                               \
//    if (!gsf.dimensions().dimensionless())                                     \
//    {                                                                          \
//        FatalErrorInFunction                                                   \
//            << " : gsf not dimensionless"                                      \
//            << abort(FatalError);                                              \
//    }                                                                          \
//                                                                               \
//    tmp<GeometricField<scalar, PatchField, GeoMesh>> tFunc                     \
//    (                                                                          \
//        New                                                                    \
//        (                                                                      \
//            tgsf,                                                              \
//            #func "(" + gsf.name() + ')',                                      \
//            dimless                                                            \
//        )                                                                      \
//    );                                                                         \
//                                                                               \
//    func(tFunc.ref(), n, gsf);                                                 \
//                                                                               \
//    tgsf.clear();                                                              \
//                                                                               \
//    return tFunc;                                                              \
//}


	template <template<class> class PatchField, class GeoMesh>
	void jn(GeometricField<scalar, PatchField, GeoMesh>& gsf, const int n,
		const GeometricField<scalar, PatchField, GeoMesh>& gsf1)
	{
		jn(gsf.primitiveFieldRef(), n, gsf1.primitiveField());
		jn(gsf.boundaryFieldRef(), n, gsf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> jn(const int n,
		const GeometricField<scalar, PatchField, GeoMesh>& gsf)
	{
		if (!gsf.dimensions().dimensionless()) { FatalErrorInFunction << "gsf not dimensionless" << abort(FatalError); }
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tFunc(
			GeometricField<scalar, PatchField, GeoMesh>::New("jn" "(" + gsf.name() + ')', gsf.mesh(), dimless));
		jn(tFunc.ref(), n, gsf);
		return tFunc;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> jn(const int n,
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgsf)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gsf = tgsf();
		if (!gsf.dimensions().dimensionless()) { FatalErrorInFunction << " : gsf not dimensionless" << abort(FatalError); }
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tFunc(New(tgsf, "jn" "(" + gsf.name() + ')', dimless));
		jn(tFunc.ref(), n, gsf);
		tgsf.clear();
		return tFunc;
	}

	template <template<class> class PatchField, class GeoMesh>
	void yn(GeometricField<scalar, PatchField, GeoMesh>& gsf, const int n,
		const GeometricField<scalar, PatchField, GeoMesh>& gsf1)
	{
		yn(gsf.primitiveFieldRef(), n, gsf1.primitiveField());
		yn(gsf.boundaryFieldRef(), n, gsf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> yn(const int n,
		const GeometricField<scalar, PatchField, GeoMesh>& gsf)
	{
		if (!gsf.dimensions().dimensionless()) { FatalErrorInFunction << "gsf not dimensionless" << abort(FatalError); }
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tFunc(
			GeometricField<scalar, PatchField, GeoMesh>::New("yn" "(" + gsf.name() + ')', gsf.mesh(), dimless));
		yn(tFunc.ref(), n, gsf);
		return tFunc;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> yn(const int n,
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgsf)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gsf = tgsf();
		if (!gsf.dimensions().dimensionless()) { FatalErrorInFunction << " : gsf not dimensionless" << abort(FatalError); }
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tFunc(New(tgsf, "yn" "(" + gsf.name() + ')', dimless));
		yn(tFunc.ref(), n, gsf);
		tgsf.clear();
		return tFunc;
	}

//#undef BesselFunc


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //