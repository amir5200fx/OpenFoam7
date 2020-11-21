#pragma once
#ifndef _polyModifyPoint_Header
#define _polyModifyPoint_Header

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
	tnbLib::polyModifyPoint

Description
	Class describing modification of a point.

\*---------------------------------------------------------------------------*/

#include <label.hxx>
#include <point.hxx>
#include <topoAction.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						   Class polyModifyPoint Declaration
	\*---------------------------------------------------------------------------*/

	class polyModifyPoint
		:
		public topoAction
	{
		// Private Data

			//- Point ID
		label pointID_;

		//- New point location
		point location_;

		//- Remove from current zone
		bool removeFromZone_;

		//- New zone ID
		label zoneID_;

		//- Does the point support a cell
		bool inCell_;


	public:

		// Static Data Members

			//- Runtime type information
		//TypeName("modifyPoint");
		static const char* typeName_() { return "modifyPoint"; }
		static FoamDynamicMesh_EXPORT const ::tnbLib::word typeName;
		static FoamDynamicMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct null.  Used only for list construction
		polyModifyPoint()
			:
			pointID_(-1),
			location_(Zero),
			removeFromZone_(false),
			zoneID_(-1),
			inCell_(false)
		{}

		//- Construct from components
		polyModifyPoint
		(
			const label pointID,
			const point& newP,
			const bool removeFromZone,
			const label newZoneID,
			const bool inCell
		)
			:
			pointID_(pointID),
			location_(newP),
			removeFromZone_(removeFromZone),
			zoneID_(newZoneID),
			inCell_(inCell)
		{}

		//- Construct and return a clone
		virtual autoPtr<topoAction> clone() const
		{
			return autoPtr<topoAction>(new polyModifyPoint(*this));
		}


		// Default Destructor

		// Member Functions

			//- Point ID
		label pointID() const
		{
			return pointID_;
		}

		//- New point location
		const point& newPoint() const
		{
			return location_;
		}

		//- Does the point belong to a zone?
		bool isInZone() const
		{
			return zoneID_ >= 0;
		}

		//- Should the point be removed from current zone
		bool removeFromZone() const
		{
			return removeFromZone_;
		}

		//- Point zone ID
		label zoneID() const
		{
			return zoneID_;
		}

		//- Does the point support a cell
		bool inCell() const
		{
			return inCell_;
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_polyModifyPoint_Header
