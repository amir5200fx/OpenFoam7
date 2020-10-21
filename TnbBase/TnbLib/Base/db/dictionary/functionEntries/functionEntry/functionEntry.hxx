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
		static token readLine(const word& key, Istream& is);


	public:

		// Constructors

			//- Construct from keyword, parent dictionary and Istream
		functionEntry(const word&, const dictionary&, Istream&);

		//- Disallow default bitwise copy construction
		functionEntry(const functionEntry&) = delete;


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
		static executedictionaryIstreamMemberFunctionTable* executedictionaryIstreamMemberFunctionTablePtr_;

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

		static void constructexecutedictionaryIstreamMemberFunctionTables();
		static void destroyexecutedictionaryIstreamMemberFunctionTables();

		//- Execute the functionEntry in a sub-dict context
		static bool execute
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
		static executeprimitiveEntryIstreamMemberFunctionTable* executeprimitiveEntryIstreamMemberFunctionTablePtr_;

		template <class functionEntryType>
		class addexecuteprimitiveEntryIstreamMemberFunctionToTable
		{
		public:
			addexecuteprimitiveEntryIstreamMemberFunctionToTable(const word& lookup = functionEntryType::typeName)
			{
				std::cout << "typename = " << lookup << std::endl;
				system("pause");
				constructexecuteprimitiveEntryIstreamMemberFunctionTables();
				executeprimitiveEntryIstreamMemberFunctionTablePtr_->insert(lookup, functionEntryType::execute);
			}

			~addexecuteprimitiveEntryIstreamMemberFunctionToTable()
			{
				destroyexecuteprimitiveEntryIstreamMemberFunctionTables();
			}
		};

		static void constructexecuteprimitiveEntryIstreamMemberFunctionTables();
		static void destroyexecuteprimitiveEntryIstreamMemberFunctionTables();

		//- Execute the functionEntry in a primitiveEntry context
		static bool execute
		(
			const word& functionName,
			const dictionary& parentDict,
			primitiveEntry&,
			Istream&
		);

		//- Write
		virtual void write(Ostream&) const;


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const functionEntry&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_functionEntry_Header
