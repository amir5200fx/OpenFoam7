#pragma once
#ifndef _prefixOSstream_Header
#define _prefixOSstream_Header

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
	tnbLib::prefixOSstream

Description
	Version of OSstream which prints a prefix on each line.

	This is useful for running in parallel as it allows the processor number
	to be automatically prepended to each message line.

SourceFiles
	prefixOSstream.C

\*---------------------------------------------------------------------------*/

#include <OSstream.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class prefixOSstream Declaration
	\*---------------------------------------------------------------------------*/

	class prefixOSstream
		:
		public OSstream
	{
		// Private Data

		bool printPrefix_;
		string prefix_;


		// Private Member Functions

		inline void checkWritePrefix();


	public:

		// Constructors

			//- Set stream status
		FoamBase_EXPORT prefixOSstream
		(
			ostream& os,
			const string& name,
			streamFormat format = ASCII,
			versionNumber version = currentVersion,
			compressionType compression = UNCOMPRESSED
		);


		// Member Functions

			// Enquiry

				//- Return the prefix of the stream
		const string& prefix() const
		{
			return prefix_;
		}

		//- Return non-const access to the prefix of the stream
		string& prefix()
		{
			return prefix_;
		}


		// Write functions

			//- Write next token to stream
		FoamBase_EXPORT virtual Ostream& write(const token&);

		//- Write character
		FoamBase_EXPORT virtual Ostream& write(const char);

		//- Write character string
		FoamBase_EXPORT virtual Ostream& write(const char*);

		//- Write word
		FoamBase_EXPORT virtual Ostream& write(const word&);

		//- Write string
		FoamBase_EXPORT virtual Ostream& write(const string&);

		//- Write std::string surrounded by quotes.
		//  Optional write without quotes.
		FoamBase_EXPORT virtual Ostream& writeQuoted
		(
			const std::string&,
			const bool quoted = true
		);

		//- Write int32_t
		FoamBase_EXPORT virtual Ostream& write(const int32_t);

		//- Write int64_t
		FoamBase_EXPORT virtual Ostream& write(const int64_t);

		//- Write floatScalar
		FoamBase_EXPORT virtual Ostream& write(const floatScalar);

		//- Write doubleScalar
		FoamBase_EXPORT virtual Ostream& write(const doubleScalar);

		//- Write longDoubleScalar
		FoamBase_EXPORT virtual Ostream& write(const longDoubleScalar);

		//- Write binary block
		FoamBase_EXPORT virtual Ostream& write(const char*, std::streamsize);

		//- Add indentation characters
		FoamBase_EXPORT virtual void indent();


		// Print

			//- Print description of IOstream to Ostream
		FoamBase_EXPORT virtual void print(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_prefixOSstream_Header
