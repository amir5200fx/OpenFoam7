#pragma once
#ifndef _faceToCellStencil_Header
#define _faceToCellStencil_Header

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
	tnbLib::faceToCellStencil

Description
	baseclass for extended cell centred addressing. Contains per cell a
	list of neighbouring faces in global addressing.

SourceFiles
	faceToCellStencil.C

\*---------------------------------------------------------------------------*/

#include <globalIndex.hxx>
#include <boolList.hxx>
#include <HashSet.hxx>
#include <indirectPrimitivePatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class polyMesh;

	/*---------------------------------------------------------------------------*\
						  Class faceToCellStencil Declaration
	\*---------------------------------------------------------------------------*/

	class faceToCellStencil
		:
		public labelListList
	{
		// Private Data

		const polyMesh& mesh_;

		//- Global numbering for faces
		const globalIndex globalNumbering_;

	public:

		// Constructors

		//- Construct from mesh
		FoamFiniteVolume_EXPORT explicit faceToCellStencil(const polyMesh&);


		// Member Functions

		const polyMesh& mesh() const
		{
			return mesh_;
		}

		//- Global numbering for faces
		const globalIndex& globalNumbering() const
		{
			return globalNumbering_;
		}

	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_faceToCellStencil_Header
