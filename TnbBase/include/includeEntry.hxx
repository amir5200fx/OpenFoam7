#pragma once
#ifndef _includeEntry_Header
#define _includeEntry_Header

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
	tnbLib::functionEntries::includeEntry

Description
	Specify an include file when reading dictionaries, expects a
	single string to follow.

	An example of the \c \#include directive:
	\verbatim
		#include "includeFile"
	\endverbatim

	The usual expansion of environment variables and other constructs
	(eg, the \c ~OpenFOAM/ expansion) is retained.

See also
	fileName, string::expand()

SourceFiles
	includeEntry.C

\*---------------------------------------------------------------------------*/

#include <functionEntry.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionEntries
	{

		/*---------------------------------------------------------------------------*\
								Class includeEntry Declaration
		\*---------------------------------------------------------------------------*/

		class includeEntry
			:
			public functionEntry
		{

		protected:

			// Protected Member Functions

				//- Read the include fileName from Istream, expand and return
			static FoamBase_EXPORT fileName includeFileName(Istream&, const dictionary&);

			//- Expand include fileName and return
			static FoamBase_EXPORT fileName includeFileName
			(
				const fileName& dir,
				const fileName&,
				const dictionary&
			);


		public:

			// Static Data Members

				//- Report which file is included to stdout
			static FoamBase_EXPORT bool log;


			//- Runtime type information
			//ClassName("include");
			static const char* typeName_() { return "include"; } 
			static FoamBase_EXPORT const ::tnbLib::word typeName; 
			static FoamBase_EXPORT int debug;


			// Constructors

				//- Disallow default bitwise copy construction
			FoamBase_EXPORT includeEntry(const includeEntry&) = delete;


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
			FoamBase_EXPORT void operator=(const includeEntry&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionEntries
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_includeEntry_Header
