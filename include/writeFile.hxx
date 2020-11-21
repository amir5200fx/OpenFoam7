#pragma once
#ifndef _writeFile_Header
#define _writeFile_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2012-2019 OpenFOAM Foundation
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
	tnbLib::functionObjects::writeFile

Description
	functionObject base class for writing single files

See also
	tnbLib::functionObject
	tnbLib::functionObjects::logFiles

SourceFiles
	writeFile.C

\*---------------------------------------------------------------------------*/

#include <objectRegistry.hxx>
#include <IOmanip.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
							 Class functionObjectFile Declaration
		\*---------------------------------------------------------------------------*/

		class writeFile
		{

		protected:

			// Protected data

				//- Reference to the region objectRegistry
			const objectRegistry& fileObr_;

			//- Prefix
			const word prefix_;


		public:

			//- Directory prefix
			static FoamBase_EXPORT const word outputPrefix;

			//- Additional characters for writing
			static FoamBase_EXPORT label addChars;


			// Constructors

				//- Construct from objectRegistry and prefix
			FoamBase_EXPORT writeFile
			(
				const objectRegistry& obr,
				const word& prefix
			);

			//- Disallow default bitwise copy construction
			FoamBase_EXPORT writeFile(const writeFile&) = delete;


			//- Destructor
			FoamBase_EXPORT ~writeFile();


			// Member Functions

				//- Initialise the output stream for writing
			FoamBase_EXPORT void initStream(Ostream& os) const;

			//- Return the base directory for output
			FoamBase_EXPORT fileName baseFileDir() const;

			//- Return the base directory for the current time value
			FoamBase_EXPORT fileName baseTimeDir() const;

			//- Return the value width when writing to stream with optional offset
			FoamBase_EXPORT Omanip<int> valueWidth(const label offset = 0) const;

			//- Write a commented string to stream
			FoamBase_EXPORT void writeCommented(Ostream& os, const string& str) const;

			//- Write a tabbed string to stream
			FoamBase_EXPORT void writeTabbed(Ostream& os, const string& str) const;

			//- Write a commented header to stream
			FoamBase_EXPORT void writeHeader(Ostream& os, const string& str) const;

			//- Write the current time to stream
			FoamBase_EXPORT void writeTime(Ostream& os) const;

			//- Write a (commented) header property and value pair
			template<class Type>
			void writeHeaderValue
			(
				Ostream& os,
				const string& property,
				const Type& value
			) const;

			//- Return width of character stream output
			FoamBase_EXPORT label charWidth() const;


			// Member Operators

				//- Disallow default bitwise assignment
			FoamBase_EXPORT void operator=(const writeFile&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <writeFileI.hxx>

//#ifdef NoRepository
//#include <writeFileTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_writeFile_Header
