#pragma once
#ifndef _uint32_Header
#define _uint32_Header

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
	uint32

Description
	32bit uinteger

SourceFiles
	uint32.C
	uint32IO.C

\*---------------------------------------------------------------------------*/

#include <cstdint>
#include <climits>
#include <cstdlib>

#include <word.hxx>
#include <pTraits.hxx>
#include <direction.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class Istream;
	class Ostream;

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	//- Return a word representation of an uint32
	FoamBase_EXPORT word name(const uint32_t);

	// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

	FoamBase_EXPORT uint32_t readUint32(Istream&);
	FoamBase_EXPORT bool read(const char*, uint32_t&);
	FoamBase_EXPORT Istream& operator>>(Istream&, uint32_t&);
	FoamBase_EXPORT Ostream& operator<<(Ostream&, const uint32_t);

	//- Template specialization for pTraits<uint32_t>
	template<>
	class pTraits<uint32_t>
	{
		uint32_t p_;

	public:

		//- Component type
		typedef uint32_t cmptType;


		// Member constants

			//- Dimensionality of space
		static FoamBase_EXPORT const direction dim = 3;

		//- Rank of uint32_t is 0
		static FoamBase_EXPORT const direction rank = 0;

		//- Number of components in uint32_t is 1
		static FoamBase_EXPORT const direction nComponents = 1;


		// Static Data Members

		static FoamBase_EXPORT const char* const typeName;
		static FoamBase_EXPORT const char* const componentNames[];
		static FoamBase_EXPORT const uint32_t zero;
		static FoamBase_EXPORT const uint32_t one;
		static FoamBase_EXPORT const uint32_t min;
		static FoamBase_EXPORT const uint32_t max;
		static FoamBase_EXPORT const uint32_t rootMax;
		static FoamBase_EXPORT const uint32_t rootMin;


		// Constructors

			//- Construct from primitive
		FoamBase_EXPORT explicit pTraits(const uint32_t&);

		//- Construct from Istream
		FoamBase_EXPORT pTraits(Istream&);


		// Member Functions

			//- Access to the uint32_t value
		operator uint32_t() const
		{
			return p_;
		}

		//- Access to the uint32_t value
		operator uint32_t&()
		{
			return p_;
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_uint32_Header
