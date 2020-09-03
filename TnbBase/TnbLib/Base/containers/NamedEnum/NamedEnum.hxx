#pragma once
#ifndef _NamedEnum_Header
#define _NamedEnum_Header

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

Class
	tnbLib::NamedEnum

Description
	Initialise the NamedEnum HashTable from the static list of names.

SourceFiles
	NamedEnum.C

\*---------------------------------------------------------------------------*/

#include <HashTable.hxx>
#include <stringList.hxx>
#include <wordList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							  Class NamedEnum Declaration
	\*---------------------------------------------------------------------------*/

	template<class Enum, unsigned int nEnum>
	class NamedEnum
		:
		public HashTable<unsigned int>
	{
		// Private Member Functions

			//- Disallow default bitwise copy construction
		NamedEnum(const NamedEnum&) = delete;

		//- Disallow default bitwise assignment
		void operator=(const NamedEnum&) = delete;


	public:

		// Static Data Members

			//- The set of names corresponding to the enumeration Enum
		static const char* names[nEnum];


		// Constructors

			//- Construct from names
		NamedEnum();


		// Member Functions

			//- Read a word from Istream and return the corresponding
			//  enumeration element
		Enum read(Istream&) const;

		//- Write the name representation of the enumeration to an Ostream
		void write(const Enum e, Ostream&) const;

		//- The set of names as a list of strings
		static stringList strings();

		//- The set of names as a list of words
		static wordList words();


		// Member Operators

			//- Return the enumeration element corresponding to the given name
		const Enum operator[](const char* name) const
		{
			return Enum(HashTable<unsigned int>::operator[](name));
		}

		//- Return the enumeration element corresponding to the given name
		const Enum operator[](const word& name) const
		{
			return Enum(HashTable<unsigned int>::operator[](name));
		}

		//- Return the name of the given enumeration element
		const char* operator[](const Enum e) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <NamedEnumI.hxx>

//#ifdef NoRepository
//#include <NamedEnum.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_NamedEnum_Header
