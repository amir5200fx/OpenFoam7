#pragma once
#ifndef _cellPointWeight_Header
#define _cellPointWeight_Header

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
	tnbLib::cellPointWeight

Description
	tnbLib::cellPointWeight

SourceFiles
	cellPointWeight.C

\*---------------------------------------------------------------------------*/

#include <vector.hxx>
#include <barycentric.hxx>
#include <triFace.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class polyMesh;

	/*---------------------------------------------------------------------------*\
							   Class cellPointWeight Declaration
	\*---------------------------------------------------------------------------*/

	class cellPointWeight
	{
	protected:

		// Protected data

		   //- Cell index
		const label celli_;

		//- Weights applied to tet vertices. Equal to the barycentric coordinates
		//  of the interpolation position.
		barycentric weights_;

		//- Face vertex indices
		triFace faceVertices_;


		// Protected Member Functions

		void findTetrahedron
		(
			const polyMesh& mesh,
			const vector& position,
			const label celli
		);

		void findTriangle
		(
			const polyMesh& mesh,
			const vector& position,
			const label facei
		);


	public:

		//- Debug switch
		static int debug;

		//- Tolerance used in calculating barycentric co-ordinates
		//  (applied to normalised values)
		static scalar tol;


		// Constructors

			//- Construct from components
		cellPointWeight
		(
			const polyMesh& mesh,
			const vector& position,
			const label celli,
			const label facei = -1
		);


		// Member Functions

			//- Cell index
		inline label cell() const
		{
			return celli_;
		}

		//- Interpolation weights
		inline const barycentric& weights() const
		{
			return weights_;
		}

		//- Interpolation addressing for points on face
		inline const triFace& faceVertices() const
		{
			return faceVertices_;
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cellPointWeight_Header
