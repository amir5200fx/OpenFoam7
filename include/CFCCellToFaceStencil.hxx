#pragma once
#ifndef _CFCCellToFaceStencil_Header
#define _CFCCellToFaceStencil_Header

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
	tnbLib::CFCCellToFaceStencil

Description
	Combined corresponding cellToCellStencil of owner and neighbour.

SourceFiles
	CFCCellToFaceStencil.C

\*---------------------------------------------------------------------------*/

#include <cellToFaceStencil.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						Class CFCCellToFaceStencil Declaration
	\*---------------------------------------------------------------------------*/

	class CFCCellToFaceStencil
		:
		public cellToFaceStencil
	{
	public:

		// Constructors

			//- Construct from mesh
		FoamFiniteVolume_EXPORT explicit CFCCellToFaceStencil(const polyMesh&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_CFCCellToFaceStencil_Header
