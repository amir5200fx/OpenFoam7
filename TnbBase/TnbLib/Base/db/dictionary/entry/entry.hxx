#pragma once
#ifndef _entry_Header
#define _entry_Header

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
	tnbLib::entry

Description
	A keyword and a list of tokens is an 'entry'.

	An entry can be read, written and printed, and the types and values of
	its tokens analysed.  An entry is a high-level building block for data
	description.  It is a front-end for the token parser. A list of entries
	can be used as a set of keyword syntax elements, for example.

SourceFiles
	entry.C
	entryIO.C

\*---------------------------------------------------------------------------*/

#include <keyType.hxx>
#include <IDLList.hxx>
#include <fileName.hxx>
#include <autoPtr.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class ITstream;
	class dictionary;

	// Forward declaration of friend functions and operators

	class entry;
	FoamBase_EXPORT Ostream& operator<<(Ostream&, const entry&);

	/*---------------------------------------------------------------------------*\
							   Class entry Declaration
	\*---------------------------------------------------------------------------*/

	class entry
		: public IDLList<entry>::link
	{
		// Private Data

			//- Keyword of entry
		keyType keyword_;


		// Private Member Functions

			//- Get the next valid keyword. Return true if is valid keyType.
		static FoamBase_EXPORT bool getKeyword(keyType&, token&, Istream&);

		//- Get the next valid keyword otherwise return false
		static FoamBase_EXPORT bool getKeyword(keyType&, Istream&);


	public:

		static FoamBase_EXPORT int disableFunctionEntries;


		// Constructors

			//- Construct from keyword
		FoamBase_EXPORT entry(const keyType&);

		//- Copy constructor
		FoamBase_EXPORT entry(const entry&);

		//- Construct on freestore as copy with reference to the
		//  dictionary the copy belongs to
		FoamBase_EXPORT virtual autoPtr<entry> clone
		(
			const dictionary& parentDict
		) const = 0;

		//- Construct on freestore as copy
		//  Note: the parent directory is set to dictionary::null
		FoamBase_EXPORT virtual autoPtr<entry> clone() const;

		//- Construct from Istream and insert into dictionary
		static FoamBase_EXPORT bool New(dictionary& parentDict, Istream&);

		//- Construct on freestore from Istream and return
		static FoamBase_EXPORT autoPtr<entry> New(Istream& is);


		//- Destructor
		virtual ~entry()
		{}


		// Member Functions

			//- Return keyword
		const keyType& keyword() const
		{
			return keyword_;
		}

		//- Return non-const access to keyword
		keyType& keyword()
		{
			return keyword_;
		}

		//- Return the dictionary name
		FoamBase_EXPORT virtual const fileName& name() const = 0;

		//- Return the dictionary name
		FoamBase_EXPORT virtual fileName& name() = 0;

		//- Return line number of first token in dictionary
		FoamBase_EXPORT virtual label startLineNumber() const = 0;

		//- Return line number of last token in dictionary
		FoamBase_EXPORT virtual label endLineNumber() const = 0;

		//- Return true if this entry is a stream
		virtual bool isStream() const
		{
			return false;
		}

		//- Return token stream if this entry is a primitive entry
		FoamBase_EXPORT virtual ITstream& stream() const = 0;

		//- Return true if this entry is a dictionary
		virtual bool isDict() const
		{
			return false;
		}

		//- Return dictionary if this entry is a dictionary
		FoamBase_EXPORT virtual const dictionary& dict() const = 0;

		//- Return non-const access to dictionary if this entry is a dictionary
		FoamBase_EXPORT virtual dictionary& dict() = 0;

		//- Write
		FoamBase_EXPORT virtual void write(Ostream&) const = 0;


		// Member Operators

		FoamBase_EXPORT void operator=(const entry&);

		FoamBase_EXPORT bool operator==(const entry&) const;
		FoamBase_EXPORT bool operator!=(const entry&) const;


		// Ostream operator

		friend FoamBase_EXPORT Ostream& operator<<(Ostream&, const entry&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_entry_Header
