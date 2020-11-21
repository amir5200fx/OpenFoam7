#pragma once
#ifndef _objectRegistry_Header
#define _objectRegistry_Header

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
	tnbLib::objectRegistry

Description
	Registry of regIOobjects

SourceFiles
	objectRegistry.C

\*---------------------------------------------------------------------------*/

#include <HashTable.hxx>
#include <regIOobject.hxx>
#include <wordReList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						   Class objectRegistry Declaration
	\*---------------------------------------------------------------------------*/

	class objectRegistry
		:
		public regIOobject,
		public HashTable<regIOobject*>
	{
		// Private Data

			//- Master time objectRegistry
		const Time& time_;

		//- Parent objectRegistry
		const objectRegistry& parent_;

		//- Local directory path of this objectRegistry relative to time
		fileName dbDir_;

		//- Current event
		mutable label event_;


		// Private Member Functions

			//- Is the objectRegistry parent_ different from time_
			//  Used to terminate searching within the ancestors
		FoamBase_EXPORT bool parentNotTime() const;


	public:

		//- Declare type name for this IOobject
		//TypeName("objectRegistry");
		static const char* typeName_() { return "objectRegistry"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct the time objectRegistry given an initial estimate
			//  for the number of entries
		FoamBase_EXPORT explicit objectRegistry
		(
			const Time& db,
			const label nIoObjects = 128
		);

		//- Construct a sub-registry given an IObject to describe the registry
		//  and an initial estimate for the number of entries
		FoamBase_EXPORT explicit objectRegistry
		(
			const IOobject& io,
			const label nIoObjects = 128
		);

		//- Disallow default bitwise copy construction
		FoamBase_EXPORT objectRegistry(const objectRegistry&);


		//- Destructor
		FoamBase_EXPORT virtual ~objectRegistry();


		// Member Functions

			// Access

				//- Return time
		const Time& time() const
		{
			return time_;
		}

		//- Return the parent objectRegistry
		const objectRegistry& parent() const
		{
			return parent_;
		}

		//- Local directory path of this objectRegistry relative to the time
		virtual const fileName& dbDir() const
		{
			return dbDir_;
		}

		//- Return the list of names of the IOobjects
		FoamBase_EXPORT wordList names() const;

		//- Return the sorted list of names of the IOobjects
		FoamBase_EXPORT wordList sortedNames() const;

		//- Return the list of names of IOobjects of given class name
		FoamBase_EXPORT wordList names(const word& className) const;

		//- Return the sorted list of names of IOobjects of given class name
		FoamBase_EXPORT wordList sortedNames(const word& className) const;

		//- Return the list of names of the IOobjects of given type
		template<class Type>
		wordList names() const;

		//- Return the list of objects whose name matches the input regExp
		template<class Type>
		wordList names(const wordRe& name) const;

		//- Return the list of objects whose name matches the input regExp
		template<class Type>
		wordList names(const wordReList& name) const;

		//- Lookup and return a const sub-objectRegistry. Optionally create
		//  it if it does not exist.
		FoamBase_EXPORT const objectRegistry& subRegistry
		(
			const word& name,
			const bool forceCreate = false
		) const;

		//- Lookup and return all objects of the given Type
		template<class Type>
		HashTable<const Type*> lookupClass(const bool strict = false) const;

		//- Lookup and return all objects of the given Type
		template<class Type>
		HashTable<Type*> lookupClass(const bool strict = false);

		//- Is the named Type found?
		template<class Type>
		bool foundObject(const word& name) const;

		//- Lookup and return the object of the given Type
		template<class Type>
		const Type& lookupObject(const word& name) const;

		//- Lookup and return the object reference of the given Type
		template<class Type>
		Type& lookupObjectRef(const word& name) const;

		//- Return new event number.
		FoamBase_EXPORT label getEvent() const;


		// Edit

			//- Rename
		FoamBase_EXPORT virtual void rename(const word& newName);

		//- Add an regIOobject to registry
		FoamBase_EXPORT bool checkIn(regIOobject&) const;

		//- Remove an regIOobject from registry
		FoamBase_EXPORT bool checkOut(regIOobject&) const;

		//- Remove all regIOobject owned by the registry
		FoamBase_EXPORT void clear();


		// Reading

			//- Return true if any of the object's files have been modified
		FoamBase_EXPORT virtual bool modified() const;

		//- Read the objects that have been modified
		FoamBase_EXPORT void readModifiedObjects();

		//- Read object if modified
		FoamBase_EXPORT virtual bool readIfModified();


		// Writing

			//- writeData function required by regIOobject but not used
			//  for this class, write is used instead
		virtual bool writeData(Ostream&) const
		{
			NotImplemented;

			return false;
		}

		//- Write the objects
		FoamBase_EXPORT virtual bool writeObject
		(
			IOstream::streamFormat fmt,
			IOstream::versionNumber ver,
			IOstream::compressionType cmp,
			const bool write
		) const;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamBase_EXPORT void operator=(const objectRegistry&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <objectRegistryI.hxx>

//#ifdef NoRepository
//#include <objectRegistryTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_objectRegistry_Header
