#pragma once
#ifndef _int64_Header
#define _int64_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2014-2019 OpenFOAM Foundation
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
	int64

Description
	64bit integer

SourceFiles
	int64.C
	int64IO.C

\*---------------------------------------------------------------------------*/

#include <cstdint>
#include <climits>
#include <cstdlib>

#include <word.hxx>
#include <pTraits.hxx>
#include <direction.hxx>

#ifndef UINT64_MIN
#define UINT64_MIN 0
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class Istream;
	class Ostream;

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	//- Return a word representation of an int64
	FoamBase_EXPORT word name(const int64_t);

	// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

	FoamBase_EXPORT int64_t readInt64(Istream&);
	FoamBase_EXPORT bool read(const char*, int64_t&);
	FoamBase_EXPORT Istream& operator>>(Istream&, int64_t&);
	FoamBase_EXPORT Ostream& operator<<(Ostream&, const int64_t);

	inline void writeEntry(Ostream& os, const int64_t value)
	{
		os << value;
	}


	//- Template specialization for pTraits<int64_t>
	template<>
	class pTraits<int64_t>
	{
		int64_t p_;

	public:

		//- Component type
		typedef int64_t cmptType;


		// Member constants

			//- Dimensionality of space
		static FoamBase_EXPORT const direction dim = 3;

		//- Rank of int64_t is 0
		static FoamBase_EXPORT const direction rank = 0;

		//- Number of components in int64_t is 1
		static FoamBase_EXPORT const direction nComponents = 1;


		// Static Data Members

		static FoamBase_EXPORT const char* const typeName;
		static FoamBase_EXPORT const char* const componentNames[];
		static FoamBase_EXPORT const int64_t zero;
		static FoamBase_EXPORT const int64_t one;
		static FoamBase_EXPORT const int64_t min;
		static FoamBase_EXPORT const int64_t max;
		static FoamBase_EXPORT const int64_t rootMax;
		static FoamBase_EXPORT const int64_t rootMin;


		// Constructors

			//- Construct from primitive
		FoamBase_EXPORT explicit pTraits(const int64_t&);

		//- Construct from Istream
		FoamBase_EXPORT pTraits(Istream&);


		// Member Functions

			//- Access to the int64_t value
		operator int64_t() const
		{
			return p_;
		}

		//- Access to the int value
		operator int64_t&()
		{
			return p_;
		}
	};


	inline int64_t mag(const int64_t l)
	{
		return (int64_t)::labs((long)l);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_int64_Header
