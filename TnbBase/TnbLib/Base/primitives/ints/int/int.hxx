#pragma once
#ifndef _int_Header
#define _int_Header

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

Primitive
	int

Description
	System integer

SourceFiles
	intIO.C

\*---------------------------------------------------------------------------*/

#include <int32.hxx>
#include <int64.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

#define MAXMIN(retType, type1, type2)              \
                                                   \
inline retType max(const type1 s1, const type2 s2) \
{                                                  \
    return (s1 > s2)? s1: s2;                      \
}                                                  \
                                                   \
inline retType min(const type1 s1, const type2 s2) \
{                                                  \
    return (s1 < s2)? s1: s2;                      \
}


	inline int8_t max(const int8_t s1, const int8_t s2) { return (s1 > s2) ? s1 : s2; }
	inline int8_t min(const int8_t s1, const int8_t s2) { return (s1 < s2) ? s1 : s2; }
		
	inline int16_t max(const int16_t s1, const int16_t s2) { return (s1 > s2) ? s1 : s2; }
	inline int16_t min(const int16_t s1, const int16_t s2) { return (s1 < s2) ? s1 : s2; }

		
	inline int32_t max(const int32_t s1, const int32_t s2) { return (s1 > s2) ? s1 : s2; }
	inline int32_t min(const int32_t s1, const int32_t s2) { return (s1 < s2) ? s1 : s2; }
		
	inline int64_t max(const int64_t s1, const int32_t s2) { return (s1 > s2) ? s1 : s2; }
	inline int64_t min(const int64_t s1, const int32_t s2) { return (s1 < s2) ? s1 : s2; }
		
	inline int64_t max(const int32_t s1, const int64_t s2) { return (s1 > s2) ? s1 : s2; }
	inline int64_t min(const int32_t s1, const int64_t s2) { return (s1 < s2) ? s1 : s2; }
		
	inline int64_t max(const int64_t s1, const int64_t s2) { return (s1 > s2) ? s1 : s2; }
	inline int64_t min(const int64_t s1, const int64_t s2) { return (s1 < s2) ? s1 : s2; }


		// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

		int readInt(Istream&);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_int_Header
