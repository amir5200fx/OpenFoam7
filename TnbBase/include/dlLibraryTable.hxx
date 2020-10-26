#pragma once
#ifndef _dlLibraryTable_Header
#define _dlLibraryTable_Header

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
	tnbLib::dlLibraryTable

Description
	A table of dynamically loaded libraries

SourceFiles
	dlLibraryTable.C

\*---------------------------------------------------------------------------*/

#include <label.hxx>
#include <DynamicList.hxx>
#include <className.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						   Class dlLibraryTable Declaration
	\*---------------------------------------------------------------------------*/

	class dlLibraryTable
	{
		// Private Member Functions

		DynamicList<void*> libPtrs_;

		DynamicList<fileName> libNames_;


	public:

		// Declare name of the class and its debug switch
		//ClassName("dlLibraryTable");
		static const char* typeName_() { return "dlLibraryTable"; } 
		static FoamBase_EXPORT const ::tnbLib::word typeName; 
		static FoamBase_EXPORT int debug;

		// Constructors

			//- Construct null
		FoamBase_EXPORT dlLibraryTable();

		//- Construct from dictionary and name of 'libs' entry giving
		//  the libraries to load
		FoamBase_EXPORT dlLibraryTable(const dictionary&, const word&);

		//- Disallow default bitwise copy construction
		FoamBase_EXPORT dlLibraryTable(const dlLibraryTable&) = delete;


		//- Destructor
		FoamBase_EXPORT ~dlLibraryTable();


		// Member Functions

			//- Open the named library, optionally with warnings if problems occur
		FoamBase_EXPORT bool open(const fileName& name, const bool verbose = true);

		//- Close the named library, optionally with warnings if problems occur
		FoamBase_EXPORT bool close(const fileName& name, const bool verbose = true);

		//- Find the handle of the named library
		FoamBase_EXPORT void* findLibrary(const fileName& name);

		//- Open all the libraries listed in the 'libsEntry' entry in the
		//  given dictionary if present
		FoamBase_EXPORT bool open(const dictionary&, const word& libsEntry);

		//- Open all the libraries listed in the 'libsEntry' entry in the
		//  given dictionary if present and check the additions
		//  to the given constructor table
		template<class TablePtr>
		bool open
		(
			const dictionary&,
			const word& libsEntry,
			const TablePtr& tablePtr
		);


		// Member Operators

			//- Disallow default bitwise assignment
		FoamBase_EXPORT void operator=(const dlLibraryTable&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <dlLibraryTableI.hxx>

//#ifdef NoRepository
//#include <dlLibraryTableTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_dlLibraryTable_Header
