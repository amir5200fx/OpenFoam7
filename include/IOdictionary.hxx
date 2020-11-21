#pragma once
#ifndef _IOdictionary_Header
#define _IOdictionary_Header

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
	tnbLib::IOdictionary

Description
	IOdictionary is derived from dictionary and IOobject to give the dictionary
	automatic IO functionality via the objectRegistry.  To facilitate IO,
	IOdictionary is provided with a constructor from IOobject and writeData and
	write functions.

SourceFiles
	IOdictionary.C
	IOdictionaryIO.C

\*---------------------------------------------------------------------------*/

#include <baseIOdictionary.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class IOdictionary Declaration
	\*---------------------------------------------------------------------------*/

	class IOdictionary
		:
		public baseIOdictionary
	{

	public:

		// Constructors

			//- Construct given an IOobject
		FoamBase_EXPORT IOdictionary(const IOobject&);

		//- Construct given an IOobject and dictionary
		FoamBase_EXPORT IOdictionary(const IOobject&, const dictionary&);

		//- Construct given an IOobject and Istream
		FoamBase_EXPORT IOdictionary(const IOobject&, Istream&);

		//- Copy constructor
		FoamBase_EXPORT IOdictionary(const IOdictionary&);

		//- Move constructor
		FoamBase_EXPORT IOdictionary(IOdictionary&&);


		//- Destructor
		FoamBase_EXPORT virtual ~IOdictionary();


		// Member Functions
		//- ReadData function required for regIOobject read operation
		FoamBase_EXPORT bool readData(Istream&) override;  // added by amir

		//- WriteData function required for regIOobject write operation
		FoamBase_EXPORT bool writeData(Ostream&) const override;

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


		// Member Operators

			//- Move assignment
		FoamBase_EXPORT void operator=(IOdictionary&&);
	};


	//- Template function for obtaining global status
	template<>
	inline bool typeGlobal<IOdictionary>()
	{
		return true;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_IOdictionary_Header
