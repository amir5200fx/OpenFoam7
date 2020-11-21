#pragma once
#ifndef _hashedWordList_Header
#define _hashedWordList_Header

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
	tnbLib::hashedWordList

Description
	A wordList with hashed indices for faster lookup by name.

SourceFiles
	hashedWordListI.H
	hashedWordList.C

\*---------------------------------------------------------------------------*/

#include <wordList.hxx>
#include <HashTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class hashedWordList;

	// Forward declaration of friend functions and operators
	FoamBase_EXPORT Istream& operator>>(Istream&, hashedWordList&);
	FoamBase_EXPORT Ostream& operator<<(Ostream&, const hashedWordList&);


	/*---------------------------------------------------------------------------*\
						   Class hashedWordList Declaration
	\*---------------------------------------------------------------------------*/

	class hashedWordList
		:
		public List<word>
	{
		// Private Data

		HashTable<label, word> indices_;


		// Private Member Functions

			//- Rebuild the hash of indices
		FoamBase_EXPORT void rehash();

	public:

		// Constructors

			//- Construct null
		FoamBase_EXPORT hashedWordList();

		//- Copy constructor
		FoamBase_EXPORT hashedWordList(const hashedWordList&);

		//- Move constructor
		FoamBase_EXPORT hashedWordList(hashedWordList&&);

		//- Construct from list of names
		FoamBase_EXPORT hashedWordList(const UList<word>& names);

		//- Move constructor transferring the parameter contents
		FoamBase_EXPORT hashedWordList(List<word>&& names);

		//- Construct from number and list of names
		FoamBase_EXPORT hashedWordList(const label nNames, const char** names);

		//- Construct from a nullptr-terminated list of names
		FoamBase_EXPORT hashedWordList(const char** names);

		//- Construct from Istream
		FoamBase_EXPORT hashedWordList(Istream&);


		// Member Functions

			//- Clear the list, i.e. set size to zero.
		FoamBase_EXPORT void clear();

		//- Append an element at the end of the list
		FoamBase_EXPORT void append(const word&);

		//- Does the list contain the specified name
		inline bool found(const word&) const;

		//- Does the list contain the specified name
		inline bool contains(const word&) const;

		//- Transfer the contents of the argument List into this list
		//  and annul the argument list.
		FoamBase_EXPORT void transfer(List<word>&);


		// Member Operators

			//- Assignment operator
		inline void operator=(const hashedWordList&);

		//- Move assignment operator
		inline void operator=(hashedWordList&&);

		//- Assignment operator from list of names
		inline void operator=(const UList<word>& names);

		//- Return name corresponding to specified index
		inline const word& operator[](const label index) const;

		//- Return index corresponding to specified name
		inline label operator[](const word&) const;


		// Istream operators

		friend FoamBase_EXPORT Istream& operator>>(Istream&, hashedWordList&);
		friend FoamBase_EXPORT Ostream& operator<<(Ostream&, const hashedWordList&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <hashedWordListI.hxx>

#endif // !_hashedWordList_Header
