#pragma once
#ifndef _meshSearchMeshObject_Header
#define _meshSearchMeshObject_Header

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
	tnbLib::meshSearchMeshObject

Description
	MeshObject wrapper around meshSearch(mesh).

SourceFiles

\*---------------------------------------------------------------------------*/

#include <MeshObject.hxx>
#include <meshSearch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
				  Class meshSearchMeshObject Declaration
	\*---------------------------------------------------------------------------*/

	class meshSearchMeshObject
		:
		public MeshObject<polyMesh, GeometricMeshObject, meshSearchMeshObject>,
		public meshSearch
	{

	public:

		// Declare name of the class and its debug switch
		TypeName("meshSearchMeshObject");


		// Constructors

			//- Constructor given polyMesh
		explicit meshSearchMeshObject(const polyMesh& mesh);

		//- Destructor
		virtual ~meshSearchMeshObject()
		{}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_meshSearchMeshObject_Header
