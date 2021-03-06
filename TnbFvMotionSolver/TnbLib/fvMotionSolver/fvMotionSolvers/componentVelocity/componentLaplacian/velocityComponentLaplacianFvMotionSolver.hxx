#pragma once
#ifndef _velocityComponentLaplacianFvMotionSolver_Header
#define _velocityComponentLaplacianFvMotionSolver_Header

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
	tnbLib::velocityComponentLaplacianFvMotionSolver

Description
	Mesh motion solver for an fvMesh.  Based on solving the cell-centre
	Laplacian for the given component of the motion velocity.

SourceFiles
	velocityComponentLaplacianFvMotionSolver.C

\*---------------------------------------------------------------------------*/

#include <componentVelocityMotionSolver.hxx>
#include <fvMotionSolver.hxx>

#include <volFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward class declarations
	class motionDiffusivity;

	/*---------------------------------------------------------------------------*\
			  Class velocityComponentLaplacianFvMotionSolver Declaration
	\*---------------------------------------------------------------------------*/

	class velocityComponentLaplacianFvMotionSolver
		:
		public componentVelocityMotionSolver,
		public fvMotionSolver
	{
		// Private Data

			//- Cell-centre motion field
		mutable volScalarField cellMotionU_;

		//- Diffusivity used to control the motion
		autoPtr<motionDiffusivity> diffusivityPtr_;


	public:

		//- Runtime type information
		//TypeName("velocityComponentLaplacian");
		static const char* typeName_() { return "velocityComponentLaplacian"; }
		static FoamFvMotionSolver_EXPORT const ::tnbLib::word typeName;
		static FoamFvMotionSolver_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from polyMesh and dictionary
		FoamFvMotionSolver_EXPORT velocityComponentLaplacianFvMotionSolver
		(
			const polyMesh&,
			const dictionary&
		);

		//- Disallow default bitwise copy construction
		FoamFvMotionSolver_EXPORT velocityComponentLaplacianFvMotionSolver
		(
			const velocityComponentLaplacianFvMotionSolver&
		) = delete;


		//- Destructor
		FoamFvMotionSolver_EXPORT ~velocityComponentLaplacianFvMotionSolver();


		// Member Functions

			//- Non-const access to the cellMotionU in order to allow changes
			//  to the boundary motion
		volScalarField& cellMotionU()
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
		FoamFvMotionSolver_EXPORT void operator=
			(
				const velocityComponentLaplacianFvMotionSolver&
				) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_velocityComponentLaplacianFvMotionSolver_Header
