#pragma once
#ifndef _localIOdictionary_Header
#define _localIOdictionary_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2015-2019 OpenFOAM Foundation
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
	tnbLib::localIOdictionary

Description
	localIOdictionary is derived from IOdictionary but excludes parallel
	master reading.

SourceFiles
	localIOdictionary.C

\*---------------------------------------------------------------------------*/

#include <baseIOdictionary.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class localIOdictionary Declaration
	\*---------------------------------------------------------------------------*/

	class localIOdictionary
		:
		public baseIOdictionary
	{

	public:

		// Constructors

			//- Construct given an IOobject
		FoamBase_EXPORT localIOdictionary(const IOobject& io);

		//- Construct given an IOobject and dictionary
		FoamBase_EXPORT localIOdictionary(const IOobject& io, const dictionary& dict);

		//- Construct given an IOobject and Istream
		FoamBase_EXPORT localIOdictionary(const IOobject& io, Istream& is);

		//- Construct given an IOobject, supply wanted typeName
		FoamBase_EXPORT localIOdictionary(const IOobject& io, const word& wantedType);

		//- Move constructor
		FoamBase_EXPORT localIOdictionary(localIOdictionary&&);


		//- Destructor
		FoamBase_EXPORT virtual ~localIOdictionary();


		// Member Functions

			//- Is object global
		virtual bool global() const
		{
			return false;
		}

		//- Return complete path + object name if the file exists
		//  in the case otherwise null
		virtual fileName filePath() const
		{
			// Use default (local only) search strategy
			return localFilePath(type());
		}


		// Member Operators

			//- Move assignment
		FoamBase_EXPORT void operator=(localIOdictionary&&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_localIOdictionary_Header
