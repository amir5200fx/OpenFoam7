#pragma once
#ifndef _regIOobject_Header
#define _regIOobject_Header

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
	tnbLib::regIOobject

Description
	regIOobject is an abstract class derived from IOobject to handle
	automatic object registration with the objectRegistry.

SourceFiles
	regIOobject.C
	regIOobjectRead.C
	regIOobjectWrite.C

\*---------------------------------------------------------------------------*/

#include <IOobject.hxx>
#include <typeInfo.hxx>
#include <OSspecific.hxx>
#include <NamedEnum.hxx>
#include <labelList.hxx> // added by amir
#include <ISstream.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							 Class regIOobject Declaration
	\*---------------------------------------------------------------------------*/

	class regIOobject
		:
		public IOobject
	{

	protected:

		//- Helper: check readOpt flags and read if necessary
		FoamBase_EXPORT bool readHeaderOk
		(
			const IOstream::streamFormat PstreamFormat,
			const word& typeName
		);


	private:

		// Private Data

			//- Is this object registered with the registry
		bool registered_;

		//- Is this object owned by the registry
		bool ownedByRegistry_;

		//- List of modification watch indices
		mutable labelList watchIndices_;

		//- eventNo of last update
		label eventNo_;

		//- Istream for reading
		autoPtr<ISstream> isPtr_;


		// Private Member Functions

			//- Return Istream
		FoamBase_EXPORT Istream& readStream(const bool read = true);

		//- Dissallow assignment
		FoamBase_EXPORT void operator=(const regIOobject&);


	public:

		// Static data

			//- Runtime type information
		//TypeName("regIOobject");
		static const char* typeName_() { return "regIOobject"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		static FoamBase_EXPORT float fileModificationSkew;


		// Constructors

			//- Construct from IOobject. Optional flag for if IOobject is the
			//  top level regIOobject.
		FoamBase_EXPORT regIOobject(const IOobject&, const bool isTime = false);

		//- Copy constructor
		FoamBase_EXPORT regIOobject(const regIOobject&);

		//- Copy constructor, transferring registry registration to copy
		//  if registerCopy is true
		FoamBase_EXPORT regIOobject(const regIOobject&, bool registerCopy);

		//- Copy constructor with new name, transferring registry registration
		//  to copy as specified
		FoamBase_EXPORT regIOobject(const word& newName, const regIOobject&, bool registerCopy);

		//- Copy constructor with new IO parameters
		FoamBase_EXPORT regIOobject(const IOobject&, const regIOobject&);


		//- Destructor
		FoamBase_EXPORT virtual ~regIOobject();


		// Member Functions

			// Registration

				//- Add object to registry
		FoamBase_EXPORT bool checkIn();

		//- Remove object from registry
		FoamBase_EXPORT bool checkOut();

		//- Add file watch on object (if registered and READ_IF_MODIFIED)
		FoamBase_EXPORT virtual void addWatch();

		//- Is this object owned by the registry?
		inline bool ownedByRegistry() const;

		//- Transfer ownership of this object to its registry
		inline void store();

		//- Transfer ownership of the given object pointer to its registry
		//  and return reference to object.
		template<class Type>
		inline static Type& store(Type*);

		//- Transfer ownership of the given object pointer to its registry
		//  and return reference to object.
		template<class Type>
		inline static Type& store(autoPtr<Type>&);

		//- Release ownership of this object from its registry
		inline void release();


		// Dependency checking

			//- Event number at last update.
		inline label eventNo() const;

		//- Event number at last update.
		inline label& eventNo();

		//- Return true if up-to-date with respect to given object
		//  otherwise false
		FoamBase_EXPORT bool upToDate(const regIOobject&) const;

		//- Return true if up-to-date with respect to given objects
		//  otherwise false
		FoamBase_EXPORT bool upToDate
		(
			const regIOobject&,
			const regIOobject&
		) const;

		//- Return true if up-to-date with respect to given objects
		//  otherwise false
		FoamBase_EXPORT bool upToDate
		(
			const regIOobject&,
			const regIOobject&,
			const regIOobject&
		) const;

		//- Return true if up-to-date with respect to given objects
		//  otherwise false
		FoamBase_EXPORT bool upToDate
		(
			const regIOobject&,
			const regIOobject&,
			const regIOobject&,
			const regIOobject&
		) const;

		//- Set up to date (obviously)
		FoamBase_EXPORT void setUpToDate();


		// Edit

			//- Rename
		FoamBase_EXPORT virtual void rename(const word& newName);


		// Reading

			//- Return complete path + object name if the file exists
			//  in the case directory otherwise null. Does not search
			//  up if parallel. Can be overridden to provide this functionality
			//  (e.g. IOdictionary)
		FoamBase_EXPORT virtual fileName filePath() const;

		//- Read and check header info
		FoamBase_EXPORT bool headerOk();

		//- Return Istream and check object type against that given
		FoamBase_EXPORT Istream& readStream(const word&, const bool read = true);

		//- Close Istream
		FoamBase_EXPORT void close();

		//- Virtual readData function.
		//  Must be defined in derived types for which
		//  re-reading is required
		FoamBase_EXPORT virtual bool readData(Istream&);

		//- Read object
		FoamBase_EXPORT virtual bool read();

		//- Add file watch for fileName on object if not yet watched. Return
		//  index of watch
		FoamBase_EXPORT virtual label addWatch(const fileName&);

		//- Return file-monitoring handles
		inline const labelList& watchIndices() const;

		//- Return file-monitoring handles
		inline labelList& watchIndices();

		//- Return true if the object's file (or files for objectRegistry)
		//  have been modified. (modified state is cached by Time)
		FoamBase_EXPORT virtual bool modified() const;

		//- Read object if modified (as set by call to modified)
		FoamBase_EXPORT virtual bool readIfModified();

		//- Is object same for all processors
		//  Defaults to false, must be overridden by global IO classes
		FoamBase_EXPORT virtual bool global() const;


		// Writing

			//- Pure virtual writaData function.
			//  Must be defined in derived types
		FoamBase_EXPORT virtual bool writeData(Ostream&) const = 0;

		//- Write using given format, version and compression
		FoamBase_EXPORT virtual bool writeObject
		(
			IOstream::streamFormat,
			IOstream::versionNumber,
			IOstream::compressionType,
			const bool write
		) const;

		//- Write using setting from DB
		FoamBase_EXPORT virtual bool write(const bool write = true) const;


		// Member Operators

		FoamBase_EXPORT void operator=(const IOobject&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <regIOobjectI.hxx>

#endif // !_regIOobject_Header
