#pragma once
#ifndef _velocityLaplacianFvMotionSolver_Header
#define _velocityLaplacianFvMotionSolver_Header

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
	tnbLib::velocityLaplacianFvMotionSolver

Description
	Mesh motion solver for an fvMesh.  Based on solving the cell-centre
	Laplacian for the motion velocity.

SourceFiles
	velocityLaplacianFvMotionSolver.C

\*---------------------------------------------------------------------------*/

#include <velocityMotionSolver.hxx>
#include <fvMotionSolver.hxx>
#include <volFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward class declarations
	class motionDiffusivity;

	/*---------------------------------------------------------------------------*\
				  Class velocityLaplacianFvMotionSolver Declaration
	\*---------------------------------------------------------------------------*/

	class velocityLaplacianFvMotionSolver
		:
		public velocityMotionSolver,
		public fvMotionSolver
	{
		// Private Data

			//- Cell-centre motion field
		mutable volVectorField cellMotionU_;

		//- Diffusivity used to control the motion
		autoPtr<motionDiffusivity> diffusivityPtr_;


	public:

		//- Runtime type information
		//TypeName("velocityLaplacian");
		static const char* typeName_() { return "velocityLaplacian"; }
		static FoamFvMotionSolver_EXPORT const ::tnbLib::word typeName;
		static FoamFvMotionSolver_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from polyMesh and dictionary
		FoamFvMotionSolver_EXPORT velocityLaplacianFvMotionSolver
		(
			const polyMesh&,
			const dictionary&
		);

		//- Disallow default bitwise copy construction
		FoamFvMotionSolver_EXPORT velocityLaplacianFvMotionSolver
		(
			const velocityLaplacianFvMotionSolver&
		);


		//- Destructor
		FoamFvMotionSolver_EXPORT ~velocityLaplacianFvMotionSolver();


		// Member Functions

			//- Return reference to the cell motion velocity field
		volVectorField& cellMotionU()
		{
			return cellMotionU_;
		}

		//- Return const reference to the cell motion velocity field
		const volVectorField& cellMotionU() const
		{
			return cellMotionU_;
		}

		//- Return point location obtained from the current motion field
		FoamFvMotionSolver_EXPORT virtual tmp<pointField> curPoints() const;

		//- Solve for motion
		FoamFvMotionSolver_EXPORT virtual void solve();

		//- Update topology
		FoamFvMotionSolver_EXPORT virtual void updateMesh(const mapPolyMesh&);


		// Member Operators

			//- Disallow default bitwise assignment
		FoamFvMotionSolver_EXPORT void operator=(const velocityLaplacianFvMotionSolver&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_velocityLaplacianFvMotionSolver_Header
