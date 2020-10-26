#pragma once
#ifndef _word_Header
#define _word_Header

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
	tnbLib::word

Description
	A class for handling words, derived from string.

	A word is a string of characters without whitespace, quotes, slashes,
	semicolons or brace brackets. Words are delimited by whitespace.

SourceFiles
	word.C
	wordIO.C

\*---------------------------------------------------------------------------*/

#include <tnbString.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of friend functions and operators
	class word;
	inline word operator&(const word&, const word&);
	FoamBase_EXPORT Istream& operator>>(Istream&, word&);
	FoamBase_EXPORT Ostream& operator<<(Ostream&, const word&);


	/*---------------------------------------------------------------------------*\
							   Class word Declaration
	\*---------------------------------------------------------------------------*/

	class word
		:
		public string
	{
		// Private Member Functions

			//- Strip invalid characters from this word
		inline void stripInvalid();


	public:

		// Static Data Members

		static FoamBase_EXPORT const char* const typeName;
		static FoamBase_EXPORT int debug;

		//- An empty word
		static FoamBase_EXPORT const word null;


		// Constructors

			//- Construct null
		inline word();

		//- Copy constructor
		inline word(const word&);

		//- Copy constructor of character array
		inline word(const char*, const bool doStripInvalid = true);

		//- Copy constructor with a maximum number of characters
		inline word
		(
			const char*,
			const size_type,
			const bool doStripInvalid
		);

		//- Copy constructor of string
		inline word(const string&, const bool doStripInvalid = true);

		//- Copy constructor of std::string
		inline word(const std::string&, const bool doStripInvalid = true);

		//- Construct from Istream
		FoamBase_EXPORT word(Istream&);


		// Member Functions

			//- Is this character valid for a word
		inline static bool valid(char);


		// Member Operators

			// Assignment

		inline void operator=(const word&);
		inline void operator=(const string&);
		inline void operator=(const std::string&);
		inline void operator=(const char*);


		// Friend Operators

		friend word operator&(const word&, const word&);


		// IOstream Operators

		friend Istream& operator>>(Istream&, word&);
		friend Ostream& operator<<(Ostream&, const word&);
	};


	FoamBase_EXPORT void writeEntry(Ostream& os, const word& value);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <wordI.hxx>

#endif // !_word_Header
