#pragma once
#ifndef _nearWallDistNoSearch_Header
#define _nearWallDistNoSearch_Header

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
	tnbLib::nearWallDistNoSearch

Description
	Distance calculation for cells with face on a wall. Does not search
	anything, just takes normal component of distance.

SourceFiles
	nearWallDistNoSearch.C

\*---------------------------------------------------------------------------*/

#include <volFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class fvMesh;

	/*---------------------------------------------------------------------------*\
							   Class nearWallDistNoSearch Declaration
	\*---------------------------------------------------------------------------*/

	class nearWallDistNoSearch
		:
		public volScalarField::Boundary
	{
		// Private Data

		//- Reference to mesh
		const fvMesh& mesh_;


		// Private Member Functions

		//- Do all calculations.
		FoamFiniteVolume_EXPORT void doAll();


	public:

		// Constructors

		//- Construct from components
		FoamFiniteVolume_EXPORT nearWallDistNoSearch(const fvMesh& mesh);

		//- Disallow default bitwise copy construction
		FoamFiniteVolume_EXPORT nearWallDistNoSearch(const nearWallDistNoSearch&) = delete;


		//- Destructor
		FoamFiniteVolume_EXPORT virtual ~nearWallDistNoSearch();


		// Member Functions

		//- Correct for mesh geom/topo changes
		FoamFiniteVolume_EXPORT virtual void correct();


		// Member Operators

		//- Disallow default bitwise assignment
		FoamFiniteVolume_EXPORT void operator=(const nearWallDistNoSearch&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_nearWallDistNoSearch_Header
