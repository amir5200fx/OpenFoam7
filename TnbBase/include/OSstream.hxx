#pragma once
#ifndef _OSstream_Header
#define _OSstream_Header

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
	tnbLib::OSstream

Description
	Generic output stream.

SourceFiles
	OSstreamI.H
	OSstream.C

\*---------------------------------------------------------------------------*/

#include <Ostream.hxx>
#include <fileName.hxx>

#include <iostream>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							  Class OSstream Declaration
	\*---------------------------------------------------------------------------*/

	class OSstream
		:
		public Ostream
	{
		// Private Data

		fileName name_;
		ostream& os_;


	public:

		// Constructors

			//- Set stream status
		OSstream
		(
			ostream& os,
			const string& name,
			streamFormat format = ASCII,
			versionNumber version = currentVersion,
			compressionType compression = UNCOMPRESSED
		);


		// Member Functions

			// Enquiry

				//- Return the name of the stream
				//  Useful for Fstream to return the filename
		virtual const fileName& name() const
		{
			return name_;
		}

		//- Return non-const access to the name of the stream
		//  Useful to alter the stream name
		virtual fileName& name()
		{
			return name_;
		}

		//- Return flags of output stream
		FoamBase_EXPORT virtual ios_base::fmtflags flags() const;


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
		//  In the rare case that the string contains a final trailing
		//  backslash, it will be dropped to the appearance of an escaped
		//  double-quote.
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


		// Stream state functions

			//- Set flags of output stream
		FoamBase_EXPORT virtual ios_base::fmtflags flags(const ios_base::fmtflags flags);

		//- Flush stream
		FoamBase_EXPORT virtual void flush();

		//- Add newline and flush stream
		FoamBase_EXPORT virtual void endl();

		//- Get width of output field
		FoamBase_EXPORT virtual int width() const;

		//- Set width of output field (and return old width)
		FoamBase_EXPORT virtual int width(const int);

		//- Get precision of output field
		FoamBase_EXPORT virtual int precision() const;

		//- Set precision of output field (and return old precision)
		FoamBase_EXPORT virtual int precision(const int);


		// STL stream

			//- Access to underlying std::ostream
		virtual ostream& stdStream()
		{
			return os_;
		}

		//- Const access to underlying std::ostream
		virtual const ostream& stdStream() const
		{
			return os_;
		}


		// Print

			//- Print description of IOstream to Ostream
		FoamBase_EXPORT virtual void print(Ostream&) const;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamBase_EXPORT void operator=(const OSstream&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <OSstreamI.hxx>

#endif // !_OSstream_Header
