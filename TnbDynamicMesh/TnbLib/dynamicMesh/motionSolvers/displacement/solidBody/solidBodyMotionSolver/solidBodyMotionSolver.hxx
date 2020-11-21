#pragma once
#ifndef _solidBodyMotionSolver_Header
#define _solidBodyMotionSolver_Header

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
	tnbLib::solidBodyMotionSolver

Description
	Solid-body motion of the mesh specified by a run-time selectable
	motion function.

SourceFiles
	solidBodyMotionSolver.C

\*---------------------------------------------------------------------------*/

#include <points0MotionSolver.hxx>
#include <solidBodyMotionFunction.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					   Class solidBodyMotionSolver Declaration
	\*---------------------------------------------------------------------------*/

	class solidBodyMotionSolver
		:
		public points0MotionSolver
	{
		// Private Data

			//- The motion control function
		autoPtr<solidBodyMotionFunction> SBMFPtr_;

		//- Points to move when cell zone is supplied
		labelList pointIDs_;

		//- Flag to indicate whether all cells should move
		bool moveAllCells_;


	public:

		//- Runtime type information
		//TypeName("solidBody");
		static const char* typeName_() { return "solidBody"; }
		static FoamDynamicMesh_EXPORT const ::tnbLib::word typeName;
		static FoamDynamicMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from mesh and dictionary
		FoamDynamicMesh_EXPORT solidBodyMotionSolver
		(
			const polyMesh&,
			const dictionary&
		);

		//- Disallow default bitwise copy construction
		solidBodyMotionSolver(const solidBodyMotionSolver&) = delete;


		//- Destructor
		FoamDynamicMesh_EXPORT ~solidBodyMotionSolver();


		// Member Functions

			//- Return point location obtained from the current motion field
		FoamDynamicMesh_EXPORT virtual tmp<pointField> curPoints() const;

		//- Solve for motion
		virtual void solve()
		{}


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const solidBodyMotionSolver&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_solidBodyMotionSolver_Header
