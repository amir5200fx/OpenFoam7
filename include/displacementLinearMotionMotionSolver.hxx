#pragma once
#ifndef _displacementLinearMotionMotionSolver_Header
#define _displacementLinearMotionMotionSolver_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2018-2019 OpenFOAM Foundation
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
	tnbLib::displacementLinearMotionMotionSolver

Description
	Mesh motion solver simple linear expansion and contraction of a mesh
	region defined by a motion axis and the extents of the motion.

	Example:
	\verbatim
		dynamicFvMesh   dynamicMotionSolverFvMesh;

		motionSolver    displacementLinearMotion;

		axis            (0 1 0);
		xFixed          0.8;
		xMoving         0;
		displacement    table
		(
			(0 0)
			(4 0.7)
		);
	\endverbatim

	This mesh is compressed between \c xFixed and \c xMoving in the direction
	\c axis between time 0 and 4 with a maximum displacement of 0.7.
	The mesh beyond \c xFixed is fixed and beyond \c xMoving moves with maximum
	displacement.

SourceFiles
	displacementLinearMotionMotionSolver.C

\*---------------------------------------------------------------------------*/

#include <points0MotionSolver.hxx>
#include <Function1.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
				 Class displacementLinearMotionMotionSolver Declaration
	\*---------------------------------------------------------------------------*/

	class displacementLinearMotionMotionSolver
		:
		public points0MotionSolver
	{
		// Private Data

			//- Axis of the linear motion
		vector axis_;

		//- The location of the end of motion
		scalar xFixed_;

		//- The location moving with the specified displacement
		scalar xMoving_;

		//- The displacement as a function of time
		autoPtr<Function1<scalar>> displacement_;


	public:

		//- Runtime type information
		//TypeName("displacementLinearMotion");
		static const char* typeName_() { return "displacementLinearMotion"; }
		static FoamDynamicMesh_EXPORT const ::tnbLib::word typeName;
		static FoamDynamicMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from polyMesh and dictionary
		FoamDynamicMesh_EXPORT displacementLinearMotionMotionSolver
		(
			const polyMesh&,
			const dictionary&
		);

		//- Disallow default bitwise copy construction
		FoamDynamicMesh_EXPORT displacementLinearMotionMotionSolver
		(
			const displacementLinearMotionMotionSolver&
		);


		//- Destructor
		FoamDynamicMesh_EXPORT ~displacementLinearMotionMotionSolver();


		// Member Functions

			//- Return point location obtained from the current motion field
		FoamDynamicMesh_EXPORT virtual tmp<pointField> curPoints() const;

		//- Solve for motion
		virtual void solve()
		{}


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const displacementLinearMotionMotionSolver&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_displacementLinearMotionMotionSolver_Header
