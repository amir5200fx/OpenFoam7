#pragma once
#ifndef _calcEntry_Header
#define _calcEntry_Header

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
	tnbLib::functionEntries::calcEntry

Description
	Uses dynamic compilation to provide calculating functionality
	for entering dictionary entries.

	E.g.

	\verbatim
	a 1.0;
	b 3;
	c #calc "$a/$b";
	\endverbatim

	Note the explicit trailing 0 ('1.0') to force a to be read (and written)
	as a floating point number.

Note
	Internally this is just a wrapper around codeStream functionality - the
	#calc string gets used to construct a dictionary for codeStream.

SourceFiles
	calcEntry.C

\*---------------------------------------------------------------------------*/

#include <functionEntry.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class dlLibraryTable;

	namespace functionEntries
	{

		/*---------------------------------------------------------------------------*\
								 Class calcEntry Declaration
		\*---------------------------------------------------------------------------*/

		class calcEntry
			:
			public functionEntry
		{

		public:

			//- Runtime type information
			//ClassName("calc");
			static const char* typeName_() { return "calc"; } 
			static FoamBase_EXPORT const ::tnbLib::word typeName; 
			static FoamBase_EXPORT int debug;


			// Constructors

				//- Disallow default bitwise copy construction
			calcEntry(const calcEntry&) = delete;


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
			void operator=(const calcEntry&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionEntries
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_calcEntry_Header
