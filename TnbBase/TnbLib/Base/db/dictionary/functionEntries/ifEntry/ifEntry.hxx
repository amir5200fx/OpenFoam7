#pragma once
#ifndef _ifEntry_Header
#define _ifEntry_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2018-2019 OpenFOAM Foundation
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
	tnbLib::functionEntries::ifEntry

Description
	Conditional parsing of dictionary entries.

	E.g.
	\verbatim
		U_inlet 15;

		#if #calc "${U_inlet} < 10"
			..
		#else
			..
		#endif
	\endverbatim

	Note:
	- only supports single line, '\' is not supported
	- condition should be readable as a \c Switch
	  (supports 0,1, true, false, etc.)

See also
	tnbLib::functionEntries::ifeqEntry
	tnbLib::Switch

SourceFiles
	ifEntry.C

\*---------------------------------------------------------------------------*/

#include <ifeqEntry.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionEntries
	{

		/*---------------------------------------------------------------------------*\
								  Class ifEntry Declaration
		\*---------------------------------------------------------------------------*/

		class ifEntry
			:
			public ifeqEntry
		{
			friend class ifeqEntry;

			// Private Member Functions

				//- Execute the functionEntry in a sub-dict context
			static bool execute
			(
				DynamicList<filePos>& stack,
				dictionary& parentDict,
				Istream& is
			);


		public:

			//- Runtime type information
			//ClassName("if");
			static const char* typeName_() { return "if"; }
			static FoamBase_EXPORT const ::tnbLib::word typeName; 
			static FoamBase_EXPORT int debug;


			// Constructors

				//- Disallow default bitwise copy construction
			FoamBase_EXPORT ifEntry(const ifEntry&) = delete;


			// Member Functions

				//- Execute the functionEntry in a sub-dict context
			static FoamBase_EXPORT bool execute(dictionary& parentDict, Istream& is);


			// Member Operators

				//- Disallow default bitwise assignment
			FoamBase_EXPORT void operator=(const ifEntry&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionEntries
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_ifEntry_Header
