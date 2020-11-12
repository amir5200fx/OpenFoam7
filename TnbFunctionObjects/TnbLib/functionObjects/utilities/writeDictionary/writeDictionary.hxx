#pragma once
#ifndef _writeDictionary_Header
#define _writeDictionary_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2019 OpenFOAM Foundation
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
	tnbLib::functionObjects::writeDictionary

Description
	Writes dictionaries on start-up and on change.

SourceFiles
	writeDictionary.C

\*---------------------------------------------------------------------------*/

#include <functionObject.hxx>
#include <wordList.hxx>
#include <SHA1Digest.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class objectRegistry;

	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
							   Class writeDictionary Declaration
		\*---------------------------------------------------------------------------*/

		class writeDictionary
			:
			public functionObject
		{
			// Private Data

				//- Reference to the database
			const objectRegistry& obr_;

			//- Names of dictionaries to monitor
			wordList dictNames_;

			//- List of changed dictionaries (only those registered to database)
			List<SHA1Digest> digests_;


			// Private Member Functions

				//- Helper function to write the dictionary if found at location
			FoamFunctionObjects_EXPORT bool tryDirectory
			(
				const label dictI,
				const word& location,
				bool& firstDict
			);


		public:

			//- Runtime type information
			//TypeName("writeDictionary");
			static const char* typeName_() { return "writeDictionary"; }
			static FoamFunctionObjects_EXPORT const ::tnbLib::word typeName;
			static FoamFunctionObjects_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from Time and dictionary
			FoamFunctionObjects_EXPORT writeDictionary
			(
				const word& name,
				const Time& runTime,
				const dictionary& dict
			);

			//- Disallow default bitwise copy construction
			FoamFunctionObjects_EXPORT writeDictionary(const writeDictionary&) = delete;


			//- Destructor
			FoamFunctionObjects_EXPORT virtual ~writeDictionary();


			// Member Functions

				//- Read the writeDictionary data
			FoamFunctionObjects_EXPORT virtual bool read(const dictionary&);

			//- Execute, currently does nothing
			FoamFunctionObjects_EXPORT virtual bool execute();

			//- Write the selected dictionaries
			FoamFunctionObjects_EXPORT virtual bool write();


			// Member Operators

				//- Disallow default bitwise assignment
			FoamFunctionObjects_EXPORT void operator=(const writeDictionary&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_writeDictionary_Header
