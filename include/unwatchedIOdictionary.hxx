#pragma once
#ifndef _unwatchedIOdictionary_Header
#define _unwatchedIOdictionary_Header

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
	tnbLib::unwatchedIOdictionary

Description
	unwatchedIOdictionary is like IOdictionary but stores
	dependencies as files instead of fileMonitor watchIndices. Used
	to read controlDict since there fileMonitor not yet setup.

\*---------------------------------------------------------------------------*/

#include <baseIOdictionary.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					   Class unwatchedIOdictionary Declaration
	\*---------------------------------------------------------------------------*/

	class unwatchedIOdictionary
		:
		public baseIOdictionary
	{
		// Private member data

		fileNameList files_;


	public:

		// Constructors

			//- Construct given an IOobject
		FoamBase_EXPORT unwatchedIOdictionary(const IOobject& io);

		//- Construct given an IOobject and dictionary
		FoamBase_EXPORT unwatchedIOdictionary
		(
			const IOobject& io,
			const dictionary& dict
		);

		//- Construct given an IOobject and Istream
		FoamBase_EXPORT unwatchedIOdictionary(const IOobject& io, Istream& is);

		//- Move constructor
		FoamBase_EXPORT unwatchedIOdictionary(unwatchedIOdictionary&&);


		//- Destructor
		FoamBase_EXPORT virtual ~unwatchedIOdictionary();


		// Member Functions

			//- This object is global
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

		//- Add file watch on object (READ_IF_MODIFIED)
		FoamBase_EXPORT virtual void addWatch();

		//- Add file watch for fileName on object if not yet watched. Return
		//  index of watch
		FoamBase_EXPORT virtual label addWatch(const fileName&);

		const fileNameList& files() const
		{
			return files_;
		}

		fileNameList& files()
		{
			return files_;
		}


		// Member Operators

			//- Move assignment
		FoamBase_EXPORT void operator=(unwatchedIOdictionary&&);
	};


	//- Template function for obtaining global status
	template<>
	inline bool typeGlobal<unwatchedIOdictionary>()
	{
		return true;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_unwatchedIOdictionary_Header
