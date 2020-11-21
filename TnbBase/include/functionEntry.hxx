#pragma once
#ifndef _functionEntry_Header
#define _functionEntry_Header

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

Namespace
	tnbLib::functionEntries

Description
	Namespace for containing a functionEntry.


Class
	tnbLib::functionEntry

Description
	A functionEntry causes entries to be added/manipulated on the specified
	dictionary given an input stream.

	In dictionaries, a \c '\#' sigil is typically used for a functionEntry.

SourceFiles
	functionEntry.C
	functionEntryIO.C

\*---------------------------------------------------------------------------*/

#include <word.hxx>
#include <memberFunctionSelectionTables.hxx>
#include <primitiveEntry.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class dictionary;

	/*---------------------------------------------------------------------------*\
							   Class functionEntry Declaration
	\*---------------------------------------------------------------------------*/

	class functionEntry
		:
		public primitiveEntry
	{
		// Private Member Functions

			//- Read line as string token
		static FoamBase_EXPORT token readLine(const word& key, Istream& is);


	public:

		// Constructors

			//- Construct from keyword, parent dictionary and Istream
		FoamBase_EXPORT functionEntry(const word&, const dictionary&, Istream&);

		//- Disallow default bitwise copy construction
		FoamBase_EXPORT functionEntry(const functionEntry&) = delete;


		// Member Function Selectors

		/*declareMemberFunctionSelectionTable
		(
			bool,
			functionEntry,
			execute,
			dictionaryIstream,
			(
				dictionary& parentDict,
				Istream& is
				),
				(parentDict, is)
		);*/

		typedef bool (*executedictionaryIstreamMemberFunctionPtr)(dictionary& parentDict, Istream& is);
		typedef HashTable<executedictionaryIstreamMemberFunctionPtr, word, string::hash>
		executedictionaryIstreamMemberFunctionTable;
		static FoamBase_EXPORT executedictionaryIstreamMemberFunctionTable* executedictionaryIstreamMemberFunctionTablePtr_;

		template <class functionEntryType>
		class addexecutedictionaryIstreamMemberFunctionToTable
		{
		public:
			addexecutedictionaryIstreamMemberFunctionToTable(const word& lookup = functionEntryType::typeName)
			{
				constructexecutedictionaryIstreamMemberFunctionTables();
				executedictionaryIstreamMemberFunctionTablePtr_->insert(lookup, functionEntryType::execute);
			}

			~addexecutedictionaryIstreamMemberFunctionToTable() { destroyexecutedictionaryIstreamMemberFunctionTables(); }
		};

		static FoamBase_EXPORT void constructexecutedictionaryIstreamMemberFunctionTables();
		static FoamBase_EXPORT void destroyexecutedictionaryIstreamMemberFunctionTables();

		//- Execute the functionEntry in a sub-dict context
		static FoamBase_EXPORT bool execute
		(
			const word& functionName,
			dictionary& parentDict,
			Istream&
		);

		/*declareMemberFunctionSelectionTable
		(
			bool,
			functionEntry,
			execute,
			primitiveEntryIstream,
			(
				const dictionary& parentDict,
				primitiveEntry& entry,
				Istream& is
				),
				(parentDict, entry, is)
		);*/

		typedef bool (*executeprimitiveEntryIstreamMemberFunctionPtr)(const dictionary& parentDict, primitiveEntry& entry,
		                                                              Istream& is);
		typedef HashTable<executeprimitiveEntryIstreamMemberFunctionPtr, word, string::hash>
		executeprimitiveEntryIstreamMemberFunctionTable;
		static FoamBase_EXPORT executeprimitiveEntryIstreamMemberFunctionTable* executeprimitiveEntryIstreamMemberFunctionTablePtr_;

		template <class functionEntryType>
		class addexecuteprimitiveEntryIstreamMemberFunctionToTable
		{
		public:
			addexecuteprimitiveEntryIstreamMemberFunctionToTable(const word& lookup = functionEntryType::typeName)
			{
				constructexecuteprimitiveEntryIstreamMemberFunctionTables();
				executeprimitiveEntryIstreamMemberFunctionTablePtr_->insert(lookup, functionEntryType::execute);
			}

			~addexecuteprimitiveEntryIstreamMemberFunctionToTable()
			{
				destroyexecuteprimitiveEntryIstreamMemberFunctionTables();
			}
		};

		static FoamBase_EXPORT void constructexecuteprimitiveEntryIstreamMemberFunctionTables();
		static FoamBase_EXPORT void destroyexecuteprimitiveEntryIstreamMemberFunctionTables();

		//- Execute the functionEntry in a primitiveEntry context
		static FoamBase_EXPORT bool execute
		(
			const word& functionName,
			const dictionary& parentDict,
			primitiveEntry&,
			Istream&
		);

		//- Write
		FoamBase_EXPORT virtual void write(Ostream&) const;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamBase_EXPORT void operator=(const functionEntry&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_functionEntry_Header
