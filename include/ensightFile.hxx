#pragma once
#ifndef _ensightFile_Header
#define _ensightFile_Header

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
	tnbLib::ensightFile

Description
	Ensight output with specialized write() for strings, integers and floats.
	Correctly handles binary write as well.

\*---------------------------------------------------------------------------*/

#include <OFstream.hxx>
#include <IOstream.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							Class ensightFile Declaration
	\*---------------------------------------------------------------------------*/

	class ensightFile
		:
		public OFstream
	{
		// Private Data

			//- Allow undef in results
		static FoamConversion_EXPORT bool allowUndef_;

		//- Value to represent undef in results
		static FoamConversion_EXPORT scalar undefValue_;

		//- The '*' mask appropriate for subDir
		static FoamConversion_EXPORT string mask_;

		//- The printf format for zero-padded subdirectory numbers
		static FoamConversion_EXPORT string dirFmt_;


	public:

		// Constructors

			//- Construct from pathname
		FoamConversion_EXPORT ensightFile
		(
			const fileName& pathname,
			IOstream::streamFormat format = IOstream::BINARY
		);

		//- Disallow default bitwise copy construction
		FoamConversion_EXPORT ensightFile(const ensightFile&);


		//- Destructor
		FoamConversion_EXPORT ~ensightFile();


		// Access

			//- Return setting for whether 'undef' values are allowed in results
		static FoamConversion_EXPORT bool allowUndef();

		//- The '*' mask appropriate for subDir
		static FoamConversion_EXPORT string mask();

		//- Consistent zero-padded numbers for subdirectories
		static FoamConversion_EXPORT string subDir(const label);

		//- Set width of subDir and mask. Default width is 8 digits.
		//  Max width is 31 digits.
		static FoamConversion_EXPORT void subDirWidth(const label);

		//- Return current width of subDir and mask.
		static FoamConversion_EXPORT label subDirWidth();


		// Edit

		static FoamConversion_EXPORT bool allowUndef(bool);

		//- Assign the value to represent undef in the results
		//  Returns the previous value
		//  NB: do not use values larger than floatScalarvGreat
		static FoamConversion_EXPORT scalar undefValue(const scalar);


		// Output

			//- Inherit write from Ostream
		using Ostream::write;

		//- Binary write
		FoamConversion_EXPORT virtual Ostream& write(const char* buf, std::streamsize count);

		//- Write element keyword with trailing newline, optionally with undef
		FoamConversion_EXPORT virtual Ostream& writeKeyword(const string& key);

		//- Write "C Binary" for binary files (eg, geometry/measured)
		FoamConversion_EXPORT Ostream& writeBinaryHeader();

		//- Write undef value
		FoamConversion_EXPORT Ostream& writeUndef();

		//- Write C-string as "%80s" or as binary
		FoamConversion_EXPORT Ostream& write(const char* value);

		//- Write string as "%80s" or as binary
		FoamConversion_EXPORT Ostream& write(const string& value);

		//- Write integer as "%10d" or as binary
		FoamConversion_EXPORT Ostream& write(const label value);

		//- Write integer with specified width or as binary
		FoamConversion_EXPORT Ostream& write(const label value, const label fieldWidth);

		//- Write float as "%12.5e" or as binary
		FoamConversion_EXPORT Ostream& write(const scalar value);

		//- Add carriage return to ascii stream
		FoamConversion_EXPORT void newline();


		// Member Operators

			//- Disallow default bitwise assignment
		FoamConversion_EXPORT void operator=(const ensightFile&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_ensightFile_Header
