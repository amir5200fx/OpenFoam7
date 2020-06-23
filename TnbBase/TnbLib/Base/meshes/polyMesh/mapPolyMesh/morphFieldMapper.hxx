#pragma once
#ifndef _morphFieldMapper_Header
#define _morphFieldMapper_Header

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
	tnbLib::morphFieldMapper

Description
	Abstract base class to hold the Field mapping for mesh morphs.

\*---------------------------------------------------------------------------*/

#include <generalFieldMapper.hxx>
#include <Map.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class morphFieldMapper Declaration
	\*---------------------------------------------------------------------------*/

	class morphFieldMapper
		:
		public generalFieldMapper
	{

	public:

		// Constructors

			//- Null constructor
		morphFieldMapper()
		{}


		//- Destructor
		virtual ~morphFieldMapper()
		{}


		// Member Functions

			//- Return size of field before mapping
		virtual label sizeBeforeMapping() const = 0;

		//- Are there any inserted objects
		virtual bool insertedObjects() const = 0;

		//- Return list of inserted objects
		virtual const labelList& insertedObjectLabels() const = 0;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_morphFieldMapper_Header
