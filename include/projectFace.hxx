#pragma once
#ifndef _projectFace_Header
#define _projectFace_Header

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
	tnbLib::blockFaces::projectFace

Description
	Projects the given set of face points onto the selected surface of the
	geometry provided as a searchableSurfaces object.

SourceFiles
	projectFace.C

\*---------------------------------------------------------------------------*/

#include <blockFace.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace blockFaces
	{

		/*---------------------------------------------------------------------------*\
								   Class projectFace Declaration
		\*---------------------------------------------------------------------------*/

		class projectFace
			:
			public blockFace
		{
			// Private Data

				//- The surface onto which the points are projected
			const searchableSurface& surface_;


			// Private Member Functions

			FoamFvMesh_EXPORT const searchableSurface& lookupSurface
			(
				const searchableSurfaces& geometry,
				Istream& is
			) const;

			//- Convert i,j to single index
			FoamFvMesh_EXPORT label index
			(
				const labelPair& n,
				const labelPair& coord
			) const;

			//- Calculate lambdas (but unnormalised)
			FoamFvMesh_EXPORT void calcLambdas
			(
				const labelPair& n,
				const pointField& points,
				scalarField& lambdaI,
				scalarField& lambdaJ
			) const;


		public:

			//- Runtime type information
			//TypeName("project");
			static const char* typeName_() { return "project"; }
			static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
			static FoamFvMesh_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from Istream setting pointsList
			FoamFvMesh_EXPORT projectFace
			(
				const dictionary& dict,
				const label index,
				const searchableSurfaces& geometry,
				Istream&
			);

			//- Disallow default bitwise copy construction
			FoamFvMesh_EXPORT projectFace(const projectFace&) = delete;


			//- Destructor
			virtual ~projectFace()
			{}


			// Member Functions

				//- Project the given points onto the surface
			FoamFvMesh_EXPORT virtual void project
			(
				const blockDescriptor&,
				const label blockFacei,
				pointField& points
			) const;


			// Member Operators

				//- Disallow default bitwise assignment
			FoamFvMesh_EXPORT void operator=(const projectFace&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace blockFaces
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_projectFace_Header
