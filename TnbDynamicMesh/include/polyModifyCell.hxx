#pragma once
#ifndef _polyModifyCell_Header
#define _polyModifyCell_Header

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
	tnbLib::polyModifyCell

Description
	Class describing modification of a cell.

\*---------------------------------------------------------------------------*/

#include <label.hxx>
#include <topoAction.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						   Class polyModifyCell Declaration
	\*---------------------------------------------------------------------------*/

	class polyModifyCell
		:
		public topoAction
	{
		// Private Data

			//- Cell ID
		label cellID_;

		//- Remove from current zone
		bool removeFromZone_;

		//- New zone ID
		label zoneID_;


	public:

		// Static Data Members

			//- Runtime type information
		//TypeName("modifyCell");
		static const char* typeName_() { return "modifyCell"; }
		static FoamDynamicMesh_EXPORT const ::tnbLib::word typeName;
		static FoamDynamicMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct null.  Used only for list construction
		polyModifyCell()
			:
			cellID_(-1),
			removeFromZone_(false),
			zoneID_(-1)
		{}

		//- Construct from components
		polyModifyCell
		(
			const label cellID,
			const bool removeFromZone,
			const label newZoneID
		)
			:
			cellID_(cellID),
			removeFromZone_(removeFromZone),
			zoneID_(newZoneID)
		{}

		//- Construct and return a clone
		virtual autoPtr<topoAction> clone() const
		{
			return autoPtr<topoAction>(new polyModifyCell(*this));
		}


		// Default Destructor

		// Member Functions

			//- Cell ID
		label cellID() const
		{
			return cellID_;
		}

		//- Does the cell belong to a zone?
		bool isInZone() const
		{
			return zoneID_ >= 0;
		}

		bool removeFromZone() const
		{
			return removeFromZone_;
		}

		//- Cell zone ID
		label zoneID() const
		{
			return zoneID_;
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_polyModifyCell_Header
