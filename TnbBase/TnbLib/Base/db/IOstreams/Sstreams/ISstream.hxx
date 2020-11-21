#pragma once
#ifndef _ISstream_Header
#define _ISstream_Header

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
	tnbLib::ISstream

Description
	Generic input stream.

SourceFiles
	ISstreamI.H
	ISstream.C

\*---------------------------------------------------------------------------*/

#include <Istream.hxx>
#include <fileName.hxx>

#include <iostream>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class ISstream Declaration
	\*---------------------------------------------------------------------------*/

	class ISstream
		:
		public Istream
	{
		// Private Data

		fileName name_;
		istream& is_;


		// Private Member Functions

		FoamBase_EXPORT char nextValid();

		FoamBase_EXPORT void readWordToken(token&);

		// Private Member Functions


			//- Read a verbatim string (excluding block delimiters).
		FoamBase_EXPORT Istream& readVerbatim(string&);

		//- Read a variable name (includes '{')
		FoamBase_EXPORT Istream& readVariable(string&);


	public:

		// Constructors

			//- Construct as wrapper around istream
		inline ISstream
		(
			istream& is,
			const string& name,
			streamFormat format = ASCII,
			versionNumber version = currentVersion,
			compressionType compression = UNCOMPRESSED
		);


		//- Destructor
		virtual ~ISstream()
		{}


		// Member Functions

			// Inquiry

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


		// Read functions

			//- Raw, low-level get character function.
		inline ISstream& get(char&);

		//- Raw, low-level peek function.
		//  Does not remove the character from the stream.
		//  Returns the next character in the stream or EOF if the
		//  end of file is read.
		inline int peek();

		//- Raw, low-level getline into a string function.
		inline ISstream& getLine(string&);

		//- Raw, low-level putback character function.
		inline ISstream& putback(const char&);

		//- Return next token from stream
		FoamBase_EXPORT virtual Istream& read(token&);

		//- Read a character
		FoamBase_EXPORT virtual Istream& read(char&);

		//- Read a word
		FoamBase_EXPORT virtual Istream& read(word&);

		//- Read a string (including enclosing double-quotes).
		//  Backslashes are retained, except when escaping double-quotes
		//  and an embedded newline character.
		FoamBase_EXPORT virtual Istream& read(string&);

		//- Read a label
		FoamBase_EXPORT virtual Istream& read(label&);

		//- Read a floatScalar
		FoamBase_EXPORT virtual Istream& read(floatScalar&);

		//- Read a doubleScalar
		FoamBase_EXPORT virtual Istream& read(doubleScalar&);

		//- Read a longDoubleScalar
		FoamBase_EXPORT virtual Istream& read(longDoubleScalar&);

		//- Read binary block
		FoamBase_EXPORT virtual Istream& read(char*, std::streamsize);

		//- Rewind and return the stream so that it may be read again
		FoamBase_EXPORT virtual Istream& rewind();


		// Stream state functions

			//- Set flags of output stream
		FoamBase_EXPORT virtual ios_base::fmtflags flags(const ios_base::fmtflags flags);


		// STL stream

			//- Access to underlying std::istream
		virtual istream& stdStream()
		{
			return is_;
		}

		//- Const access to underlying std::istream
		virtual const istream& stdStream() const
		{
			return is_;
		}


		// Print

			//- Print description of IOstream to Ostream
		FoamBase_EXPORT virtual void print(Ostream&) const;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamBase_EXPORT void operator=(const ISstream&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <ISstreamI.hxx>

#endif // !_ISstream_Header
