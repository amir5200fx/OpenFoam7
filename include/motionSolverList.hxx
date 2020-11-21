#pragma once
#ifndef _motionSolverList_Header
#define _motionSolverList_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2019 OpenFOAM Foundation
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
	tnbLib::motionSolverList

Description
	Motion of the mesh specified as a list of motion solvers.

	The motion solvers are executed in order and the resulting displacements
	accumulated into an overall displacement and the displaced point positions
	returned.

SourceFiles
	motionSolverList.C

\*---------------------------------------------------------------------------*/

#include <motionSolver.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					   Class motionSolverList Declaration
	\*---------------------------------------------------------------------------*/

	class motionSolverList
		:
		public motionSolver
	{
		// Private Data

		PtrList<motionSolver> motionSolvers_;


	public:

		//- Runtime type information
		//TypeName("motionSolverList");
		static const char* typeName_() { return "motionSolverList"; }
		static FoamDynamicMesh_EXPORT const ::tnbLib::word typeName;
		static FoamDynamicMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from mesh and dictionary
		FoamDynamicMesh_EXPORT motionSolverList(const polyMesh&, const dictionary&);

		//- Disallow default bitwise copy construction
		motionSolverList(const motionSolverList&) = delete;


		//- Destructor
		FoamDynamicMesh_EXPORT virtual ~motionSolverList();


		// Member Functions

			//- Provide current points for motion.  Uses current motion field
		FoamDynamicMesh_EXPORT virtual tmp<pointField> curPoints() const;

		//- Solve for motion
		FoamDynamicMesh_EXPORT virtual void solve();

		//- Update local data for geometry changes
		FoamDynamicMesh_EXPORT virtual void movePoints(const pointField&);

		//-  Update local data for topology changes
		FoamDynamicMesh_EXPORT virtual void updateMesh(const mapPolyMesh&);


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const motionSolverList&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_motionSolverList_Header
