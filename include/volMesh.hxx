#pragma once
#ifndef _volMesh_Header
#define _volMesh_Header

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
	tnbLib::volMesh

Description
	Mesh data needed to do the Finite Volume discretisation.

Class
	tnbLib::isVolMesh

Description
	Supports static assertion that a template argument is of type volMesh.

\*---------------------------------------------------------------------------*/

#include <GeoMesh.hxx>
#include <fvMesh.hxx>
#include <primitiveMesh.hxx>

#include <type_traits>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class volMesh Declaration
	\*---------------------------------------------------------------------------*/

	class volMesh
		:
		public GeoMesh<fvMesh>
	{

	public:

		// Constructors

			//- Construct from fvMesh
		explicit volMesh(const fvMesh& mesh)
			:
			GeoMesh<fvMesh>(mesh)
		{}


		// Member Functions

			//- Return size
		label size() const
		{
			return size(mesh_);
		}

		//- Return size
		static label size(const Mesh& mesh)
		{
			return mesh.nCells();
		}

		//- Return cell centres
		const volVectorField& C()
		{
			return mesh_.C();
		}
	};


	/*---------------------------------------------------------------------------*\
							  Class isVolMesh Declaration
	\*---------------------------------------------------------------------------*/

	template<class T>
	class isVolMesh
		:
		public std::false_type
	{};


	template<>
	class isVolMesh<volMesh>
		:
		public std::true_type
	{};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_volMesh_Header
