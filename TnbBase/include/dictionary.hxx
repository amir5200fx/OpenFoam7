#pragma once
#ifndef _dictionary_Header
#define _dictionary_Header

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
	tnbLib::dictionary

Description
	A list of keyword definitions, which are a keyword followed by any number
	of values (e.g. words and numbers). The keywords can represent patterns
	which are matched using Posix regular expressions. The general order for
	searching is as follows:
	- exact match
	- pattern match (in reverse order)
	- optional recursion into the enclosing (parent) dictionaries

	The dictionary class is the base class for IOdictionary.
	It also serves as a bootstrap dictionary for the objectRegistry data
	dictionaries since, unlike the IOdictionary class, it does not use an
	objectRegistry itself to work.

	To add - a merge() member function with a non-const dictionary parameter?
	This would avoid unnecessary cloning in the add(entry*, bool) method.

SourceFiles
	dictionary.C
	dictionaryIO.C

\*---------------------------------------------------------------------------*/

#include <entry.hxx>
#include <IDLList.hxx>
#include <DLList.hxx>
#include <fileName.hxx>
#include <ITstream.hxx> 
#include <HashTable.hxx>
#include <wordList.hxx>
#include <className.hxx>

#include <VectorSpace.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of friend functions and operators
	class regExp;
	class dictionary;
	class SHA1Digest;

	class ITstream;  // added by amir

	FoamBase_EXPORT Istream& operator>>(Istream&, dictionary&);
	FoamBase_EXPORT Ostream& operator<<(Ostream&, const dictionary&);

	/*---------------------------------------------------------------------------*\
							Class dictionaryName Declaration
	\*---------------------------------------------------------------------------*/

	class dictionaryName
	{
		// Private Data

		fileName name_;


	public:

		// Constructors

			//- Construct dictionaryName null
		dictionaryName()
		{}

		//- Construct dictionaryName as copy of the given fileName
		dictionaryName(const fileName& name)
			:
			name_(name)
		{}

		//- Move constructor
		dictionaryName(dictionaryName&& name)
			:
			name_(move(name.name_))
		{}


		// Member Functions

			//- Return the dictionary name
		const fileName& name() const
		{
			return name_;
		}

		//- Return the dictionary name
		fileName& name()
		{
			return name_;
		}

		//- Return the local dictionary name (final part of scoped name)
		const word dictName() const
		{
			const word scopedName = name_.name();

			string::size_type i = scopedName.rfind('.');

			if (i == scopedName.npos)
			{
				return scopedName;
			}
			else
			{
				return scopedName.substr(i + 1, scopedName.npos);
			}
		}


		// Member Operators

		void operator=(const dictionaryName& name)
		{
			name_ = name.name_;
		}

		void operator=(dictionaryName&& name)
		{
			name_ = move(name.name_);
		}
	};


	/*---------------------------------------------------------------------------*\
							   Class dictionary Declaration
	\*---------------------------------------------------------------------------*/

	class dictionary
		:
		public dictionaryName,
		public IDLList<tnbLib::entry>
	{
		// Private Data

			//- If true write optional keywords and values
			//  if not present in dictionary
		static FoamBase_EXPORT bool writeOptionalEntries;

		//- HashTable of the entries held on the DL-list for quick lookup
		HashTable<tnbLib::entry*> hashedEntries_;

		//- Parent dictionary
		const dictionary& parent_;

		//- Entries of matching patterns
		DLList<tnbLib::entry*> patternEntries_;

		//- Patterns as precompiled regular expressions
		DLList<autoPtr<regExp>> patternRegexps_;


		// Private Member Functions

			 //- Find and return an entry data stream pointer if present
			 //  otherwise return nullptr. Allows scoping using '.'
		FoamBase_EXPORT const tnbLib::entry* lookupScopedSubEntryPtr
		(
			const word&,
			bool recursive,
			bool patternMatch
		) const;

		//- Search patterns table for exact match or regular expression match
		FoamBase_EXPORT bool findInPatterns
		(
			const bool patternMatch,
			const word& Keyword,
			DLList<tnbLib::entry*>::const_iterator& wcLink,
			DLList<autoPtr<regExp>>::const_iterator& reLink
		) const;

		//- Search patterns table for exact match or regular expression match
		FoamBase_EXPORT bool findInPatterns
		(
			const bool patternMatch,
			const word& Keyword,
			DLList<tnbLib::entry*>::iterator& wcLink,
			DLList<autoPtr<regExp>>::iterator& reLink
		);


	public:

		//- Declare friendship with the entry class for IO
		friend class entry;


		// Declare name of the class and its debug switch
		//ClassName("dictionary");
		static const char* typeName_() { return "dictionary"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName; 
		static FoamBase_EXPORT int debug;


		//- Null dictionary
		static FoamBase_EXPORT const dictionary null;


		// Constructors

			//- Construct top-level dictionary null
		FoamBase_EXPORT dictionary();

		//- Construct top-level empty dictionary with given name
		FoamBase_EXPORT dictionary(const fileName& name);

		//- Construct given the entry name, parent dictionary and Istream,
		//  reading entries until lastEntry or EOF
		FoamBase_EXPORT dictionary
		(
			const fileName& name,
			const dictionary& parentDict,
			Istream&
		);

		//- Construct top-level dictionary from Istream,
		//  reading entries until EOF
		FoamBase_EXPORT dictionary(Istream&);

		//- Construct top-level dictionary from Istream,
		//  reading entries until EOF, optionally keeping the header
		FoamBase_EXPORT dictionary(Istream&, const bool keepHeader);

		//- Construct as copy given the parent dictionary
		FoamBase_EXPORT dictionary(const dictionary& parentDict, const dictionary&);

		//- Construct top-level dictionary as copy
		FoamBase_EXPORT dictionary(const dictionary&);

		//- Construct top-level dictionary as copy from pointer to dictionary.
		//  A null pointer is treated like an empty dictionary.
		FoamBase_EXPORT dictionary(const dictionary*);

		//- Move constructor transferring parameter contents
		//  given parent dictionary
		FoamBase_EXPORT dictionary(const dictionary& parentDict, dictionary&&);

		//- Move constructor
		FoamBase_EXPORT dictionary(dictionary&&);

		//- Construct and return clone
		FoamBase_EXPORT autoPtr<dictionary> clone() const;

		//- Construct top-level dictionary on freestore from Istream
		static FoamBase_EXPORT autoPtr<dictionary> New(Istream&);


		//- Destructor
		FoamBase_EXPORT virtual ~dictionary();


		// Member Functions

			//- Return the parent dictionary
		const dictionary& parent() const
		{
			return parent_;
		}

		//- Return whether this dictionary is null
		bool isNull() const
		{
			return this == &null;
		}

		//- Return the top of the tree
		FoamBase_EXPORT const dictionary& topDict() const;

		//- Return line number of first token in dictionary
		FoamBase_EXPORT label startLineNumber() const;

		//- Return line number of last token in dictionary
		FoamBase_EXPORT label endLineNumber() const;

		//- Return the SHA1 digest of the dictionary contents
		FoamBase_EXPORT SHA1Digest digest() const;

		//- Return the dictionary as a list of tokens
		FoamBase_EXPORT tokenList tokens() const;


		// Search and lookup

			//- Search dictionary for given keyword
			//  If recursive, search parent dictionaries
			//  If patternMatch, use regular expressions
		FoamBase_EXPORT bool found
		(
			const word&,
			bool recursive = false,
			bool patternMatch = true
		) const;

		//- Find and return an entry data stream pointer if present
		//  otherwise return nullptr.
		//  If recursive, search parent dictionaries.
		//  If patternMatch, use regular expressions
		FoamBase_EXPORT const tnbLib::entry* lookupEntryPtr
		(
			const word&,
			bool recursive,
			bool patternMatch
		) const;

		//- Find and return an entry data stream pointer for manipulation
		//  if present otherwise return nullptr.
		//  If recursive, search parent dictionaries.
		//  If patternMatch, use regular expressions.
		FoamBase_EXPORT tnbLib::entry* lookupEntryPtr
		(
			const word&,
			bool recursive,
			bool patternMatch
		);

		//- Find and return an entry data stream if present otherwise error.
		//  If recursive, search parent dictionaries.
		//  If patternMatch, use regular expressions.
		FoamBase_EXPORT const tnbLib::entry& lookupEntry
		(
			const word&,
			bool recursive,
			bool patternMatch
		) const;

		//- Find and return an entry data stream
		//  If recursive, search parent dictionaries.
		//  If patternMatch, use regular expressions.
		FoamBase_EXPORT ITstream& lookup
		(
			const word&,
			bool recursive = false,
			bool patternMatch = true
		) const;

		//- Find and return a T,
		//  if not found throw a fatal error.
		//  If recursive, search parent dictionaries.
		//  If patternMatch, use regular expressions.
		template<class T>
		T lookupType
		(
			const word&,
			bool recursive = false,
			bool patternMatch = true
		) const;

		//- Find and return a T,
		//  if not found return the given default value.
		//  If recursive, search parent dictionaries.
		//  If patternMatch, use regular expressions.
		template<class T>
		T lookupOrDefault
		(
			const word&,
			const T&,
			bool recursive = false,
			bool patternMatch = true
		) const;

		//- Find and return a T, if not found return the given
		//  default value, and add to dictionary.
		//  If recursive, search parent dictionaries.
		//  If patternMatch, use regular expressions.
		template<class T>
		T lookupOrAddDefault
		(
			const word&,
			const T&,
			bool recursive = false,
			bool patternMatch = true
		);

		//- Find an entry if present, and assign to T
		//  Returns true if the entry was found.
		//  If recursive, search parent dictionaries.
		//  If patternMatch, use regular expressions.
		template<class T>
		bool readIfPresent
		(
			const word&,
			T&,
			bool recursive = false,
			bool patternMatch = true
		) const;

		//- Find and return an entry data stream pointer if present
		//  otherwise return nullptr. Allows scoping using '.'.
		//  Special handling for ':' at start of keyword and '..'.
		FoamBase_EXPORT const tnbLib::entry* lookupScopedEntryPtr
		(
			const word&,
			bool recursive,
			bool patternMatch
		) const;

		//- Check if entry is a sub-dictionary
		FoamBase_EXPORT bool isDict(const word&) const;

		//- Find and return a sub-dictionary pointer if present
		//  otherwise return nullptr.
		FoamBase_EXPORT const dictionary* subDictPtr(const word&) const;

		//- Find and return a sub-dictionary pointer if present
		//  otherwise return nullptr.
		FoamBase_EXPORT dictionary* subDictPtr(const word&);

		//- Find and return a sub-dictionary
		FoamBase_EXPORT const dictionary& subDict(const word&) const;

		//- Find and return a sub-dictionary for manipulation
		FoamBase_EXPORT dictionary& subDict(const word&);

		//- Find and return a sub-dictionary as a copy, or
		//  return an empty dictionary if the sub-dictionary does not exist
		FoamBase_EXPORT dictionary subOrEmptyDict
		(
			const word&,
			const bool mustRead = false
		) const;

		//- Find and return a sub-dictionary if found
		//  otherwise return this dictionary
		FoamBase_EXPORT const dictionary& optionalSubDict(const word&) const;

		//- Return the table of contents
		FoamBase_EXPORT wordList toc() const;

		//- Return the sorted table of contents
		FoamBase_EXPORT wordList sortedToc() const;

		//- Return the list of available keys or patterns
		FoamBase_EXPORT List<keyType> keys(bool patterns = false) const;


		// Editing

			//- Substitute the given keyword prepended by '$' with the
			//  corresponding sub-dictionary entries
		FoamBase_EXPORT bool substituteKeyword(const word& keyword);

		//- Substitute the given scoped keyword prepended by '$' with the
		//  corresponding sub-dictionary entries
		FoamBase_EXPORT bool substituteScopedKeyword(const word& keyword);

		//- Add a new entry
		//  With the merge option, dictionaries are interwoven and
		//  primitive entries are overwritten
		FoamBase_EXPORT bool add(entry*, bool mergeEntry = false);

		//- Add an entry
		//  With the merge option, dictionaries are interwoven and
		//  primitive entries are overwritten
		FoamBase_EXPORT void add(const entry&, bool mergeEntry = false);

		//- Add a word entry
		//  optionally overwrite an existing entry
		FoamBase_EXPORT void add(const keyType&, const word&, bool overwrite = false);

		//- Add a string entry
		//  optionally overwrite an existing entry
		FoamBase_EXPORT void add(const keyType&, const string&, bool overwrite = false);

		//- Add a label entry
		//  optionally overwrite an existing entry
		FoamBase_EXPORT void add(const keyType&, const label, bool overwrite = false);

		//- Add a scalar entry
		//  optionally overwrite an existing entry
		FoamBase_EXPORT void add(const keyType&, const scalar, bool overwrite = false);

		//- Add a dictionary entry
		//  optionally merge with an existing sub-dictionary
		FoamBase_EXPORT void add
		(
			const keyType&,
			const dictionary&,
			bool mergeEntry = false
		);

		//- Add a T entry
		//  optionally overwrite an existing entry
		template<class T>
		void add(const keyType&, const T&, bool overwrite = false);

		//- Assign a new entry, overwrite any existing entry
		FoamBase_EXPORT void set(entry*);

		//- Assign a new entry, overwrite any existing entry
		FoamBase_EXPORT void set(const entry&);

		//- Assign a dictionary entry, overwrite any existing entry
		FoamBase_EXPORT void set(const keyType&, const dictionary&);

		//- Assign a T entry, overwrite any existing entry
		template<class T>
		void set(const keyType&, const T&);

		//- Remove an entry specified by keyword
		FoamBase_EXPORT bool remove(const word&);

		//- Change the keyword for an entry,
		//  optionally forcing overwrite of an existing entry
		FoamBase_EXPORT bool changeKeyword
		(
			const keyType& oldKeyword,
			const keyType& newKeyword,
			bool forceOverwrite = false
		);

		//- Merge entries from the given dictionary.
		//  Also merge sub-dictionaries as required.
		FoamBase_EXPORT bool merge(const dictionary&);

		//- Clear the dictionary
		FoamBase_EXPORT void clear();

		//- Transfer the contents of the argument and annul the argument.
		FoamBase_EXPORT void transfer(dictionary&);


		// Read

			//- Read dictionary from Istream
		FoamBase_EXPORT bool read(Istream&);

		//- Read dictionary from Istream, optionally keeping the header
		FoamBase_EXPORT bool read(Istream&, const bool keepHeader);


		// Write

			//- Write dictionary, normally with sub-dictionary formatting
		FoamBase_EXPORT void write(Ostream&, const bool subDict = true) const;


		// Member Operators

			//- Find and return entry
		FoamBase_EXPORT ITstream& operator[](const word&) const;

		FoamBase_EXPORT void operator=(const dictionary&);

		FoamBase_EXPORT void operator=(dictionary&&);

		//- Include entries from the given dictionary.
		//  Warn, but do not overwrite existing entries.
		FoamBase_EXPORT void operator+=(const dictionary&);

		//- Conditionally include entries from the given dictionary.
		//  Do not overwrite existing entries.
		FoamBase_EXPORT void operator|=(const dictionary&);

		//- Unconditionally include entries from the given dictionary.
		//  Overwrite existing entries.
		FoamBase_EXPORT void operator<<=(const dictionary&);


		// IOstream Operators

			//- Read dictionary from Istream
		friend FoamBase_EXPORT Istream& operator>>(Istream&, dictionary&);

		//- Write dictionary to Ostream
		friend FoamBase_EXPORT Ostream& operator<<(Ostream&, const dictionary&);
	};


	// Global Operators

	//- Combine dictionaries.
	//  Starting from the entries in dict1 and then including those from dict2.
	//  Warn, but do not overwrite the entries from dict1.
	FoamBase_EXPORT dictionary operator+(const dictionary& dict1, const dictionary& dict2);

	//- Combine dictionaries.
	//  Starting from the entries in dict1 and then including those from dict2.
	//  Do not overwrite the entries from dict1.
	FoamBase_EXPORT dictionary operator|(const dictionary& dict1, const dictionary& dict2);


	// Global Functions

	//- Write a dictionary entry
	FoamBase_EXPORT void writeEntry(Ostream& os, const dictionary& dict);

	//- Helper function to write the keyword and entry
	template<class EntryType>
	void writeEntry(Ostream& os, const word& entryName, const EntryType& value);

	//- Helper function to write the keyword and entry only if the
	//  values are not equal. The value is then output as value2
	template<class EntryType>
	void writeEntryIfDifferent
	(
		Ostream& os,
		const word& entryName,
		const EntryType& value1,
		const EntryType& value2
	);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <dictionaryTemplatesI.hxx>

//#ifdef NoRepository
//#include <dictionaryTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_dictionary_Header
