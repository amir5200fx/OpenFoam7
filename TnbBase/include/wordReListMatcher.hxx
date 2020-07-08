#pragma once
#ifndef _wordReListMatcher_Header
#define _wordReListMatcher_Header

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
	tnbLib::wordReListMatcher

Description
	A wrapper for matching a List of wordRe.

Note
	The constructor should remain non-explicit. This allows automatic
	conversion from UList\<wordRe\> to wordReListMatcher in search
	functions.

SourceFiles
	wordReListMatcherI.H

\*---------------------------------------------------------------------------*/

#include <wordReList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class wordReListMatcher Declaration
	\*---------------------------------------------------------------------------*/

	class wordReListMatcher
	{
		// Private Data

			//- Reference to underlying list
		const UList<wordRe>& reList_;

	public:

		// Constructors

			//- Construct from a List of wordRe
		inline wordReListMatcher(const UList<wordRe>&);


		// Member Functions

			// Access

		inline label size() const;
		inline bool  empty() const;

		//- Return underlying list of wordRe
		inline const UList<wordRe>& operator()() const;


		// Searching

				//- Return true if string matches any of the regular expressions
				//  Smart match as regular expression or as a string.
				//  Optionally specify a literal match only.
		inline bool match(const string&, bool literalMatch = false) const;

	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <wordReListMatcherI.hxx>

#endif // !_wordReListMatcher_Header
