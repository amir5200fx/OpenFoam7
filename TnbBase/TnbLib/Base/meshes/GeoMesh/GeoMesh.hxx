#pragma once
#ifndef _GeoMesh_Header
#define _GeoMesh_Header

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
	tnbLib::GeoMesh

Description
	Generic mesh wrapper used by volMesh, surfaceMesh, pointMesh etc.

\*---------------------------------------------------------------------------*/

#include <objectRegistry.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class GeoMesh Declaration
	\*---------------------------------------------------------------------------*/

	template<class MESH>
	class GeoMesh
	{

	protected:

		// Protected data

			//- Reference to Mesh
		const MESH& mesh_;


	public:

		// Public Typedefs

		typedef MESH Mesh;
		typedef typename MESH::BoundaryMesh BoundaryMesh;


		// Constructors

			//- Construct from MESH
		explicit GeoMesh(const MESH& mesh)
			:
			mesh_(mesh)
		{}


		// Member Functions

			//- Return the object registry
		const objectRegistry& thisDb() const
		{
			return mesh_;
		}


		// Member Operators

			//- Return reference to polyMesh
		const MESH& operator()() const
		{
			return mesh_;
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_GeoMesh_Header
