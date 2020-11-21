#pragma once
#ifndef _displacementMeshMoverMotionSolver_Header
#define _displacementMeshMoverMotionSolver_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2019 OpenFOAM Foundation
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
	tnbLib::displacementMeshMoverMotionSolver

Description
	Mesh motion solver for an fvMesh.  Based on solving the cell-centre
	Laplacian for the motion displacement.

SourceFiles
	displacementMeshMoverMotionSolver.C

\*---------------------------------------------------------------------------*/

#include <displacementMotionSolver.hxx>
#include <externalDisplacementMeshMover.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
				 Class displacementMeshMoverMotionSolver Declaration
	\*---------------------------------------------------------------------------*/

	class displacementMeshMoverMotionSolver
		:
		public displacementMotionSolver
	{
		// Private Data

		mutable autoPtr<externalDisplacementMeshMover> meshMoverPtr_;


	public:

		//- Runtime type information
		//TypeName("displacementMeshMover");
		static const char* typeName_() { return "displacementMeshMover"; }
		static FoamSnappyHexMesh_EXPORT const ::tnbLib::word typeName;
		static FoamSnappyHexMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from polyMesh and dictionary
		FoamSnappyHexMesh_EXPORT displacementMeshMoverMotionSolver(const polyMesh&, const dictionary&);

		//- Disallow default bitwise copy construction
		FoamSnappyHexMesh_EXPORT displacementMeshMoverMotionSolver
		(
			const displacementMeshMoverMotionSolver&
		);


		//- Destructor
		FoamSnappyHexMesh_EXPORT ~displacementMeshMoverMotionSolver();


		// Member Functions

		FoamSnappyHexMesh_EXPORT externalDisplacementMeshMover& meshMover() const;

		//- Return point location obtained from the current motion field
		FoamSnappyHexMesh_EXPORT virtual tmp<pointField> curPoints() const;

		//- Solve for motion
		FoamSnappyHexMesh_EXPORT virtual void solve();

		//- Update local data for geometry changes
		FoamSnappyHexMesh_EXPORT virtual void movePoints(const pointField&);

		//- Update topology
		FoamSnappyHexMesh_EXPORT virtual void updateMesh(const mapPolyMesh&);


		// Member Operators

			//- Disallow default bitwise assignment
		FoamSnappyHexMesh_EXPORT void operator=(const displacementMeshMoverMotionSolver&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_displacementMeshMoverMotionSolver_Header
