#pragma once
#ifndef _polyRemoveFace_Header
#define _polyRemoveFace_Header

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
	tnbLib::polyRemoveFace

Description
	Class containing data for face removal.

\*---------------------------------------------------------------------------*/

#include <label.hxx>
#include <topoAction.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							Class polyRemoveFace Declaration
	\*---------------------------------------------------------------------------*/

	class polyRemoveFace
		:
		public topoAction
	{
		// Private Data

			//- Face ID
		label faceID_;

		//- Merge faceID or -1
		label mergeFaceID_;

	public:

		// Static Data Members

			//- Runtime type information
		TypeName("removeFace");


		// Constructors

			//- Construct null.  Used for constructing lists
		polyRemoveFace()
			:
			faceID_(-1),
			mergeFaceID_(-1)
		{}

		//- Construct from components
		polyRemoveFace(const label faceID, const label mergeFaceID = -1)
			:
			faceID_(faceID),
			mergeFaceID_(mergeFaceID)
		{}

		//- Construct and return a clone
		virtual autoPtr<topoAction> clone() const
		{
			return autoPtr<topoAction>(new polyRemoveFace(*this));
		}


		// Default Destructor


		// Member Functions

			//- Return face ID
		label faceID() const
		{
			return faceID_;
		}

		//- Return merge face ID
		label mergeFaceID() const
		{
			return mergeFaceID_;
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_polyRemoveFace_Header
