#pragma once
#ifndef _negEntry_Header
#define _negEntry_Header

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
	tnbLib::functionEntries::negEntry

Description
	Negate a dictionary variable by prefixing with \c #neg

	E.g.
	\verbatim
		Umean 5.75;
		.
		.
		.
		inlet
		{
			type            uniformFixedValue;
			uniformValue    (#neg $Umean 0 0);
		}
	\endverbatim
	Note the space required between the \c #neg and the '$'

SourceFiles
	negEntry.C

\*---------------------------------------------------------------------------*/

#include <functionEntry.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionEntries
	{

		/*---------------------------------------------------------------------------*\
								 Class negEntry Declaration
		\*---------------------------------------------------------------------------*/

		class negEntry
			:
			public functionEntry
		{
			// Private Member Functions

				//- Lookup variable, negate and return as a string
			static FoamBase_EXPORT string negateVariable
			(
				const dictionary& parentDict,
				Istream& is
			);


		public:

			//- Runtime type information
			//ClassName("neg");
			static const char* typeName_() { return "neg"; } 
			static FoamBase_EXPORT const ::tnbLib::word typeName; 
			static FoamBase_EXPORT int debug;


			// Constructors

				//- Disallow default bitwise copy construction
			FoamBase_EXPORT negEntry(const negEntry&) = delete;


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
			FoamBase_EXPORT void operator=(const negEntry&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionEntries
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_negEntry_Header
