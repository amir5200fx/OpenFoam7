#pragma once
#ifndef _patchInteractionDataList_Header
#define _patchInteractionDataList_Header

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
	tnbLib::patchInteractionDataList

Description
	List container for patchInteractionData class

\*---------------------------------------------------------------------------*/

#include <patchInteractionData.hxx>
#include <polyMesh.hxx>
#include <dictionary.hxx>
#include <labelList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	/*---------------------------------------------------------------------------*\
					  Class patchInteractionDataList Declaration
	\*---------------------------------------------------------------------------*/

	class patchInteractionDataList
		:
		public List<patchInteractionData>
	{
		// Private Data

			//- List of patch IDs for each patch group
		labelListList patchGroupIDs_;


	public:

		// Constructor

			//- Construct null
		FoamLagrangian_EXPORT patchInteractionDataList();

		//- Construct copy
		FoamLagrangian_EXPORT patchInteractionDataList(const patchInteractionDataList& pidl);

		//- Construct from Istream
		FoamLagrangian_EXPORT patchInteractionDataList(const polyMesh& mesh, const dictionary& dict);


		// Member Functions

			//- Return label of group containing patch id
			//  Returns -1 if patch id is not present
		FoamLagrangian_EXPORT label applyToPatch(const label id) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_patchInteractionDataList_Header
