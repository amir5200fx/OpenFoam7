#pragma once
#ifndef _scalar_Header
#define _scalar_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2019 OpenFOAM Foundation
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
	tnbLib::scalar

Description
	Single floating point number identical to float or double depending on
	whether WM_SP, WM_DP or WM_LP is defined.

SourceFiles
	scalar.C

\*---------------------------------------------------------------------------*/

#include <floatScalar.hxx>
#include <doubleScalar.hxx>
#include <longDoubleScalar.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define WM_DP

#if defined(WM_SP)

// Define scalar as a float

namespace tnbLib
{
	typedef floatScalar scalar;

	static const scalar great = floatScalarGreat;
	static const scalar rootGreat = floatScalarRootGreat;
	static const scalar vGreat = floatScalarVGreat;
	static const scalar rootVGreat = floatScalarRootVGreat;
	static const scalar small = floatScalarSmall;
	static const scalar rootSmall = floatScalarRootSmall;
	static const scalar vSmall = floatScalarVSmall;
	static const scalar rootVSmall = floatScalarRootVSmall;
}

#elif defined(WM_DP)

// Define scalar as a double

namespace tnbLib
{
	typedef doubleScalar scalar;

	static const scalar great = doubleScalarGreat;
	static const scalar rootGreat = doubleScalarRootGreat;
	static const scalar vGreat = doubleScalarVGreat;
	static const scalar rootVGreat = doubleScalarRootVGreat;
	static const scalar small = doubleScalarSmall;
	static const scalar rootSmall = doubleScalarRootSmall;
	static const scalar vSmall = doubleScalarVSmall;
	static const scalar rootVSmall = doubleScalarRootVSmall;
}

#elif defined(WM_LP)

// Define scalar as a long double

namespace tnbLib
{
	typedef longDoubleScalar scalar;

	static const scalar great = longDoubleScalarGreat;
	static const scalar rootGreat = longDoubleScalarRootGreat;
	static const scalar vGreat = longDoubleScalarVGreat;
	static const scalar rootVGreat = longDoubleScalarRootVGreat;
	static const scalar small = longDoubleScalarSmall;
	static const scalar rootSmall = longDoubleScalarRootSmall;
	static const scalar vSmall = longDoubleScalarVSmall;
	static const scalar rootVSmall = longDoubleScalarRootVSmall;
}

#else

#error "Precision not set, please set either WM_SP, WM_DP or WM_LP"

#endif

//- Deprecated limit constant for backward-compatibility
namespace tnbLib
{
	static const scalar GREAT = great;
	static const scalar ROOTGREAT = rootGreat;
	static const scalar VGREAT = vGreat;
	static const scalar ROOTVGREAT = rootVGreat;
	static const scalar SMALL = small;
	static const scalar ROOTSMALL = rootSmall;
	static const scalar VSMALL = vSmall;
	static const scalar ROOTVSMALL = rootVSmall;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// Additional global and transcendental functions

namespace tnbLib
{
	scalar readScalar(Istream& is);

	//- Inverse normalized incomplete gamma function
	scalar invIncGamma(const scalar a, const scalar P);

	//- Normalized upper incomplete gamma function
	scalar incGammaRatio_Q(const scalar a, const scalar x);

	//- Normalized lower incomplete gamma function
	scalar incGammaRatio_P(const scalar a, const scalar x);

	//- Upper incomplete gamma function
	scalar incGamma_Q(const scalar a, const scalar x);

	//- Lower incomplete gamma function
	scalar incGamma_P(const scalar a, const scalar x);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_scalar_Header
