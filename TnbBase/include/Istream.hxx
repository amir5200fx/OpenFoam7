#pragma once
#ifndef _Istream_Header
#define _Istream_Header

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
	Foam::Istream

Description
	An Istream is an abstract base class for all input systems
	(streams, files, token lists etc).  The basic operations
	are construct, close, read token, read primitive and read binary
	block.

	In addition, version control and line number counting is incorporated.
	Usually one would use the read primitive member functions, but if one
	were reading a stream on unknown data sequence one can read token by
	token, and then analyse.

SourceFiles
	Istream.C

\*---------------------------------------------------------------------------*/

#include <IOstream.hxx>
//#include <token.hxx> deactivated by amir


namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						   Class Istream Declaration
\*---------------------------------------------------------------------------*/

	class token;

	class Istream
		: public IOstream
	{
		// Private data

			//- Has a token been put back on the stream
		bool putBack_;

		//- The last token put back on the stream
		token* putBackToken_;


	public:

		// Constructors

			//- Set stream status
		FoamBase_EXPORT Istream
		(
			streamFormat format = ASCII,
			versionNumber version = currentVersion,
			compressionType compression = UNCOMPRESSED
		);
		/*:
		IOstream(format, version, compression),
		putBack_(false)
	{}*/


	// Destructor

		FoamBase_EXPORT virtual ~Istream();
		//{}


		// Member functions

			// Read functions

		//- Put back token
		//  Only a single put back is permitted
		FoamBase_EXPORT void putBack(const token&);

		//- Get the put back token if there is one and return true.
		//  Return false if no put back token is available.
		FoamBase_EXPORT bool getBack(token&);

		//- Peek at the put back token without removing it.
		//  Returns false if no put back token is available and set the
		//  token to undefined.
		FoamBase_EXPORT 	bool peekBack(token&);

		//- Return next token from stream
		FoamBase_EXPORT virtual Istream& read(token&) = 0;

		//- Read a character
		FoamBase_EXPORT virtual Istream& read(char&) = 0;

		//- Read a word
		FoamBase_EXPORT virtual Istream& read(word&) = 0;

		// Read a string (including enclosing double-quotes)
		FoamBase_EXPORT virtual Istream& read(string&) = 0;

		//- Read a label
		FoamBase_EXPORT virtual Istream& read(label&) = 0;

		//- Read a floatScalar
		FoamBase_EXPORT virtual Istream& read(floatScalar&) = 0;

		//- Read a doubleScalar
		FoamBase_EXPORT virtual Istream& read(doubleScalar&) = 0;

		//- Read a longDoubleScalar
		FoamBase_EXPORT virtual Istream& read(longDoubleScalar&) = 0;

		//- Read binary block
		FoamBase_EXPORT virtual Istream& read(char*, std::streamsize) = 0;

		//- Rewind and return the stream so that it may be read again
		FoamBase_EXPORT virtual Istream& rewind() = 0;


		// Read List punctuation tokens

		FoamBase_EXPORT Istream& readBegin(const char* funcName);
		FoamBase_EXPORT Istream& readEnd(const char* funcName);
		FoamBase_EXPORT Istream& readEndBegin(const char* funcName);

		FoamBase_EXPORT char readBeginList(const char* funcName);
		FoamBase_EXPORT char readEndList(const char* funcName);


		// Member operators

			//- Return a non-const reference to const Istream
			//  Needed for read-constructors where the stream argument is temporary:
			//  e.g. thing thisThing(IFstream("thingFileName")());
		FoamBase_EXPORT Istream& operator()() const;
	};


	// --------------------------------------------------------------------
	// ------ Manipulators (not taking arguments)
	// --------------------------------------------------------------------

	typedef Istream& (*IstreamManip)(Istream&);

	//- operator>> handling for manipulators without arguments
	inline Istream& operator>>(Istream& is, IstreamManip f)
	{
		return f(is);
	}

	//- operator>> handling for manipulators without arguments
	inline Istream& operator>>(Istream& is, IOstreamManip f)
	{
		f(is);
		return is;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
}

#ifdef NoRepository
//#   include "HashTable.cxx"  // Edited by amir
#endif

#endif // !_Istream_Header