#pragma once
#ifndef _namedVertex_Header
#define _namedVertex_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2016-2018 OpenFOAM Foundation
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
	tnbLib::blockVertices::namedVertex

Description
	Gives name to a vertex.

SourceFiles
	namedVertex.C

\*---------------------------------------------------------------------------*/

#include <blockVertex.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace blockVertices
	{

		/*---------------------------------------------------------------------------*\
								   Class namedVertex Declaration
		\*---------------------------------------------------------------------------*/

		class namedVertex
			:
			public blockVertex
		{
		protected:

			// Protected member data

				//- The dictionary variable name for the vertex number
			word name_;

			//- The vertex location
			autoPtr<blockVertex> vertexPtr_;


		public:

			//- Runtime type information
			//TypeName("name");
			static const char* typeName_() { return "name"; }
			static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
			static FoamFvMesh_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from Istream setting pointsList
			FoamFvMesh_EXPORT namedVertex
			(
				const dictionary&,
				const label index,
				const searchableSurfaces& geometry,
				Istream&
			);


			//- Destructor
			virtual ~namedVertex()
			{}


			// Member Functions

			FoamFvMesh_EXPORT virtual operator point() const;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace blockVertices
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_namedVertex_Header
