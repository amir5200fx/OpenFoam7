#pragma once
#ifndef _dimensionedScalar_Header
#define _dimensionedScalar_Header

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

Typedef
	tnbLib::dimensionedScalar

Description
	Dimensioned scalar obtained from generic dimensioned type.

SourceFiles
	dimensionedScalar.C

\*---------------------------------------------------------------------------*/

#include <dimensionedType.hxx>
#include <scalar.hxx>
#include <dimensionedScalarFwd.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	FoamBase_EXPORT dimensionedScalar operator+(const dimensionedScalar&, const scalar);
	FoamBase_EXPORT dimensionedScalar operator+(const scalar, const dimensionedScalar&);

	FoamBase_EXPORT dimensionedScalar operator-(const dimensionedScalar&, const scalar);
	FoamBase_EXPORT dimensionedScalar operator-(const scalar, const dimensionedScalar&);

	FoamBase_EXPORT dimensionedScalar operator*(const dimensionedScalar&, const scalar);
	FoamBase_EXPORT dimensionedScalar operator/(const scalar, const dimensionedScalar&);

	FoamBase_EXPORT dimensionedScalar pow(const dimensionedScalar&, const dimensionedScalar&);
	FoamBase_EXPORT dimensionedScalar pow3(const dimensionedScalar&);
	FoamBase_EXPORT dimensionedScalar pow4(const dimensionedScalar&);
	FoamBase_EXPORT dimensionedScalar pow5(const dimensionedScalar&);
	FoamBase_EXPORT dimensionedScalar pow6(const dimensionedScalar&);
	FoamBase_EXPORT dimensionedScalar pow025(const dimensionedScalar&);

	FoamBase_EXPORT dimensionedScalar sqrt(const dimensionedScalar&);
	FoamBase_EXPORT dimensionedScalar cbrt(const dimensionedScalar&);
	FoamBase_EXPORT dimensionedScalar hypot(const dimensionedScalar&, const dimensionedScalar&);

	FoamBase_EXPORT dimensionedScalar sign(const dimensionedScalar&);
	FoamBase_EXPORT dimensionedScalar pos(const dimensionedScalar&);
	FoamBase_EXPORT dimensionedScalar pos0(const dimensionedScalar&);
	FoamBase_EXPORT dimensionedScalar neg(const dimensionedScalar&);
	FoamBase_EXPORT dimensionedScalar neg0(const dimensionedScalar&);
	FoamBase_EXPORT dimensionedScalar posPart(const dimensionedScalar&);
	FoamBase_EXPORT dimensionedScalar negPart(const dimensionedScalar&);

	FoamBase_EXPORT dimensionedScalar exp(const dimensionedScalar&);
	FoamBase_EXPORT dimensionedScalar log(const dimensionedScalar&);
	FoamBase_EXPORT dimensionedScalar log10(const dimensionedScalar&);
	FoamBase_EXPORT dimensionedScalar sin(const dimensionedScalar&);
	FoamBase_EXPORT dimensionedScalar cos(const dimensionedScalar&);
	FoamBase_EXPORT dimensionedScalar tan(const dimensionedScalar&);
	FoamBase_EXPORT dimensionedScalar asin(const dimensionedScalar&);
	FoamBase_EXPORT dimensionedScalar acos(const dimensionedScalar&);
	FoamBase_EXPORT dimensionedScalar atan(const dimensionedScalar&);
	FoamBase_EXPORT dimensionedScalar atan2(const dimensionedScalar&, const dimensionedScalar&);
	FoamBase_EXPORT dimensionedScalar sinh(const dimensionedScalar&);
	FoamBase_EXPORT dimensionedScalar cosh(const dimensionedScalar&);
	FoamBase_EXPORT dimensionedScalar tanh(const dimensionedScalar&);
	FoamBase_EXPORT dimensionedScalar asinh(const dimensionedScalar&);
	FoamBase_EXPORT dimensionedScalar acosh(const dimensionedScalar&);
	FoamBase_EXPORT dimensionedScalar atanh(const dimensionedScalar&);
	FoamBase_EXPORT dimensionedScalar erf(const dimensionedScalar&);
	FoamBase_EXPORT dimensionedScalar erfc(const dimensionedScalar&);
	FoamBase_EXPORT dimensionedScalar lgamma(const dimensionedScalar&);
	FoamBase_EXPORT dimensionedScalar j0(const dimensionedScalar&);
	FoamBase_EXPORT dimensionedScalar j1(const dimensionedScalar&);
	FoamBase_EXPORT dimensionedScalar jn(const int, const dimensionedScalar&);
	FoamBase_EXPORT dimensionedScalar y0(const dimensionedScalar&);
	FoamBase_EXPORT dimensionedScalar y1(const dimensionedScalar&);
	FoamBase_EXPORT dimensionedScalar yn(const int, const dimensionedScalar&);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_dimensionedScalar_Header
