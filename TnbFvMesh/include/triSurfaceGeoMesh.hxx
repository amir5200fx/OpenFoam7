#pragma once
#ifndef _triSurfaceGeoMesh_Header
#define _triSurfaceGeoMesh_Header

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
	tnbLib::triSurfaceGeoMesh

Description
	The triSurface GeoMesh (for holding fields).

	Similar to the volGeoMesh used for the Finite Volume discretization.

\*---------------------------------------------------------------------------*/

#include <GeoMesh.hxx>
#include <triSurface.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	class triSurfaceGeoMesh
		:
		public GeoMesh<triSurface>
	{

	public:

		// Constructors

			//- Construct from triSurface reference
		explicit triSurfaceGeoMesh(const triSurface& mesh)
			:
			GeoMesh<triSurface>(mesh)
		{}


		// Member Functions

			//- Return size
		static label size(const triSurface& mesh)
		{
			return mesh.size();
		}

		//- Return size
		label size() const
		{
			return size(mesh_);
		}

	};

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_triSurfaceGeoMesh_Header
