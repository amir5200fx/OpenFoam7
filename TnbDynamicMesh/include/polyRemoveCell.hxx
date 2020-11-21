#pragma once
#ifndef _polyRemoveCell_Header
#define _polyRemoveCell_Header

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
	tnbLib::polyRemoveCell

Description
	Class containing data for cell removal.

\*---------------------------------------------------------------------------*/

#include <label.hxx>
#include <topoAction.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						   Class polyRemoveCell Declaration
	\*---------------------------------------------------------------------------*/

	class polyRemoveCell
		:
		public topoAction
	{
		// Private Data

			//- Cell ID
		label cellID_;

		//- Merge cell ID or -1
		label mergeCellID_;

	public:

		// Static Data Members

			//- Runtime type information
		//TypeName("removeCell");
		static const char* typeName_() { return "removeCell"; }
		static FoamDynamicMesh_EXPORT const ::tnbLib::word typeName;
		static FoamDynamicMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct null.  Used for constructing lists
		polyRemoveCell()
			:
			cellID_(-1),
			mergeCellID_(-1)
		{}

		//- Construct from components
		polyRemoveCell(const label cellID, const label mergeCellID = -1)
			:
			cellID_(cellID),
			mergeCellID_(mergeCellID)
		{}

		//- Construct and return a clone
		virtual autoPtr<topoAction> clone() const
		{
			return autoPtr<topoAction>(new polyRemoveCell(*this));
		}


		// Default Destructor


		// Member Functions

			//- Return cell ID
		label cellID() const
		{
			return cellID_;
		}

		//- Return cell ID
		label mergeCellID() const
		{
			return mergeCellID_;
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_polyRemoveCell_Header
