#pragma once
#ifndef _IOList_Header
#define _IOList_Header

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
	tnbLib::IOList

Description
	A List of objects of type \<T\> with automated input and output.

SourceFiles
	IOList.C

\*---------------------------------------------------------------------------*/

#include <List.hxx>
#include <regIOobject.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class IOList Declaration
	\*---------------------------------------------------------------------------*/

	template<class T>
	class IOList
		:
		public regIOobject,
		public List<T>
	{

	public:

		//- Runtime type information
		TypeName("List");


		// Constructors

			//- Construct from IOobject
		IOList(const IOobject&);

		//- Construct from IOobject and size of IOList
		IOList(const IOobject&, const label);

		//- Construct from IOobject and a List
		IOList(const IOobject&, const List<T>&);

		//- Move construct by transferring the List contents
		IOList(const IOobject&, List<T>&&);

		//- Copy constructor
		//IOList(const IOList<T>&);

		//- Move constructor
		//IOList(IOList<T>&&);


		//- Destructor
		virtual ~IOList();


		// Member Functions

		bool writeData(Ostream&) const;


		// Member Operators

		void operator=(const IOList<T>&);
		void operator=(IOList<T>&&);

		void operator=(const List<T>&);
		void operator=(List<T>&&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <IOListI.hxx>

//#ifdef NoRepository
//#include <IOList.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_IOList_Header
