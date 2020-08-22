#pragma once
#ifndef _projectVertex_Header
#define _projectVertex_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2016-2019 OpenFOAM Foundation
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
	tnbLib::blockVertices::projectVertex

Description
	Projects the vertex onto the selected surfacees of the
	geometry provided as a searchableSurfaces object.

SourceFiles
	projectVertex.C

\*---------------------------------------------------------------------------*/

#include <pointVertex.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace blockVertices
	{

		/*---------------------------------------------------------------------------*\
								Class projectVertex Declaration
		\*---------------------------------------------------------------------------*/

		class projectVertex
			:
			public pointVertex
		{
			// Private Data

			const searchableSurfaces& geometry_;

			//- The indices of surfaces onto which the points are projected
			labelList surfaces_;


		public:

			//- Runtime type information
			TypeName("project");


			// Constructors

				//- Construct from Istream setting pointsList
			projectVertex
			(
				const dictionary&,
				const label index,
				const searchableSurfaces& geometry,
				Istream&
			);

			//- Disallow default bitwise copy construction
			projectVertex(const projectVertex&) = delete;


			//- Destructor
			virtual ~projectVertex()
			{}


			// Member Functions

				//- Project the given points onto the surface
			virtual operator point() const;


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const projectVertex&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace blockVertices
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_projectVertex_Header
