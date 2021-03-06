#pragma once
#ifndef _dynamicMotionSolverFvMesh_Header
#define _dynamicMotionSolverFvMesh_Header

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
	tnbLib::dynamicMotionSolverFvMesh

Description
	The dynamicMotionSolverFvMesh

SourceFiles
	dynamicMotionSolverFvMesh.C

\*---------------------------------------------------------------------------*/

#include <dynamicFvMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class motionSolver;

	/*---------------------------------------------------------------------------*\
					  Class dynamicMotionSolverFvMesh Declaration
	\*---------------------------------------------------------------------------*/

	class dynamicMotionSolverFvMesh
		:
		public dynamicFvMesh
	{
		// Private Data

		autoPtr<motionSolver> motionPtr_;

		//- Optional list of vectorFields to update for mesh motion
		//  For modern solvers using Uf and correctPhi to update the flux
		//  after motion it is not necessary to specify a "velocityFields" list
		velocityMotionCorrection velocityMotionCorrection_;


	public:

		//- Runtime type information
		//TypeName("dynamicMotionSolverFvMesh");
		static const char* typeName_() { return "dynamicMotionSolverFvMesh"; }
		static FoamDynamicMesh_EXPORT const ::tnbLib::word typeName;
		static FoamDynamicMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from IOobject
		FoamDynamicMesh_EXPORT dynamicMotionSolverFvMesh(const IOobject& io);

		//- Disallow default bitwise copy construction
		FoamDynamicMesh_EXPORT dynamicMotionSolverFvMesh(const dynamicMotionSolverFvMesh&) = delete;


		//- Destructor
		FoamDynamicMesh_EXPORT ~dynamicMotionSolverFvMesh();


		// Member Functions

			//- Return the motionSolver
		FoamDynamicMesh_EXPORT const motionSolver& motion() const;

		//- Update the mesh for both mesh motion and topology change
		FoamDynamicMesh_EXPORT virtual bool update();


		// Write

			//- Write the underlying polyMesh and other data
		FoamDynamicMesh_EXPORT virtual bool writeObject
		(
			IOstream::streamFormat fmt,
			IOstream::versionNumber ver,
			IOstream::compressionType cmp,
			const bool write = true
		) const;


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const dynamicMotionSolverFvMesh&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_dynamicMotionSolverFvMesh_Header
