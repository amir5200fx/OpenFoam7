#pragma once
#ifndef _dictionaryEntry_Header
#define _dictionaryEntry_Header

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
	tnbLib::dictionaryEntry

Description
	A keyword and a list of tokens is a 'dictionaryEntry'.

	An dictionaryEntry can be read, written and printed, and the types and
	values of its tokens analysed.  A dictionaryEntry is a high-level building
	block for data description.  It is a front-end for the token parser.
	A list of entries can be used as a set of keyword syntax elements,
	for example.

SourceFiles
	dictionaryEntry.C
	dictionaryEntryIO.C

\*---------------------------------------------------------------------------*/

//#include <entry.hxx>  Edited by amir
#include <dictionary.hxx>
#include <InfoProxy.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of friend functions and operators

	class dictionaryEntry;

	FoamBase_EXPORT Ostream& operator<<(Ostream&, const dictionaryEntry&);


	/*---------------------------------------------------------------------------*\
							   Class dictionaryEntry Declaration
	\*---------------------------------------------------------------------------*/

	class dictionaryEntry
		:
		public tnbLib::entry,
		public dictionary
	{
		// Private Member Functions

		FoamBase_EXPORT void readData(Istream&);

		//- Dissallow bitwise copy
		FoamBase_EXPORT dictionaryEntry(const dictionary&);


	public:

		// Constructors

			//- Construct from the parent dictionary and Istream
		FoamBase_EXPORT dictionaryEntry(const dictionary& parentDict, Istream&);

		//- Construct from the keyword, parent dictionary and a Istream
		FoamBase_EXPORT dictionaryEntry
		(
			const keyType&,
			const dictionary& parentDict,
			Istream&
		);

		//- Construct from the keyword, parent dictionary and a dictionary
		FoamBase_EXPORT dictionaryEntry
		(
			const keyType&,
			const dictionary& parentDict,
			const dictionary& dict
		);

		//- Construct as copy for the given parent dictionary
		FoamBase_EXPORT dictionaryEntry
		(
			const dictionary& parentDict,
			const dictionaryEntry&
		);

		autoPtr<tnbLib::entry> clone(const dictionary& parentDict) const
		{
			return autoPtr<tnbLib::entry>(new dictionaryEntry(parentDict, *this));
		}


		// Member Functions

			//- Return the local dictionary name (final part of scoped name)
		const word dictName() const
		{
			return dictionary::dictName();
		}

		//- Return the dictionary name (scoped, e.g. dictA::dictB::dictC)
		const fileName& name() const
		{
			return dictionary::name();
		}

		//- Return the dictionary name (scoped, e.g. dictA::dictB::dictC)
		fileName& name()
		{
			return dictionary::name();
		}

		//- Return line number of first token in dictionary
		FoamBase_EXPORT label startLineNumber() const;

		//- Return line number of last token in dictionary
		FoamBase_EXPORT label endLineNumber() const;

		//- This entry is not a primitive,
		//  calling this function generates a FatalError
		FoamBase_EXPORT ITstream& stream() const;

		//- Return true because this entry is a dictionary
		bool isDict() const
		{
			return true;
		}

		//- Return dictionary
		FoamBase_EXPORT const dictionary& dict() const;

		//- Return non-const access to dictionary
		FoamBase_EXPORT dictionary& dict();

		//- Write
		FoamBase_EXPORT void write(Ostream&) const;

		//- Return info proxy.
		//  Used to print token information to a stream
		InfoProxy<dictionaryEntry> info() const
		{
			return *this;
		}


		// Ostream operator

		friend FoamBase_EXPORT Ostream& operator<<(Ostream&, const dictionaryEntry&);
	};


	template<>
	FoamBase_EXPORT Ostream& operator<<(Ostream&, const InfoProxy<dictionaryEntry>&);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_dictionaryEntry_Header
