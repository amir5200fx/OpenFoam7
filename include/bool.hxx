#pragma once
#ifndef _bool_Header
#define _bool_Header

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

Primitive
	bool

Description
	System bool

SourceFiles
	boolIO.C

\*---------------------------------------------------------------------------*/

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <includeModule.hxx>

namespace tnbLib
{

	class Istream;
	class Ostream;

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	FoamBase_EXPORT Istream& operator>>(Istream&, bool&);
	FoamBase_EXPORT Ostream& operator<<(Ostream&, const bool);

	FoamBase_EXPORT bool readBool(Istream&);

	inline void writeEntry(Ostream& os, const bool value)
	{
		os << value;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <pTraits.hxx>
#include <direction.hxx>

namespace tnbLib
{

	// template specialisation for pTraits<bool>
	template<>
	class pTraits<bool>
	{
		bool p_;

	public:

		//- Component type
		typedef bool cmptType;

		// Member constants

			//- Dimensionality of space
		static FoamBase_EXPORT const direction dim = 3;

		//- Rank of bool is 0
		static FoamBase_EXPORT const direction rank = 0;

		//- Number of components in bool is 1
		static FoamBase_EXPORT const direction nComponents = 1;


		// Static Data Members

		static FoamBase_EXPORT const char* const typeName;
		static FoamBase_EXPORT const char* const componentNames[];
		static FoamBase_EXPORT const bool zero;
		static FoamBase_EXPORT const bool one;


		// Constructors

			//- Construct from primitive
		FoamBase_EXPORT explicit pTraits(const bool&);

		//- Construct from Istream
		FoamBase_EXPORT pTraits(Istream&);


		// Member Functions

			//- Access to the bool value
		operator bool() const
		{
			return p_;
		}

		//- Access to the bool value
		operator bool&()
		{
			return p_;
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_bool_Header
