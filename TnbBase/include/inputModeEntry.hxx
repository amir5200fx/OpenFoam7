#pragma once
#ifndef _inputModeEntry_Header
#define _inputModeEntry_Header

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
	tnbLib::functionEntries::inputModeEntry

Description
	Specify the input mode when reading dictionaries, expects
	a single word to follow.

	An example of \c \#inputMode directive:
	\verbatim
		#inputMode merge
	\endverbatim

	The possible input modes:
	  - \par merge      merge sub-dictionaries when possible
	  - \par overwrite  keep last entry and silently remove previous ones
	  - \par protect    keep initial entry and silently ignore subsequent ones
	  - \par warn       keep initial entry and warn about subsequent ones
	  - \par error      issue a FatalError for duplicate entries
	  - \par default    currently identical to merge

SourceFiles
	inputModeEntry.C

\*---------------------------------------------------------------------------*/

#include <functionEntry.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionEntries
	{

		/*---------------------------------------------------------------------------*\
								Class inputModeEntry Declaration
		\*---------------------------------------------------------------------------*/

		class inputModeEntry
			:
			public functionEntry
		{
			//- The input mode options
			enum inputMode
			{
				MERGE,
				OVERWRITE,
				PROTECT,
				WARN,
				ERROR
			};

			//- The current input mode
			static FoamBase_EXPORT inputMode mode_;


			// Private Member Functions

				//- Read the mode as a word and set enum appropriately
			static FoamBase_EXPORT void setMode(Istream&);


		public:

			//- Runtime type information
			static const char* typeName_() { return "inputMode"; } 
			static FoamBase_EXPORT const ::tnbLib::word typeName; 
			static FoamBase_EXPORT int debug;


			// Constructors

				//- Disallow default bitwise copy construction
			FoamBase_EXPORT inputModeEntry(const inputModeEntry&) = delete;


			// Member Functions

				//- Execute the functionEntry in a sub-dict context
			static FoamBase_EXPORT bool execute(dictionary& parentDict, Istream&);

			//- Reset the inputMode to %default (ie, %merge)
			static FoamBase_EXPORT void clear();

			//- Return true if the inputMode is %merge
			static FoamBase_EXPORT bool merge();

			//- Return true if the inputMode is %overwrite
			static FoamBase_EXPORT bool overwrite();

			//- Return true if the inputMode is %protect
			static FoamBase_EXPORT bool protect();

			//- Return true if the inputMode is %error
			static FoamBase_EXPORT bool error();


			// Member Operators

				//- Disallow default bitwise assignment
			FoamBase_EXPORT void operator=(const inputModeEntry&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionEntries
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_inputModeEntry_Header
