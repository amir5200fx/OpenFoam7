#pragma once
#ifndef _multiSolidBodyMotionSolver_Header
#define _multiSolidBodyMotionSolver_Header

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
	tnbLib::multiSolidBodyMotionSolver

Description
	Solid-body motion of the mesh specified by a run-time selectable
	motion function.

SourceFiles
	multiSolidBodyMotionSolver.C

\*---------------------------------------------------------------------------*/

#include <points0MotionSolver.hxx>
#include <solidBodyMotionFunction.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					   Class multiSolidBodyMotionSolver Declaration
	\*---------------------------------------------------------------------------*/

	class multiSolidBodyMotionSolver
		:
		public points0MotionSolver
	{
		// Private Data

			//- The motion control function
		PtrList<solidBodyMotionFunction> SBMFs_;

		//- Specified cellZones
		labelList zoneIDs_;

		//- Points to move per cellZone
		labelListList pointIDs_;


	public:

		//- Runtime type information
		//TypeName("multiSolidBodyMotionSolver");
		static const char* typeName_() { return "multiSolidBodyMotionSolver"; }
		static FoamDynamicMesh_EXPORT const ::tnbLib::word typeName;
		static FoamDynamicMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from mesh and dictionary
		FoamDynamicMesh_EXPORT multiSolidBodyMotionSolver
		(
			const polyMesh&,
			const dictionary&
		);

		//- Disallow default bitwise copy construction
		multiSolidBodyMotionSolver(const multiSolidBodyMotionSolver&) = delete;


		//- Destructor
		FoamDynamicMesh_EXPORT ~multiSolidBodyMotionSolver();


		// Member Functions

			//- Return point location obtained from the current motion field
		FoamDynamicMesh_EXPORT virtual tmp<pointField> curPoints() const;

		//- Solve for motion
		virtual void solve()
		{}


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const multiSolidBodyMotionSolver&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_multiSolidBodyMotionSolver_Header
