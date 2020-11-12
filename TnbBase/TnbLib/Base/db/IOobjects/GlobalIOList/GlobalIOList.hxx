#pragma once
#ifndef _GlobalIOList_Header
#define _GlobalIOList_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2015-2020 OpenFOAM Foundation
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
	tnbLib::GlobalIOList

Description
	IOList with global data (so optionally read from master)

SourceFiles
	GlobalIOList.C

\*---------------------------------------------------------------------------*/

#include <List.hxx>
#include <regIOobject.hxx>

#ifdef FoamBase_EXPORT_DEFINE
#define FoamGlobalIOList_EXPORT __declspec(dllexport)
#else
#ifdef FoamGlobalIOList_EXPORT_DEFINE
#define FoamGlobalIOList_EXPORT __declspec(dllexport)
#else
#define FoamGlobalIOList_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class GlobalIOList Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class GlobalIOList
		:
		public regIOobject,
		public List<Type>
	{

	public:

		//TypeName("List");
		static const char* typeName_() { return "List"; }
		static FoamGlobalIOList_EXPORT const ::tnbLib::word typeName;
		static FoamGlobalIOList_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from IOobject
		GlobalIOList(const IOobject&);

		//- Construct from IOobject
		GlobalIOList(const IOobject&, const label size);

		//- Construct from IOobject and a List
		GlobalIOList(const IOobject&, const List<Type>&);

		//- Move construct by transferring the List contents
		GlobalIOList(const IOobject&, List<Type>&&);

		//- Copy constructor
		GlobalIOList(const GlobalIOList<Type>&);

		//- Move constructor
		GlobalIOList(GlobalIOList<Type>&&);


		//- Destructor
		virtual ~GlobalIOList();


		// Member Functions

			//- Is object global
		virtual bool global() const
		{
			return true;
		}

		//- Return complete path + object name if the file exists
		//  either in the case/processor or case otherwise null
		virtual fileName filePath() const
		{
			return globalFilePath(type());
		}

		//- ReadData function required for regIOobject read operation
		virtual bool readData(Istream&);

		//- WriteData function required for regIOobject write operation
		bool writeData(Ostream&) const;


		// Member Operators

		void operator=(const GlobalIOList<Type>&);
		void operator=(GlobalIOList<Type>&&);

		void operator=(const List<Type>&);
		void operator=(List<Type>&&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <GlobalIOListI.hxx>

//#ifdef NoRepository
//#   include <GlobalIOList.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_GlobalIOList_Header
