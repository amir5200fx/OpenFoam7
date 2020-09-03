#pragma once
#ifndef _DimensionedScalarField_Header
#define _DimensionedScalarField_Header

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
	tnbLib::DimensionedScalarField

Description
	Scalar specific part of the implementation of DimensionedField.

SourceFiles
	DimensionedScalarField.C

\*---------------------------------------------------------------------------*/

#include <DimensionedField.hxx>
#include <scalar.hxx>

//#define TEMPLATE template<class GeoMesh>
//#include <DimensionedFieldFunctionsM.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> stabilise
	(
		const DimensionedField<scalar, GeoMesh>&,
		const dimensioned<scalar>&
	);

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> stabilise
	(
		const tmp<DimensionedField<scalar, GeoMesh>>&,
		const dimensioned<scalar>&
	);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator +(const dimensioned<scalar>& dt1,
	                                                  const DimensionedField<scalar, GeoMesh>& df2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator +(const scalar& t1, const DimensionedField<scalar, GeoMesh>& df2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator +(const dimensioned<scalar>& dt1,
	                                                  const tmp<DimensionedField<scalar, GeoMesh>>& tdf2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator
	+(const scalar& t1, const tmp<DimensionedField<scalar, GeoMesh>>& tdf2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator +(const DimensionedField<scalar, GeoMesh>& df1,
	                                                  const dimensioned<scalar>& dt2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator +(const DimensionedField<scalar, GeoMesh>& df1, const scalar& t2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator +(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1,
	                                                  const dimensioned<scalar>& dt2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator
	+(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1, const scalar& t2);
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator -(const dimensioned<scalar>& dt1,
	                                                  const DimensionedField<scalar, GeoMesh>& df2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator -(const scalar& t1, const DimensionedField<scalar, GeoMesh>& df2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator -(const dimensioned<scalar>& dt1,
	                                                  const tmp<DimensionedField<scalar, GeoMesh>>& tdf2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator
	-(const scalar& t1, const tmp<DimensionedField<scalar, GeoMesh>>& tdf2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator -(const DimensionedField<scalar, GeoMesh>& df1,
	                                                  const dimensioned<scalar>& dt2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator -(const DimensionedField<scalar, GeoMesh>& df1, const scalar& t2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator -(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1,
	                                                  const dimensioned<scalar>& dt2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator
	-(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1, const scalar& t2);

		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator *(const DimensionedField<scalar, GeoMesh>& df1,
	                                                  const DimensionedField<scalar, GeoMesh>& df2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator *(const DimensionedField<scalar, GeoMesh>& df1,
	                                                  const tmp<DimensionedField<scalar, GeoMesh>>& tdf2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator *(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1,
	                                                  const DimensionedField<scalar, GeoMesh>& df2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator *(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1,
	                                                  const tmp<DimensionedField<scalar, GeoMesh>>& tdf2);
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1,
	                                                  const DimensionedField<scalar, GeoMesh>& df2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1,
	                                                  const tmp<DimensionedField<scalar, GeoMesh>>& tdf2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1,
	                                                  const DimensionedField<scalar, GeoMesh>& df2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1,
	                                                  const tmp<DimensionedField<scalar, GeoMesh>>& tdf2);

		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator /(const dimensioned<scalar>& dt1,
	                                                  const DimensionedField<scalar, GeoMesh>& df2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator /(const scalar& t1, const DimensionedField<scalar, GeoMesh>& df2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator /(const dimensioned<scalar>& dt1,
	                                                  const tmp<DimensionedField<scalar, GeoMesh>>& tdf2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator
	/(const scalar& t1, const tmp<DimensionedField<scalar, GeoMesh>>& tdf2);

		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow(const DimensionedField<scalar, GeoMesh>& df1,
	                                           const DimensionedField<scalar, GeoMesh>& df2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow(const DimensionedField<scalar, GeoMesh>& df1,
	                                           const tmp<DimensionedField<scalar, GeoMesh>>& tdf2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1,
	                                           const DimensionedField<scalar, GeoMesh>& df2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1,
	                                           const tmp<DimensionedField<scalar, GeoMesh>>& tdf2);
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow(const dimensioned<scalar>& dt1,
	                                           const DimensionedField<scalar, GeoMesh>& df2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow(const scalar& t1, const DimensionedField<scalar, GeoMesh>& df2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow(const dimensioned<scalar>& dt1,
	                                           const tmp<DimensionedField<scalar, GeoMesh>>& tdf2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow(const scalar& t1, const tmp<DimensionedField<scalar, GeoMesh>>& tdf2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow(const DimensionedField<scalar, GeoMesh>& df1,
	                                           const dimensioned<scalar>& dt2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow(const DimensionedField<scalar, GeoMesh>& df1, const scalar& t2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1,
	                                           const dimensioned<scalar>& dt2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow(const tmp<DimensionedField<scalar, GeoMesh>>& tdf2, const scalar& t2);

		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> atan2(const DimensionedField<scalar, GeoMesh>& df1,
	                                             const DimensionedField<scalar, GeoMesh>& df2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> atan2(const DimensionedField<scalar, GeoMesh>& df1,
	                                             const tmp<DimensionedField<scalar, GeoMesh>>& tdf2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> atan2(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1,
	                                             const DimensionedField<scalar, GeoMesh>& df2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> atan2(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1,
	                                             const tmp<DimensionedField<scalar, GeoMesh>>& tdf2);
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> atan2(const dimensioned<scalar>& dt1,
	                                             const DimensionedField<scalar, GeoMesh>& df2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> atan2(const scalar& t1, const DimensionedField<scalar, GeoMesh>& df2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> atan2(const dimensioned<scalar>& dt1,
	                                             const tmp<DimensionedField<scalar, GeoMesh>>& tdf2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> atan2(const scalar& t1, const tmp<DimensionedField<scalar, GeoMesh>>& tdf2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> atan2(const DimensionedField<scalar, GeoMesh>& df1,
	                                             const dimensioned<scalar>& dt2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> atan2(const DimensionedField<scalar, GeoMesh>& df1, const scalar& t2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> atan2(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1,
	                                             const dimensioned<scalar>& dt2);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> atan2(const tmp<DimensionedField<scalar, GeoMesh>>& tdf2, const scalar& t2);


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow3(const DimensionedField<scalar, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow3(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow4(const DimensionedField<scalar, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow4(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow5(const DimensionedField<scalar, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow5(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow6(const DimensionedField<scalar, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow6(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow025(const DimensionedField<scalar, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow025(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> sqrt(const DimensionedField<scalar, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> sqrt(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> cbrt(const DimensionedField<scalar, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> cbrt(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> sign(const DimensionedField<scalar, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> sign(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pos(const DimensionedField<scalar, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pos(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pos0(const DimensionedField<scalar, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pos0(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> neg(const DimensionedField<scalar, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> neg(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> neg0(const DimensionedField<scalar, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> neg0(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> posPart(const DimensionedField<scalar, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> posPart(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> negPart(const DimensionedField<scalar, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> negPart(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1);

		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> exp(const DimensionedField<scalar, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> exp(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> log(const DimensionedField<scalar, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> log(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> log10(const DimensionedField<scalar, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> log10(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> sin(const DimensionedField<scalar, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> sin(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> cos(const DimensionedField<scalar, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> cos(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> tan(const DimensionedField<scalar, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> tan(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> asin(const DimensionedField<scalar, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> asin(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> acos(const DimensionedField<scalar, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> acos(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> atan(const DimensionedField<scalar, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> atan(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> sinh(const DimensionedField<scalar, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> sinh(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> cosh(const DimensionedField<scalar, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> cosh(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> tanh(const DimensionedField<scalar, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> tanh(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> asinh(const DimensionedField<scalar, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> asinh(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> acosh(const DimensionedField<scalar, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> acosh(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> atanh(const DimensionedField<scalar, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> atanh(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> erf(const DimensionedField<scalar, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> erf(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> erfc(const DimensionedField<scalar, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> erfc(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> lgamma(const DimensionedField<scalar, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> lgamma(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> j0(const DimensionedField<scalar, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> j0(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> j1(const DimensionedField<scalar, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> j1(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> y0(const DimensionedField<scalar, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> y0(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> y1(const DimensionedField<scalar, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> y1(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1);


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#define BesselFunc(func)                                                       \
//                                                                               \
//template<class GeoMesh>                                                        \
//tmp<DimensionedField<scalar, GeoMesh>> func                                    \
//(                                                                              \
//    const int n,                                                               \
//    const DimensionedField<scalar, GeoMesh>&                                   \
//);                                                                             \
//                                                                               \
//template<class GeoMesh>                                                        \
//tmp<DimensionedField<scalar, GeoMesh>> func                                    \
//(                                                                              \
//    const int n,                                                               \
//    const tmp<DimensionedField<scalar, GeoMesh>>&                              \
//);

		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> jn(const int n, const DimensionedField<scalar, GeoMesh>&);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> jn(const int n, const tmp<DimensionedField<scalar, GeoMesh>>&);
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> yn(const int n, const DimensionedField<scalar, GeoMesh>&);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> yn(const int n, const tmp<DimensionedField<scalar, GeoMesh>>&);

//#undef BesselFunc


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#include <undefFieldFunctionsM.hxx>

#include <DimensionedScalarFieldI.hxx>

//#ifdef NoRepository
//#include <DimensionedScalarField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_DimensionedScalarField_Header
