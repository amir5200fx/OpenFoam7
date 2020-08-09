#pragma once
#ifndef _FECCellToFaceStencil_Header
#define _FECCellToFaceStencil_Header

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
	tnbLib::FECCellToFaceStencil

Description
	All cells connected via edge to face.

SourceFiles
	FECCellToFaceStencil.C

\*---------------------------------------------------------------------------*/

#include <cellToFaceStencil.hxx>
#include <EdgeMap.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						Class FECCellToFaceStencil Declaration
	\*---------------------------------------------------------------------------*/

	class FECCellToFaceStencil
		:
		public cellToFaceStencil
	{
		// Private Member Functions

			//- Calculates per edge the neighbour data (= edgeCells)
		void calcEdgeBoundaryData
		(
			const boolList& isValidBFace,
			const labelList& boundaryEdges,
			EdgeMap<labelList>& neiGlobal
		) const;

		//- Calculates per face the edge connected data
		//  (= cell or boundary in global numbering).
		void calcFaceStencil(labelListList& faceStencil) const;


	public:

		// Constructors

			//- Construct from all cells and boundary faces
		explicit FECCellToFaceStencil(const polyMesh&);

	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_FECCellToFaceStencil_Header
