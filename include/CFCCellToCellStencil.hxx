#pragma once
#ifndef _CFCCellToCellStencil_Header
#define _CFCCellToCellStencil_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
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
	tnbLib::CFCCellToCellStencil

Description

SourceFiles
	CFCCellToCellStencil.C

\*---------------------------------------------------------------------------*/

#include <cellToCellStencil.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						Class CFCCellToCellStencil Declaration
	\*---------------------------------------------------------------------------*/

	class CFCCellToCellStencil
		:
		public cellToCellStencil
	{
		// Private Member Functions

			//- Calculates per face the neighbour data (= cell or boundary face)
		FoamFiniteVolume_EXPORT void calcFaceBoundaryData(labelList& neiGlobal) const;

		//- Calculates per cell the neighbour data
		//  (= cell or boundary in global numbering).
		//  First element is always cell itself!
		FoamFiniteVolume_EXPORT void calcCellStencil(labelListList& globalCellCells) const;


	public:

		// Constructors

			//- Construct from mesh
		FoamFiniteVolume_EXPORT explicit CFCCellToCellStencil(const polyMesh& mesh);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_CFCCellToCellStencil_Header
