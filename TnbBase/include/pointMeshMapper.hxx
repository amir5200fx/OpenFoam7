#pragma once
#ifndef _pointMeshMapper_Header
#define _pointMeshMapper_Header

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
	tnbLib::pointMeshMapper

Description
	Class holds all the necessary information for mapping fields associated
	with pointMesh.

SourceFiles
	pointMeshMapper.C

\*---------------------------------------------------------------------------*/

#include <pointMapper.hxx>
#include <pointBoundaryMeshMapper.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class pointMesh;
	class mapPolyMesh;

	/*---------------------------------------------------------------------------*\
							Class pointMeshMapper Declaration
	\*---------------------------------------------------------------------------*/

	class pointMeshMapper
	{
		// Private Data

			//- Reference to mesh
		const pointMesh& mesh_;

		//- Point mapper
		pointMapper pointMap_;

		//- Boundary mapper
		pointBoundaryMeshMapper boundaryMap_;


	public:

		// Constructors

			//- Construct from pointMesh
		pointMeshMapper(const pointMesh& mesh, const mapPolyMesh& mpm)
			:
			mesh_(mesh),
			pointMap_(mesh, mpm),
			boundaryMap_(mesh, pointMap_, mpm)
		{}

		//- Disallow default bitwise copy construction
		pointMeshMapper(const pointMeshMapper&) = delete;


		// Member Functions


			//- Return reference to mesh fields belong to
		const pointMesh& mesh() const
		{
			return mesh_;
		}

		//- Return reference to objectRegistry storing fields. Can be
		//  removed once fields stored on pointMesh.
		const objectRegistry& thisDb() const
		{
			return mesh_();
		}

		//- Return point mapper
		const morphFieldMapper& pointMap() const
		{
			return pointMap_;
		}

		//- Return boundary mapper
		const pointBoundaryMeshMapper& boundaryMap() const
		{
			return boundaryMap_;
		}


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const pointMeshMapper&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_pointMeshMapper_Header
