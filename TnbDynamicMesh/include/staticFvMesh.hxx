#pragma once
#ifndef _staticFvMesh_Header
#define _staticFvMesh_Header

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
	tnbLib::staticFvMesh

Description
	tnbLib::staticFvMesh

SourceFiles
	staticFvMesh.C

\*---------------------------------------------------------------------------*/


#include <dynamicFvMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class staticFvMesh Declaration
	\*---------------------------------------------------------------------------*/

	class staticFvMesh
		:
		public dynamicFvMesh
	{
	public:

		//- Runtime type information
		TypeName("staticFvMesh");


		// Constructors

			//- Construct from IOobject
		staticFvMesh(const IOobject& io);

		//- Disallow default bitwise copy construction
		staticFvMesh(const staticFvMesh&) = delete;


		//- Destructor
		~staticFvMesh();


		// Member Functions

			//- Is mesh dynamic
		virtual bool dynamic() const
		{
			return false;
		}

		//- Dummy update function which does not change the mesh
		virtual bool update();


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const staticFvMesh&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_staticFvMesh_Header
