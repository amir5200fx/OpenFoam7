#pragma once
#ifndef _scalarFieldField_Header
#define _scalarFieldField_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
	 \\/     M anipulation  |
-------------------------------------------------------------------------------
License
	This file is part of OpenFOAM.

	OpenFOAM is free software: you can redistribute it and/or modify it
	under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
	ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
	FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
	for more details.

	You should have received a copy of the GNU General Public License
	along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

InClass
	tnbLib::scalarFieldField

Description
	Specialisation of FieldField\<T\> for scalar.

SourceFiles
	scalarFieldField.C

\*---------------------------------------------------------------------------*/

#include <FieldField.hxx>
#include <scalar.hxx>

//#define TEMPLATE template<template<class> class Field>
//#include <FieldFieldFunctionsM.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	// added by amir
	template<class Type>
	class Field;

	typedef  Field<scalar> scalarField;

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<template<class> class Field>
	void stabilise
	(
		FieldField<Field, scalar>& Res,
		const FieldField<Field, scalar>& sf,
		const scalar s
	);


	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> stabilise
	(
		const FieldField<Field, scalar>&,
		const scalar s
	);


	template<template<class> class Field>
	tmp<FieldField<Field, scalar>> stabilise
	(
		const tmp<FieldField<Field, scalar>>&,
		const scalar s
	);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template <template<class> class Field>
	void add(FieldField<Field, scalar>& f, const scalar& s1, const FieldField<Field, scalar>& f2);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> operator +(const scalar& s1, const FieldField<Field, scalar>& f2);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> operator +(const scalar& s1, const tmp<FieldField<Field, scalar>>& tf2);
	template <template<class> class Field>
	void add(FieldField<Field, scalar>& f, const FieldField<Field, scalar>& f1, const scalar& s2);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> operator +(const FieldField<Field, scalar>& f1, const scalar& s2);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> operator +(const tmp<FieldField<Field, scalar>>& tf1, const scalar& s2);
		
	template <template<class> class Field>
	void subtract(FieldField<Field, scalar>& f, const scalar& s1, const FieldField<Field, scalar>& f2);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> operator -(const scalar& s1, const FieldField<Field, scalar>& f2);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> operator -(const scalar& s1, const tmp<FieldField<Field, scalar>>& tf2);
	template <template<class> class Field>
	void subtract(FieldField<Field, scalar>& f, const FieldField<Field, scalar>& f1, const scalar& s2);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> operator -(const FieldField<Field, scalar>& f1, const scalar& s2);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> operator -(const tmp<FieldField<Field, scalar>>& tf1, const scalar& s2);

		
	template <template<class> class Field>
	void multiply(FieldField<Field, scalar>& f, const FieldField<Field, scalar>& f1, const FieldField<Field, scalar>& f2);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> operator *(const FieldField<Field, scalar>& f1, const FieldField<Field, scalar>& f2);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> operator *(const FieldField<Field, scalar>& f1,
	                                          const tmp<FieldField<Field, scalar>>& tf2);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> operator *(const tmp<FieldField<Field, scalar>>& tf1,
	                                          const FieldField<Field, scalar>& f2);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> operator *(const tmp<FieldField<Field, scalar>>& tf1,
	                                          const tmp<FieldField<Field, scalar>>& tf2);
		
	template <template<class> class Field>
	void divide(FieldField<Field, scalar>& f, const FieldField<Field, scalar>& f1, const FieldField<Field, scalar>& f2);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> operator /(const FieldField<Field, scalar>& f1, const FieldField<Field, scalar>& f2);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> operator /(const FieldField<Field, scalar>& f1,
	                                          const tmp<FieldField<Field, scalar>>& tf2);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> operator /(const tmp<FieldField<Field, scalar>>& tf1,
	                                          const FieldField<Field, scalar>& f2);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> operator /(const tmp<FieldField<Field, scalar>>& tf1,
	                                          const tmp<FieldField<Field, scalar>>& tf2);

		
	template <template<class> class Field>
	void divide(FieldField<Field, scalar>& f, const scalar& s1, const FieldField<Field, scalar>& f2);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> operator /(const scalar& s1, const FieldField<Field, scalar>& f2);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> operator /(const scalar& s1, const tmp<FieldField<Field, scalar>>& tf2);

		
	template <template<class> class Field>
	void pow(FieldField<Field, scalar>& f, const FieldField<Field, scalar>& f1, const FieldField<Field, scalar>& f2);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> pow(const FieldField<Field, scalar>& f1, const FieldField<Field, scalar>& f2);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> pow(const FieldField<Field, scalar>& f1, const tmp<FieldField<Field, scalar>>& tf2);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> pow(const tmp<FieldField<Field, scalar>>& tf1, const FieldField<Field, scalar>& f2);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> pow(const tmp<FieldField<Field, scalar>>& tf1,
	                                    const tmp<FieldField<Field, scalar>>& tf2);
		
	template <template<class> class Field>
	void pow(FieldField<Field, scalar>& f, const scalar& s1, const FieldField<Field, scalar>& f2);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> pow(const scalar& s1, const FieldField<Field, scalar>& f2);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> pow(const scalar& s1, const tmp<FieldField<Field, scalar>>& tf2);
	template <template<class> class Field>
	void pow(FieldField<Field, scalar>& f, const FieldField<Field, scalar>& f1, const scalar& s);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> pow(const FieldField<Field, scalar>& f1, const scalar& s);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> pow(const tmp<FieldField<Field, scalar>>& tf1, const scalar& s);

		
	template <template<class> class Field>
	void atan2(FieldField<Field, scalar>& f, const FieldField<Field, scalar>& f1, const FieldField<Field, scalar>& f2);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> atan2(const FieldField<Field, scalar>& f1, const FieldField<Field, scalar>& f2);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> atan2(const FieldField<Field, scalar>& f1, const tmp<FieldField<Field, scalar>>& tf2);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> atan2(const tmp<FieldField<Field, scalar>>& tf1, const FieldField<Field, scalar>& f2);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> atan2(const tmp<FieldField<Field, scalar>>& tf1,
	                                    const tmp<FieldField<Field, scalar>>& tf2);
		
	template <template<class> class Field>
	void atan2(FieldField<Field, scalar>& f, const scalar& s1, const FieldField<Field, scalar>& f2);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> atan2(const scalar& s1, const FieldField<Field, scalar>& f2);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> atan2(const scalar& s1, const tmp<FieldField<Field, scalar>>& tf2);
	template <template<class> class Field>
	void atan2(FieldField<Field, scalar>& f, const FieldField<Field, scalar>& f1, const scalar& s);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> atan2(const FieldField<Field, scalar>& f1, const scalar& s);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> atan2(const tmp<FieldField<Field, scalar>>& tf1, const scalar& s);


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		
	template <template<class> class Field>
	void pow3(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> pow3(const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> pow3(const tmp<FieldField<Field, scalar>>& tf);
		
	template <template<class> class Field>
	void pow4(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> pow4(const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> pow4(const tmp<FieldField<Field, scalar>>& tf);
		
	template <template<class> class Field>
	void pow5(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> pow5(const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> pow5(const tmp<FieldField<Field, scalar>>& tf);
		
	template <template<class> class Field>
	void pow6(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> pow6(const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> pow6(const tmp<FieldField<Field, scalar>>& tf);
		
	template <template<class> class Field>
	void pow025(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> pow025(const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> pow025(const tmp<FieldField<Field, scalar>>& tf);
		
	template <template<class> class Field>
	void sqrt(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> sqrt(const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> sqrt(const tmp<FieldField<Field, scalar>>& tf);
		
	template <template<class> class Field>
	void cbrt(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> cbrt(const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> cbrt(const tmp<FieldField<Field, scalar>>& tf);
		
	template <template<class> class Field>
	void sign(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> sign(const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> sign(const tmp<FieldField<Field, scalar>>& tf);
		
	template <template<class> class Field>
	void pos(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> pos(const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> pos(const tmp<FieldField<Field, scalar>>& tf);
		
	template <template<class> class Field>
	void pos0(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> pos0(const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> pos0(const tmp<FieldField<Field, scalar>>& tf);
		
	template <template<class> class Field>
	void neg(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> neg(const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> neg(const tmp<FieldField<Field, scalar>>& tf);
		
	template <template<class> class Field>
	void neg0(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> neg0(const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> neg0(const tmp<FieldField<Field, scalar>>& tf);
		
	template <template<class> class Field>
	void posPart(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> posPart(const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> posPart(const tmp<FieldField<Field, scalar>>& tf);
		
	template <template<class> class Field>
	void negPart(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> negPart(const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> negPart(const tmp<FieldField<Field, scalar>>& tf);
		
	template <template<class> class Field>
	void exp(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> exp(const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> exp(const tmp<FieldField<Field, scalar>>& tf);
		
	template <template<class> class Field>
	void log(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> log(const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> log(const tmp<FieldField<Field, scalar>>& tf);
		
	template <template<class> class Field>
	void log10(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> log10(const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> log10(const tmp<FieldField<Field, scalar>>& tf);
		
	template <template<class> class Field>
	void sin(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> sin(const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> sin(const tmp<FieldField<Field, scalar>>& tf);
		
	template <template<class> class Field>
	void cos(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> cos(const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> cos(const tmp<FieldField<Field, scalar>>& tf);
		
	template <template<class> class Field>
	void tan(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> tan(const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> tan(const tmp<FieldField<Field, scalar>>& tf);
		
	template <template<class> class Field>
	void asin(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> asin(const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> asin(const tmp<FieldField<Field, scalar>>& tf);
		
	template <template<class> class Field>
	void acos(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> acos(const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> acos(const tmp<FieldField<Field, scalar>>& tf);
		
	template <template<class> class Field>
	void atan(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> atan(const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> atan(const tmp<FieldField<Field, scalar>>& tf);
		
	template <template<class> class Field>
	void sinh(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> sinh(const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> sinh(const tmp<FieldField<Field, scalar>>& tf);
		
	template <template<class> class Field>
	void cosh(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> cosh(const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> cosh(const tmp<FieldField<Field, scalar>>& tf);
		
	template <template<class> class Field>
	void tanh(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> tanh(const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> tanh(const tmp<FieldField<Field, scalar>>& tf);
		
	template <template<class> class Field>
	void asinh(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> asinh(const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> asinh(const tmp<FieldField<Field, scalar>>& tf);
		
	template <template<class> class Field>
	void acosh(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> acosh(const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> acosh(const tmp<FieldField<Field, scalar>>& tf);
		
	template <template<class> class Field>
	void atanh(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> atanh(const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> atanh(const tmp<FieldField<Field, scalar>>& tf);
		
	template <template<class> class Field>
	void erf(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> erf(const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> erf(const tmp<FieldField<Field, scalar>>& tf);
		
	template <template<class> class Field>
	void erfc(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> erfc(const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> erfc(const tmp<FieldField<Field, scalar>>& tf);
		
	template <template<class> class Field>
	void lgamma(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> lgamma(const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> lgamma(const tmp<FieldField<Field, scalar>>& tf);
		
	template <template<class> class Field>
	void j0(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> j0(const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> j0(const tmp<FieldField<Field, scalar>>& tf);
		
	template <template<class> class Field>
	void j1(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> j1(const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> j1(const tmp<FieldField<Field, scalar>>& tf);
		
	template <template<class> class Field>
	void y0(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> y0(const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> y0(const tmp<FieldField<Field, scalar>>& tf);
		
	template <template<class> class Field>
	void y1(FieldField<Field, scalar>& res, const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> y1(const FieldField<Field, scalar>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> y1(const tmp<FieldField<Field, scalar>>& tf);


//#define BesselFunc(func)                                                       \
//void func                                                                      \
//(                                                                              \
//    FieldField<Field, scalar>& Res,                                            \
//    const int n,                                                               \
//    const FieldField<Field, scalar>& sf                                        \
//);                                                                             \
//tmp<scalarField> func(const int n, const FieldField<Field, scalar>&);          \
//tmp<scalarField> func(const int n, const tmp<FieldField<Field, scalar>>&);

		
	void jn(FieldField<Field, scalar>& Res, const int n, const FieldField<Field, scalar>& sf);
	tmp<scalarField> jn(const int n, const FieldField<Field, scalar>&);
	tmp<scalarField> jn(const int n, const tmp<FieldField<Field, scalar>>&);
		
	void yn(FieldField<Field, scalar>& Res, const int n, const FieldField<Field, scalar>& sf);
	tmp<scalarField> yn(const int n, const FieldField<Field, scalar>&);
	tmp<scalarField> yn(const int n, const tmp<FieldField<Field, scalar>>&);

//#undef BesselFunc


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#include <undefFieldFunctionsM.hxx>

#include <scalarFieldFieldI.hxx>

//#ifdef NoRepository
//#include <scalarFieldField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_scalarFieldField_Header
