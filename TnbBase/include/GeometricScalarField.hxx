#pragma once
#ifndef _GeometricScalarField_Header
#define _GeometricScalarField_Header

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
	tnbLib::GeometricScalarField

Description
	Scalar specific part of the implementation of GeometricField.

SourceFiles
	GeometricScalarField.C

\*---------------------------------------------------------------------------*/

#include <GeometricField.hxx>
#include <DimensionedScalarField.hxx>

//#define TEMPLATE template<template<class> class PatchField, class GeoMesh>
//#include <GeometricFieldFunctionsM.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<template<class> class PatchField, class GeoMesh>
	void stabilise
	(
		GeometricField<scalar, PatchField, GeoMesh>&,
		const GeometricField<scalar, PatchField, GeoMesh>&,
		const dimensioned<scalar>&
	);

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> stabilise
	(
		const GeometricField<scalar, PatchField, GeoMesh>&,
		const dimensioned<scalar>&
	);

	template<template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> stabilise
	(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>&,
		const dimensioned<scalar>&
	);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator +(const dimensioned<scalar>& dt1,
	                                                            const GeometricField<scalar, PatchField, GeoMesh>& df2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator +(const scalar& t1,
	                                                            const GeometricField<scalar, PatchField, GeoMesh>& df2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator +(const dimensioned<scalar>& dt1,
	                                                            const tmp<GeometricField<scalar, PatchField, GeoMesh>>&
	                                                            tdf2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator +(const scalar& t1,
	                                                            const tmp<GeometricField<scalar, PatchField, GeoMesh>>&
	                                                            tdf2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator +(const GeometricField<scalar, PatchField, GeoMesh>& df1,
	                                                            const dimensioned<scalar>& dt2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator +(const GeometricField<scalar, PatchField, GeoMesh>& df1,
	                                                            const scalar& t2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1, const dimensioned<scalar>& dt2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1, const scalar& t2);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator -(const dimensioned<scalar>& dt1,
	                                                            const GeometricField<scalar, PatchField, GeoMesh>& df2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator -(const scalar& t1,
	                                                            const GeometricField<scalar, PatchField, GeoMesh>& df2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator -(const dimensioned<scalar>& dt1,
	                                                            const tmp<GeometricField<scalar, PatchField, GeoMesh>>&
	                                                            tdf2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator -(const scalar& t1,
	                                                            const tmp<GeometricField<scalar, PatchField, GeoMesh>>&
	                                                            tdf2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator -(const GeometricField<scalar, PatchField, GeoMesh>& df1,
	                                                            const dimensioned<scalar>& dt2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator -(const GeometricField<scalar, PatchField, GeoMesh>& df1,
	                                                            const scalar& t2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1, const dimensioned<scalar>& dt2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1, const scalar& t2);

		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator *(const GeometricField<scalar, PatchField, GeoMesh>& df1,
	                                                            const GeometricField<scalar, PatchField, GeoMesh>& df2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator *(const GeometricField<scalar, PatchField, GeoMesh>& df1,
	                                                            const tmp<GeometricField<scalar, PatchField, GeoMesh>>&
	                                                            tdf2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1, const GeometricField<scalar, PatchField, GeoMesh>& df2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1,
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf2);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator /(const GeometricField<scalar, PatchField, GeoMesh>& df1,
	                                                            const GeometricField<scalar, PatchField, GeoMesh>& df2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator /(const GeometricField<scalar, PatchField, GeoMesh>& df1,
	                                                            const tmp<GeometricField<scalar, PatchField, GeoMesh>>&
	                                                            tdf2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1, const GeometricField<scalar, PatchField, GeoMesh>& df2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1,
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf2);

		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator /(const dimensioned<scalar>& dt1,
	                                                            const GeometricField<scalar, PatchField, GeoMesh>& df2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator /(const scalar& t1,
	                                                            const GeometricField<scalar, PatchField, GeoMesh>& df2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator /(const dimensioned<scalar>& dt1,
	                                                            const tmp<GeometricField<scalar, PatchField, GeoMesh>>&
	                                                            tdf2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> operator /(const scalar& t1,
	                                                            const tmp<GeometricField<scalar, PatchField, GeoMesh>>&
	                                                            tdf2);

		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow(const GeometricField<scalar, PatchField, GeoMesh>& df1,
	                                                     const GeometricField<scalar, PatchField, GeoMesh>& df2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow(const GeometricField<scalar, PatchField, GeoMesh>& df1,
	                                                     const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1,
	                                                     const GeometricField<scalar, PatchField, GeoMesh>& df2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1,
	                                                     const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf2);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow(const dimensioned<scalar>& dt1,
	                                                     const GeometricField<scalar, PatchField, GeoMesh>& df2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow(const scalar& t1,
	                                                     const GeometricField<scalar, PatchField, GeoMesh>& df2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow(const dimensioned<scalar>& dt1,
	                                                     const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow(const scalar& t1,
	                                                     const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow(const GeometricField<scalar, PatchField, GeoMesh>& df1,
	                                                     const dimensioned<scalar>& dt2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow(const GeometricField<scalar, PatchField, GeoMesh>& df1,
	                                                     const scalar& t2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1,
	                                                     const dimensioned<scalar>& dt2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf2,
	                                                     const scalar& t2);

		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> atan2(const GeometricField<scalar, PatchField, GeoMesh>& df1,
	                                                       const GeometricField<scalar, PatchField, GeoMesh>& df2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> atan2(const GeometricField<scalar, PatchField, GeoMesh>& df1,
	                                                       const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> atan2(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1,
	                                                       const GeometricField<scalar, PatchField, GeoMesh>& df2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> atan2(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1,
	                                                       const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf2);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> atan2(const dimensioned<scalar>& dt1,
	                                                       const GeometricField<scalar, PatchField, GeoMesh>& df2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> atan2(const scalar& t1,
	                                                       const GeometricField<scalar, PatchField, GeoMesh>& df2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> atan2(const dimensioned<scalar>& dt1,
	                                                       const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> atan2(const scalar& t1,
	                                                       const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> atan2(const GeometricField<scalar, PatchField, GeoMesh>& df1,
	                                                       const dimensioned<scalar>& dt2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> atan2(const GeometricField<scalar, PatchField, GeoMesh>& df1,
	                                                       const scalar& t2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> atan2(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1,
	                                                       const dimensioned<scalar>& dt2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> atan2(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf2,
	                                                       const scalar& t2);


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow3(const GeometricField<scalar, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow3(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow4(const GeometricField<scalar, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow4(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow5(const GeometricField<scalar, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow5(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow6(const GeometricField<scalar, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow6(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow025(const GeometricField<scalar, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pow025(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> sqrt(const GeometricField<scalar, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> sqrt(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> cbrt(const GeometricField<scalar, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> cbrt(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> sign(const GeometricField<scalar, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> sign(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pos(const GeometricField<scalar, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pos(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pos0(const GeometricField<scalar, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> pos0(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> neg(const GeometricField<scalar, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> neg(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> neg0(const GeometricField<scalar, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> neg0(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> posPart(const GeometricField<scalar, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> posPart(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> negPart(const GeometricField<scalar, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> negPart(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1);

		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> exp(const GeometricField<scalar, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> exp(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> log(const GeometricField<scalar, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> log(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> log10(const GeometricField<scalar, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> log10(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> sin(const GeometricField<scalar, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> sin(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> cos(const GeometricField<scalar, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> cos(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> tan(const GeometricField<scalar, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> tan(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> asin(const GeometricField<scalar, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> asin(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> acos(const GeometricField<scalar, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> acos(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> atan(const GeometricField<scalar, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> atan(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> sinh(const GeometricField<scalar, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> sinh(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> cosh(const GeometricField<scalar, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> cosh(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> tanh(const GeometricField<scalar, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> tanh(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> asinh(const GeometricField<scalar, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> asinh(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> acosh(const GeometricField<scalar, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> acosh(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> atanh(const GeometricField<scalar, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> atanh(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> erf(const GeometricField<scalar, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> erf(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> erfc(const GeometricField<scalar, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> erfc(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> lgamma(const GeometricField<scalar, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> lgamma(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> j0(const GeometricField<scalar, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> j0(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> j1(const GeometricField<scalar, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> j1(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> y0(const GeometricField<scalar, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> y0(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> y1(const GeometricField<scalar, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> y1(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tdf1);


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#define BesselFunc(func)                                                       \
//                                                                               \
//template<template<class> class PatchField, class GeoMesh>                      \
//void func                                                                      \
//(                                                                              \
//    GeometricField<scalar, PatchField, GeoMesh>& Res,                          \
//    const int n,                                                               \
//    const GeometricField<scalar, PatchField, GeoMesh>& sf                      \
//);                                                                             \
//                                                                               \
//template<template<class> class PatchField, class GeoMesh>                      \
//tmp<GeometricField<scalar, PatchField, GeoMesh>> func                          \
//(                                                                              \
//    const int n,                                                               \
//    const GeometricField<scalar, PatchField, GeoMesh>&                         \
//);                                                                             \
//                                                                               \
//template<template<class> class PatchField, class GeoMesh>                      \
//tmp<GeometricField<scalar, PatchField, GeoMesh>> func                          \
//(                                                                              \
//    const int n,                                                               \
//    const tmp<GeometricField<scalar, PatchField, GeoMesh>>&                    \
//);

		
	template <template<class> class PatchField, class GeoMesh>
	void jn(GeometricField<scalar, PatchField, GeoMesh>& Res, const int n,
	        const GeometricField<scalar, PatchField, GeoMesh>& sf);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> jn(const int n, const GeometricField<scalar, PatchField, GeoMesh>&);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> jn(const int n,
	                                                    const tmp<GeometricField<scalar, PatchField, GeoMesh>>&);
		
	template <template<class> class PatchField, class GeoMesh>
	void yn(GeometricField<scalar, PatchField, GeoMesh>& Res, const int n,
	        const GeometricField<scalar, PatchField, GeoMesh>& sf);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> yn(const int n, const GeometricField<scalar, PatchField, GeoMesh>&);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> yn(const int n,
	                                                    const tmp<GeometricField<scalar, PatchField, GeoMesh>>&);

//#undef BesselFunc


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#include <undefFieldFunctionsM.hxx>

#include <GeometricScalarFieldI.hxx>

//#ifdef NoRepository
//#include <GeometricScalarField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_GeometricScalarField_Header
