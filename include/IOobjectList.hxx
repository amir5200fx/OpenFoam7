#pragma once
#ifndef _IOobjectList_Header
#define _IOobjectList_Header

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
	tnbLib::IOobjectList

Description
	List of IOobjects with searching and retrieving facilities.

SourceFiles
	IOobjectList.C

\*---------------------------------------------------------------------------*/

#include <HashPtrTable.hxx>
#include <IOobject.hxx>
#include <wordReList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							Class IOobjectList Declaration
	\*---------------------------------------------------------------------------*/

	class IOobjectList
		:
		public HashPtrTable<IOobject>
	{

	public:

		// Constructors

			//- Construct given an initial estimate for the number of entries
		FoamBase_EXPORT explicit IOobjectList(const label nIoObjects = 128);

		//- Construct from objectRegistry and instance path
		FoamBase_EXPORT IOobjectList
		(
			const objectRegistry& db,
			const fileName& instance,
			const fileName& local = "",
			IOobject::readOption r = IOobject::MUST_READ,
			IOobject::writeOption w = IOobject::NO_WRITE,
			bool registerObject = true
		);

		//- Copy constructor
		FoamBase_EXPORT IOobjectList(const IOobjectList&);


		//- Destructor
		FoamBase_EXPORT ~IOobjectList();


		// Member Functions

			//- Add an IOobject to the list
		FoamBase_EXPORT bool add(IOobject&);

		//- Remove an IOobject from the list
		FoamBase_EXPORT bool remove(IOobject&);

		//- Lookup a given name and return IOobject ptr if found else nullptr
		FoamBase_EXPORT IOobject* lookup(const word& name) const;

		//- Return the list for all IOobects whose name matches name
		FoamBase_EXPORT IOobjectList lookup(const wordRe& name) const;

		//- Return the list for all IOobects whose name matches name
		FoamBase_EXPORT IOobjectList lookup(const wordReList& patterns) const;

		//- Return the list for all IOobjects of a given class
		FoamBase_EXPORT IOobjectList lookupClass(const word& className) const;

		//- Return the list of names of the IOobjects
		FoamBase_EXPORT wordList names() const;

		//- Return the sorted list of names of the IOobjects
		FoamBase_EXPORT wordList sortedNames() const;

		//- Return the list of names of the IOobjects of given class
		FoamBase_EXPORT wordList names(const word& className) const;

		//- Return the sorted list of names of the IOobjects of given class
		FoamBase_EXPORT wordList sortedNames(const word& className) const;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamBase_EXPORT void operator=(const IOobjectList&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_IOobjectList_Header
