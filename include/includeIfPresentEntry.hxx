#pragma once
#ifndef _includeIfPresentEntry_Header
#define _includeIfPresentEntry_Header

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
	tnbLib::functionEntries::includeIfPresentEntry

Description
	Specify a file to include if it exists. Expects a single string to follow.

	The \c \#includeIfPresent directive is similar to the \c \#include
	directive, but does not generate an error if the file does not exist.

See also
	tnbLib::functionEntries::includeEntry

SourceFiles
	includeIfPresentEntry.C

\*---------------------------------------------------------------------------*/

#include <includeEntry.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionEntries
	{

		/*---------------------------------------------------------------------------*\
							Class includeIfPresentEntry Declaration
		\*---------------------------------------------------------------------------*/

		class includeIfPresentEntry
			:
			public includeEntry
		{

		public:

			//- Runtime type information
			//ClassName("includeIfPresent");
			static const char* typeName_() { return "includeIfPresent"; } 
			static FoamBase_EXPORT const ::tnbLib::word typeName; 
			static FoamBase_EXPORT int debug;


			// Constructors

				//- Disallow default bitwise copy construction
			FoamBase_EXPORT includeIfPresentEntry(const includeIfPresentEntry&) = delete;


			// Member Functions

				//- Execute the functionEntry in a sub-dict context
			static FoamBase_EXPORT bool execute(dictionary& parentDict, Istream&);

			//- Execute the functionEntry in a primitiveEntry context
			static FoamBase_EXPORT bool execute
			(
				const dictionary& parentDict,
				primitiveEntry&,
				Istream&
			);


			// Member Operators

				//- Disallow default bitwise assignment
			FoamBase_EXPORT void operator=(const includeIfPresentEntry&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionEntries
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_includeIfPresentEntry_Header
