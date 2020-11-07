#pragma once
#ifndef _CFCFaceToCellStencil_Header
#define _CFCFaceToCellStencil_Header

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
	tnbLib::CFCFaceToCellStencil

Description

SourceFiles
	CFCFaceToCellStencil.C

\*---------------------------------------------------------------------------*/

#include <faceToCellStencil.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						Class CFCFaceToCellStencil Declaration
	\*---------------------------------------------------------------------------*/

	class CFCFaceToCellStencil
		:
		public faceToCellStencil
	{
		// Private Member Functions

			//- Calculates per face the neighbour data (= faces of cell).
			//  Leaves out the face itself since this is already in stencil.
		FoamFiniteVolume_EXPORT void calcFaceBoundaryData(labelListList& neiGlobal) const;

		//- Calculates per cell the neighbour data
		//  (= cell or boundary in global numbering).
		//  First element is always cell itself!
		FoamFiniteVolume_EXPORT void calcCellStencil(labelListList& globalCellFaces) const;


	public:

		// Constructors

			//- Construct from mesh
		FoamFiniteVolume_EXPORT explicit CFCFaceToCellStencil(const polyMesh&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_CFCFaceToCellStencil_Header
