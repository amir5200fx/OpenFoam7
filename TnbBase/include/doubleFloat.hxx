#pragma once
#ifndef _doubleFloat_Header
#define _doubleFloat_Header

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

\*---------------------------------------------------------------------------*/

#include <label.hxx>
#include <products.hxx>

#include <cmath>

#ifndef DUMMY_SCALAR_FUNCTIONS
#define DUMMY_SCALAR_FUNCTIONS
inline float j0f(float x) { return float(_j0(double(x))); }
inline float j1f(float x) { return float(_j1(double(x))); }
inline float y0f(float x) { return float(_y0(double(x))); }
inline float y1f(float x) { return float(_y1(double(x))); }
inline float jnf(const int n, const float s) { return float(_jn(n, double(s))); }
inline float ynf(const int n, const float s) { return float(_yn(n, double(s))); }
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<class Cmpt>
	class typeOfRank<Cmpt, 0>
	{
	public:

		typedef Cmpt type;
	};


	template<class Cmpt>
	class symmTypeOfRank<Cmpt, 0>
	{
	public:

		typedef Cmpt type;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<class T>
	inline bool equal(const T& s1, const T& s2)
	{
		return s1 == s2;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_doubleFloat_Header
