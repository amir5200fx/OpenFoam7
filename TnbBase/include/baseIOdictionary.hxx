#pragma once
#ifndef _baseIOdictionary_Header
#define _baseIOdictionary_Header

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
	tnbLib::baseIOdictionary

Description
	baseIOdictionary is derived from dictionary and IOobject to give the
	dictionary automatic IO functionality via the objectRegistry.
	To facilitate IO,
	IOdictionary is provided with a constructor from IOobject and writeData and
	write functions.

SourceFiles
	baseIOdictionary.C
	baseIOdictionaryIO.C

\*---------------------------------------------------------------------------*/

#include <dictionary.hxx>
#include <regIOobject.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class baseIOdictionary Declaration
	\*---------------------------------------------------------------------------*/

	class baseIOdictionary
		:
		public regIOobject,
		public dictionary
	{
		// Private Data

	protected:  // added by amir

		static FoamBase_EXPORT bool writeDictionaries;

	public:

		//TypeName("dictionary");
		static const char* typeName_() { return "dictionary"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct given an IOobject
		FoamBase_EXPORT baseIOdictionary(const IOobject&);

		//- Construct given an IOobject and dictionary
		FoamBase_EXPORT baseIOdictionary(const IOobject&, const dictionary&);

		//- Construct given an IOobject and Istream
		FoamBase_EXPORT baseIOdictionary(const IOobject&, Istream&);

		//- Copy constructor
		FoamBase_EXPORT baseIOdictionary(const baseIOdictionary&);

		//- Move constructor
		FoamBase_EXPORT baseIOdictionary(baseIOdictionary&&);


		//- Destructor
		FoamBase_EXPORT virtual ~baseIOdictionary();


		// Member Functions

			//- Return complete path + object name if the file exists
			//  either in the case/processor or case otherwise null
		FoamBase_EXPORT virtual fileName filePath() const = 0;

		//- Name function is needed to disambiguate those inherited
		//  from regIOobject and dictionary
		FoamBase_EXPORT const word& name() const;

		//- ReadData function required for regIOobject read operation
		FoamBase_EXPORT virtual bool readData(Istream&);

		//- WriteData function required for regIOobject write operation
		FoamBase_EXPORT virtual bool writeData(Ostream&) const;

		//- Is object global
		FoamBase_EXPORT virtual bool global() const = 0;


		// Member Operators

			//- Assignment of other baseIOdictionary's entries to this
			//  baseIOdictionary
		FoamBase_EXPORT void operator=(const baseIOdictionary&);

		//- Move assignment
		FoamBase_EXPORT void operator=(baseIOdictionary&&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_baseIOdictionary_Header
