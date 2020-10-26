#pragma once
#ifndef _ITstream_Header
#define _ITstream_Header

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
	tnbLib::ITstream

Description
	Input token stream.

SourceFiles
	ITstream.C

\*---------------------------------------------------------------------------*/

#include <tokenList.hxx>
#include <Istream.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class ITstream Declaration
	\*---------------------------------------------------------------------------*/

	class ITstream
		:
		public Istream,
		public tokenList
	{
		// Private Data

			//- Name of ITstream
		fileName name_;

		//- Index of token currently being read
		label tokenIndex_;


	public:

		// Constructors

			//- Construct from components
		ITstream
		(
			const string& name,
			const UList<token>& tokens,
			streamFormat format = ASCII,
			versionNumber version = currentVersion
		)
			:
			Istream(format, version),
			tokenList(tokens),
			name_(name),
			tokenIndex_(0)
		{
			setOpened();
			setGood();
		}


		//- Move construct from components, transferring the tokens
		ITstream
		(
			const string& name,
			List<token>&& tokens,
			streamFormat format = ASCII,
			versionNumber version = currentVersion
		)
			:
			Istream(format, version),
			tokenList(move(tokens)),
			name_(name),
			tokenIndex_(0)
		{
			setOpened();
			setGood();
		}


		//- Copy constructor
		ITstream(const ITstream& its)
			:
			Istream(ASCII, currentVersion),
			tokenList(its),
			name_(its.name_),
			tokenIndex_(0)
		{
			setOpened();
			setGood();
		}


		//- Destructor
		virtual ~ITstream()
		{}


		// Member Functions

			// Inquiry

				//- Return the name of the stream
		const fileName& name() const
		{
			return name_;
		}

		//- Return non-const access to the name of the stream
		fileName& name()
		{
			return name_;
		}

		//- Return the current token index
		label tokenIndex() const
		{
			return tokenIndex_;
		}

		//- Return non-const access to the current token index
		label& tokenIndex()
		{
			return tokenIndex_;
		}

		//- Return the number of remaining tokens
		label nRemainingTokens() const
		{
			return size() - tokenIndex_;
		}

		//- Return flags of output stream
		ios_base::fmtflags flags() const
		{
			return ios_base::fmtflags(0);
		}


		// Read functions

			//- Return next token from stream
		FoamBase_EXPORT virtual Istream& read(token&);

		//- Read a character
		FoamBase_EXPORT virtual Istream& read(char&);

		//- Read a word
		FoamBase_EXPORT virtual Istream& read(word&);

		// Read a string (including enclosing double-quotes)
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


		// Edit

			//- Set flags of stream
		ios_base::fmtflags flags(const ios_base::fmtflags)
		{
			return ios_base::fmtflags(0);
		}


		// Print

			//- Print description of IOstream to Ostream
		FoamBase_EXPORT void print(Ostream&) const;


		// Member Operators

			//- Assignment operator
		FoamBase_EXPORT void operator=(const ITstream& its)
		{
			Istream::operator=(its);
			tokenList::operator=(its);
			name_ = its.name_;
			tokenIndex_ = 0;

			setOpened();
			setGood();
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_ITstream_Header
